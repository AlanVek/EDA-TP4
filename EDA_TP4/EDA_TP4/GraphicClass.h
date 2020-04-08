#pragma once
#include <iostream>
#include <allegro5/allegro.h>


#define BITAMOUNT 15

class GraphicClass {
public:

	//GraphicClass constructor.
	GraphicClass(unsigned int height_, unsigned int width_);

	void draw(ALLEGRO_BITMAP* bit, int xPos, int yPos);

	bool createBitmaps(void);

	bool loadBitmaps(void);

	bool createDisplay(void);

	ALLEGRO_DISPLAY*& getDisplay(void);

	~GraphicClass();

private:

	ALLEGRO_BITMAP* myBitmaps[BITAMOUNT];
	ALLEGRO_DISPLAY* display;
	unsigned int width, height;
	
};

