#include "storage.h"
#include "memory.h"

void loadFile(const char* name, int addr) {
    FILE* file = fopen(name, "r");
    if (file) {
        while (!feof(file)) {
            char byte = fgetc(file);
            memwrite(addr, byte);
            addr++;
        }
    }
    fclose(file);
}

void dumpFile(const char* name, int addr, int length) {
    FILE* file = fopen(name, "w");
    if (file) {
        while(length > 0) {
            fputc(memread(addr), file);
            addr++;
            length--;
        }
    }
    fclose(file);
}

int l_loadFile(lua_State* L) {
    const char* name = luaL_checkstring(L, 1);
    lua_Integer addr = luaL_checkinteger(L, 2);
    
    loadFile(name, addr);

    return 0;
}

int l_dumpFile(lua_State* L) {
    const char* name = luaL_checkstring(L, 1);
    lua_Integer addr = luaL_checkinteger(L, 2);
    lua_Integer length = luaL_checkinteger(L, 3);
    
    dumpFile(name, addr, length);

    return 0;
}

void storage_pushLuaFunctions(lua_State* L) {
    define_lua_function(L, "loadFile", l_loadFile);
    define_lua_function(L, "dumpFile", l_dumpFile);
}