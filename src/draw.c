#include "draw.h"
#include "memory.h"
#include "rendering.h"
#include <math.h>

#define PI 3.14159265

TTF_Font* font;

void load_font(const char* name, int size) {
    font = TTF_OpenFont(name, size);
}

void unload_font() {
    if (font != NULL) {
        TTF_CloseFont(font);
        font = NULL;
    }
}

void pixel(int x, int y, int c) {
    int addr = screen_to_addr(x, y);
    if (0 <= x && x < WIDTH && 0 <= y && y < HEIGHT) {
        memwrite(addr,   r(c));
        memwrite(addr+1, g(c));
        memwrite(addr+2, b(c));
        memwrite(addr+3, a(c));
    }
}

void circle(int x, int y, int r, int c) {
    float delta_angle = 1 / (2 * PI * r); 
    for (float angle=0; angle < 2 * PI; angle += delta_angle) {
        pixel(cos(angle) * r + x, sin(angle) * r + y, c);
    }
}

void rectangle(int x0, int y0, int x1, int y1, int c) {
    for (int x = x0; x <= x1; x++) {
        for (int y = y0; y <= y1; y++) {
            pixel(x, y, c);
        }
    }
}

void print_text(const char* text, int x, int y, int c) {
    if (font != NULL) {
        SDL_Color fg; fg.r=0xff; fg.g=0xff; fg.b=0xff; fg.a=0xff;
        SDL_Color bg; bg.r=0x00; bg.g=0x00; bg.b=0x00; bg.a=0x00;
        SDL_Surface* surface = TTF_RenderUTF8(font, text, fg, bg);
        int size = surface->format->BytesPerPixel;
        SDL_Color* color;
        for(int px=0; px<surface->w; px++) {
            for(int py=0; py<surface->h; py++) {
                Uint8* pix = (Uint8*) surface->pixels + py * surface->pitch + px * size;
                color = surface->format->palette->colors + *pix;
                if (color->r) pixel(x+px, y-py, c);
            }
        }
        SDL_FreeSurface(surface);
    }
}

void sprite(int addr, int x, int y){
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            int c = byte(memread(addr+4*(j+8*i)))*0x1000000+byte(memread(addr+1+4*(j+8*i)))*0x10000+byte(memread(addr+2+4*(j+8*i)))*0x100+byte(memread(addr+3+4*(j+8*i)));
            pixel(x+j,y-i,c);
        }    
    }
}

int l_load_font(lua_State* L) {
    const char* text = luaL_checkstring(L, 1);
    lua_Integer size = (lua_Integer) luaL_checknumber(L, 2);
    load_font(text, size);
    return 0;
}

int l_pixel(lua_State* L) {
    lua_Integer x = (lua_Integer) luaL_checknumber(L, 1);
    lua_Integer y = (lua_Integer) luaL_checknumber(L, 2);
    lua_Integer c = (lua_Integer) luaL_checknumber(L, 3);
    pixel(x, y, c);
    return 0;
}

int l_circle(lua_State* L) {
    lua_Integer x = (lua_Integer) luaL_checknumber(L, 1);
    lua_Integer y = (lua_Integer) luaL_checknumber(L, 2);
    lua_Number r = luaL_checknumber(L, 3);
    lua_Integer c = (lua_Integer) luaL_checknumber(L, 4);

    circle(x, y, r, c);

    return 0;
}

int l_rectangle(lua_State* L) {
    lua_Integer x0 = (lua_Integer) luaL_checknumber(L, 1);
    lua_Integer y0 = (lua_Integer) luaL_checknumber(L, 2);
    lua_Integer x1 = (lua_Integer) luaL_checknumber(L, 3);
    lua_Integer y1 = (lua_Integer) luaL_checknumber(L, 4);
    lua_Integer c = (lua_Integer) luaL_checknumber(L, 5);

    rectangle(x0, y0, x1, y1, c);

    return 0;
}

int l_print_text(lua_State* L) {
    const char* text = luaL_checkstring(L, 1);
    lua_Integer x = (lua_Integer) luaL_checknumber(L, 2);
    lua_Integer y = (lua_Integer) luaL_checknumber(L, 3);
    lua_Integer c = (lua_Integer) luaL_checknumber(L, 4);

    print_text(text, x, y, c);

    return 0;
}

int l_sprite(lua_State* L) {
    lua_Integer addr = (lua_Integer) luaL_checknumber(L, 1);
    lua_Integer x = (lua_Integer) luaL_checknumber(L, 2);
    lua_Integer y = (lua_Integer) luaL_checknumber(L, 3);

    sprite(addr, x, y);

    return 0;
}


void draw_pushLuaFunctions(lua_State* L) {
    define_lua_function(L, "pixel", l_pixel);
    define_lua_function(L, "circle", l_circle);
    define_lua_function(L, "rectangle", l_rectangle);
    define_lua_function(L, "print", l_print_text);
    define_lua_function(L, "loadFont", l_load_font);
    define_lua_function(L, "sprite", l_sprite);
}
