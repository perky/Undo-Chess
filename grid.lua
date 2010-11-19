grid = {}

--- --------------------------------------------------------------------------
-- Sets up a 2d grid.
-- 
-- @param w:number width of grid 
-- @param h:number height of grid
-- ---------------------------------------------------------------------------
function grid:init( w, h )
	-- load empty grid
	for x = 1, w do
		self[x] = {}
		for y = 1, h do
			self[x][y] = nil
		end
	end
	
	self.w = w
	self.h = h
	
	if grid.init_hook then grid:init_hook() end
	-- copy to the timegrid.
	self.timecopy = {}
	setmetatable( self.timecopy, {__index = grid} )
	self:copy( self, self.timecopy )
end

--- --------------------------------------------------------------------------
-- Copies grid a to grid b.
--
-- @param a:grid
-- @param b:grid
-- ---------------------------------------------------------------------------
function grid:copy( a, b )
	for x = 1, grid.w do
		b[x] = {}
		for y = 1, grid.h do
			b[x][y] = a[x][y]
		end
	end
end

--- --------------------------------------------------------------------------
-- Moves a unit to a different position on the grid
--
-- @param x1,y1:number position of unit to move
-- @param x2,y2:number position of where to move to
-- ---------------------------------------------------------------------------
function grid:do_move( x1, y1, x2, y2 )
	local a, b = self[x1][y1], self[x2][y2]
	
	-- check if box is valid
	if a == nil then return false end
	
	-- return false if trying to attack own team
	local team = a.team
	if b and team == b.team then return false end
	
	-- return false if no move
	if x1 == x2 and y1 == y2 then return end

	-- return false if it is not a valid move
	local victim
	local allowed = self:calculate_moves( x1, y1, a.piece.movetype, a )
	for k, move in pairs( allowed ) do
		if x2 == move[1] and y2 == move[2] then
			victim = self[x2][y2]
			self[x2][y2] = a
			self[x1][y1] = nil
			return true, victim
		end
	end
	
	return false
end

function grid:timecopy_add( move )
	if moves.redo_move_hook then moves:redo_move_hook( move, self.timecopy ) end
end

function grid:draw()
	love.graphics.setLineStyle( 'rough' )
	local boxsize = 32
	local spacing = -1
	local xpos = 50
	local ypos = 100
	self.mouse_over_box = false
	
	-- draw grid co-ordinates
	love.graphics.setColor( 10, 10, 10 )
	for x = 1, self.w do
		local pixel_x = xpos+(x-1)*(boxsize+spacing)
		love.graphics.print( x, pixel_x+9, ypos-34 )
	end
	local letters = "abcdefghi"
	for y = 1, self.h do
		local pixel_y = ypos+(y-1)*(boxsize+spacing)
		love.graphics.print( letters:sub(y,y), xpos-20, pixel_y-5  )
	end
	
	-- draw grid
	local odd = 1
	for x = 1, self.w do
		odd = odd + 1
	for y = 1, self.h do
		love.graphics.setColor( 0, 0, 0, 255 )
		local pixel_x = xpos+(x-1)*(boxsize+spacing)
		local pixel_y = ypos+(y-1)*(boxsize+spacing)
		local unit = self[x][y]
		
		if odd % 2 == 0 then
			-- draw light coloured square
			love.graphics.setColor( 210, 210, 210 )
			love.graphics.rectangle( 'fill', pixel_x, pixel_y, boxsize-1, boxsize )
		else
			-- draw even coloured square
			love.graphics.setColor( 110, 110, 110 )
			love.graphics.rectangle( 'fill', pixel_x, pixel_y, boxsize-1, boxsize )
		end
		odd = odd + 1
		
		-- check if mouse is in box area
		if self.check_mouse( pixel_x, pixel_y, boxsize ) then
			self.mouse_in( x, y )
			love.graphics.setColor( 0, 0, 150, 30 )
			love.graphics.rectangle( 'fill', pixel_x, pixel_y, boxsize-1, boxsize )
		end
		
		if unit and unit.clone then
			love.graphics.setColor( 160, 20, 20 )
			love.graphics.rectangle( 'fill', pixel_x, pixel_y, boxsize, boxsize )
		end
		
		-- draw highlighted selection
		if self.selected_box and x == self.selected_box[1] and y == self.selected_box[2] then
			love.graphics.setColor( 30, 30, 230 )
			love.graphics.rectangle( 'fill', pixel_x, pixel_y, boxsize, boxsize )
		end
		
		-- draw the box outline
		love.graphics.setColor( 0, 0, 0, 255 )
		love.graphics.rectangle( 'line', pixel_x, pixel_y, boxsize, boxsize )
		-- draw the box contents
		--self:draw_contents( x, y, pixel_x, pixel_y )
		
		-- draw unit
		if unit and not unit.selected then
			love.graphics.setColor( WHITE() )
			love.graphics.drawq( state_chess.pieces, unit.piece[unit.team], pixel_x-1, pixel_y )
			--love.graphics.print( unit.key, pixel_x, pixel_y )
		end
	end
	end
	
	-- draw possible moves
	if self.selected_box and self.allowed then
		for k, box in pairs( self.allowed )do
			local pixel_x = xpos+(box[1]-1)*(boxsize+spacing)
			local pixel_y = ypos+(box[2]-1)*(boxsize+spacing)

			love.graphics.setColor( 230, 190, 0 )
			love.graphics.circle( 'fill', pixel_x+16, pixel_y+16, 5 )
		end
	end
	
	-- draw units
	if self.selected_box then
		local mx, my = love.mouse.getPosition()
		local unit = self.selected_unit
		if unit then
		love.graphics.drawq( state_chess.pieces, unit.piece[unit.team], mx-16, my-16 )
		end
	end
end

grid.movetype_bishop = { {-1,-1}, {-1, 1}, {1,-1}, { 1, 1} }
grid.movetype_rook   = { {-1, 0}, { 0,-1}, {1, 0}, { 0, 1} }
grid.movetype_queen  = { {-1, 0}, { 0,-1}, {1, 0}, { 0, 1}, {-1,-1}, {-1, 1}, {1,-1}, { 1, 1} }
function grid:calculate_moves( x, y, type, unit )
	local allowed
	if type == 'pawn' then
		return self:calculate_moves_pawn( x, y, unit )
	elseif type == 'rook' then
		return self:calculate_moves_main( x, y, grid.movetype_rook )
	elseif type == 'bishop' then
		return self:calculate_moves_main( x, y, grid.movetype_bishop )
	elseif type == 'queen' then
		return self:calculate_moves_main( x, y, grid.movetype_queen )
	elseif type == 'knight' then
		return self:calculate_moves_knight( x, y )
	elseif type == 'king' then
		return self:calculate_moves_king( x, y )
	end
end

function grid:calculate_moves_main( x, y, type )
	local allowed = {}
	
	for k, r in pairs( type ) do
		local tx = x + r[1]
		local ty = y + r[2]
		while tx > 0 and ty > 0 and tx <= self.w and ty <= self.h do
			if not self[tx][ty] then
				table.insert( allowed, {tx,ty} )
				tx = tx + r[1]
				ty = ty + r[2]
			else
				if self[x][y].team ~= self[tx][ty].team then
					table.insert( allowed, {tx,ty} )
				end
				break
			end
		end
	end
	
	return allowed
end

function grid:calculate_moves_knight( x, y )
	local allowed = {}
	local moves = { {-2,-1}, {-1,-2}, {1,-2}, {2,-1}, {2,1}, {1,2}, {-1,2}, {-2,1} }
	for k, move in ipairs( moves ) do
		local tx = x + move[1]
		local ty = y + move[2]
		if tx > 0 and ty > 0 and tx <= self.w and ty <= self.h then
		if not self[tx][ty] then
			table.insert( allowed, {tx,ty} )
		elseif self[x][y] and self[x][y].team ~= self[tx][ty].team then
				table.insert( allowed, {tx,ty} )
		end
		end
	end
	return allowed
end

function grid:calculate_moves_pawn( x, y, unit )
	local allowed = {}
	local moves = { { 0,-1}, { 0, 1}, {-1,-1}, {-1, 1}, {1,-1}, { 1, 1} }
	if y == 2 or y == 7 then
		table.insert( moves, {0,-2} )
		table.insert( moves, {0, 2} )
	end
	
	for k, move in ipairs( moves ) do
		local tx = x + move[1]
		local ty = y + move[2]
		if tx > 0 and ty > 0 and tx <= self.w and ty <= self.h then
			if not self[tx][ty] then
				if (move[1] == 0 and move[2] == -1) or (move[1] == 0 and move[2] == 1)
				or (move[1] == 0 and move[2] == 2)  or (move[1] == 0 and move[2] == -2) then
					table.insert( allowed, {tx,ty} )
				end
			elseif self[tx][ty] and self[x][y].team ~= self[tx][ty].team then
				if (move[1] == -1 and move[2] == 1) or (move[1] == -1 and move[2] == -1) or
				(move[1] == 1 and move[2] == -1) or (move[1] == 1 and move[2] == 1) then
					table.insert( allowed, {tx,ty} )
				end
			end
		end
	end
	return allowed
end

function grid:calculate_moves_king( x, y )
	local allowed = {}
	local moves = grid.movetype_queen
	for k, move in ipairs( moves ) do
		local tx = x + move[1]
		local ty = y + move[2]
		if tx > 0 and ty > 0 and tx <= self.w and ty <= self.h and
		not self[tx][ty] then
			table.insert( allowed, {tx,ty} )
		else
			if self[tx][ty] and self[x][y].team ~= self[tx][ty].team then
				table.insert( allowed, {tx,ty} )
			end
		end
	end
	return allowed
end

function grid:highlight_moves( size, spacing )
	
end


function grid.check_mouse( x, y, boxsize )
	local x2 = x+boxsize
	local y2 = y+boxsize
	local mx, my = love.mouse.getPosition(  )
	if mx > x and mx < x2 and my > y and my < y2 then
		return true
	end
end

function grid.mouse_in( box_x, box_y )
	grid.mouse_over_box = { box_x, box_y }
end

function grid:on_select()
	local bx, by = self.mouse_over_box[1], self.mouse_over_box[2]
	if self[bx][by] then
		self.selected_box = self.mouse_over_box
		self.selected_unit = self[bx][by]
		self[bx][by].selected = true
		local type = self[bx][by].piece.movetype
		local allowed = self:calculate_moves( bx, by, type, self[bx][by] )
		self.allowed = allowed
	end
end

function grid:on_deselect()
	local x1, y1 = self.selected_box[1], self.selected_box[2]
	local x2, y2 = self.mouse_over_box[1], self.mouse_over_box[2]
	self[x1][y1].selected = false
	self.selected_box = false
	state_chess.do_move( x1, y1, x2, y2 )
end

function grid:refresh( pos )
	local last_pos = moves.pos
	moves.pos = 1
	self:copy( self.timecopy, self )
	
	while moves.pos < last_pos do
		moves:redo_move()
	end
end