require 'socket'

udp = {}
udp.receive = {}

function udp:new( ip, port )
	if self.sock then self.sock:close() end
	self.sock = socket.udp()
	self.sock:settimeout(0)
	self.sock:setsockname( ip or '*', port or 0 )
	local _, port = self.sock:getsockname()
	
	self.packet_count = 1
	self.remote_packet_count = 1
	self.sent_packets = {}
	self.received_packets = {}
	self.next_heartbeat = os.time() + UDP_HEARTBEAT_INTERVAL
	self.heartbeat_count = 4
	self.last_packet_time = os.time()
	self.peer_connected = false
	self.peer_can_timeout = true
	self.reliable_mode = true
	
	return port
end

function udp:connect( ip, port )
	self.sock:setpeername( ip, port )
	self.connected = true
	self.peer_ip = ip
	self.peer_port = port
end

function udp:disconnect()
	self.sock:setpeername('*')
	self.connected = false
end

function udp:send( datagram, ip, port )
	local prefix = string.format( "%s,%i,", NET_GAME_ID, self.packet_count )
	datagram = prefix .. datagram
	
	if self.connected then
		self.sock:send( datagram )
	elseif ip and port then
		self.sock:sendto( datagram, ip, port )
	else
		return false
	end
	
	if self.reliable_mode then
		self.sent_packets[ self.packet_count ] = {
			got_ack = false,
			time_sent = os.time(),
			datagram = datagram
		}
		self.packet_count = self.packet_count + 1
	end
end

function udp:update( dt )
	local data, ip, port, timeout
	if self.connected then
		data = self.sock:receive()
		ip, port = self.peer_ip, self.peer_port
	else
		data, ip, port, timeout = self.sock:receivefrom()
	end
	
	if data then
		data = data:split(',')
		if data[1] == NET_GAME_ID then
			if data[3] == 'ack' then
				if self.reliable_mode then self:receive_ack( data ) end
			elseif data[3] == 'hbt' then
				self:receive_heartbeat( data )
			else
				if self.reliable_mode then
					local packet_id = tonumber(data[2])
					self:send_ack( data )
					if not self.received_packets[ packet_id ] then
						self.received_packets[ packet_id ] = true
						self:receive_message( data, data[3], ip, port )
					end
				else
					self:receive_message( data, data[3], ip, port )
				end
			end
			
			self.peer_connected = true
			self.last_packet_time = os.time()
		end
	end
	
	if os.time() > self.next_heartbeat then
		self.next_heartbeat = os.time() + UDP_HEARTBEAT_INTERVAL
		udp:send_heartbeat()
	end
	
	if self.reliable_mode then
		if self.peer_can_timeout and os.time() > self.last_packet_time + UDP_PEER_TIMEOUT then
			self:peer_timeout()
		end
	
		for k, packet in ipairs( self.sent_packets ) do
			if not packet.got_ack and os.time() > packet.time_sent + UDP_ACK_TIMEOUT then
				self.sock:send( packet.datagram )
				packet.time_sent = os.time()
			end
		end
	end
end

function udp:send_heartbeat()
	local datagram = string.format( "%s,%i,%s", NET_GAME_ID, 0, 'hbt' )
	self.sock:send( datagram )
end

function udp:receive_heartbeat( data )
end

function udp:send_ack( data )
	local datagram = string.format( "%s,%s,%s", NET_GAME_ID, data[2], 'ack' )
	self.sock:send( datagram )
end

function udp:receive_ack( data )
	local packet = self.sent_packets[ tonumber(data[2]) ]
	if packet then
		packet.got_ack = true
	end
end

function udp:receive_message( data, msg_id, ip, port )
	if self.receive[ msg_id ] then
		self.receive[ msg_id ]( self, data, ip, port )
	end
end

function udp:peer_timeout()
	self.peer_connected = false
end