local ui = require("ui")
local game = require("game")
local lobby = {}

function lobby.lobby()
    local x, y, msg
    local port=45569

    if isHost() then
        msg='host'
    elseif isClient() then
        msg='client'
    elseif serverWaiting() then
        msg='waiting...'
    else
        msg='offline'
    end
    ui.printAlignRight(msg, 127, 127, -1)
    if not connected() and not serverWaiting() then
        ui.button("host game", 0, 127, function() createHost(port) game.start() end)
        ui.button("join game", 0, 117, function() createClient("127.0.0.1", port) game.start() end)
    else
        ui.button("disconnect", 0, 127, function() closeConnection() end)
    end
end

return lobby