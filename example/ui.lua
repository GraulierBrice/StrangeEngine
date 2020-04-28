local ui = {}

function ui.button(text, x, y, action)
    local m = mousePos()
    local color = 0x888888ff
    if x <= m.x and m.x < x + 4*#text-1 and m.y < y and y-5 < m.y then
        color = -1
        if buttonDown(0) and action ~= nil then
            action()
        end
    end
    print(text, x, y, color)
end

function ui.printAlignRight(text, x, y, c)
    print(text, x-4*#text, y, c)
end

return ui