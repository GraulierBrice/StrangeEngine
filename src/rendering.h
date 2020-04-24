#ifndef _SE_RENDERING_H_
#define _SE_RENDERING_H_

#include "SDL2/SDL.h"

#include "common.h"
#include "memory.h"

#define SCREEN_ADDR 0x00000
#define BYTES_PER_PIXEL 4

#define WIDTH 128
#define HEIGHT 128

// internal

SDL_Window* window;
SDL_Renderer* renderer;

void init_screen();
void close_screen();
void clear_screen();
void draw_screen();

void clear();

int screen_to_addr(int x, int y);
void addr_to_screen(int addr, int* x, int* y);

char r(int c);
char g(int c);
char b(int c);
char a(int c);

void pixel(int x, int y, int c);

// lua

int l_clear(lua_State* L);
int l_pixel(lua_State* L);

void rendering_pushLuaFunctions(lua_State* L);

#endif