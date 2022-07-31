#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

#include "tetris.h"
#include "render.h"
#include "util.h"
#include "random.h"

#define RES_X 1366
#define RES_y 768

int main() {
    srand(time(0));
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
    
    SDL_Window *window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1366, 768, SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    struct tetris_state state;
    state.grid = malloc(sizeof(struct tetris_slot) * 16 * 10);
    
    memset(state.grid, 0, sizeof(struct tetris_slot) * 16 * 10);
    state.width = 10;
    state.height = 16;
    
    state.score = 0;
    state.lines = 0;
    state.level = 0;
    state.res_x = 1366;
    state.res_y = 768;
    
    state.last_tick_ms = 0;
    state.last_tick = 0;

    state.curr = standard_pieces[1];
    bool loop = true;
    while(loop) {
        if(!tetris_step(&state)) loop = false;
        tetris_render(&state, renderer);
    }
    return 0;
}

