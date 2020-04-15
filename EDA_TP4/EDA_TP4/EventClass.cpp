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
	int result = NULL;
	if (al_get_next_event(Queue, &Event))
		result = Event.type;
	return result;
}

//Frees memory.
EventClass::~EventClass() {
	if (Queue)
		al_destroy_event_queue(Queue);
}

//Talks different courses of action according to event input.
bool EventClass::dispatch(Simulation* sim) {
	//Simulation* sim = (Simulation*)thisSim;
	bool result = false;

	switch (Event.type) {
	case ALLEGRO_EVENT_KEY_DOWN:
		result = sim->startMoving(Event.keyboard.keycode);
		break;
	case ALLEGRO_EVENT_KEY_CHAR:
		result = sim->startMoving(Event.keyboard.keycode);
		break;

	case ALLEGRO_EVENT_KEY_UP:
		sim->stopMoving(Event.keyboard.keycode);
		result = true;
		break;
	case ALLEGRO_EVENT_TIMER:
		sim->refresh();
		result = true;
		break;
	case ALLEGRO_EVENT_DISPLAY_CLOSE:
		result = false;
		break;
	default:
		break;
	}

	return result;
}