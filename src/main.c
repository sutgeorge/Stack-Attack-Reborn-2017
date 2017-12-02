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

static void __handle_input(struct Player *player, Uint32 *l_upd_time_hrz, 
	Uint32 *l_upd_time_vrt, Uint32 *l_upd_time_jmp, bool *jumping, bool *loop) {
	
	const Uint8 *key_state = SDL_GetKeyboardState(NULL);
	SDL_Event event;

	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {
			*loop = false;
		}
	}
	
	if(SDL_GetTicks() - *l_upd_time_jmp > 500 && key_state[SDL_SCANCODE_W]) {
		*jumping = true;
		*l_upd_time_jmp = SDL_GetTicks();
	}

	if(*jumping) {
		if(player->dstrect.y + player->frame.h > WINDOW_HEIGHT) {
			player->dstrect.y = WINDOW_HEIGHT - player->frame.h;
			player->jmp_vel = JMP_VEL;
			*jumping = false;
		}

		if(SDL_GetTicks() - *l_upd_time_vrt > 1000/FPS) {
			player->dstrect.y -= player->jmp_vel;
			player->jmp_vel -= 1;
			*l_upd_time_vrt = SDL_GetTicks();
		}
	}

	if(key_state[SDL_SCANCODE_A] && SDL_GetTicks() - *l_upd_time_hrz > 1000/FPS) {
		player->dstrect.x -= player->velocity;
		*l_upd_time_hrz = SDL_GetTicks();
	}

	if(key_state[SDL_SCANCODE_D] && SDL_GetTicks() - *l_upd_time_hrz > 1000/FPS) {
		player->dstrect.x += player->velocity;
		*l_upd_time_hrz = SDL_GetTicks();
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

	bool running = true, jumping = false;
	Uint32 input_upd_time_hrz, input_upd_time_vrt, input_upd_time_jmp;
	input_upd_time_vrt = input_upd_time_hrz = input_upd_time_jmp = SDL_GetTicks();

	while(running) {		
		__handle_input(&player, &input_upd_time_hrz, &input_upd_time_vrt,
			&input_upd_time_jmp, &jumping, &running);
		__render(renderer, &player);
	}

	__exit(window);
	return 0;
}
