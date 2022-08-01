#pragma once

#include "tetris.h"
#include "SDL2/SDL.h"

void draw_bg(struct tetris_state *state, SDL_Renderer *renderer);
void draw_grid(struct tetris_state *state, SDL_Renderer *renderer, bool draw_curr, bool draw_stop_bar);


