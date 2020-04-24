#include "memory.h"
#include <stdlib.h>

#define MEM_SIZE 0x100000

void memory_init() {
    memory = (char*) malloc(sizeof(char) * MEM_SIZE);
}

void memory_clear() {
    free(memory);
}

char memread(int addr) {
    if (0 <= addr && addr < MEM_SIZE) {
        return memory[addr];
    }
    return 0;
}

void memwrite(int addr, char value) {
    if (0 <= addr && addr < MEM_SIZE) {
        memory[addr] = value;
    }
}

void memfill(int addr, int length, char value) {
    for (int i = addr; i < addr + length; i++) {
        memwrite(i, value);
    }
}

int l_memread(lua_State* L) {
    lua_Integer addr = (lua_Integer) luaL_checknumber(L, 1);
    lua_pushinteger(L, memread(addr));
    return 1;
}

int l_memwrite(lua_State* L) {
    lua_Integer addr = (lua_Integer) luaL_checknumber(L, 1);
    lua_Integer value = (lua_Integer) luaL_checknumber(L, 2);
    memwrite(addr, value);
    return 0;
}

int l_memfill(lua_State* L) {
    lua_Integer addr = (lua_Integer) luaL_checknumber(L, 1);
    lua_Integer length = (lua_Integer) luaL_checknumber(L, 2);
    lua_Integer value = (lua_Integer) luaL_checknumber(L, 3);
    memfill(addr, length, value);
    return 0;
}

void memory_pushLuaFunctions(lua_State* L) {
    define_lua_function(L, "memread", l_memread);
    define_lua_function(L, "memwrite", l_memwrite);
    define_lua_function(L, "memfill", l_memfill);
}