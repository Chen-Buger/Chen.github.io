#pragma once

#include"sprite.h"
#include<easyx.h>

struct background {
	struct sprite super;
	int yA;
	int yB;
	IMAGE* imgBackground;
};

void backgroundInit(struct background*);
void backgroundDestroy(struct background*);