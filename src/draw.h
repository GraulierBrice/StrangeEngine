#ifndef _SE_DRAW_H_
#define _SE_DRAW_H_

#include <SDL2/SDL_ttf.h>

#include "common.h"

// internal

void load_font(const char* file, int size);
void unload_font();

void pixel(int x, int y, int c);
void circle(int x, int y, int r, int c);
void rectangle(int x0, int y0, int x1, int y1, int c);

void print_text(const char* text, int x, int y, int c);

// lua
int l_pixel(lua_State* L);
int l_circle(lua_State* L);
int l_rectangle(lua_State* L);

int l_print_text(lua_State* L);
int l_load_font(lua_State* L);

void draw_pushLuaFunctions(lua_State* L);

#endif