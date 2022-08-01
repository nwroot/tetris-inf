#include "render.h"

void draw_grid(struct tetris_state *state, SDL_Renderer *renderer) {
    SDL_Rect outline;
    
    outline.x = state->res_x/20;
    outline.y = state->res_y/20;
    
    outline.h = state->res_y - (state->res_y/20 * 2);
    outline.w = (outline.h / state->height) * state->width;
    
    
    outline.x = (state->res_x - outline.w)/2;
    outline.y = (state->res_y - outline.h)/2;
    SDL_RenderDrawRect(renderer, &outline);
    
    int square_sz = outline.h / state->height;
    
    for(int i = 0; i < state->width; i++) {
        SDL_RenderDrawLine(renderer, outline.x + (i * square_sz), outline.y, outline.x + outline.w, outline.y + outline.w);
    }
    return;
}
