#pragma once

#include<easyx.h>
#include"sprite.h"

enum enemyType {
	enemyType0,
	enemyType1,
	enemyType2
};

enum enemyStatus {
	enemy_normal,
	enemy_down0,
	enemy_down1,
	enemy_down2,
	enemy_down3,
	enemy_down4,
	enemy_down5,
	enemy_destroy
};

struct enemy {
	struct sprite super;
	void (*hited)(struct enemy*);
	void (*destroy)(struct enemy*);

	IMAGE** imgArrEnemy;
	IMAGE** imgArrEnemyMask;
	enum enemyType enemyType;
	int v;
	int life;
	int enemyDownCnt;
	int status;
	int lastStatusBeforeDestroy;
};

void enemyInit(struct enemy* e);