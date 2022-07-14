#include "render.h"

void draw_grid(struct tetris_state *state, SDL_Renderer *renderer, bool draw_curr) {
    SDL_Rect outline;
    
    outline.x = state->res_x/20;
    outline.y = state->res_y/20;
    
    outline.h = state->res_y - (state->res_y/20 * 2);
    outline.w = (outline.h / state->height) * state->width;
    
    
    outline.x = (state->res_x - outline.w)/2;
    outline.y = (state->res_y - outline.h)/2;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &outline);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &outline);
    
    int square_sz = outline.h / state->height;
    
    for(int i = 0; i < state->width; i++) {
        SDL_RenderDrawLine(renderer, outline.x + (i * square_sz), outline.y, outline.x + (i * square_sz), outline.y + outline.h);
    }
    
        
    for(int i = 0; i < state->height; i++) {
        SDL_RenderDrawLine(renderer, outline.x , outline.y + (i * square_sz), outline.x + outline.w, outline.y  + (i * square_sz));
    }
    
    for(int i = 0; i < state->height; i++) {
        for(int j = 0; j < state->width; j++) {
            if(state->grid[i * (state->width) + j].state != 0) {
                SDL_Rect piece;
                piece.x = outline.x + j * square_sz;
                piece.y = outline.y + i * square_sz;
                piece.w = square_sz;
                piece.h = square_sz;
                SDL_RenderFillRect(renderer, &piece);
            }
        }
    }
    
    if(draw_curr) {
        SDL_Rect piece;
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                if(state->curr.piece_def[i][j] != 0) {
                
                    piece.x = outline.x + j * square_sz;
                    piece.y = outline.y + i * square_sz;
                    piece.w = square_sz;
                    piece.h = square_sz;
                    SDL_RenderFillRect(renderer, &piece);
                }
            }
        }
        //SDL_RenderFillRect(renderer, &piece);
    }
    
    return;
}
