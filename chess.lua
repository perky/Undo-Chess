require 'grid'
require 'moves'

state_chess = Gamestate.new()
local chess = state_chess

function chess.enter( last_state, arg, ip, port, name )
	if DEV_MODE then ip = '127.0.0.1' end
	chess.setup_udp( ip, port )
	
	if MULTIPLAYER then
		THEIRNAME = name
	else
		THEIRNAME = 'yourself'
	end
	
	local font = love.graphics.newFont(GOO_SKINPATH .. 'oldsansblack.ttf', 22)
	love.graphics.setFont( font )
	
	chess.messages = {}
	table.insert(chess.messages, ip)
	table.insert(chess.messages, port)
	table.insert(chess.messages, name)
	
	chess.pieces = love.graphics.newImage( 'chess_pieces.png' )
	chess.piecesBatch = love.graphics.newSpriteBatch( chess.pieces, 16 )
	
	chess.pawn = {
		love.graphics.newQuad(0, 0, 32, 32, 202, 81 ),
		love.graphics.newQuad(0, 34, 32, 32, 202, 81 ),
		movetype = 'pawn'
	}
	
	chess.rook = {
		love.graphics.newQuad(34*1, 34*0, 32, 32, 202, 81 ),
		love.graphics.newQuad(34*1, 34*1, 32, 32, 202, 81 ),
		movetype = 'rook'
	}
	
	chess.queen = {
		love.graphics.newQuad(34*2, 34*0, 32, 32, 202, 81 ),
		love.graphics.newQuad(34*2, 34*1, 32, 32, 202, 81 ),
		movetype = 'queen'
	}
	
	chess.king = {
		love.graphics.newQuad(34*3, 34*0, 32, 32, 202, 81 ),
		love.graphics.newQuad(34*3, 34*1, 32, 32, 202, 81 ),
		movetype = 'king'
	}
	
	chess.knight = {
		love.graphics.newQuad(34*4, 34*0, 32, 32, 202, 81 ),
		love.graphics.newQuad(34*4, 34*1, 32, 32, 202, 81 ),
		movetype = 'knight'
	}
	
	chess.bishop = {
		love.graphics.newQuad(34*5, 34*0, 32, 32, 202, 81 ),
		love.graphics.newQuad(34*5, 34*1, 32, 32, 202, 81 ),
		movetype = 'bishop'
	}
	
	chess.unit_count = 1
	chess.current_team = 1
	
	chess.my_team = (MYTEAM == 1) and 'white' or 'black'
	chess.their_team = (MYTEAM == 2) and 'white' or 'black'
	chess.team_names = { 'white', 'black' }
	
	grid:init( 8, 8 )
	moves:init()
end

function grid:init_hook()
	chess.add_unit( 1, 1, chess.rook, 	1 )
	chess.add_unit( 2, 1, chess.knight, 1 )
	chess.add_unit( 3, 1, chess.bishop, 1 )
	chess.add_unit( 4, 1, chess.queen, 	1 )
	chess.add_unit( 5, 1, chess.king, 	1 )
	chess.add_unit( 6, 1, chess.bishop, 1 )
	chess.add_unit( 7, 1, chess.knight, 1 )
	chess.add_unit( 8, 1, chess.rook, 	1 )
	for i = 1, 8 do chess.add_unit( i, 2, chess.pawn, 1 ) end
	
	chess.add_unit( 1, 8, chess.rook, 	2 )
	chess.add_unit( 2, 8, chess.knight, 2 )
	chess.add_unit( 3, 8, chess.bishop, 2 )
	chess.add_unit( 4, 8, chess.queen, 	2 )
	chess.add_unit( 5, 8, chess.king, 	2 )
	chess.add_unit( 6, 8, chess.bishop, 2 )
	chess.add_unit( 7, 8, chess.knight, 2 )
	chess.add_unit( 8, 8, chess.rook, 	2 )
	for i = 1, 8 do chess.add_unit( i, 7, chess.pawn, 2 ) end
end

function chess.add_unit( x, y, piece, team )
	local new_unit = {x,y}
	new_unit.piece = piece
	new_unit.team  = team
	new_unit.key = chess.unit_count
	chess.unit_count = chess.unit_count + 1
	grid[x][y] = new_unit
	return new_unit
end

function chess.mousepressed( arg, x, y, button )
	if button == 'l' and grid.mouse_over_box then
		grid:on_select()
		chess.last_move_pos = moves.pos
	elseif button == 'l' and moves.selected_move_id then
		moves.pos = moves.selected_move_id
		grid:refresh()
	elseif button == 'wu' then
		moves:undo_move()
	elseif button == 'wd' then
		moves:redo_move()
	end
end

function chess.mousereleased( arg, x, y, button )
	if button == 'l' and grid.selected_box and grid.mouse_over_box then
		moves:goto( chess.last_move_pos )
		grid:on_deselect()
	elseif button == 'l' and grid.selected_box and moves.selected_move_id then
		moves:goto( chess.last_move_pos )
		
		local x1, y1 = grid.selected_box[1], grid.selected_box[2]
		grid[x1][y1].selected = false
		grid.selected_box = false
		local unit = grid[x1][y1]
		
		chess.udp_send_jumpmove( unit.key, x1, y1, moves.pos, moves.selected_move_id )
		chess.do_jumpmove( unit, x1, y1, moves.selected_move_id )
		chess.did_move()
	elseif button == 'l' and grid.selected_box then
		local x1, y1 = grid.selected_box[1], grid.selected_box[2]
		grid[x1][y1].selected = false
		grid.selected_box = false
	end
end

function chess.keypressed( arg, key, unicode )
end

function chess.do_jumpmove( unit, x1, y1, move_id, remote )
	local s_move = moves[move_id]
	
	if not chess.can_move( unit, remote ) then return false end
	if s_move.type == 'timelock' or s_move.type == 'jump_in' or s_move.type == 'jump_out' then return false end
	if unit.clone then return false end
	if s_move.team and s_move.team ~= unit.team then return end
	
	local move_out = {}
	move_out.type = 'jump_out'
	move_out.unit = unit
	move_out.message = "jump out "..unit.key
	move_out.original_key = unit.key
	move_out.team = unit.team
	
	local move_in = {}
	move_in.type = 'jump_in'
	move_in.unit = unit
	move_in.message = "jump in "..unit.key
	move_in.team = unit.team
	move_in.original_key = unit.key
	move_in.x = x1
	move_in.y = y1
	move_in.move_out = move_out
	
	moves:add( move_out )
	moves:add( move_in, move_id )
	moves:forward()
	grid:refresh()
end

function chess.do_move( x1, y1, x2, y2 )
	if not chess.can_move( grid[x1][y1] ) then return end
	if x1 == x2 and y1 == y2 then return end
	
	chess.udp_send_normalmove( x1, y1, x2, y2 )
	local did_move, victim = grid:do_move( x1, y1, x2, y2 )
	if did_move then
		chess.add_move( x1, y1, x2, y2, grid[x2][y2], victim )
		chess.did_move()
	end
end

function chess.did_move()
	if chess.current_team == MYTEAM then
		if MYTEAM == 1 then 
			chess.current_team = 2
		else
			chess.current_team = 1
		end
	else
		chess.current_team = MYTEAM
	end
end

function chess.can_move( unit, remote )
	local move = moves[moves.pos]
	if not remote and MULTIPLAYER then
		if MYTEAM ~= chess.current_team then return false end
		if MYTEAM ~= unit.team then return false end
	end
	if not unit then return false end
	if move and move.type == 'empty' then return true end
	if move and unit.team ~= move.team then return false end
	if move and (move.type == 'timelock' or move.type == 'jump_in' or move.type == 'jump_out') then return false end
	return true
end

function chess.add_move( x1, y1, x2, y2, unit, victim, pos )
	local move = {}
	move.unit = unit
	move.start = { x = x1, y = y1 }
	move.destination = { x = x2, y = y2 }
	move.victim = victim
	move.type = 'normal'
	
	local letter = "abcdefghi"
	move.message = unit.piece.movetype.." to "..letter:sub(y2,y2)..x2
	moves:add( move )
	
	local pos = pos or moves.pos
	if pos < moves.last then
		local move 		= {}
		move.message 	= "TIMELINE LOCKED"
		move.team 		= unit.team
		move.type 		= 'timelock'
		moves:add( move, moves.last+1 )
	end
	
	moves:forward()
	grid:refresh()
end

function chess.update( dt )
	udp:update()
	moves:update()
	
	if grid.selected_box and moves.selected_move_id then
		moves:goto( moves.selected_move_id )
	end
end

function chess.draw()
	love.graphics.setColor( WHITE() )
	
	moves:draw()
	grid:draw()
	
	love.graphics.setColor( BLACK() )
	local str1 = string.format( "%s (%s) vs %s (%s)", MYNAME, chess.my_team, THEIRNAME, chess.their_team )
	local str2 = string.format( "%s's turn", chess.team_names[ chess.current_team ] )
	love.graphics.print( str1, 15, 5 )
	love.graphics.print( str2, 15, 35 )
end

function moves:undo_move_hook( pos )
	grid:refresh()
end

function moves:redo_move_hook( move, g )
	local g = g or grid
	if not move then return end
	
	if move.type == 'normal' then	
		local x1, y1 = move.start.x, move.start.y
		local x2, y2 = move.destination.x, move.destination.y
		if g[x1][y1] then
			move.team = g[x1][y1].team
		end
		local did_move, victim = g:do_move( x1, y1, x2, y2 )
		move.victim = victim
		move.invalid = not did_move
	elseif move.type == 'jump_in' then
		local x1, y1 = move.x, move.y
		local unit1 = move.unit
		local unit2 = {}
		for k,v in pairs(unit1) do
			unit2[k] = v
		end
		
		unit2.clone = true
		
		move.move_out.clone_key = unit2.key
		g[x1][y1] = unit2
	elseif move.type == 'jump_out' then
		for x = 1, grid.w do
		for y = 1, grid.h do
			if g[x][y] and g[x][y].key == move.original_key then
				if g[x][y].clone then
					g[x][y].clone = false
				else
					g[x][y] = nil
				end
			end
		end
		end
	end
end

function chess.find_unit_bykey( key )
	for x = 1, grid.w do
	for y = 1, grid.h do
		if grid[x][y] and grid[x][y].key == key then
			return grid[x][y], x, y
		end
	end
	end
end

function chess.setup_udp( ip, port )
	if MULTIPLAYER then
		udp:connect( ip, port )
		udp.peer_can_timeout = true
		udp.reliable_mode = true
	
		chess.ip = ip
		chess.port = port
	end
end

function chess.udp_send_normalmove( x1, y1, x2, y2 )
	local unit = grid[x1][y1]
	local team = unit.team
	local datagram = string.format( "%s,%i,%i,%i,%i,%i,%i", 'move', x1, y1, x2, y2, moves.pos, team )
	udp:send( datagram )
end

function chess.udp_send_jumpmove( unit_key, x, y, move_id1, move_id2 )
	local datagram = string.format( "%s,%i,%i,%i,%i,%i", 'jump', unit_key, x, y, move_id1, move_id2 )
	udp:send( datagram )
end

function udp.receive.jump( self, data, ip, port )
	local unit_key = tonumber(data[4])
	local x, y = tonumber(data[5]), tonumber(data[6])
	local move_id1 = tonumber(data[7])
	local move_id2 = tonumber(data[8])
	
	local last_pos = moves.pos
	moves:goto( move_id1 )
	
	local unit = grid[x][y]
	chess.did_move()
	chess.do_jumpmove( unit, x, y, move_id2, true )
	
	moves:goto( last_pos )
end

function udp.receive.move( self, data, ip, port )
	local x1, y1 = tonumber(data[4]), tonumber(data[5])
	local x2, y2 = tonumber(data[6]), tonumber(data[7])
	local move_pos = tonumber(data[8])
	local team = tonumber(data[9])
	
	if moves.pos == move_pos then
		local did_move, victim = grid:do_move( x1, y1, x2, y2 )
		if did_move then
			chess.add_move( x1, y1, x2, y2, grid[x2][y2], victim )
		end
	else
		local last_pos = moves.pos
		moves.pos = move_pos
		grid:refresh()
		chess.add_move( x1, y1, x2, y2, grid[x1][y1] )
		moves.pos = last_pos
		grid:refresh()
	end
	
	chess.did_move()
end