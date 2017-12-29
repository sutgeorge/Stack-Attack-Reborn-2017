#ifndef CRANE_H
#define CRANE_H
#include "main.h"
#include "stdlib.h"
#include "time.h"

struct Crane {
	SDL_Texture *texture;
	SDL_Rect dstrect;
	SDL_Renderer *renderer;
        Uint32 l_upd_time_vrt, last_slide_time;
        bool sliding;
        int target_x;
        enum direction{LEFT, RIGHT} dir;
};

void draw_crane(struct Crane *crane);

void draw_pipe(SDL_Renderer *renderer);

void init_crane(struct Crane *crane, SDL_Renderer *renderer);

void slide(struct Crane *crane);

void drop_crate(struct Crane *crane);

#endif 
