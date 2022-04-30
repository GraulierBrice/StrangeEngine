#include "rendering.h"
#include <SDL2/SDL_video.h>

SDL_Window* window;
SDL_Renderer* renderer;

void init_screen() {
    window = SDL_CreateWindow(
        "Strange Engine",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        512, 512,
        SDL_WINDOW_RESIZABLE
    );
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);
    SDL_ShowCursor(0);
    SDL_ShowWindow(window);
}

void close_screen() {
    free(window);
    free(renderer);
}

void clear_screen() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff);
    SDL_RenderClear(renderer);
}

void draw_screen() {
    int x, y;
    for(int i=SCREEN_ADDR; i<SCREEN_ADDR + WIDTH * HEIGHT * BYTES_PER_PIXEL; i += BYTES_PER_PIXEL) {
        addr_to_screen(i, &x, &y);
        SDL_SetRenderDrawColor(renderer, memread(i), memread(i+1), memread(i+2), memread(i+3));
        SDL_RenderDrawPoint(renderer, x, HEIGHT - y-1);
    }
    SDL_RenderPresent(renderer);
}

SDL_Window* get_window() {
    return window;
}

int screen_to_addr(int x, int y) {
    x = x % WIDTH;
    y = y % HEIGHT;
    return SCREEN_ADDR + BYTES_PER_PIXEL * (x + y * WIDTH);
}

void addr_to_screen(int addr, int* x, int* y) {
    int n = (addr - SCREEN_ADDR)/BYTES_PER_PIXEL;
    *x = n % WIDTH;
    *y = n / WIDTH;
}

char r(int c) {
    return c >> 24;
}

char g(int c) {
    return c >> 16;
}

char b(int c) {
    return c >> 8;
}

char a(int c) {
    return c;
}

void clear() {
    memfill(SCREEN_ADDR, WIDTH * HEIGHT * BYTES_PER_PIXEL, 0);
}

int l_clear(lua_State* L) {
    clear();
    return 0;
}

void rendering_pushLuaFunctions(lua_State* L) {
    define_lua_function(L, "clear", l_clear);
}
