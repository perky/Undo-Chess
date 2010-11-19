-- MENU SCREEN
state_start = Gamestate.new()
state_menu  = Gamestate.new()
local start = state_start
local menu  = state_menu
local logo  = love.graphics.newImage( 'logo.png' )
menu.receive = {}

function start.enter()
	start.player_name = ""
end

function start.draw()
	love.graphics.setColor( BLACK() )
	local w = love.graphics.getWidth()
	love.graphics.rectangle( 'fill', 0, 100, w, 100 )
	
	love.graphics.setColor( WHITE() )
	love.graphics.printf( 'ENTER YOUR NAME THEN PRESS ENTER', 0, 110, w, 'center' )
	love.graphics.printf( start.player_name, 0, 140, w, 'center' )
end

function start.keypressed( arg, key, unicode )
	if key == 'return' then
		if start.player_name == "" then start.player_name = "noob" end
		MYNAME = start.player_name
		Gamestate.switch( state_menu )
	elseif key == 'backspace' then
		start.player_name = start.player_name:sub(1,-2)
	elseif unicode ~= 0 and unicode <= 122 and unicode >= 97 then
		start.player_name = start.player_name..string.char(unicode)
	end
end

--------------------

local oldsans42 = love.graphics.newFont(GOO_SKINPATH .. 'oldsansblack.ttf', 42)
local oldsans22 = love.graphics.newFont(GOO_SKINPATH .. 'oldsansblack.ttf', 22)
menu.button_style = {
	backgroundColor = {0,0,0,0},
	backgroundColorHover = {131,203,21,0},
	borderColor = {0,0,0,0},
	borderColorHover = {0,0,0,0},
	textColor = {10,10,10},
	textColorHover = {150,150,150},
	textFont = oldsans42
}
menu.button_style2 = {
	backgroundColor = {0,0,0,0},
	backgroundColorHover = {131,203,21,0},
	borderColor = {0,0,0,50},
	borderColorHover = {0,0,0,50},
	textColor = {10,10,10},
	textColorHover = {150,150,150},
	textFont = oldsans22
}

function menu.enter()
	menu.connect_to_masterserver()
	menu.create_gui()
end

local next_heartbeat = love.timer.getTime() + 5
function menu.update( dt )
	udp:update()
end

function menu.receive.list( self, data, ip, port )
	local list = {}
	if menu.peer_list then menu.peer_list:destroy() end

	menu.peer_list = goo.null:new()
	menu.peer_list:setPos( 300, 110 )
	menu.peer_list.count = 0
	for i = 4, #data-1, 3 do
		local btn = goo.button:new( menu.peer_list )
		btn:setText( data[i+2]..' - '..data[i] )
		btn:setStyle( menu.button_style2 )
		btn:sizeToText()
		btn:setPos( 0, (menu.peer_list.count*30) )
		btn.onClick = function()
			local datagram = string.format( "%s,%s,%s", 'play', data[i], data[i+1] )
			udp:send( datagram )
			menu.play_multiplayer( data[i], tonumber(data[i+1]), data[i+2], 1 )
		end
		menu.peer_list.count = menu.peer_list.count + 1
	end
end

function menu.receive.play( self, data, ip, port )
	menu.play_multiplayer( data[4], tonumber(data[5]), data[6], 2 )
end

function menu.connect_to_masterserver()
	udp.peer_can_timeout = false
	udp.reliable_mode = false
	
	udp.receive.play = menu.receive.play
	udp.receive.list = menu.receive.list
	
	udp:connect( MASTERSERVER_IP, MASTERSERVER_PORT )
	udp:send( 'connect,' .. MYNAME )
	udp:send_heartbeat()
end

function menu.keypressed( arg, key, unicode )
end

function menu.create_gui()
	menu.frame = goo.null:new()
	menu.frame:setPos( 20, 50 )
	local btn = goo.button:new( menu.frame )
		btn:setText( 'Play Alone' )
		btn:setStyle( menu.button_style )
		btn:sizeToText()
		btn:setPos( 0, 50 )
		btn.onClick = menu.play_alone
	local btn = goo.button:new( menu.frame )
		btn:setText( 'Play Tutorial' )
		btn:setStyle( menu.button_style )
		btn:sizeToText()
		btn:setPos( 0, 100 )
		btn.onClick = menu.play_tutorial
	local btn = goo.button:new( menu.frame )
		btn:setText( 'Quit Game' )
		btn:setStyle( menu.button_style )
		btn:sizeToText()
		btn:setPos( 0, 150 )
		btn.onClick = menu.quit_game
	
	menu.alpha = 50
	anim:easy( menu, 'alpha', 255, 0, 2 )
end

function menu.draw()
	local w, h = love.graphics.getWidth(), love.graphics.getHeight()
	
	love.graphics.setColor( WHITE() )
	love.graphics.draw( logo, 10, 10 )
	
	love.graphics.setColor( 255,255,255, menu.alpha )
	love.graphics.rectangle( 'fill', 0, 0, w, h )
end

function menu.play_alone()
	menu.frame:destroy()
	if menu.peer_list then menu.peer_list:destroy() end
	udp.receive.list = nil
	udp.receive.play = nil
	
	MYTEAM = 1
	MULTIPLAYER = false
	
	udp:send( 'disconnect' )
	Gamestate.switch( state_chess, '127.0.0.1', 5555, '' )
end

function menu.play_multiplayer( ip, port, name, team )
	menu.frame:destroy()
	if menu.peer_list then menu.peer_list:destroy() end
	udp.receive.list = nil
	udp.receive.play = nil
	
	MYTEAM = team
	MULTIPLAYER = true
	
	udp:send( 'disconnect' )
	Gamestate.switch( state_chess, ip, port, name )
end

function menu.play_tutorial()
	menu.frame:destroy()
	if menu.peer_list then menu.peer_list:destroy() end
	udp.receive.list = nil
	udp.receive.play = nil
	
	MYTEAM = 1
	MULTIPLAYER = false
	
	udp:send( 'disconnect' )
	Gamestate.switch( state_tutorial )
end

function menu.quit_game( btn )
	udp:send( 'disconnect' )
	love.event.push('q')
end

