#include "common.h"
#include <libgen.h>

int main(int argc, char* argv[]) {
    if (argc == 0) {
        exit(0);
    }

    start_system();


    char* ts1 = strdup(argv[1]);
    char* ts2 = strdup(argv[1]);
    char* dir = dirname(ts1);
    char* file = basename(ts2);

    if (chdir(dir)) {
        perror(argv[1]);
        stop_system();
        exit(1);
    }
    

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    luaL_dofile(L, file);
    pushAllLuaFunctions(L);
    
    load_font("PICO-8 mono.ttf", 4);
    
    call_lua_function(L, "start");


    while(running) {
        float frame_start = time();
        handleEvents();
        update_input();
        call_lua_function(L, "update");
        
        clear_screen();
        draw_screen();

        float frame_end = time();
        fps = 1/(frame_end - frame_start);
    }
    
    call_lua_function(L, "finish");

    stop_system();
    lua_close(L);
    
    return 0;
}