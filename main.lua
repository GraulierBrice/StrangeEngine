local lobby = require("lobby")
local game = require("game")

function update()
    clear()
    if (connected()) then game.mainloop() end
    lobby.lobby()
    pixel(mousePos().x, mousePos().y, -1)
end

function finish()
    closeConnection()
end