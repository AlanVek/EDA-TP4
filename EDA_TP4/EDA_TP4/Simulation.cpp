#include "Simulation.h"
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>

using namespace std;

bool setAllegro(void);


//Simulation constructor.
Simulation::Simulation(unsigned int width_, unsigned int height_, double FPS_, int wormCount_) :

	width (width_), height(height_), FPS(FPS_), wormCount(wormCount_){

	graphicControl = nullptr;
	timeControl = nullptr;
	eventControl = nullptr;

	for (int i = 0; i < wormCount; i++)
		wormVector[i] = nullptr;

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

	//Attempts to initialize worms.
	else if (!initializeWorms()) {
		cout << "Failed to initialize worms.\n";
		result = false;
	}

	//If everything was initialized correctly, it sets default key values for worm movement.
	if (result)
		setDefaultKeys();
	return result;
}

/*Initializes Allegro and its addons. Return false and prints
the correspondent message if any process failed. */
bool setAllegro(void) {
	bool result = true;

	//Attempts to initialize Allegro.
	if (!al_init()) {
		cout << "Failed to Initialize Allegro\n";
		result = false;
	}

	//Attempts to initialize keyboard.
	else if (!al_install_keyboard()) {
		cout << "Failed to install keyboard\n";
		result = false;
	}

	//Attempts to initialize image addon.
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

	/*else if (!graphicControl->createBitmaps()) {
		cout << "Failed to create bitmaps.\n";
		result = false;
	}*/

	//Sets event source for timer, mouse, display and keyboard.
	if (result) {
		al_register_event_source(eventControl->getQueue(), al_get_timer_event_source(timeControl->getTimer()));
		al_register_event_source(eventControl->getQueue(), al_get_display_event_source(graphicControl->getDisplay()));
		al_register_event_source(eventControl->getQueue(), al_get_keyboard_event_source());

		result = graphicControl->createBitmaps();
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
bool Simulation::dispatch(void) {
	return (eventControl->dispatch(this));
}

/* When a key gets pressed, it checks if it's a key linked to
any worm's movement. If so, then it tells the worm to start the movement.*/
bool Simulation::startMoving(int keyCode) {

	int movementType;
	for (int i = 0; i < wormCount; i++) {
		movementType = wormVector[i]->checkKeyCode(keyCode);
		if (movementType) {
			if(Simulation::timer(wormVector[i])){
				wormVector[i]->start(keyCode, movementType);
				return true;
			}
		}
	}
	return false;

}
/*If a key's been released, it checks if it's a key linked to
any worm's movement. If so, then it tells the worm to stop the movement.*/
void Simulation::stopMoving(int keyCode) {
	int whichMove;
	for (int i = 0; i < wormCount; i++) {
		whichMove = wormVector[i]->checkKeyCode(keyCode);
		if (whichMove) {

			switch (Simulation::keyUp(wormVector[i])) {

			case CHANGEDIR :
				wormVector[i]->stop(keyCode, whichMove); // crear funcion que lo de vuelta 
				break;

			case STOPMOVING :
				wormVector[i]->stop(keyCode, whichMove);
				break;
			default:
				break;
			}
		}
	}
}

/* When timer does a lap, the image gets refreshed
and the worms' stepCount gets updated to the next step.*/
void Simulation::refresh(void) {

	al_clear_to_color(al_map_rgb(255, 255, 255));
	for (int i = 0; i < wormCount; i++) {
		graphicControl->draw(wormVector[i]);
		wormVector[i]->updateStep();		
	}
	al_flip_display();
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

//Sets default key values.
void Simulation::setDefaultKeys(void) {
	int moveKeys1[] = { ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RIGHT};
	int moveKeys2[] = { ALLEGRO_KEY_D, ALLEGRO_KEY_A};
	
	wormVector[0]->setJumpKey(ALLEGRO_KEY_UP);
	wormVector[0]->setMoveKeys(moveKeys1,2);

	wormVector[1]->setJumpKey(ALLEGRO_KEY_W);
	wormVector[1]->setMoveKeys(moveKeys2,2);
}


bool Simulation::timer(Worm * wormDirection) {

	Worm* wormptr = wormDirection;


	if (wormptr->getTimer() == 0) {
		timeControl->startTimer();
	}

	if (wormptr->getTimer() >= 100) {
		return true;
	}

	wormptr->addTimer(al_get_timer_count(timeControl->getTimer())) ;

	return false;
}

int Simulation::keyUp(Worm* wormDirection) {

	Worm* wormptr = wormDirection;
	int result;

	if (wormptr->getTimer() < 100) {
		result = CHANGEDIR;
	}
	else {
		result = STOPMOVING;
	}

	return result;
}