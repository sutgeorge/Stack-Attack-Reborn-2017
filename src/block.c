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

struct Block *create_block() {
	/**
	Allocates memory for a Block structure and returns the pointer to
	this memory location.
	**/
	struct Block *block = malloc(sizeof(struct Block));
	return block;
}

void delete_block(struct Block *block) {
	/**
	Deallocates the memory allocated for the Block struct.
	**/
	free(block);
}

void remove_block_from_array(int block_index, struct Block *blocks[], int *number_of_blocks) {
	/**
	Removes the block with the index "block_index" from the array "blocks"
	**/

	delete_block(blocks[block_index]);
	blocks[block_index] = NULL;

	/// This moves all the blocks in the array with one position to the left
	for (int i = (block_index + 1); i < (*number_of_blocks); i++) {
		blocks[i - 1] = blocks[i];
	}

	(*number_of_blocks)--;
}

void add_block_to_block_array(struct Block *block, struct Block *blocks[], int *number_of_blocks) {
	/**
	Adds the block given in the first parameter to the array of blocks "blocks[]"
	**/

	if (*number_of_blocks < 0)
		return;
	/// ... for avoiding undefined behaviour in case the number_of_blocks
	/// parameter will be negative....

	blocks[*number_of_blocks] = block;
	(*number_of_blocks)++;
}
