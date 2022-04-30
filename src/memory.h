#ifndef _SE_MEMORY_H_
#define _SE_MEMORY_H_

#include "common.h"

// internal

void memory_init();
void memory_clear();
int byte(int n);

char memread(int addr);
void memwrite(int addr, char value);
void memfill(int addr, int length, char value);
void memcopy(int src, int dst, int length);
long memory_addr();

// lua

int l_memread(lua_State* L);
int l_memwrite(lua_State* L);
int l_memfill(lua_State* L);
int l_memcopy(lua_State* L);

void memory_pushLuaFunctions(lua_State* L);

#endif
