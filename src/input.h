#ifndef _SE_INPUT_H_
#define _SE_INPUT_H_

#include "SDL2/SDL.h"
#include "memory.h"

void update_input();
void update_keyboard();
void update_mouse();
void update_with_scancode(const Uint8* states, SDL_Scancode scancode, int id);

void mousePos(int* x, int* y);
int buttonPress(int id);
int buttonDown(int id);
int buttonUp(int id);

int l_mousePos(lua_State* L);
int l_buttonPress(lua_State* L);
int l_buttonDown(lua_State* L);
int l_buttonUp(lua_State* L);

void input_pushLuaFunctions(lua_State* L);

#endif