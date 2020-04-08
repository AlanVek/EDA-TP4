#include "EventClass.h"
#include "Simulation.h"
EventClass::EventClass(ALLEGRO_EVENT_QUEUE* Queue_) : Queue(Queue_) {};

//Attempts to create Allegro event queue. Returns false if unsuccessful. 
bool EventClass::createEventQueue() { return (Queue = al_create_event_queue()); }

//Class getters.
ALLEGRO_EVENT_QUEUE* EventClass::getQueue(void) { return Queue; }
ALLEGRO_EVENT EventClass::getEvent(void) { return Event; }

//Returns the type of the next event in the queue, or NULL if queue is empty.
int EventClass::getNextEventType() {
	if (al_get_next_event(Queue, &Event))
		return Event.type;
	else
		return NULL;
}

//Frees memory.
EventClass::~EventClass() {
	if (Queue) 
		al_destroy_event_queue(Queue);
}

//Talks different courses of action according to event input.
bool EventClass::dispatch(void* thisSim) {
	Simulation* simPtr = (Simulation*) thisSim;
	bool result = false;

	switch (Event.type) {
	case ALLEGRO_EVENT_KEY_DOWN:
		result = simPtr->startMoving(Event.keyboard.keycode);
		break;
	case ALLEGRO_EVENT_KEY_CHAR:
		result = simPtr->startMoving(Event.keyboard.keycode);
		break;

	case ALLEGRO_EVENT_KEY_UP:
		simPtr->stopMoving(Event.keyboard.keycode);
		result = true;
		break;
	case ALLEGRO_EVENT_TIMER:
		simPtr->refresh();
		result = true;
		break;
	default:
		//cout << ALLEGRO_EVENT_KEY_CHAR << endl;
		break;
	}

	return result;
}


