#pragma once

struct sprite {
	void (*draw)(sprite*);
	void(*update)(sprite*);

	int x;
	int y;

	int width;
	int height;
};