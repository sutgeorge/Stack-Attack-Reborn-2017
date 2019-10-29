#include "block.h"

void init_block(struct Block *block, int x, int y, SDL_Renderer *renderer) {
	int texture_w, texture_h;

	block->renderer = renderer;
	block->texture = IMG_LoadTexture(renderer, "res/block.png");
	SDL_QueryTexture(block->texture, NULL, NULL, &texture_w, &texture_h);

	block->dstrect.x = x;
	block->dstrect.y = y;
	block->dstrect.w = texture_w;
	block->dstrect.h = texture_h;
	block->falling = false;
}

void draw_block(struct Block *block) {
	SDL_RenderCopy(block->renderer, block->texture, NULL, &block->dstrect);
}
