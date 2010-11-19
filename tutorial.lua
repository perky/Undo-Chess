state_tutorial = Gamestate.new()
local tutorial = {}
tutorial.mt = {}
local ocean

local msg_pos
local msg_list = {
	{ 'Welcome to the UndoChess tutorial.\nPress space to continue.' },
	{ 'To play a move drag a piece with the mouse, try it', 50, 300 },
	{ 'This the timeline, notice how each move displayed', 380, 55 },
	{ 'Click on your last move in the timeline, notice how the peice has jumped back', 380, 55 },
	{ "Playing a move now will overwrite the move you're currently on", 380, 55 },
	{ "You cannot overwrite your opponents moves", 380, 55 },
	{ "Notice the new move called TIMELINE LOCKED", 380, 55 },
	{ "These are created everytime you play in the past", 380, 55 },
	{ "You cannot overwrite these moves", 380, 55 },
	{ "Hint: you can also use the mousewheel scroll up and down the timeline", 380, 55 },
	{ "Try taking a peice with a pawn, then go back a prevent this from happening", 320, 260 },
	{ "If you go back the the present you might notice some moves become INVALID" },
	{ "This is because the changed past means some future moves are invalid moves", 320, 260 },
	{ "Lets try time travel, goto the present", 37, 350 },
	{ "Now drag a peice from the board onto a past move in the timeline", 37, 350 },
	{ "That peice has now jumped back in time in it's own place", 37, 350 },
	{ "Two moves change: one to 'jump out' and one to 'jump in'", 37, 350 },
	{ "Goto any move between these", 37, 350 },
	{ "Notice your peice is red, this means it has time traveled", 37, 350 },
	{ "As you scroll down past 'jump out' the original peice will dissapear", 37, 350 },
	{ "You cannot jump onto an opponents move or a LOCKED move", 37, 350 },
	{ "Nor can you overwrite a jump move", 37, 350 },
	{ "This concludes the tutorial, press space to return to menu" },
}

function state_tutorial:enter( last_state )
	setmetatable( tutorial, tutorial.mt )
	tutorial.mt.__index = state_chess
	MULTIPLAYER = false
	Gamestate.switch( tutorial )
	
	ocean = Ocean:new()
	msg_pos = 1
	next_msg()
end

function tutorial.finished()
	Gamestate.switch( state_menu )
end

function next_msg( )
	local msg = msg_list[msg_pos]
	msg_pos = msg_pos + 1
	if not msg then
		tutorial.finished()
		return
	end
	
	local bottle = StayBottle:new(nil,msg[1])
	if msg[2] and msg[3] then
		bottle:setPosition(msg[2],msg[3])
	end
	if msg[4] then bottle:setWidth( msg[4] ) end
	if msg[5] then bottle:setHeight( msg[5] ) end
	bottle:setExitCallback( next_msg )
	ocean:addBottle( bottle )
end

function tutorial:update( dt )
	state_chess:update( dt )
	ocean:update( dt )
end

function tutorial:draw()
	state_chess:draw()
	ocean:draw()
end