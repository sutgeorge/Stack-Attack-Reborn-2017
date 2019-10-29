#ifndef BLOCK_H
#define BLOCK_H
#include "main.h"

struct Block {
	SDL_Texture *texture;
	SDL_Rect dstrect;
	SDL_Renderer *renderer;
	bool falling;  /// True if the block is in the air and currently falling
		       /// and false if the block is in a stationary state.
};

void init_block(struct Block *block, int x, int y, SDL_Renderer *renderer);

void draw_block(struct Block *block);

#endif
