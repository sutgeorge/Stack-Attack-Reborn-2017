#include "main.h"
#include "player.h"
#include "crane.h"
#include "block.h"

/**
	TODO: Implement a linked list of Block structs
	      (Another idea would be to make an array of Block structs and
      	       keep a variable which holds the number of blocks that have been
       	       inserted into the array) ---> IN PROGRESS
	TODO: Draw every block in the array (THE ARRAY SHOULD BE AN ARRAY OF
	      POINTERS TO BLOCK STRUCTS SO THAT YOU CAN APPLY DELETION FUNCTION
      	      ON SPECIFIC INDEXES OF THE ARRAY!!!!!)
	TODO: Make a function for deleting a block
      	TODO: Make a function for removing a block from the array
	TODO: Change <drop_crate> function name to <generate_crate>
**/

static bool __init(SDL_Window **window, SDL_Renderer **renderer,
	               struct Player *player, struct Crane *crane,
	               struct Block *block, struct Block *blocks[]) {
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
		if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
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

static void __delete_blocks_from_array(struct Block *blocks[], int *number_of_blocks) {
	/**
	Deletes all blocks from the array of blocks.
	**/

	while (*number_of_blocks > 0) {
		remove_block_from_array(*number_of_blocks - 1, blocks, number_of_blocks);
	}
}

static void __test() {

	/**
	Some stupid function for debugging
	(I've used it to find out the size in bytes of a Block struct)
	**/
	printf("-------------------------------------------------------\n");
	printf("The size of a Block structure: %d\n", sizeof(struct Block));
	printf("-------------------------------------------------------\n");
}

int main() {
	__test();
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	Uint32 frame_rate_upd_time = SDL_GetTicks();
	struct Player player;
	struct Crane crane;
	struct Block block;
	struct Block *blocks[200];
	int number_of_blocks = 0;

	if(!__init(&window, &renderer, &player, &crane, &block, blocks))
		return 0;

	bool running = true;

	while(running) {
		__handle_input(&player, &running);
		player_block_collision(&player, &block);
		jump(&player);
		fall(&player);
                slide(&crane);
                drop_crate(&crane, blocks, &number_of_blocks);
		__render(renderer, &player, &crane, &block, &frame_rate_upd_time);
	}

	__delete_blocks_from_array(blocks, &number_of_blocks);
	__exit(window);
	return 0;
}
