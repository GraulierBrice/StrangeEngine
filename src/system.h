#ifndef _SE_SYSTEM_H_
#define _SE_SYSTEM_H_

#include "common.h"
#include "memory.h"
#include "rendering.h"
#include "draw.h"
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

// internal

float time();
void start_system();
void stop_system();
void quit();

float framerate();
void set_fps(float f);
bool is_running();

// lua

int l_time(lua_State* L);
int l_quit(lua_State* L);
int l_framerate(lua_State* L);

void system_pushLuaFunctions(lua_State* L);

#endif