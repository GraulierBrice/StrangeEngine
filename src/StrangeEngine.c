#include "common.h"

int main(int argc, char* argv[]) {
    if (argc == 0) {
        exit(0);
    }

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    luaL_dofile(L, argv[1]);
    
    pushAllLuaFunctions(L);


    
    start_system();
    
    call_lua_function(L, "start");


    while(running) {
        float frame_start = time();
        handleEvents();

        call_lua_function(L, "update");
        
        clear_screen();
        call_lua_function(L, "draw");
        draw_screen();

        float frame_end = time();
        fps = 1/(frame_end - frame_start);
    }
    
    stop_system();
    lua_close(L);
    
    return 0;
}