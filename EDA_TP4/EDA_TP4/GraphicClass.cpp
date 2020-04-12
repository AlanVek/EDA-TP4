#include "GraphicClass.h"
#include "Worm.h"
#include <string>

using namespace std;

//GraphicClass constructor.
GraphicClass::GraphicClass(unsigned int width_, unsigned int height_) :
	width(width_), height(height_) {
	for (int i = 0; i < (XFRAMES + 1); i++)
		moveBitmaps[i] = nullptr;

	for (int i = 0; i < (YFRAMES + 1); i++)
		jumpBitmaps[i] = nullptr;

	display = nullptr;
	background = nullptr;
}

//Attempts to create bitmaps. Returns true if successful.
bool GraphicClass::createBitmaps(void) {
	bool result = true;

	for (int i = 0; i < (XFRAMES + 1); i++) {
		if (!(moveBitmaps[i] = al_create_bitmap(width, height)))
			result = false;
	}

	for (int i = 0; i < (YFRAMES + 1); i++) {
		if (!(jumpBitmaps[i] = al_create_bitmap(width, height)))
			result = false;
	}

	if (!(background = al_create_bitmap(width, height)))
		result = false;
	if (result)
		result = loadBitmaps();

	return result;
}
//Attempts to create display. Returns true if successful.
bool GraphicClass::createDisplay(void) {
	return (display = al_create_display(width, height));
}

ALLEGRO_DISPLAY*& GraphicClass::getDisplay(void) { return display; }

//Frees memory.
GraphicClass::~GraphicClass(void) {
	for (int i = 0; i < (XFRAMES + 1); i++) {
		if (moveBitmaps[i])
			al_destroy_bitmap(moveBitmaps[i]);
	}

	for (int i = 0; i < (YFRAMES + 1); i++) {
		if (jumpBitmaps[i])
			al_destroy_bitmap(jumpBitmaps[i]);
	}

	if (display)
		al_destroy_display(display);

	if (background)
		al_destroy_bitmap(background);
}

/*Draws every worm in its current position, with its corresponding bitmap.*/
void GraphicClass::draw(void* whichWorm) {
	Worm* wormPtr = (Worm*)whichWorm;
	ALLEGRO_BITMAP* temp = nullptr;

	/*State is 3 by default (idle worm state).*/
	int state = 3;

	/*If worm is jumping, it gets the jumping step and loads jumping image.*/
	if (wormPtr->getJumpState()) {
		state = wormPtr->getStepJump();
		temp = jumpBitmaps[state];
	}
	else {
		/*If worm is moving, it gets the movement step.*/
		if (wormPtr->getMovementState()) {
			state = wormPtr->getStepMove();
			temp = moveBitmaps[state];
		}

		/*Loads image (either moving image or idle image. */
		temp = moveBitmaps[state];
	}

	//Draws bitmap (either the real one or mirrored, depending on the worm's direction.
	if (wormPtr->getDirection() == 1)
		al_draw_bitmap(temp, wormPtr->getXPos(), wormPtr->getYPos(), ALLEGRO_FLIP_HORIZONTAL);
	else
		al_draw_bitmap(temp, wormPtr->getXPos(), wormPtr->getYPos(), 0);
}

/*Loads all bitmaps.*/
bool GraphicClass::loadBitmaps(void) {
	bool result = true;

	string name = "wwalking/wwalk-F";
	string tempstr;
	char* tempchar = (char*)malloc(30 * sizeof(char));

	if (!tempchar)
		return false;

	for (int i = 0; i < (XFRAMES + 1); i++) {
		tempstr = name + to_string(i + 1) + ".png";

		tempchar = strcpy(tempchar, tempstr.c_str());

		if (!(moveBitmaps[i] = al_load_bitmap(tempchar)))
			result = false;
	}

	if (!(background = al_load_bitmap("Scenario.png")))
		result = false;

	name = "wjump/wjump-F";

	for (int i = 0; i < (YFRAMES + 1); i++) {
		tempstr = name + to_string(i + 1) + ".png";

		tempchar = strcpy(tempchar, tempstr.c_str());

		if (!(jumpBitmaps[i] = al_load_bitmap(tempchar)))
			result = false;
	}

	free(tempchar);

	return result;
}

void GraphicClass::drawBackground(void) { al_draw_bitmap(background, 0, 0, 0); }