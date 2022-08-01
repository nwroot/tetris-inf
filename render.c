#include "render.h"
#include "util.h"

static SDL_Texture *bg = NULL;

void draw_bg(struct tetris_state *state, SDL_Renderer *renderer) {
    if(!bg) {
        bg = load_texture_from_file("assets/bg.png", renderer);
    }
    
    SDL_RenderCopy(renderer, bg, NULL, NULL);
}

void draw_grid(struct tetris_state *state, SDL_Renderer *renderer, bool draw_curr, bool draw_stop_bar) {
    SDL_Rect outline;
    
    //outline.x = state->res_x/20;
    //outline.y = state->res_y/20;
    
    outline.h = state->res_y - (state->res_y/20 * 2);
    outline.w = (outline.h / state->height) * state->width;

    outline.x = (state->res_x - outline.w)/2;
    outline.y = (state->res_y - outline.h)/2;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 192);
    SDL_RenderFillRect(renderer, &outline);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 192);
    SDL_RenderDrawRect(renderer, &outline);
    
    int square_sz = outline.h / state->height;
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for(int i = 0; i < state->width; i++) {
        SDL_RenderDrawLine(renderer, outline.x + (i * square_sz), outline.y, outline.x + (i * square_sz), outline.y + outline.h);
    }
    
        
    for(int i = 0; i < state->height; i++) {
        SDL_RenderDrawLine(renderer, outline.x , outline.y + (i * square_sz), outline.x + outline.w, outline.y  + (i * square_sz));
    }
    
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    for(int i = 0; i < state->height; i++) {
        for(int j = 0; j < state->width; j++) {
            if(state->grid[i * (state->width) + j].state != 0) {
                SDL_Rect piece;
                piece.x = outline.x + j * square_sz + 1;
                piece.y = outline.y + i * square_sz + 1;
                piece.w = square_sz - 1;
                piece.h = square_sz - 1;
                SDL_RenderFillRect(renderer, &piece);
            }
        }
    }
    
    if(draw_curr) {
        SDL_SetRenderDrawColor(renderer, 0, 70, 170, 255);
        SDL_Rect piece;
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                if(state->curr.piece_def[i][j] != 0) {
                    piece.x = outline.x + (j + state->curr_x) * square_sz + 1;
                    piece.y = outline.y + (i + state->curr_y) * square_sz + 1;
                    piece.w = square_sz - 1;
                    piece.h = square_sz - 1;
                    SDL_RenderFillRect(renderer, &piece);
                }
            }
        }
    }
    if(draw_stop_bar) {
        SDL_Rect rect;
        rect.x = (state->res_x / 20);
        rect.y = (state->res_y / 20) * 18;
        rect.w = (state->res_x / 20) * 2;
        rect.h = (state->res_y / 20) / 2;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &rect);
        
        rect.x++;
        rect.y++;
        rect.w -= 2;
        rect.h -= 2;
        
        double res = ((double) state->time_stop_left) / state->time_stop_max;
        rect.w = rect.w * res;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &rect);
    }
    
    SDL_RenderPresent(renderer);
    return;
}
