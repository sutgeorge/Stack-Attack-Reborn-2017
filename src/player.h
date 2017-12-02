#ifndef PLAYER_H
#define PLAYER_H
#include "main.h"

struct Player {
	SDL_Texture *sprite_sheet;
	int sheet_w, sheet_h, 
	num_frames_vert, num_frames_horz, 
	velocity, jmp_vel;
	SDL_Rect frame, dstrect;
};

void init_player(struct Player* player, char *texture_path, 
				 int frames_x, int frames_y, SDL_Renderer *renderer);

#endif