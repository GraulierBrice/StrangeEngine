#ifndef _SE_SYSTEM_H_
#define _SE_SYSTEM_H_

#include "common.h"

// internal
int running;
struct timeval startTime;
float fps;

float time();
void start_system();
void stop_system();
void quit();

float framerate();

// lua

int l_time(lua_State* L);
int l_quit(lua_State* L);
int l_framerate(lua_State* L);

void system_pushLuaFunctions(lua_State* L);

#endif