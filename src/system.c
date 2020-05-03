#include "system.h"
//#include <sys/time.h>

float time() {
    struct timeval t;
    gettimeofday(&t, NULL);
    float s =  t.tv_sec - startTime.tv_sec;
    float us =  t.tv_usec - startTime.tv_usec;
    return s + us / (float)1000000;
}

void start_system() {
    memory_init();
    init_screen();
    TTF_Init();
    gettimeofday(&startTime, NULL);
    running = 1;
}

void stop_system() {
    memory_clear();
    close_screen();
    unload_font();
}

void quit() {
    running = 0;
}

float framerate() {
    return fps;
}

int l_time(lua_State* L) {
    lua_pushnumber(L, time());
    return 1;
}

int l_quit(lua_State* L) {
    quit();
    return 0;
}

int l_framerate(lua_State* L) {
    lua_pushnumber(L, framerate());
    return 1;
}

void system_pushLuaFunctions(lua_State* L) {
    define_lua_function(L, "time", l_time);
    define_lua_function(L, "quit", l_quit);
    define_lua_function(L, "framerate", l_framerate);
}