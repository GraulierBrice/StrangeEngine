local ui=require("ui")

local game = {}
local gamedata = {}

function game.start()
    gamedata = {
        host = {x=64, y=10, bullets={}, hp=10 },
        client = {x=64, y=10, bullets={}, hp=10}
    }
end

function me()
    if (isHost()) then return gamedata.host
    else return gamedata.client end
end

function him()
    if (isHost()) then return gamedata.client
    else return gamedata.host end
end

function receive()
    memfill(0x20000, 0x200ff, 0)
    him().bullets={}
    if (receiveData(0x20000, 4) == 1) then
        local p = him()
        p.hp = memread(0x20000)
        p.x = memread(0x20001)
        p.y = memread(0x20002)
        local n = memread(0x20003)
        p.bullets = {}
        if (receiveData(0x20004, n * 4) == 1) then
            for i = 0, n-1 do
                p.bullets[i+1] = {
                    x=memread(0x20004+4*i),
                    y=127-memread(0x20004+4*i+1),
                    vx=memread(0x20004+4*i+2),
                    vy=-memread(0x20004+4*i+3)
                }
            end
        end
    end
end

function send()
    memfill(0x20000, 0x200ff, 0)
    local p = me()
    memwrite(0x20000, p.hp)
    memwrite(0x20001, p.x)
    memwrite(0x20002, p.y)
    memwrite(0x20003, #p.bullets)
    for i = 0, #p.bullets-1 do
        memwrite(0x20004+4*i, p.bullets[i+1].x)
        memwrite(0x20004+4*i+1, p.bullets[i+1].y)
        memwrite(0x20004+4*i+2, p.bullets[i+1].vx)
        memwrite(0x20004+4*i+3, p.bullets[i+1].vy)
    end
    sendData(0x20000, 4)
    sendData(0x20004, 4*#p.bullets)
end

function game.mainloop()
    if buttonPress(4) then me().x = me().x + 1 end
    if buttonPress(5) then me().x = me().x - 1 end
    if buttonDown(7) then
        me().bullets[#me().bullets+1] = {
            x = me().x,
            y = me().y+5,
            vx = 0,
            vy = 3
        }
    end
    rectangle(me().x-2, me().y-2, me().x+2, me().y+2, 0x00ffffff)
    rectangle(him().x-2, 127-him().y-2, him().x+2, 127-him().y+2, 0xffff00ff)

    for i = 0, #me().bullets-1 do
        me().bullets[i+1].x = me().bullets[i+1].x + me().bullets[i+1].vx
        me().bullets[i+1].y = me().bullets[i+1].y + me().bullets[i+1].vy
        pixel(me().bullets[i+1].x, me().bullets[i+1].y, 0x00ffffff)
    end

    for i = 0, #him().bullets-1 do
        local x = him().bullets[i+1].x
        local y = him().bullets[i+1].y
        if me().x-2 <= x and x<=me().x+2 and me().y-2 <= y and y<=me().y+2 then
            me().hp = me().hp-1
        end
        pixel(him().bullets[i+1].x, him().bullets[i+1].y, 0xffff00ff)
    end

    if (#me().bullets > 0) then
        if (me().bullets[1].y>127) then
            table.remove( me().bullets, 1)
        end
    end

    print(me().hp.." "..#me().bullets, 0, 7, 0x00ffffff)
    print(him().hp.." "..#him().bullets, 0, 107, 0xffff00ff)

    send() receive()
end

return game