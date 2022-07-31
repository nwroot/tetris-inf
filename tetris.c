#include "tetris.h"
#include "render.h"
#include <SDL2/SDL.h>

#define MS_PER_TICK 10

struct tetris_piece standard_pieces[7] = {
{
    .piece_def = {
        { 0, 0, 0, 0 },
        { 1, 1, 1, 1 },
        { 0, 0, 0, 0,},
        { 0, 0, 0, 0,}
    },
    .use_custom_rot = false,
    .size_x = 4,
    .size_y = 4
},
{
    .piece_def = {
        { 1, 0, 0 ,0 },
        { 1, 1, 1, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
    },
    .use_custom_rot = true,
    .size_x = 3,
    .size_y = 3,
    .rot_center_x = 1,
    .rot_center_y = 1
},
{
    .piece_def = {
        { 0, 0, 1 ,0 },
        { 1, 1, 1, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
    },
    .use_custom_rot = true,
     .size_x = 3,
    .size_y = 3,
    .rot_center_x = 1,
    .rot_center_y = 1
},

{
    .piece_def = {
        { 1, 1, 0 ,0 },
        { 1, 1, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
    },
    .size_x = 2,
    .size_y = 2,
    .use_custom_rot = true,
    .rot_center_x = NO_ROT,
    .rot_center_y = NO_ROT
},
{
    .piece_def = {
        { 0, 1, 1 ,0 },
        { 1, 1, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
    },
    .use_custom_rot = true,
     .size_x = 3,
    .size_y = 3,
    .rot_center_x = 1,
    .rot_center_y = 1
},
{
    .piece_def = {
        { 0, 1, 0 ,0 },
        { 1, 1, 1, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
    },
    .use_custom_rot = true,
    .size_x = 3,
    .size_y = 3,
    .rot_center_x = 1,
    .rot_center_y = 1
},
{
    .piece_def = {
        { 1, 1, 0 ,0 },
        { 0, 1, 1, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
    },
    .use_custom_rot = true,
    .size_x = 3,
    .size_y = 3,
    .rot_center_x = 1,
    .rot_center_y = 1
}
};

int tetris_step(struct tetris_state *tetris) {
    if(SDL_GetTicks() <= tetris->last_tick_ms + MS_PER_TICK) {
        return 2;
    }
    
    SDL_Event event;
    if(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                return 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        // Disallowed
                        break;
                    case SDLK_LEFT:
                        tetris->curr_x -= 1;
                        if(check_collision(&tetris->curr, tetris)) tetris->curr_x += 1;
                        break;
                    case SDLK_RIGHT:
                        tetris->curr_x += 1;
                        if(check_collision(&tetris->curr, tetris)) tetris->curr_x -= 1;
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
                        break;
                }
                break;
        }
    }
    tetris->last_tick++;
    
    // move piece
    if(tetris->last_tick % 20 == 0) {
        tetris->curr_y += 1;
        int res = check_collision(&tetris->curr, tetris);
        if(res == 1 || res == 2) { // settle
            tetris->curr_y -= 1;
            tetris_settle(tetris);
            tetris_clear_lines(tetris);
            tetris_new_piece(tetris);
        }
    }
    tetris->last_tick_ms = SDL_GetTicks();
    return 1;  
}

void tetris_settle(struct tetris_state *tetris) {
    for(int i = 0; i < tetris->curr.size_y; i++) {
        for(int j = 0; j < tetris->curr.size_x; j++) {
            if(tetris->curr.piece_def[i][j]) {
                tetris->grid[(tetris->curr_y + i) * tetris->width + (tetris->curr_x + j)].state = 1;
            }
        }
    }
}

void tetris_clear_lines(struct tetris_state *tetris) {
    for(int i = 0; i < tetris->height; i++) {
        bool line_complete = true;
        for(int j = 0; j < tetris->width; j++) {
            if(!tetris->grid[i * tetris->width + j].state) {
                line_complete = false;
                break;
            }
        }
        if(line_complete) {
            for(int j = i - 1; j >= 0; j--) {
                for(int k = 0; k < tetris->width; k++) {
                    tetris->grid[tetris->width * (j + 1) + k] = tetris->grid[tetris->width * j + k];
                }
            }
        }
    }
}

void tetris_new_piece(struct tetris_state *tetris) {
    tetris->curr = standard_pieces[rand() % 7];
    tetris->curr_x = tetris->width/2;
    tetris->curr_y = 0;
}

void tetris_render(struct tetris_state *tetris, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    draw_grid(tetris, renderer, 1);
}

void rotar(int *mat, int n){ 
 int helper[n][n]; 
 for(int i = 0; i<n; ++i){ 
  for(int j = 0; j<n; ++j){ 
   helper[i][j] = mat[i * n + j]; 
  } 
 } 
 for(int i = 0; i<n; ++i){ 
  for(int j = n-1; j>=0; --j){ 
   mat[i * n + j] = helper[n-1-j][i]; 
  } 
 } 
} 
 
 
void do_rot_matrix(struct tetris_piece *piece) {
    if(piece->use_custom_rot) {
        if(piece->rot_center_x == 1 && piece->rot_center_y == 1) {
            int mat[3][3];
            
            for(int i = 0; i < 3; i++) memcpy(mat[i], piece->piece_def[i], sizeof(uint32_t) * 3);
            rotar((int *)mat, 3);
            
            for(int i = 0; i < 3; i++) memcpy(piece->piece_def[i], mat[i], sizeof(uint32_t) * 3);
        }
    } else {
        rotar((int *)piece->piece_def, 4);
    }
}


// returns 0 on correct status
// returns 1 on collision with other pieces
// returns 2 on collisions with bottom of grid
// returns 3 on horizontal out of bounds
bool check_collision(struct tetris_piece *piece, struct tetris_state *state) {
    for(int i = 0; i < piece->size_y; i++) {
        for(int j = 0; j < piece->size_x; j++) {
            if(piece->piece_def[i][j] && state->curr_y + i >= state->height) return 2;
            if(piece->piece_def[i][j] && (state->curr_x + j < 0 || state->curr_x + j >= state->width || state->curr_y + i < 0 || state->curr_y + i >= state->height)) {
                printf("OOB\n");
                return 3;
            }
        }
    }
    if(state->curr_x < 0 || (state->curr_x + piece->size_x) > state->width || (state->curr_y + piece->size_y) > state->height || state->curr_y < 0) {
        //printf("OOB_old\n");
        //return 1;
    }
    for(int i = 0; i < piece->size_y; i++) {
        for(int j = 0; j < piece->size_x; j++) {
            if(piece->piece_def[i][j] && state->grid[(state->curr_y + i) * state->width + (state->curr_x + j)].state) {
                printf("Collision\n");
                return 1;
            }
        }
    }

    return 0;
}
        
