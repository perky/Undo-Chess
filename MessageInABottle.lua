--[[
    MessageInABottle.lua - 2010-11-08
    http://bitbucket.org/dannyfritz/message-in-a-bottle/
    Danny "TechnoCat" Fritz dannyfritz@gmail.com
    Commons Attribution-ShareAlike 3.0
--]]

--An OO library for Lua by Kikito,
--can be found at https://github.com/kikito/middleclass
require 'goo/MiddleClass.lua'
require 'GraphicsStateStack.lua'


MessageBottle = class('MessageBottle')
TimeBottle = MessageBottle:subclass('TimeBottle')

--[[
Default values
--]]
MessageBottle.DEFAULT_SOUND = "blip.ogg"
MessageBottle.DEFAULT_VOLUME = 0.5
MessageBottle.DEFAULT_BUTTON = ' ' --Button to close/select
MessageBottle.DEFAULT_INDICATOR = love.graphics.newImage('input-indicator.png') --Image to 

MessageBottle.DEFAULT_X = 20
MessageBottle.DEFAULT_Y = 180
MessageBottle.DEFAULT_WIDTH = 300
MessageBottle.DEFAULT_HEIGHT = 80

MessageBottle.DEFAULT_FONT = love.graphics.newFont(18)
MessageBottle.DEFAULT_ALIGN = 'left'
MessageBottle.DEFAULT_FGCOLOR = {r=255,g=255,b=255}
MessageBottle.DEFAULT_FGALPHA = 1

MessageBottle.DEFAULT_BGRADIUS = 10 --pixels to draw the rounded corners
MessageBottle.DEFAULT_BGRADIUSSEGMENTS = 32 --how precisely to draw the circle
MessageBottle.DEFAULT_BGCOLOR = {r=0,g=0,b=0}
MessageBottle.DEFAULT_BGALPHA = 0.8

MessageBottle.DEFAULT_EASETIME = 0.5 --seconds to ease
MessageBottle.DEFAULT_FADETIME = 0.3 --seconds to fade alpha
MessageBottle.DEFAULT_EASEOFFSET = 10

MessageBottle.DEFAULT_ID = "NO_ID"
MessageBottle.DEFAULT_TEXT = "Text is not set."

TimeBottle.TIMEOUT = 6 --seconds to keep the bottle alive

function MessageBottle:drawBackground()
  --draw background
  --self.bgAlpha
  --self.alpha
  love.graphics.pushState()
  local r,g,b,a = self.bgColor.r, self.bgColor.g, self.bgColor.b
  local a = self.bgAlpha * self.alpha
  local r = self.bgRadius
  local x,y = self.x, self.y
  local w,h = self.width, self.height
  local segments = self.bgRadiusSegments
  love.graphics.setColor(r,g,b,a)
  --center rectangle
  love.graphics.rectangle("fill",
      x, y,
      w, h)
  --top border
  love.graphics.rectangle("fill",
      x, y-r,
      w, r)
  -- right border
  love.graphics.rectangle("fill",
      x+w, y,
      r, h)
  --bottom border
  love.graphics.rectangle("fill",
      x, y+h,
      w, r)
  --left border
  love.graphics.rectangle("fill",
      x-r, y,
      r, h)
  --top left corner
  love.graphics.setScissor(
      x-r, y-r,
      r, r)
  love.graphics.circle("fill",
      x, y,
      r, segments)
  --top right corner
  love.graphics.setScissor(
      x+w, y-r,
      r, r)
  love.graphics.circle("fill",
      x+w, y,
      r, segments)
  --bottom right corner
  love.graphics.setScissor(
      x+w, y+h,
      r, r)
  love.graphics.circle("fill",
      x+w, y+h,
      r, segments)
  --bottom left corner
  love.graphics.setScissor(
      x-r, y+h,
      r, r)
  love.graphics.circle("fill",
      x, y+h,
      r, segments)
  love.graphics.popState()
end



--[[
  Ocean
  This is a class to store and invoke the focussed bottles
  (A queue)
--]]
Ocean = class('Ocean')

function Ocean:initialize()
  super.initialize(self)
  self.bottles = {}
  self.response = ""
  self.responseTime = 0
  self.responseID = ""
  self.time = 0
end

function Ocean:update(dt)
  if #self.bottles > 0 then
    self.time = self.time + dt
    local bottle = self.bottles[1]
    if bottle.focusTime == 0 then
      bottle:enterCallback()
    end
    local tmp = self.response
    self.response = bottle:update(dt)
    if self.response==nil then
      self.response = tmp
    else
      self.responseTime = self.time
      self.responseID = self.bottles[1].id
    end
    if not bottle.alive then
      bottle:exitCallback(self.response)
      table.remove(self.bottles,1)
    end
  end
end

function Ocean:draw()
  if #self.bottles > 0 then
    self.bottles[1]:draw()
  end
end

function Ocean:addBottle(bottle)
  local bottles = self.bottles
  table.insert(bottles, #bottles+1, bottle)
end



--[[
  Message Bottle
  This is a default message bottle class
  Bottle background is drawn here.
--]]



function MessageBottle:initialize(id, text)
  super.initialize(self)

  self.id = id or self.class.DEFAULT_ID
  self.text  = text or self.class.DEFAULT_TEXT
  self.alive = true --Set to flag to mark for deletion
  
  --Callbacks
  self.enterCB = function() return end
  self.exitCB = function(response) return end
  
  --Sounds
  self.sound = self.class.DEFAULT_SOUND
  self.volume = self.class.DEFAULT_VOLUME

  --Buttons
  self.button = self.class.DEFAULT_BUTTON
  self.buttonDown = false --Flag to make the button action happen on release
  self.indicator = indicator or self.class.DEFAULT_INDICATOR

  --Dimensions
  self.x = self.class.DEFAULT_X
  self.y = self.class.DEFAULT_Y
  self.width = self.class.DEFAULT_WIDTH
  self.height = self.class.DEFAULT_HEIGHT

  --Foreground settings
  self.fgColor = self.class.DEFAULT_FGCOLOR
  self.fgAlpha = self.class.DEFAULT_FGALPHA
  self.font = self.class.DEFAULT_FONT
  self.align = self.class.DEFAULT_ALIGN

  --Background settings
  self.bgColor = self.class.DEFAULT_BGCOLOR
  self.bgAlpha = self.class.DEFAULT_BGALPHA
  self.bgRadius = self.class.DEFAULT_BGRADIUS
  self.bgRadiusSegments = self.class.DEFAULT_RADIUSSEGMENTS
  
  --Ease settings
  self.easeTarget = self.class.DEFAULT_Y
  self.easeOffset = self.class.DEFAULT_EASEOFFSET
  self.easeTime = self.class.DEFAULT_EASETIME

  --Fade settings
  self.focusTime = 0 --seconds the message has been in focus
  self.alpha = 0
  self.fadeTime = self.class.DEFAULT_FADETIME
  
end

function MessageBottle:baseUpdate(dt, focusTime)
  self.y = self:ease(focusTime,self.easeTime, self.easeTarget,self.easeOffset)
  self.alpha = self:fade(focusTime,self.fadeTime, 0,255)
  self.focusTime = self.focusTime + dt
end

function MessageBottle:enterCallback()
  --Sound
  self.source = love.audio.newSource(self.sound, "static")
  self.source:setVolume(self.volume)
  self.source:play()
  self.enterCB()
end

function MessageBottle:exitCallback(response)
  self.exitCB(response)
end

function MessageBottle:ease(t,d, a,b)
  if d <= t then
    function self:ease(t,d, a,b) return self.y end
  end
  local v = -(t/d)*(t/d-2)*b+a
  return math.floor(v)
end

function MessageBottle:fade(t,d, a,b)
  if d <= t then
    function self:fade(t,d, a,b) return 255 end
  end
  local v = t/d*b+a
  if v>=255 then
    v=255
    function self:fade(t,d, a,b) return 255 end
  end
  return v
end

function MessageBottle:setX(x)
  self.x = x
end

function MessageBottle:setY(y)
  self.easeTarget = y
  self.y = y
end

function MessageBottle:setPosition(x, y)
  self.x = x
  self.y = y
  self.easeTarget = y
end

function MessageBottle:setWidth(width)
  self.width = width
end

function MessageBottle:setHeight(height)
  self.height = height
end

function MessageBottle:setButton(button)
  self.button = button
end

function MessageBottle:setEase(ease)
  self.ease = ease
end

function MessageBottle:setEaseTime(easeTime)
  self.easeTime = easeTime
end

function MessageBottle:setFade(fade)
  self.fade = fade
end

function MessageBottle:setFadeTime(fadeTime)
  self.fadeTime = fadeTime
end

function MessageBottle:setEnterCallback(enterCB)
  self.enterCB = enterCB
end

function MessageBottle:setExitCallback(exitCB)
  self.exitCB = exitCB
end

function MessageBottle:setSound(sound)
  if sound==nil then
    self.volume = 0
    return
  end
  self.sound = sound
end

function MessageBottle:setVolume(volume)
  self.volume = volume
end

function MessageBottle:setIndicator(indicator)
  self.indicator = love.graphics.newImage(indicator)
end

function MessageBottle:setFgColor(r, g, b, a)
  self.fgColor = {r, g, b, a}
end

function MessageBottle:setFont(font, size)
  self.font = love.graphics.newFont(font,size)
end

function MessageBottle:setAlign(align)
  self.align = align
end

function MessageBottle:setBgColor(r, g, b, a)
  self.bgColor = {r, g, b, a}
end

function MessageBottle:setBgRadius(bgRadius)
  self.bgRadius = bgRadius
end

function MessageBottle:setBgRadiusSegments(bgRadiusSegments)
  self.bgRadiusSegments = bgRadiusSegments
end


--[[
  Staying Bottle
  This pops up a message bottle and
  goes away after a button is pressed
--]]

StayBottle = MessageBottle:subclass('StayBottle')

function StayBottle:initialize(id, text)
  super.initialize(self, id, text)
end

function StayBottle:update(dt)
  self:baseUpdate(dt,self.focusTime)
  if love.keyboard.isDown(self.button) and self.buttonDown==false then
    self.buttonDown = true
  elseif self.buttonDown==true and not love.keyboard.isDown(self.button) then
    self.alive = false
    return 0
  end
end

function StayBottle:draw()
  love.graphics.pushState()
  self:drawBackground()
  local color = self.fgColor
  love.graphics.setColor(color.r,color.g,color.b,self.alpha)
  love.graphics.setFont(self.font)
  local text = ""
  text = text..self.text..'\n'
  local button = self.button
  if button == " " then
    button = "space"
  end
  if math.floor(self.focusTime)%2 == 0 then
    --text = text..'press \''..button..'\' to continue'
  else
    --text = text..'press \''..button..'\' to continue...'
  end
  love.graphics.printf(text, self.x,self.y, self.width, self.align)
  local floaty = math.sin(self.focusTime*3)*3
  local y = self.y + self.height + floaty - self.indicator:getHeight()/2
  love.graphics.draw(self.indicator,self.x+self.width/2, y)
  love.graphics.popState()
end



--[[
  Timed Bottle
  This pops up a message bottle and
  goes away after a set time duration
--]]

function TimeBottle:initialize(id, text, timeout)
  super.initialize(self, id, text)
  self.timeout = timeout or self.class.TIMEOUT
end

function TimeBottle:update(dt)
  self:baseUpdate(dt,self.focusTime)
  self.timeout = self.timeout - dt
  if love.keyboard.isDown(self.button) and self.buttonDown==false then
    self.buttonDown = true
  elseif self.buttonDown==true and not love.keyboard.isDown(self.button) then
    self.alive = false
    return 0
  end
  if self.timeout <= 0 then --count down a timer
    self.alive = false
    return 1
  end
end

function TimeBottle:draw()
  love.graphics.pushState()
  self:drawBackground()
  local color = self.fgColor
  love.graphics.setColor(color.r,color.g,color.b,self.alpha)
  love.graphics.setFont(self.font)
  love.graphics.printf(self.text, self.x,self.y, self.width, self.align)
  love.graphics.popState()
end

function TimeBottle:setTimeout(timeout)
  self.timeout = timeout
end



--[[
  Choice Bottle
  This pops up a message with choices bottle
  and goes away after a choice is made
--]]

ChoiceBottle = MessageBottle:subclass('ChoiceBottle')

function ChoiceBottle:initialize(id, text, ...)
  super.initialize(self, id, text)
end

function ChoiceBottle:update(dt)
  --Draw text and choices along with cursor
  --Check keyboard / mouse input for selection
end

function ChoiceBottle:draw()
  
end

