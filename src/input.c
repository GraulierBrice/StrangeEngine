#include "input.h"

#define INPUT_ADDR 0x10000
#define MOUSE_ADDR 0x10000
#define BTN_ADDR 0x10002
#define ADDR_PER_BTN 3

int button(int btn) {
    return btn * ADDR_PER_BTN + BTN_ADDR;
}

void update_input_memory(int id, char input) {
    int addr = button(id);
    char prev_press = memread(addr);
    
    memwrite(addr, input);
    memwrite(addr+1, prev_press==0 && input!=0);
    memwrite(addr+2, prev_press!=0 && input==0);
}

void update_mouse() {
    int x, y, w, h, btn;
    btn = SDL_GetMouseState(&x, &y);
    SDL_GetWindowSize(window, &w, &h);
    memwrite(MOUSE_ADDR, x*WIDTH/w);
    memwrite(MOUSE_ADDR+1, HEIGHT - y*HEIGHT/h);
    update_input_memory(0, (btn & 1) > 0);
    update_input_memory(1, (btn & 4) > 0);
}

void update_with_scancode(const Uint8* states, SDL_Scancode scancode, int id) {
    if (states[scancode]) {
        update_input_memory(id, 1);
    } else {
        update_input_memory(id, 0);
    }
}

void update_keyboard() {
    const Uint8* states = SDL_GetKeyboardState(NULL);
    update_with_scancode(states, SDL_SCANCODE_UP, 2);
    update_with_scancode(states, SDL_SCANCODE_DOWN, 3);
    update_with_scancode(states, SDL_SCANCODE_RIGHT, 4);
    update_with_scancode(states, SDL_SCANCODE_LEFT, 5);
    update_with_scancode(states, SDL_SCANCODE_RETURN, 6);
    update_with_scancode(states, SDL_SCANCODE_SPACE, 7);
    update_with_scancode(states, SDL_SCANCODE_ESCAPE, 8);
}

void update_input() {
    update_mouse();
    update_keyboard();
}

void mousePos(int* x, int* y) {
    *x = (int) memread(MOUSE_ADDR);
    *y = (int) memread(MOUSE_ADDR+1);
}

int buttonPress(int id) {
    return memread(button(id));
}

int buttonDown(int id) {
    return memread(button(id)+1);
}

int buttonUp(int id) {
    return memread(button(id)+2);
}

int l_mousePos(lua_State* L) {
    int x, y;
    mousePos(&x, &y);
    lua_createtable(L, 0, 0);

    lua_pushstring(L, "x");
    lua_pushnumber(L, x);
    lua_settable(L, -3);

    lua_pushstring(L, "y");
    lua_pushnumber(L, y);
    lua_settable(L, -3);

    return 1;
}

int l_buttonPress(lua_State* L) {
    int btn = luaL_checkinteger(L, 1);
    lua_pushboolean(L, buttonPress(btn));
    return 1;
}

int l_buttonDown(lua_State* L) {
    int btn = luaL_checkinteger(L, 1);
    lua_pushboolean(L, buttonDown(btn));
    return 1;
}

int l_buttonUp(lua_State* L) {
    int btn = luaL_checkinteger(L, 1);
    lua_pushboolean(L, buttonUp(btn));
    return 1;
}

void input_pushLuaFunctions(lua_State* L) {
    define_lua_function(L, "mousePos", l_mousePos);
    define_lua_function(L, "buttonPress", l_buttonPress);
    define_lua_function(L, "buttonDown", l_buttonDown);
    define_lua_function(L, "buttonUp", l_buttonUp);
}