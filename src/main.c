#include "main.h"
#include "player.h"
#define WINDOW_WIDTH 768
#define WINDOW_HEIGHT 512

int main() {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);
	SDL_Window* window = SDL_CreateWindow("Stack Attack Reborn",
						dm.w / 2 - WINDOW_WIDTH / 2, 
						dm.h / 2 - WINDOW_HEIGHT / 2, 
						WINDOW_WIDTH, WINDOW_HEIGHT, 
						0);
	
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 68, 202, 255, 0);

	bool running = true;

	if(window == NULL) {
		printf("Window creation failed!\n");
		return 0;
	}

	struct Player player;
	init_player(&player, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 
			   "res/builder_sprite_sheet.png", 5, 1, renderer);

	SDL_Event event;
	while(running) {
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
				running = false;
			}
		}

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, player.sprite_sheet, 
					   &player.frame, &player.dstrect);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
