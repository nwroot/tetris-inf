#pragma once
#define NO_ROT -621

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <SDL2/SDL.h>

struct tetris_slot {
    uint32_t state: 8;
    uint32_t color: 24;
    //void *custom;
};

/*
struct tetris_piece {
    struct tetris_slot piece[4][4];
}
*/

struct tetris_piece {
    uint32_t piece_def[4][4];
    bool use_custom_rot;
    uint32_t size_x;
    uint32_t size_y;
    uint32_t rot_center_x;
    uint32_t rot_center_y;
};

struct tetris_state {
    struct tetris_slot *grid;
    size_t width;
    size_t height;
    
    
    struct tetris_piece curr;
    struct queue *piece_queue;
    int32_t curr_x;
    int32_t curr_y;
    
    uint32_t score;
    uint32_t lines;
    uint32_t level;
    uint32_t res_x;
    uint32_t res_y;
    
    uint32_t last_tick_ms;
    uint32_t last_tick;
    
    uint32_t gravity_period;
    uint32_t speed_mult;
    //struct tetris_music *music;
};

int tetris_step(struct tetris_state *tetris);
void tetris_render(struct tetris_state *tetris, SDL_Renderer *renderer);
void do_rot_matrix(struct tetris_piece *piece);
extern struct tetris_piece standard_pieces[7];
bool check_collision(struct tetris_piece *piece, struct tetris_state *state);
