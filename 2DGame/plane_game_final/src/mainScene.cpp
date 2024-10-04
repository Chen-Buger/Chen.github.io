#include"mainScene.h"
#include"bullet.h"
#include"enemy.h"
#include"enemy0.h"
#include"enemy1.h"
#include"enemy2.h"
#include<stdio.h>
#include"soundManager.h"

void mainSceneDraw(struct mainScene* s) {
	s->vecElements.clear(&s->vecElements);

	s->vecElements.append(&s->vecElements, s->bk);
	

	for (int i = 0; i < s->vecEnemy.size; i++) {
		struct enemy* pEnemy = (struct enemy*)s->vecEnemy.get(&s->vecEnemy, i);
		s->vecElements.append(&s->vecElements, pEnemy);
	}

	s->vecElements.append(&s->vecElements, s->hero);

	for (int i = 0; i < s->vecBullets.size; i++) {
		struct bullet* pBullet = (struct bullet*)s->vecBullets.get(&s->vecBullets, i);
		s->vecElements.append(&s->vecElements, pBullet);
	}

	for (int i = 0; i < s->vecElements.size; i++) {
		struct sprite* pSprite = (struct sprite*)(s->vecElements.pData[i]);
		pSprite->draw(pSprite);
	}

	char buff[10];
	sprintf_s(buff, "µÃ·Ö:%d", s->mark);
	outtextxy(0, 0, buff);
}

void generateNewEnemy(struct mainScene* s) {
	int r = rand() % 60;
	struct enemy* pEnemy = NULL;
	if (0 <= r && r < 40) {
		struct enemy0* pEnemy0 = (struct enemy0*)malloc(sizeof(struct enemy0));
		if (pEnemy0 == NULL)
			return;
		enemy0Init(pEnemy0);
		pEnemy = (struct enemy*)pEnemy0;
	}
	else if (40 <= r && r < 55) {
		struct enemy1* pEnemy1 = (struct enemy1*)malloc(sizeof(struct enemy1));
		if (pEnemy1 == NULL)
			return;
		enemy1Init(pEnemy1);
		pEnemy = (struct enemy*)pEnemy1;
	}
	else if (55 <= r && r < 60) {
		struct enemy2* pEnemy2 = (struct enemy2*)malloc(sizeof(struct enemy2));
		if (pEnemy2 == NULL)
			return;
		enemy2Init(pEnemy2);
		pEnemy = (struct enemy*)pEnemy2;
	}

	pEnemy->super.x = rand() % 383 + 20;
	if (pEnemy->enemyType == enemyType0)
		pEnemy->super.y = -26;
	else if (pEnemy->enemyType == enemyType1)
		pEnemy->super.y = -59;
	else if (pEnemy->enemyType == enemyType2)
		pEnemy->super.y = -162;

	s->vecEnemy.append(&s->vecEnemy, pEnemy);
}

void destroyInvalidEnemy(struct mainScene* s) {
	for (int i = 0; i < s->vecEnemy.size; i++) {
		struct enemy* pEnemy = (struct enemy*)s->vecEnemy.get(&s->vecEnemy, i);
		if (pEnemy->super.y > 750 || pEnemy->status == enemy_destroy) {
			if (pEnemy->status == enemy_destroy) {
				switch (pEnemy->enemyType) {
					case enemyType0:s->mark += 10; break;
					case enemyType1:s->mark += 30; break;
					case enemyType2:s->mark += 50; break;
				}
			}
			s->vecEnemy.remove(&s->vecEnemy, i);
			pEnemy->destroy(pEnemy);
			free(pEnemy);
			i--;
		}
	}
}

void generateBullet(struct mainScene* s) {
	struct bullet* pBullet = (struct bullet*)malloc(sizeof(struct bullet));
	if (pBullet == NULL) {
		return;
	}
	bulletInit(pBullet);
	pBullet->super.x = s->hero->super.x + 32;
	pBullet->super.y = s->hero->super.y - 6;
	s->vecBullets.append(&s->vecBullets, pBullet);
}

void destroyInvalidBullet(struct mainScene* s) {
	if (s->vecBullets.size <= 0)
		return;
	struct bullet* pBullet = (struct bullet*)s->vecBullets.get(&s->vecBullets, 0);
	if (pBullet->super.y < -14) {
		s->vecBullets.remove(&s->vecBullets, 0);
		bulletDestroy(pBullet);
		free(pBullet);
	}
}

void bulletHitEnemyCheck(struct mainScene* s) {
	for (int i = 0; i < s->vecBullets.size; i++) {
		struct bullet* pBullet = (struct bullet*)s->vecBullets.get(&s->vecBullets, i);
		POINT bulletPoint;
		bulletPoint.x = pBullet->super.x + 6 / 2;
		bulletPoint.y = pBullet->super.y;

		for (int j = 0; j < s->vecEnemy.size; j++) {
			struct enemy* pEnemy = (struct enemy*)s->vecEnemy.get(&s->vecEnemy, j);

			int width, height;
			width = pEnemy->super.width;
			height = pEnemy->super.height;

			int left, top, right, bottom;
			left = pEnemy->super.x;
			top = pEnemy->super.y;
			right = left + width;
			bottom = top + height;

			if (bulletPoint.x > left && bulletPoint.x<right && bulletPoint.y>top && bulletPoint.y < bottom) {
				if (pEnemy->life != 0) {
					bulletDestroy(pBullet);
					free(pBullet);
					s->vecBullets.remove(&s->vecBullets, i);
					i--;
					pEnemy->hited(pEnemy);
					if (pEnemy->life == 0) {
						s->enemyDownSoundMgr.play(&s->enemyDownSoundMgr);
					}
					break;
				}
			}
		}
	}
}

bool heroHitEnemyCheck(struct mainScene* s) {
	RECT rectHero;
	rectHero.left = s->hero->super.x + 16;
	rectHero.top = s->hero->super.y + 10;
	rectHero.right = s->hero->super.x + 16 * 3;
	rectHero.bottom = s->hero->super.y + 62;

	for (int i = 0; i < s->vecEnemy.size; i++) {
		struct enemy* pEnemy = (struct enemy*)s->vecEnemy.get(&s->vecEnemy, i);
		int enemyWidth = 0, enemyHeight = 0;
		if (pEnemy->status != enemy_normal)
			continue;
		RECT rectEnemy;
		rectEnemy.left = pEnemy->super.x;
		rectEnemy.top = pEnemy->super.y;
		rectEnemy.right = pEnemy->super.x + pEnemy->super.width;
		rectEnemy.bottom = pEnemy->super.y + pEnemy->super.height;

		if (rectHero.left <= rectEnemy.right && rectHero.right >= rectEnemy.left && rectHero.top <= rectEnemy.bottom && rectHero.bottom >= rectEnemy.top) {
			if (s->hero->status == hero_normal0 || s->hero->status == hero_normal1) {
				return true;
			}
		}
	}
	return false;
}


void mainSceneUpdate(struct mainScene* s) {
	for (int i = 0; i < s->vecElements.size; i++) {
		struct sprite* pSprite = (struct sprite*)s->vecElements.pData[i];
		pSprite->update(pSprite);
	}

	int n = rand() % 20;
	if (n == 0) {
		generateNewEnemy(s);
	}
	destroyInvalidEnemy(s);

	s->bulletGenCnt++;
	if (s->bulletGenCnt >= 15) {
		generateBullet(s);
		s->bulletGenCnt = 0;
	}
	destroyInvalidBullet(s);

	bulletHitEnemyCheck(s);

	bool isHited = heroHitEnemyCheck(s);
	if (isHited == true) {
		s->hero->life--;
		s->hero->status = hero_down1;
		mciSendString("open sounds/hero_down.wma", NULL, 0, NULL);
		mciSendString("play sounds/hero_down.wma", NULL, 0, NULL);
	}
	s->soundCloseCnt++;
	if (s->soundCloseCnt >= 60) {
		s->enemyDownSoundMgr.close(&s->enemyDownSoundMgr, 1000);
		s->soundCloseCnt = 0;
	}
	
}

void mainSceneControl(struct mainScene* s, ExMessage* msg) {
	if (msg->message == WM_MOUSEMOVE) {
		s->hero->super.x = msg->x - 35;
		s->hero->super.y = msg->y - 35;
	}
}

bool mainSceneIsQuit(struct mainScene* s) {
	if (s->hero->status == hero_destroy)
		return true;
	return false;
}

void mainSceneInit(struct mainScene* s) {
	s->super.draw = (void(*)(struct scene*))mainSceneDraw;
	s->super.update = (void(*)(struct scene*))mainSceneUpdate;
	s->super.control = (void(*)(struct scene*, ExMessage * msg))mainSceneControl;
	s->super.isQuit = (bool(*)(struct scene*))mainSceneIsQuit;


	s->hero = (struct hero*)malloc(sizeof(struct hero));
	heroInit(s->hero);

	s->bulletGenCnt = 0;
	s->soundCloseCnt = 0;

	s->bk = (struct background*)malloc(sizeof(struct background));
	backgroundInit(s->bk);

	vectorInit(&s->vecElements);
	vectorInit(&s->vecEnemy);
	vectorInit(&s->vecBullets);

	s->mark = 0;
	settextcolor(WHITE);
	settextstyle(30, 0, "Î¢ÈíÑÅºÚ");
	setbkmode(TRANSPARENT);

	soundManagerInit(&s->enemyDownSoundMgr, "sound/enemy_ddown.wma");

	mciSendString("open sounds/backgroud.wma", NULL, 0, NULL);
	mciSendString("play sounds/background.wma repeat", NULL, 0, NULL);
}

void mainSceneDestroy(struct mainScene* s) {

	mciSendString("close sounds/background.wma", NULL, 0, NULL);
	mciSendString("close sounds/hero_down.wma", NULL, 0, NULL);
	soundManagerDestroy(&s->enemyDownSoundMgr);

	heroDestroy(s->hero);
	free(s->hero);

	backgroundDestroy(s->bk);
	free(s->bk);

	vectorDestroy(&s->vecElements);

	for (int i = 0; i < s->vecEnemy.size; i++) {
		struct enemy* pEnemy = (struct enemy*)s->vecEnemy.get(&s->vecEnemy, i);
		pEnemy->destroy(pEnemy);
		free(pEnemy);
	}
	vectorDestroy(&s->vecEnemy);

	for (int i = 0; i < s->vecBullets.size; i++) {
		struct bullet* pBullet = (struct bullet*)s->vecBullets.get(&s->vecBullets, i);
		bulletDestroy(pBullet);
		free(pBullet);
	}
	vectorDestroy(&s->vecBullets);
}


