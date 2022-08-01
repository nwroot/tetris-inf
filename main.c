#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <SDL2/SDL_mixer.h> 
#include <SDL2/SDL_ttf.h>

#include "tetris.h"
#include "render.h"
#include "util.h"
#include "random.h"
#include "scores.h"

#define RES_X 1366
#define RES_y 768

int main() {
    srand(time(0));
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    Mix_Music *backgroundsound = Mix_LoadMUS("tetris.wav");

    
    SDL_Window *window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1366, 768, SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    


    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    
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
    state.last_tick = 1;
    
    state.gravity_period = 60;
    state.speed_mult = 1;
    
    state.time_stop = false;
    state.just_stopped = false;
    state.just_resumed = false;
    state.time_stop_left = 500;
    state.time_stop_max = 500;

    state.next = standard_pieces[rand() % 7];
    tetris_new_piece(&state);
    bool loop = true;

    Mix_PlayMusic(backgroundsound, -1);
    //-1 plays in loop

    while(loop) {
        if(!tetris_step(&state)) loop = false;
        tetris_render(&state, renderer);

    }

    Mix_FreeMusic(backgroundsound);
    TTF_Quit();
    return 0;
}

