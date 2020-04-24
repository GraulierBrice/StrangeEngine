#ifndef _SE_INPUT_H_
#define _SE_INPUT_H_

#include "SDL2/SDL.h"
#include "memory.h"

int addr_from_scancode(SDL_Scancode scancode);

void update_input();

void inputDown(SDL_Scancode scancode);
void inputUp(SDL_Scancode scancode);
void inputMouseDown(int btn);
void inputMouseUp(int btn);
void inputMouseMotion(int x, int y);

#endif