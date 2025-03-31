#include "window.h"

//create window
SDL_Window* init_window() {	
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow(
		"Raycast",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIDTH,
		HEIGHT,
		SDL_WINDOW_SHOWN);
    
    //create renderer for window
    SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	return window;
}

// get renderer
SDL_Renderer* get_renderer(SDL_Window* window) {
  SDL_Renderer* renderer = SDL_GetRenderer(window);
  return renderer;
}

//fetch and load font
TTF_Font* load_font() {
	//initialize TTF, check for errors
	if (TTF_Init() == -1) {
		printf("TTF Initialization Failed: %s/n", TTF_GetError());
		return NULL;
	};
	TTF_Font* font = TTF_OpenFont("Roboto-Regular.ttf", 25);
	if (!font) {
		printf("font not loaded\n");
	}
	return font;
}
