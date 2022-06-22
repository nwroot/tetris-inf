#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

#include "util.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
    
    SDL_Window *window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    SDL_Texture *bg = load_texture_from_file("assets/udec.png", renderer);
    SDL_Texture *object = load_texture_from_file("assets/tetromino_2x2.png", renderer);
    
    SDL_Rect pos;
   	pos.x = 640/2;
   	pos.y = 0;
   	pos.w = 40;
   	pos.h = 40;
    
    bool loop = true;
    while(loop) {
        SDL_RenderClear(renderer);
        
        SDL_Event event;
        if(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                loop = false;
            } else if(event.type == SDL_KEYDOWN) {
            	switch(event.key.keysym.sym) {
            		case SDLK_UP:
            			pos.y += 1;
            			break;
            		case SDLK_DOWN:
            			pos.y -= 1;
            			break;
            		case SDLK_RIGHT:
            			pos.x += 1;
            			break;
            		case SDLK_LEFT:
            			pos.x -= 1;
            			break;
            		case SDLK_SPACE:
            			pos.x = 640/2;
            			pos.y = 0;
            		//default:
            	}
            }
        }
        
        pos.y += 1;
        SDL_RenderCopy(renderer, bg, NULL, NULL);
        SDL_RenderCopy(renderer, object, NULL, &pos);
        
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    return 0;
}

