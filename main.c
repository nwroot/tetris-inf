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
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
    
    SDL_Window *window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1366, 768, SDL_WINDOW_OPENGL);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    SDL_Texture *bg = load_texture_from_file("assets/udec.png", renderer);
    
    
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
    

    //struct tetris_piece piece = standard_pieces[1];
    struct tetris_piece piece = standard_pieces[randint(0,7)];
    
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            printf("%d ", piece.piece_def[i][j]);
        }
        printf("\n");
    }
    
    do_rot_matrix(&piece);
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            printf("%d ", piece.piece_def[i][j]);
        }
        printf("\n");
    }
    
    //state.curr = standard_pieces[1];
    state.curr = standard_pieces[randint(0,7)];
    
    state.curr_x = 0;
    state.curr_y = 0;
    
    bool loop = true;
    while(loop) {
    	uint32_t start_t = SDL_GetTicks();
        SDL_RenderClear(renderer);
        
        SDL_Event event;
        if(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                loop = false;
            } else if(event.type == SDL_KEYDOWN) {
            	switch(event.key.keysym.sym) {
            		case SDLK_UP:
            			state.curr_y -= 1;
            			if(check_collision(&state.curr, &state)) state.curr_y += 1;
            			break;
            		case SDLK_DOWN:
            			state.curr_y += 1;
            			if(check_collision(&state.curr, &state)) state.curr_y -= 1;
            			break;
            		case SDLK_RIGHT:
            			state.curr_x += 1;
            			if(check_collision(&state.curr, &state)) state.curr_x -= 1;
            			break;
            		case SDLK_LEFT:
            			state.curr_x -= 1;
            			if(check_collision(&state.curr, &state)) state.curr_x += 1;
            			break;
            		case SDLK_SPACE: 
            		    do_rot_matrix(&state.curr);
                        printf("%d /", state.curr_x);
                        if(check_collision(&state.curr, &state)){
                            if(state.curr_x > state.width){
                                printf("left");
                               state.curr_x += 1; 
                            } 
                            if(state.curr_x == 8 && check_collision(&state.curr, &state) || state.curr_x == 7 && check_collision(&state.curr, &state)){
                                printf("right");
                               state.curr_x -= 1;
                            }
                            if(check_collision(&state.curr, &state)){
                                do_rot_matrix(&state.curr);
                                do_rot_matrix(&state.curr);
                                do_rot_matrix(&state.curr);
                            }
                        }
                        


            		//default:
                        
            	}
            }
        }
        check_collision(&state.curr, &state);
        SDL_RenderCopy(renderer, bg, NULL, NULL); // replace by draw_bg()
        draw_grid(&state, renderer, true);
        //SDL_RenderCopy(renderer, object, NULL, &pos);
        
        SDL_RenderPresent(renderer);
        
        uint32_t end_t = SDL_GetTicks();
        if(end_t - start_t < 16) {
        	SDL_Delay(end_t - start_t);
       	}
        //SDL_Delay(16);
    }
    return 0;
}

