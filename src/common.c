#include "common.h"

void define_lua_function(lua_State* L, char* name,  void* function) {
    lua_pushcfunction(L, function);
    lua_setglobal(L, name);
}

void call_lua_function(lua_State* L, char* name) {
    if (lua_getglobal(L, name)) {
        lua_call(L, 0, 0);
    }
}