#include"menuscene.h"

void menuSceneDraw(struct menuScene* s) {
	putimage(0, 0, s->bk);
	if (s->isStartGameHover == true) {
		settextcolor(WHITE);
	}
	else {
		settextcolor(BLACK);
	}
	drawtext("¿ªÊ¼ÓÎÏ·", & s->rectStartGame, DT_CENTER);

	if (s->isEndGameHover == true) {
		settextcolor(WHITE);
	}
	else {
		settextcolor(BLACK);
	}
	drawtext("½áÊøÓÎÏ·", & s->rectEndGame, DT_CENTER);
}

void menuSceneUpdate(struct menuScene* s) {

}

void menuSceneControl(struct menuScene* s, ExMessage* msg) {
	switch (msg->message) {
		case WM_LBUTTONDOWN:
			if (s->isEndGameHover == true) {
				exit(0);
			}
			if (s->isStartGameHover == true) {
				s->isQuit = true;
			}
			break;

		case WM_MOUSEMOVE: {
			if (msg->x > s->rectStartGame.left && msg->x < s->rectStartGame.right
				&& msg->y < s->rectStartGame.bottom && msg->y > s->rectStartGame.top)
				s->isStartGameHover = true;
			else
				s->isStartGameHover = false;

			if (msg->x > s->rectEndGame.left && msg->x < s->rectEndGame.right
				&& msg->y < s->rectEndGame.bottom && msg->y > s->rectEndGame.top)
				s->isEndGameHover = true;
			else
				s->isEndGameHover = false;
			break;
		}
	}
}

bool menuSceneIsQuit(struct menuScene* s) {
	return s->isQuit;
}

void menuSceneInit(struct menuScene* s) {
	s->super.draw = (void(*)(struct scene*))menuSceneDraw;
	s->super.update = (void(*)(struct scene*))menuSceneUpdate;
	s->super.control = (void (*)(struct scene*, ExMessage*))menuSceneControl;
	s->super.isQuit = (bool(*)(struct scene*))menuSceneIsQuit;

	s->isStartGameHover = false;
	s->isEndGameHover = false;

	s->isQuit = false;

	s->bk = new IMAGE;  
	loadimage(s->bk, "img/menu.png");

	s->rectStartGame.left = 130;
	s->rectStartGame.top = 430;
	s->rectStartGame.right = 300;
	s->rectStartGame.bottom = 480;

	s->rectEndGame.left = 130;
	s->rectEndGame.top = 540;
	s->rectEndGame.right = 300;
	s->rectEndGame.bottom = 590;

	settextcolor(BLACK);
	settextstyle(50, 0, "Î¢ÈíÑÅºÚ");
	setbkmode(TRANSPARENT);
}

void menuSceneDestroy(struct menuScene* s) {
	delete s->bk;
}