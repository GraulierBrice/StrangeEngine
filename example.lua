local math = require("math")

function draw()
    clear()
    
    for x=0,127 do for y=0, 127 do
        pixel(x, y, (x+(math.cos(time())+1)*0.25)*0x00010000 + (y*(math.sin(time())+1)*0.25)*0x00000100);
    end end
    
    local x = memread(0x10000)
    local y = memread(0x10001)
    
    print(math.floor(framerate()), 0, 127, 0xffffffff)
    circle(x, y, 5, 0xff000000);

end