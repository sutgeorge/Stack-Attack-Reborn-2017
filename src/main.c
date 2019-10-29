#include "main.h"
#include "player.h"
#include "crane.h"
#include "block.h"

static bool __init(SDL_Window **window, SDL_Renderer **renderer,
	               struct Player *player, struct Crane *crane,
	               struct Block *block) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);
	*window = SDL_CreateWindow("Stack Attack Reborn",
	dm.w / 2 - WINDOW_WIDTH / 2,	/// The position of the window
	dm.h / 2 - WINDOW_HEIGHT / 2,
	WINDOW_WIDTH, WINDOW_HEIGHT,	/// Width and height of the window
	0);	/// WindowFlags are set to 0

	if(*window == NULL) {
		printf("Window creation failed!\n");
		return false;
	}

	*renderer = SDL_CreateRenderer(*window, -1, 0);

	if(*renderer == NULL) {
		printf("Renderer creation failed!\n");
		return false;
	}

	SDL_SetRenderDrawColor(*renderer, DEFAULT_DRAW_COLOR);

	init_player(player, *renderer);
	init_crane(crane, *renderer);
	init_block(block, WINDOW_WIDTH / 4, WINDOW_HEIGHT - 64, *renderer);
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

	if(SDL_GetTicks() - player->l_upd_time_jmp > 500 && !player->in_air && key_state[SDL_SCANCODE_W]) {
		player->jumping = true;
		player->l_upd_time_jmp = SDL_GetTicks();
	}

	if(key_state[SDL_SCANCODE_A]) {
		if(SDL_GetTicks() - player->l_upd_time_hrz > 1000/UPD) {
			player->dstrect.x -= player->velocity;
			player->l_upd_time_hrz = SDL_GetTicks();
			player->animate = animate_left;
		}
	} else if(key_state[SDL_SCANCODE_D]) {
		if(SDL_GetTicks() - player->l_upd_time_hrz > 1000/UPD) {
			player->dstrect.x += player->velocity;
			player->l_upd_time_hrz = SDL_GetTicks();
			player->animate = animate_right;
		}
	} else {
		player->animate = stand;
	}
}

static void __render(SDL_Renderer *renderer, struct Player *player,
	                 struct Crane *crane, struct Block *block,
	                 Uint32 *last_upd_time) {
	if(SDL_GetTicks() - *last_upd_time > 1000/FPS) {
		SDL_RenderClear(renderer);
		draw_player(player);
		draw_pipe(renderer);
		draw_crane(crane);
		draw_block(block);
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
	struct Crane crane;
	struct Block block;

	if(!__init(&window, &renderer, &player, &crane, &block))
		return 0;

	bool running = true;

	while(running) {
		__handle_input(&player, &running);
		player_block_collision(&player, &block);
		jump(&player);
		fall(&player);
                slide(&crane);
                drop_crate(&crane);
		__render(renderer, &player, &crane, &block, &frame_rate_upd_time);
	}

	__exit(window);
	return 0;
}
