local ui=require("ui")
local game = {}
local gamedata = {
    turn = 1,
    n = 0
}

function isMyTurn()
    return isHost() and gamedata.turn == 1 or isClient() and gamedata.turn == 2
end

function changeTurn()
    if gamedata.turn == 2 then
        gamedata.turn = 1
    elseif gamedata.turn == 1 then
        gamedata.turn = 2
    end
end

function netUpdate()
    if (receiveData(0x20000, 2) == 1) then
        gamedata.turn = memread(0x20000)
        gamedata.n = memread(0x20001)
    end
end

function game.mainloop()
    netUpdate()
    if (not isMyTurn()) then
        ui.printAlignRight("waiting for opponent...", 127,7, -1)
    else
        if (buttonDown(2)) then
            gamedata.n = gamedata.n + 1
        elseif (buttonDown(3)) then
            gamedata.n = gamedata.n - 1
        end
        ui.button("end", 0, 117,
            function()
                changeTurn()
                memwrite(0x20000, gamedata.turn)
                memwrite(0x20001, gamedata.n)
                sendData(0x20000, 2)
            end
        )
    end
    print(gamedata.n, 64, 64, -1)
end

return game