#include "player.h"

void init_player(struct Player* player, SDL_Renderer *renderer) {
	int frames_x = 2, frames_y = 3;
	player->sprite_sheet = IMG_LoadTexture(renderer, "res/builder_sprite_sheet.png");
	SDL_QueryTexture(player->sprite_sheet, NULL, NULL, &player->sheet_w, &player->sheet_h);	
	player->num_frames_horz = frames_x;
	player->num_frames_vert = frames_y;

	player->frame.w = player->sheet_w / 2;
	player->frame.h = player->sheet_h / 3;
	player->frame.x = 0;
	player->frame.y = player->frame.h * 2;

	player->dstrect.x = WINDOW_WIDTH / 2 - player->frame.w / 2;
	player->dstrect.y = WINDOW_HEIGHT - player->frame.h; 
	player->dstrect.w = player->frame.w;
	player->dstrect.h = player->frame.h;

	player->velocity = VELOCITY;
	player->jmp_vel = JMP_VEL;
	player->l_upd_time_hrz = 
	player->l_upd_time_vrt = 
	player->l_upd_time_jmp = SDL_GetTicks();
	player->jumping = false;
}
