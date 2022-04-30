#include "common.h"
#include <libgen.h>

#include "draw.h"
#include "events.h"
#include "input.h"
#include "memory.h"
#include "network.h"
#include "rendering.h"
#include "storage.h"
#include "system.h"

void pushAllLuaFunctions(lua_State* L) {
    memory_pushLuaFunctions(L);
    rendering_pushLuaFunctions(L);
    system_pushLuaFunctions(L);
    draw_pushLuaFunctions(L);
    input_pushLuaFunctions(L);
    storage_pushLuaFunctions(L);
    network_pushLuaFunctions(L);
}

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


    while(is_running()) {
        float frame_start = time();
        handleEvents();
        update_input();
        call_lua_function(L, "update");
        
        clear_screen();
        draw_screen();

        float frame_end = time();
        set_fps(1/(frame_end - frame_start));
    }
    
    call_lua_function(L, "finish");

    stop_system();
    lua_close(L);
    
    return 0;
}