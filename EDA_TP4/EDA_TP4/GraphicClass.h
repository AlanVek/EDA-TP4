#pragma once
#include <iostream>
#include <allegro5/allegro.h>


#define AMOUNT 4

class GraphicClass {
public:

	//GraphicClass constructor.
	GraphicClass(unsigned int height_, unsigned int width_);

	ALLEGRO_DISPLAY*& getDisplay(void);

	bool createDisplay(void);

	~GraphicClass();

private:

	ALLEGRO_DISPLAY* display;
	unsigned int width, height;
	
};

