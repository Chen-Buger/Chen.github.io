#include"gameloop.h"
#include<easyx.h>
#include"scene.h"


void gameLoop(struct scene* s, int fps) {
	timeBeginPeriod(1);
	LARGE_INTEGER startCount, endCount, F;
	QueryPerformanceFrequency(&F);

	bool isLoopOver = false;

	BeginBatchDraw();
	while (1) {
		QueryPerformanceCounter(&startCount);
		cleardevice();

		s->draw(s);
		s->update(s);

		if (s->isQuit(s))
			break;

		QueryPerformanceCounter(&endCount);
		long long elapse = (endCount.QuadPart - startCount.QuadPart) * 1000000 / F.QuadPart;
		while (elapse < 1000000 / fps) {
			Sleep(1);

			ExMessage msg;
			bool isOK = peekmessage(&msg, EX_MOUSE);
			if (isOK == true) {
				s->control(s, &msg);
			}

			QueryPerformanceCounter(&endCount);
			elapse = (endCount.QuadPart - startCount.QuadPart) * 1000000 / F.QuadPart;
		}
		FlushBatchDraw();

		if (isLoopOver == true) {
			break;
		}
	}
	EndBatchDraw();
	timeEndPeriod(1);
}