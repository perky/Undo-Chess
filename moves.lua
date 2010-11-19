moves = {}
moves.pos  = 12
moves.max  = 12
moves.last = 1
moves.turn = 1

function moves:init()
	for i = 1, moves.max-1 do
		moves[i] = {
			type = 'empty'
		}
	end
end

function moves:insert( move_table, move_pos )
	local move_pos = move_pos or self.pos
	self[ move_pos ] = move_table
end

function moves:add( move_table, move_pos )
	local move_pos = move_pos or self.pos
	self[ move_pos ] = move_table
end

function moves:forward()
	-- shift moves down to allow for more
	self.last = math.min( #self, self.max )
	if self.last >= self.max then
		-- add the move to the copy grid.
		grid:timecopy_add( self[1] )
		table.remove( self, 1 )
		self.last = self.max-1
		--self[self.max] = {type = 'empty'}
	else
		self.pos = math.min(self.pos + 1, self.max)
	end
end

function moves:goto( pos )
	moves.pos = pos
	grid:refresh()
end

function moves:remove()
end

function moves:change()
end

function moves:undo_move()
	if self.pos == 1 then return end
	self.pos = self.pos - 1
	if self.undo_move_hook then self:undo_move_hook( self.pos ) end
end

function moves:redo_move()
	if self.pos == self.max then return end
	if self.redo_move_hook then self:redo_move_hook( self[self.pos] ) end
	self.pos = self.pos + 1
end

function moves:update()
	local mx,my = love.mouse.getPosition()
	self.selected_move = nil
	self.selected_move_id = nil
	for i = 1, self.max do
		local move = self[i]
		local ypos = 30+(i-1)*36
		
		if mx > 450 and mx < 650 and my > ypos and my < ypos+32 then
			self.selected_move = self[i]
			self.selected_move_id = i
			break
		end
		
	end
end

function moves:draw()
	local w, h = love.graphics.getWidth(), love.graphics.getHeight()
	love.graphics.setColor( 50, 50, 50 )
	love.graphics.rectangle( 'fill', w-300, 0, 300, h )
	
	for i = 1, self.max do
		local move = self[i]
		local ypos = 30+(i-1)*36
		
		love.graphics.setColor( WHITE() )
		if move and move.unit then
			love.graphics.drawq( state_chess.pieces, move.unit.piece[move.team], 450, ypos )
			if move.victim then
				love.graphics.drawq( state_chess.pieces, move.victim.piece[move.victim.team], 481, ypos )
			end
		end
		
		if move then
			if move.team == 1 then
				love.graphics.setColor( 230, 230, 230 )
			elseif move.team == 2 then
				love.graphics.setColor( 30, 90, 130 )
			end
			if move.invalid then
				love.graphics.setColor( 250, 80, 80 )
			end
		else
			love.graphics.setColor( 0, 0, 0, 255 )
		end
		if i == self.selected_move_id then
			love.graphics.setColor( 50, 250, 80 )
		end
		
		love.graphics.rectangle( 'line', 450, ypos, 200, 32 )
		
		if move then
			local text = move.message
			if move.invalid then
				text = "INVALID"
			end
			local xpos = 520
			if move.type == 'timelock' then xpos = 450 end
			love.graphics.print( text or '', xpos, ypos-2 )
		end
		
		if i == self.pos then
			love.graphics.print( '<', 655, ypos )
		end
	end
	
	--local str = "Pos: "..moves.pos.." Last: "..moves.last.." Max: "..moves.max
	--love.graphics.print( str, 10, 10 )
end
