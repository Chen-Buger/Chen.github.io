#include"background.h"

void backgroundDraw(struct background* b) {
	putimage(0, b->yA, b->imgBackground);
	putimage(0, b->yB, b->imgBackground);
}

void backgroundUpdate(struct background* b) {
	b->yA = b->yA + 1;
	b->yB = b->yB + 1;
	if (b->yA >= 0) {
		b->yA = -750;
		b->yB = 0;
	}
}

void backgroundInit(struct background* b)
{
	b->super.draw = (void (*)(struct sprite*))backgroundDraw;
	b->super.update = (void (*)(struct sprite*))backgroundUpdate;
	b->yA = -750;
	b->yB = 0;
	b->imgBackground = new IMAGE;
	loadimage(b->imgBackground, "img/bg.png");
}
void backgroundDestroy(struct background* b)
{
	delete b->imgBackground;
}
