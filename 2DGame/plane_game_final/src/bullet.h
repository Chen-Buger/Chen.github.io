#pragma once

#include<easyx.h>
#include"sprite.h"

struct bullet {
	struct sprite super;
	IMAGE* imgBullet;
	IMAGE* imgBulletMask;
};

void bulletInit(struct bullet*);
void bulletDestroy(struct bullet*);