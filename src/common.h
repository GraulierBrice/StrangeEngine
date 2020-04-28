#ifndef _SE_COMMON_INC_H_
#define _SE_COMMON_INC_H_

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <math.h>

#include "memory.h"
#include "rendering.h"
#include "system.h"
#include "input.h"
#include "events.h"
#include "draw.h"
#include "storage.h"
#include "network.h"


void define_lua_function(lua_State* L, char* name, void* function);
void call_lua_function(lua_State* L, char* name);

void pushAllLuaFunctions(lua_State* L);
#endif