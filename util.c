#include "util.h"
#include <SDL2/SDL_image.h>

SDL_Texture *load_texture_from_file(const char *file, SDL_Renderer *renderer) {
	SDL_Surface *surface = IMG_Load(file);
	printf("Error: %s\n", IMG_GetError());
	SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return tex;
}
