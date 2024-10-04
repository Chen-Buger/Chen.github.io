#include <time.h>
#include "gameloop.h"
#include "mainscene.h"
#include "menuscene.h"
#include <stdio.h>

int main()
{
    srand((unsigned int)time(NULL));

    initgraph(422, 750);
    setbkcolor(WHITE);
    cleardevice();

    while (1)
    {
        menuScene menuscene;
        menuSceneInit(&menuscene);
        gameLoop((scene*)&menuscene, 60);
        menuSceneDestroy(&menuscene);

        mainScene mainscene;
        mainSceneInit(&mainscene);
        gameLoop((scene*)&mainscene, 60);
        mainSceneDestroy(&mainscene);

        settextcolor(WHITE);
        settextstyle(100, 0, "微软雅黑");

        //  游戏结束
        const char* pStr = "游戏结束";
        RECT r = { 0, 200, 422, 300 };
        drawtext(pStr, &r, DT_CENTER);

        //  计分板
        char buff[10];
        sprintf_s(buff, "得分:%d", mainscene.mark);
        r = { 0, 300, 422, 400 };
        drawtext(buff, &r, DT_CENTER);

        Sleep(3000);
    }

    closegraph();
    return 0;
}