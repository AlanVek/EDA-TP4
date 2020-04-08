#include "GraphicClass.h"
#include <allegro5/allegro_primitives.h>


#define LINE_WIDTH side/100
//GraphicClass constructor.
GraphicClass::GraphicClass(unsigned int height_, unsigned int width_) :
    width(width_), height(height_){

    display = nullptr;
}

//Attempts to create display. Returns true if successful. 
bool GraphicClass::createDisplay(void) {
    return (display = al_create_display(width, height));
}

//Gets display.
ALLEGRO_DISPLAY*& GraphicClass::getDisplay(void) { return display; }

//Frees memory.
GraphicClass::~GraphicClass(void) {
    if (display)
        al_destroy_display(display);
}

