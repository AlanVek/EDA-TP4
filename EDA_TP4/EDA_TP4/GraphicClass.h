#pragma once
#include <iostream>
#include <allegro5/allegro.h>
#define MAXBITS 15
class GraphicClass {
public:

	//GraphicClass constructor.
	GraphicClass(unsigned int width_, unsigned int height_);

	void draw(void* whichWorm);

	bool createBitmaps(void);

	bool loadBitmaps(void);

	bool createDisplay(void);

	ALLEGRO_DISPLAY*& getDisplay(void);

	void drawBackground(void);

	~GraphicClass();

private:

	ALLEGRO_BITMAP* moveBitmaps[MAXBITS];
	ALLEGRO_BITMAP* jumpBitmaps[MAXBITS];
	ALLEGRO_BITMAP* background;
	ALLEGRO_DISPLAY* display;
	unsigned int width, height;
};
