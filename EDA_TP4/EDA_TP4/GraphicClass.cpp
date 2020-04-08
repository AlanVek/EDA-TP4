#include "GraphicClass.h"

//GraphicClass constructor.

GraphicClass::GraphicClass(unsigned int height_, unsigned int width_) :
    width(width_), height(height_) {};

//Attempts to create display. Returns true if successful. 
bool GraphicClass::createBitmaps(void) {
    bool result = true;

    for (int i = 0; i < BITAMOUNT; i++) {
        if (!(myBitmaps[i] = al_create_bitmap(width, height)))
            result = false;
    }

    if (result)
        result = loadBitmaps();

    return result;
}

bool GraphicClass::createDisplay(void) {
    return (display = al_create_display(width, height));
}

ALLEGRO_DISPLAY*& GraphicClass::getDisplay(void) { return display; }

//Frees memory.
GraphicClass::~GraphicClass(void) {
    
    for (int i = 0; i < BITAMOUNT; i++) {
        if (myBitmaps[i])
            al_destroy_bitmap(myBitmaps[i]);
    }
    if (display)
        al_destroy_display(display);
}
void GraphicClass::draw(ALLEGRO_BITMAP* bit, int xPos, int yPos) {
    al_draw_bitmap(bit, xPos, yPos, 0);
}

bool GraphicClass::loadBitmaps(void) {

    bool result = true;

    //Loads bitmaps, checking for errors.

    return result;

}

