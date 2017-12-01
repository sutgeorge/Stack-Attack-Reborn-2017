#include "main.h"
#include "player.h"

static bool __init(SDL_Window **window, SDL_Renderer **renderer, struct Player *player) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);
	*window = SDL_CreateWindow("Stack Attack Reborn",
						dm.w / 2 - WINDOW_WIDTH / 2, 
						dm.h / 2 - WINDOW_HEIGHT / 2, 
						WINDOW_WIDTH, WINDOW_HEIGHT, 
						0);
	
	if(*window == NULL) {
		printf("Window creation failed!\n");
		return false;
	}

	*renderer = SDL_CreateRenderer(*window, -1, 0);
	
	if(*renderer == NULL) {
		printf("Renderer creation failed!\n");
		return false;
	}

	SDL_SetRenderDrawColor(*renderer, 68, 202, 255, 0);

	init_player(player, "res/builder_sprite_sheet.png", 5, 1, *renderer);
	return true;
}

static void __handle_input(struct Player *player) {
	const Uint8 *key_state = SDL_GetKeyboardState(NULL);
	
	/*   Jumping not implemented yet
	if(key_state[SDL_SCANCODE_W]) {

	}
	*/

	if(key_state[SDL_SCANCODE_A]) {
		player->dstrect.x--;
	}

	if(key_state[SDL_SCANCODE_D]) {
		player->dstrect.x++;
	}

}

static void __render(SDL_Renderer *renderer, struct Player *player) {
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, player->sprite_sheet, 
					   &player->frame, &player->dstrect);
	SDL_RenderPresent(renderer);
}

static void __exit(SDL_Window *window) {
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main() {
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	struct Player player;

	if(!__init(&window, &renderer, &player))
		return 0;

	bool running = true;

	SDL_Event event;
	while(running) {		
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
				running = false;
			}
		}
		__handle_input(&player);
		__render(renderer, &player);
	}

	__exit(window);
	return 0;
}
