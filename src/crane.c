#include "crane.h"

void init_crane(struct Crane *crane, SDL_Renderer *renderer) {
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
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	int pipe_width = 5;
	for(int i = 0; i < pipe_width; i++){
		SDL_RenderDrawLine(renderer, 0, WINDOW_HEIGHT / 30 + i, WINDOW_WIDTH, WINDOW_HEIGHT / 30 + i);
		SDL_RenderDrawLine(renderer, 0, WINDOW_HEIGHT / 15 + i, WINDOW_WIDTH, WINDOW_HEIGHT / 15 + i);
	}
	SDL_SetRenderDrawColor(renderer, DEFAULT_DRAW_COLOR);
}

void draw_crane(struct Crane *crane) {
	SDL_RenderCopy(crane->renderer, crane->texture, NULL, &crane->dstrect);
}

void slide(struct Crane *crane) {
        if(!crane->sliding)
                return;

        if(SDL_GetTicks() - crane->l_upd_time_vrt > 1000/UPD){
                crane->l_upd_time_vrt = SDL_GetTicks();
                if(crane->dir == RIGHT)
                        crane->dstrect.x += VELOCITY;        
                else
                        crane->dstrect.x -= VELOCITY;
        }        
}

void drop_crate(struct Crane *crane) {  
        if((crane->dstrect.x > 0 && crane->dstrect.x < WINDOW_HEIGHT)
         || SDL_GetTicks() - crane->last_slide_time < 6000)
                return;

        srand(time(NULL));
        crane->dstrect.x = -crane->dstrect.w;

        if((crane->dir = rand() % 2) == LEFT)
                crane->dstrect.x = WINDOW_WIDTH;
        
        crane->sliding = true;
        crane->last_slide_time = SDL_GetTicks();
        /**
         * crane->target_x = (rand() % (WINDOW_HEIGHT / BLOCK_SIZE))
         * ...
         * **/  
}
