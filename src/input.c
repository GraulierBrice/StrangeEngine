#include "input.h"

#define INPUT_ADDR 0x10000
#define ADDR_PER_BTN 1

int button(int btn) {
    return btn * ADDR_PER_BTN + INPUT_ADDR;
}

int addr_from_scancode(SDL_Scancode scancode) {
         if (scancode == SDL_SCANCODE_UP)                   return button(4);
    else if (scancode == SDL_SCANCODE_DOWN)                 return button(5);
    else if (scancode == SDL_SCANCODE_RIGHT)                return button(6);
    else if (scancode == SDL_SCANCODE_LEFT)                 return button(7);
    else if (scancode == SDL_SCANCODE_RETURN)               return button(8);
    else if (scancode == SDL_SCANCODE_SPACE)                return button(9);
    else if (scancode == SDL_SCANCODE_ESCAPE)               return button(10);
    else return -1;
}

void inputDown(SDL_Scancode scancode) {
    memwrite(addr_from_scancode(scancode), 1);
}

void inputUp(SDL_Scancode scancode) {
    memwrite(addr_from_scancode(scancode), 0);
}

void inputMouseDown(int btn) {
    if (btn == 0 || btn == 1) {
        memwrite(button(2 + btn), 1);
    }
}

void inputMouseUp(int btn) {
    if (btn == 0 || btn == 1) {
        memwrite(button(2 + btn), 0);
    }
}

void inputMouseMotion(int x, int y) {
    memwrite(button(0), x);
    memwrite(button(1), HEIGHT - y);
}