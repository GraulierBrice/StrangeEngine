#include "events.h"

void handleEvents() {
    SDL_Event events[10];
    SDL_PumpEvents();
    int n = SDL_PollEvent(events);
    for (int i=0; i<n; i++) {
        SDL_Event e = events[i];
             if (events[i].type == SDL_KEYDOWN)         inputDown(e.key.keysym.scancode);
        else if (events[i].type == SDL_KEYUP)           inputUp(e.key.keysym.scancode);
        else if (events[i].type == SDL_MOUSEBUTTONDOWN) inputMouseDown(e.button.button);
        else if (events[i].type == SDL_MOUSEBUTTONUP)   inputMouseUp(e.button.button);
        else if (events[i].type == SDL_QUIT)            quit();
    }
}