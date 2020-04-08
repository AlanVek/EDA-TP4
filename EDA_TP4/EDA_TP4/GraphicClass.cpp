#include "GraphicClass.h"
#include "Worm.h"

//GraphicClass constructor.
GraphicClass::GraphicClass(unsigned int height_, unsigned int width_) :
    width(width_), height(height_) {};


//Attempts to create bitmaps. Returns true if successful. 
bool GraphicClass::createBitmaps(void) {
    bool result = true;

    for (int i = 0; i < BITAMOUNT; i++) {
        if (!(moveBitmaps[i] = al_create_bitmap(width, height)))
            result = false;
        if (!(jumpBitmaps[i] = al_create_bitmap(width, height)))
            result = false;
    }

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
    
    for (int i = 0; i < BITAMOUNT; i++) {
        if (moveBitmaps[i])
            al_destroy_bitmap(moveBitmaps[i]);
        if (jumpBitmaps[i])
            al_destroy_bitmap(jumpBitmaps[i]);
    }
    if (display)
        al_destroy_display(display);
}

/*Draws every worm in its current position, with its corresponding bitmap.*/
void GraphicClass::draw(void* whichWorm) {

    Worm* wormPtr = (Worm*)whichWorm;
    ALLEGRO_BITMAP* temp;
    
    /*State is 0 by default (idle worm state).*/
    int state = 0;

    /*If worm is moving, it gets the movement step.*/
    if (wormPtr->getMovementState())
        state = wormPtr->getStepMove();

    /*If worm is jumping, it gets the jumping step.*/
    else if (wormPtr->getJumpState())
        state = wormPtr->getStepJump();

    switch (state) {
        //temp = move/jumpBitmaps[xxx]
    }
    //al_draw_bitmap(temp, wormPtr->getXPos(), wormPtr->getYPos(), 0);
 
}

/*Loads all bitmaps.*/
bool GraphicClass::loadBitmaps(void) {

    bool result = true;

    //Loads bitmaps, checking for errors.

    return result;

}


