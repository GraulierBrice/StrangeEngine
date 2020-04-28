#ifndef _SE_STORAGE_H_
#define _SE_STORAGE_H_

#include "common.h"

void loadFile(const char* name, int addr);
void dumpFile(const char* name, int addr, int length);

int l_loadFile(lua_State* L);
int l_dumpFile(lua_State* L);

void storage_pushLuaFunctions(lua_State* L);

#endif