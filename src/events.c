#include "events.h"
#include "system.h"


void handleEvents() {
    SDL_Event events[10];
    int n = SDL_PollEvent(events);
    for (int i=0; i<n; i++) {
        if (events[i].type == SDL_QUIT) quit();
    }
}