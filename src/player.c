#include "player.h"

void init_player(struct Player* player, SDL_Renderer **renderer) {
	int frames_x = 2, frames_y = 3, sheet_w, sheet_h;
	
	player->renderer = renderer;
	player->sprite_sheet = IMG_LoadTexture(*renderer, "res/builder_sprite_sheet.png");
	SDL_QueryTexture(player->sprite_sheet, NULL, NULL, &sheet_w, &sheet_h);	
	player->num_frames_horz = frames_x;
	player->num_frames_vert = frames_y;

	player->frame.w = sheet_w / 2;
	player->frame.h = sheet_h / 3;
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

	player->animate = stand;
}

void draw_player(struct Player *player) {
	player->animate(player);
	SDL_RenderCopy(*(player->renderer), player->sprite_sheet, 
	               &player->frame, &player->dstrect);
}

void animate_left(struct Player *self) {
	if(SDL_GetTicks() - self->l_upd_time_anim_l > 200) {
		self->frame_l = (self->frame_l ? 0 : 1);
		self->frame.x = self->frame.w * self->frame_l;
		self->frame.y = 0;
		self->l_upd_time_anim_l = SDL_GetTicks();
	}
}

void animate_right(struct Player *self) {
	if(SDL_GetTicks() - self->l_upd_time_anim_r > 200) {
		self->frame_r = (self->frame_r ? 0 : 1);
		self->frame.x = self->frame.w * self->frame_r;
		self->frame.y = self->frame.h;
		self->l_upd_time_anim_r = SDL_GetTicks();
	}
}

void stand(struct Player *self) {
	self->frame.x = 0;
	self->frame.y = self->frame.h * 2;
}
