#include <stdio.h>
#include <SDL2/SDL.h>
#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 500

int main() {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Stack Attack Reborn",
										  0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);	
	if(window == NULL) {
		printf("Window creation failed!\n");
		return 0;
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
