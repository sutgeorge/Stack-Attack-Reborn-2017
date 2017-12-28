#include "player.h"

void init_player(struct Player* player, SDL_Renderer *renderer) {
	int frames_x = 2, frames_y = 3, sheet_w, sheet_h;
    
	player->renderer = renderer;
	player->sprite_sheet = IMG_LoadTexture(renderer, "res/builder_sprite_sheet.png");
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
	player->ground_level = WINDOW_HEIGHT;
	player->stepped_off = false;
	player->on_block = false;
	player->in_air = false;
}

void draw_player(struct Player *player) {
	player->animate(player);
	SDL_RenderCopy(player->renderer, player->sprite_sheet,
	               &player->frame, &player->dstrect);
}

void player_block_collision(struct Player *player, struct Block *block) {
	int player_right = player->dstrect.x + player->dstrect.w - player->dstrect.w / 6,
	    player_left = player->dstrect.x + player->dstrect.w / 6,
	    player_top = player->dstrect.y,
	    player_bottom = player->dstrect.y + player->dstrect.h,
	    block_right = block->dstrect.x + block->dstrect.w,
	    block_left = block->dstrect.x,
	    block_top = block->dstrect.y,
	    block_bottom = block->dstrect.y + block->dstrect.h,
	    offset_side = 30;

	if(player_bottom >= block_top + offset_side && player_bottom <= block_bottom){
		if(player_right >= block_left && player_right <= block_left + offset_side)
			block->dstrect.x++;

		if(player_left <= block_right && player_left >= block_right - offset_side)
			block->dstrect.x--;
	}

	if(player_bottom >= block_top && player_bottom <= block_top + offset_side &&
	   ((player_left >= block_left && player_left <= block_right) ||
	   	(player_right >= block_left && player_right <= block_right))) {
		player->ground_level = block_top;
		if(!player->on_block)
			printf("on:%d\n", player->ground_level);
		player->on_block = true;
	} else if(player->on_block) {
		player->ground_level = WINDOW_HEIGHT;
		player->stepped_off = true;
		printf("off:%d\n", player->ground_level);
		player->on_block = false;
		player->in_air = true;
	}
}

void jump(struct Player *player) {
	if(player->jumping) {
		if(player->dstrect.y + player->frame.h <= player->ground_level) {
			if(SDL_GetTicks() - player->l_upd_time_vrt > 1000/UPD) {
				player->l_upd_time_vrt = SDL_GetTicks();
				player->dstrect.y -= player->jmp_vel;
				player->jmp_vel -= 1;
			}
		} else {
			player->dstrect.y = player->ground_level - player->frame.h;
			player->jmp_vel = JMP_VEL;
			player->jumping = false;
		}
	}
}

void fall(struct Player *player) {
	if(player->in_air) {
		if(player->dstrect.y + player->frame.h <= player->ground_level) {
			if(SDL_GetTicks() - player->l_upd_time_vrt > 1000/UPD) {
				player->l_upd_time_vrt = SDL_GetTicks();
				player->dstrect.y += player->jmp_vel;
				player->jmp_vel += 1;
			}
		} else {
			player->dstrect.y = player->ground_level - player->frame.h;
			player->jmp_vel = JMP_VEL;
			player->jumping = false;
			player->in_air = false;
		}
	}
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
