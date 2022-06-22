#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

int main() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    
    SDL_Window *window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    SDL_Surface *surface = IMG_Load("./textura.png");
    if(!surface) {
        printf("error: %s\n", IMG_GetError());
    }
    
    
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    bool loop = true;
    while(loop) {
        SDL_RenderClear(renderer);
        
        
        SDL_Event event;
        if(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                loop = false;
            }
        }
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        
        SDL_RenderPresent(renderer);
    }
    return 0;
}

