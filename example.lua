local toggle = true

function update()
    if buttonPress(8) then quit()
    elseif buttonDown(7) then toggle = not toggle end
end

function draw()
    clear()

    local pos = mousePos()
    if (toggle) then
        rectangle(pos.x-4, pos.y-4, pos.x+4, pos.y+4, 0xffffffff);
    end
end