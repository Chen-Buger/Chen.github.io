#include"hero.h"
#include"image.h"
#include<stdio.h>

enum heroStatus heroStatusSqauence[7] = {
	hero_normal0,
	hero_normal1,
	hero_down0,
	hero_down1,
	hero_down2,
	hero_down3,
	hero_destroy
};

void heroDraw(struct hero* h) {
	putTransparentImage(h->super.x, h->super.y, h->imgArrHeroMask[h->status], h->imgArrHero[h->status]);
}

void heroUpdate(struct hero* h) {
	h->heroUpdateCnt++;
	if (h->heroUpdateCnt >= 15) {
		h->heroUpdateCnt = 0;
		if (h->life != 0) {
			if (h->status == hero_normal0) h->status = hero_normal1;
			else if (h->status == hero_normal1) h->status = hero_normal0;
		}
		else {
			if (h->status < hero_destroy) h->status = heroStatusSqauence[h->status + 1];
		}
	}
}

void heroInit(struct hero* h) {
	h->super.draw = (void(*)(struct sprite*))heroDraw;
	h->super.update = (void(*)(struct sprite*))heroUpdate;

	h->heroUpdateCnt = 0;
	h->status = hero_normal0;
	h->life = 1;

	h->super.x = 178;
	h->super.y = 600;

	for (int i = 0; i < 6; i++) {
		h->imgArrHero[i] = new IMAGE;
		h->imgArrHeroMask[i] = new IMAGE;
	}

	char imgPath[50];
	char imgMaskPath[50];

	for (int i = 0; i < 2; i++) {
		sprintf_s(imgPath, "img/hero/hero%d.png", i);
		sprintf_s(imgMaskPath, "img/hero/hero%d_mask.png", i);
		loadimage(h->imgArrHero[i], imgPath);
		loadimage(h->imgArrHeroMask[i], imgMaskPath);
	}
	for (int i = 0; i < 4; i++) {
		sprintf_s(imgPath, "img/hero/hero_down%d.png", i);
		sprintf_s(imgMaskPath, "img/hero/hero_down%d_mask.png", i);
		loadimage(h->imgArrHero[i + 2], imgPath);
		loadimage(h->imgArrHeroMask[i + 2], imgMaskPath);
	}
}

void heroDestroy(struct hero* h) {
	for (int i = 0; i < 6; i++) {
		delete h->imgArrHero[i];
		delete h->imgArrHeroMask[i];
	}
}


