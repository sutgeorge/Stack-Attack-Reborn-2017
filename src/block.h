#ifndef BLOCK_H
#define BLOCK_H
#include "main.h"

struct Block {
	SDL_Texture *texture;
	SDL_Rect dstrect;
	SDL_Renderer *renderer;
};

void init_block(struct Block *block, SDL_Renderer *renderer);

void draw_block(struct Block *block);

#endif