#ifndef PLAYER_H
#define PLAYER_H
#include "main.h"

struct Player {
	SDL_Texture *sprite_sheet;
	SDL_Rect frame, dstrect;
	bool jumping;
	Uint32 l_upd_time_hrz, l_upd_time_vrt, l_upd_time_jmp;
	int sheet_w, sheet_h, num_frames_vert, num_frames_horz, velocity, jmp_vel;
};

void init_player(struct Player *player, char *texture_path, 
				 int frames_x, int frames_y, SDL_Renderer *renderer);

#endif