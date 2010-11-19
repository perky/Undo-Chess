
local stack = {}

function love.graphics.pushState()
 --get state
 local state = {}
 state.blendMode   = love.graphics.getBlendMode()
 state.color       = {love.graphics.getColor()}
 state.colorMode   = love.graphics.getColorMode()
 state.font        = love.graphics.getFont() or 12
 state.lineStyle   = love.graphics.getLineStyle()
 state.lineWidth   = love.graphics.getLineWidth()
 state.lineStipple = love.graphics.getLineStipple() and
                     {love.graphics.getLineStipple()} or {0xFFFF,1}
 state.scissor     = love.graphics.getScissor() or 
                     {love.graphics.getScissor()} or
                     {0,0,love.graphics.getWidth(), love.graphics.getHeight()}

 -- push state
 stack[#stack+1] = state
end

function love.graphics.popState()
 -- restore state
 local state = stack[#stack]
 love.graphics.setBlendMode( state.blendMode )
 love.graphics.setColor( unpack(state.color) )
 love.graphics.setColorMode( state.colorMode )
 love.graphics.setFont( state.font )
 love.graphics.setLine( state.lineWidth, state.lineStyle )
 love.graphics.setLineStipple( unpack(state.lineStipple) )
 love.graphics.setScissor( unpack(state.scissor) )

 -- pop state
 stack[#stack] = nil
end

