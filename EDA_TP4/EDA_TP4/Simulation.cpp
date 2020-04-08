#include "Simulation.h"
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>

using namespace std;


//Simulation constructor.
Simulation::Simulation(unsigned int width_, unsigned int height_, double FPS_, int wormCount_) :

	width (width_), height(height_), FPS(FPS_), wormCount(wormCount_){

	graphicControl = nullptr;
	timeControl = nullptr;
	eventControl = nullptr;
}

bool Simulation::initializeAll(void) {
	bool result = true;

	/*Allegro initialization error check*/
	if (!setAllegro()) {
		cout << "Failed to initialize Allegro.\n";
		result = false;
	}

	/*Initialization of graphic resources. Checks for errors.
	True parameter indicates to create a new display. */
	else if (!setSimulation(true)) {
		cout << "Failed to set simulation.\n";
		result = false;
	}	

	else if (!initializeWorms()) {
		cout << "Failed to initialize worms.\n";
		result = false;
	}
	return result;
}

/*Initializes Allegro and its addons. Return false and prints
the correspondent message if any process failed. */
bool Simulation::setAllegro(void) {
	bool result = true;
	if (!al_init()) {
		cout << "Failed to Initialize Allegro\n";
		result = false;
	}

	//Attempts to initialize keyboard.
	else if (!al_install_keyboard()) {
		cout << "Failed to install keyboard\n";
		result = false;
	}
	else if (!al_init_image_addon()) {
		cout << "Failed to initialize image addon.\n";
		result = false;
	}

	return result;
}

/*Creates needed resources and checks for initialization errors.
If there's been one, returns false. If not, returns true. 
If displayCreation is true, it creates a new display.*/
bool Simulation::setSimulation(bool displayCreation) {

	bool result = true;

	//Creates control variables and checks for proper initialization.
	graphicControl = new (nothrow) GraphicClass(width, height);
	eventControl = new (nothrow) EventClass();
	timeControl = new (nothrow) TimeClass();
	
	if (!graphicControl) {
		cout << "Failed to create graphic pointer\n";
		result = false;
	}
	else if (!eventControl) {
		cout << "Failed to create event pointer\n";
		result = false;
	}
	
	else if (!timeControl) {
		cout << "Failed to create time pointer\n";
		result = false;
	}

	//Attempts to create event queue for timer and keyboard.
	else if (!eventControl->createEventQueue()) {
		cout << "Failed to create event queue\n";
		result = false;
	}

	//Attempts to create timer.
	else if (!timeControl->createTimer(FPS)) {
		cout << "Failed to create timer\n";
		result = false;
	}

	//Attempts to create display (if requested).
	else if (displayCreation && !graphicControl->createDisplay()) {
		cout << "Failed to create display\n";
		result = false;
	}

	//Sets event source for timer, mouse, display and keyboard.
	if (result) {
		al_register_event_source(eventControl->getQueue(), al_get_timer_event_source(timeControl->getTimer()));
		al_register_event_source(eventControl->getQueue(), al_get_display_event_source(graphicControl->getDisplay()));
		al_register_event_source(eventControl->getQueue(), al_get_keyboard_event_source());
	}
	return result;
}

//Class getters.
GraphicClass* Simulation::getGraphicControl(void) { return graphicControl; }
TimeClass* Simulation::getTimeControl(void) { return timeControl; }
EventClass* Simulation::getEventControl(void) {return eventControl;}

//Destructor. Frees memory.
Simulation::~Simulation() {
	
	delete graphicControl;
	delete timeControl;
	delete eventControl;

	for (int i = 0; i < wormCount; i++)
		delete wormVector[i];
}

//Communicates "outside world" with EventClass' dispatcher.
void Simulation::dispatch(void) {
	eventControl->dispatch(this);
}


void Simulation::startMoving(void) {

}
void Simulation::stopMoving(void) {

}
void Simulation::refresh(void) {

}

/*Creates wormCount worms in memory and stores them in wormVector.
Returns false if there's been an allocation error.*/
bool Simulation::initializeWorms(void) {
	bool result = true;
	for (int i = 0; i < wormCount; i++) {
		if (!(wormVector[i] = new (nothrow) Worm))
			result = false;
	}

	return result;
}