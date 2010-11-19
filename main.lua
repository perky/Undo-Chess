-- UNDO: CHESS
-- CHESS WITH ADDED TIME TRAVEL.
require 'constants'
require 'udp'
require 'gamestate'
require 'goo/goo'
require 'anim.anim'
require 'menu'
require 'chess'
require 'MessageInABottle'
require 'tutorial'

function string:split(delimiter)
  local result = { }
  local from  = 1
  local delim_from, delim_to = string.find( self, delimiter, from  )
  while delim_from do
    table.insert( result, string.sub( self, from , delim_from-1 ) )
    from  = delim_to + 1
    delim_from, delim_to = string.find( self, delimiter, from  )
  end
  table.insert( result, string.sub( self, from  ) )
  return result
end

function love.load()
	MYPORT = udp:new( '*', 0 )
	Gamestate.switch( state_start )
	goo:load()
	love.graphics.setBackgroundColor( WHITE() )
end

function love.update( dt )
	Gamestate.update( dt )
	anim:update( dt )
	goo:update( dt )
end

function love.draw()
	goo:draw()
	Gamestate.draw()
end

function love.mousepressed( x, y, button )
	Gamestate.mousepressed( x, y, button )
	goo:mousepressed( x, y, button )
end

function love.mousereleased( x, y, button )
	Gamestate.mousereleased( x, y, button )
	goo:mousereleased( x, y, button )
end

function love.keypressed( key, unicode )
	Gamestate.keypressed( key, unicode )
	goo:keypressed( key, unicode )
end

function love.keyreleased( key, unicode )
	Gamestate.keyreleased( key, unicode )
end