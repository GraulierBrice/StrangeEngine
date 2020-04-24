function draw()
    clear()
    for i=0, 40 do
    for x=0,127 do for y=0, 127 do
        pixel(x, y, x*0x00020000 + y*0x00000200);
    end end
end
    
    local x = memread(0x10000)
    local y = memread(0x10001)
    
    print(framerate(), 0, 127, 0xffffffff)
    circle(x, y, 5, 0xff000000);

end