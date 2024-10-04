#pragma once

#include<easyx.h>
#include"sprite.h"

enum heroStatus {
	hero_normal0,
	hero_normal1,
	hero_down0,
	hero_down1,
	hero_down2,
	hero_down3,
	hero_destroy
};

struct hero {
	struct sprite super;
	IMAGE* imgArrHero[6];
	IMAGE* imgArrHeroMask[6];
	enum heroStatus status;
	int life;
	int heroUpdateCnt;
};

void heroInit(struct hero*);
void heroDestroy(struct hero*);