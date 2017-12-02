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

	init_player(player, *renderer);
	return true;
}

static void __handle_input(struct Player *player, bool *loop) {
	const Uint8 *key_state = SDL_GetKeyboardState(NULL);
	SDL_Event event;

	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {
			*loop = false;
		}
	}
	
	if(SDL_GetTicks() - player->l_upd_time_jmp > 500 && key_state[SDL_SCANCODE_W]) {
		player->jumping = true;
		player->l_upd_time_jmp = SDL_GetTicks();
	}

	if(player->jumping) {
		if(player->dstrect.y + player->frame.h > WINDOW_HEIGHT) {
			player->dstrect.y = WINDOW_HEIGHT - player->frame.h;
			player->jmp_vel = JMP_VEL;
			player->jumping = false;
		}

		if(SDL_GetTicks() - player->l_upd_time_vrt > 1000/UPD) {
			player->dstrect.y -= player->jmp_vel;
			player->jmp_vel -= 1;
			player->l_upd_time_vrt = SDL_GetTicks();
		}
	}

	if(key_state[SDL_SCANCODE_A] && SDL_GetTicks() - player->l_upd_time_hrz > 1000/UPD) {
		player->dstrect.x -= player->velocity;
		player->l_upd_time_hrz = SDL_GetTicks();
	}

	if(key_state[SDL_SCANCODE_D] && SDL_GetTicks() - player->l_upd_time_hrz > 1000/UPD) {
		player->dstrect.x += player->velocity;
		player->l_upd_time_hrz = SDL_GetTicks();
	}
}

static void __render(SDL_Renderer *renderer, struct Player *player, Uint32 *last_upd_time) {
	if(SDL_GetTicks() - *last_upd_time > 1000/FPS) {
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, player->sprite_sheet, 
						   &player->frame, &player->dstrect);
		SDL_RenderPresent(renderer);
		*last_upd_time = SDL_GetTicks();
	}
}

static void __exit(SDL_Window *window) {
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main() {
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	Uint32 frame_rate_upd_time = SDL_GetTicks();  
	struct Player player;

	if(!__init(&window, &renderer, &player))
		return 0;

	bool running = true;

	while(running) {		
		__handle_input(&player, &running);
		__render(renderer, &player, &frame_rate_upd_time);
	}

	__exit(window);
	return 0;
}
