#include "crane.h"

void init_crane(struct Crane *crane, SDL_Renderer *renderer) {
	int texture_w, texture_h;

	crane->texture = IMG_LoadTexture(renderer, "res/crane.png");
	SDL_QueryTexture(crane->texture, NULL, NULL, &texture_w, &texture_h);	 

	crane->dstrect.x = 0;
	crane->dstrect.y = 0;
	crane->dstrect.w = texture_w;
	crane->dstrect.h = texture_h;
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