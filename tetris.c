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
    tetris->just_stopped = false;
    tetris->just_resumed = false;
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
                        if(tetris->time_stop) {
                            tetris->curr_y -= 1;
                            int res = check_collision(&tetris->curr, tetris);
                            if(res == 2 || res == 3) tetris->curr_y += 1;
                        }
                        break;
                    case SDLK_LEFT:
                        tetris->curr_x -= 1;
                        if(check_collision(&tetris->curr, tetris)) tetris->curr_x += 1;
                        break;
                    case SDLK_RIGHT:
                        tetris->curr_x += 1;
                        if(check_collision(&tetris->curr, tetris)) tetris->curr_x -= 1;
                        break;
                    case SDLK_DOWN:
                        if(tetris->time_stop) {
                            tetris->curr_y += 1;
                            int res = check_collision(&tetris->curr, tetris);
                            if(res == 2 || res == 3) tetris->curr_y -= 1;
                        }
                        break;
                    case SDLK_q:
                        tetris->time_stop = !tetris->time_stop;
                        if(!tetris->time_stop) tetris->just_resumed = true;
                        else tetris->just_stopped = true;
                        break;
                    case SDLK_SPACE:
                        do_rot_matrix(&tetris->curr);
                        if(check_collision(&tetris->curr, tetris)) {
                            do_rot_matrix(&tetris->curr);
                            do_rot_matrix(&tetris->curr);
                            do_rot_matrix(&tetris->curr);
                        }
                        break;
                }
                break;
        }
    }
    
    const uint8_t *keys = SDL_GetKeyboardState(NULL);
    
    if(keys[SDL_SCANCODE_DOWN] && !tetris->time_stop) tetris->speed_mult = 6;
    
    if(tetris->time_stop_left <= 0) tetris->time_stop = 0;
        
    printf("Tick: %d, Speed: %d, Mult: %d, Stop: %d, Stop Left: %d\n", tetris->last_tick, tetris->gravity_period, tetris->speed_mult, tetris->time_stop, tetris->time_stop_left);
    // move piece
    if(!tetris->time_stop && !tetris->just_resumed && tetris->last_tick % (tetris->gravity_period / tetris->speed_mult) == 0) {
        tetris->curr_y += 1;
        int res = check_collision(&tetris->curr, tetris);
        if(res == 1 || res == 2) { // settle
            tetris->curr_y -= 1;
            tetris_settle(tetris);
            tetris_clear_lines(tetris);
            tetris_new_piece(tetris);
        }
    } else if(tetris->just_resumed) {
        int res = check_collision(&tetris->curr, tetris);
        if(res == 1 || res == 2) {
            tetris_settle(tetris);
            tetris_clear_lines(tetris);
            tetris_new_piece(tetris);
        }
    }
    if(tetris->time_stop) tetris->time_stop_left--;
    tetris->speed_mult = 1;
    tetris->last_tick++;
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

int tetris_clear_lines(struct tetris_state *tetris) {
    int lines = 0;
    for(int i = 0; i < tetris->height; i++) {
        bool line_complete = true;
        for(int j = 0; j < tetris->width; j++) {
            if(!tetris->grid[i * tetris->width + j].state) {
                line_complete = false;
                break;
            }
        }
        if(line_complete) {
            lines++;
            for(int j = i - 1; j >= 0; j--) {
                for(int k = 0; k < tetris->width; k++) {
                    tetris->grid[tetris->width * (j + 1) + k] = tetris->grid[tetris->width * j + k];
                }
            }
        }
    }
    tetris->lines += lines;
    tetris->score += lines * 100;
    
    printf("Lines: %d, Score: %d\n", tetris->lines, tetris->score);
    return lines;
}

void tetris_new_piece(struct tetris_state *tetris) {
    tetris->curr = standard_pieces[rand() % 7];
    tetris->curr_x = tetris->width/2;
    tetris->curr_y = 0;
}

void tetris_render(struct tetris_state *tetris, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    draw_bg(tetris, renderer);
    draw_grid(tetris, renderer, 1, 1);
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
    if(piece->rot_center_x == NO_ROT) return;
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
                //printf("OOB\n");
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
                //printf("Collision\n");
                return 1;
            }
        }
    }

    return 0;
}
        
