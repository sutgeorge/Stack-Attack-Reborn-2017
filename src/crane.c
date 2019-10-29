#include "crane.h"
#include "block.h"

void init_crane(struct Crane *crane, SDL_Renderer *renderer) {
	/**
	Initializes the crane by setting its properties with initial values.
	The crane will be positioned at the beginning out of the borders of
	the window.
	**/
	int texture_w, texture_h;

	crane->renderer = renderer;
	crane->texture = IMG_LoadTexture(renderer, "res/crane.png");
	SDL_QueryTexture(crane->texture, NULL, NULL, &texture_w, &texture_h);

	crane->dstrect.w = texture_w;
	crane->dstrect.h = texture_h;
        crane->dstrect.x = -texture_w;
        crane->dstrect.y = 0;

        crane->l_upd_time_vrt =
        crane->last_slide_time = SDL_GetTicks();
        crane->sliding = false;
}

void draw_pipe(SDL_Renderer *renderer) {
	/**
	Draws the pipe on which the crane slides.
	**/
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	int pipe_width = 5;
	for(int i = 0; i < pipe_width; i++){
		SDL_RenderDrawLine(renderer, 0, WINDOW_HEIGHT / 30 + i, WINDOW_WIDTH, WINDOW_HEIGHT / 30 + i);
		SDL_RenderDrawLine(renderer, 0, WINDOW_HEIGHT / 15 + i, WINDOW_WIDTH, WINDOW_HEIGHT / 15 + i);
	}
	SDL_SetRenderDrawColor(renderer, DEFAULT_DRAW_COLOR);
}

void draw_crane(struct Crane *crane) {
	/**
	Draws the crane.
	**/
	SDL_RenderCopy(crane->renderer, crane->texture, NULL, &crane->dstrect);
}

void slide(struct Crane *crane) {
	/**
	Slides the crane from the left of the screen to the right and viceversa.
	**/
        if(!crane->sliding)
                return;

	/// Updates the position of the crane only if the last update time happened
	/// more than 1000/UPD milliseconds ago.
        if(SDL_GetTicks() - crane->l_upd_time_vrt > 1000/UPD){
                crane->l_upd_time_vrt = SDL_GetTicks();
                if(crane->dir == RIGHT)
                        crane->dstrect.x += VELOCITY;
                else
                        crane->dstrect.x -= VELOCITY;
        }
}

void drop_crate(struct Crane *crane) {
	/**
	Drops the crate that is being held by the crane.
	**/
        if((crane->dstrect.x > 0 && crane->dstrect.x < WINDOW_HEIGHT)
         || SDL_GetTicks() - crane->last_slide_time < 6000)
                return;

        srand(time(NULL));
	/// Generates a random number and takes a random choice of the crane
	/// direction (so either LEFT or RIGHT). If it is LEFT, then
	/// the crane's x coordinate will be set to the WINDOW_WIDTH initially,
	/// and if the direction is RIGHT, then the x coordinate will be set
	/// to the negative value of the width of the texture. This means that
	/// the crane will be positioned exactly near the borders of the window,
	/// but outside of the window.
        if((crane->dir = rand() % 2) == LEFT)
                crane->dstrect.x = WINDOW_WIDTH;
	else
		crane->dstrect.x = -crane->dstrect.w;

        crane->sliding = true;
        crane->last_slide_time = SDL_GetTicks();
        /**
         * crane->target_x = (rand() % (WINDOW_HEIGHT / BLOCK_SIZE))
         * ...
	 * struct Block
 	crane->target_x = (rand() % (WINDOW_WIDTH / BLOCK_SIZE))
 	printf("The x coordinate of the target point of the crane: ", crane->target_x)
         * **/

	struct Block *block = malloc(sizeof(struct Block));
        crane->target_x = rand() % WINDOW_WIDTH;
        printf("The x coordinate of the target point of the crane: %d\n", crane->target_x);
	free(block);
}
