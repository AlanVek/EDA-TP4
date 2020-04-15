#pragma once
#include <allegro5/allegro.h>

class Simulation;

class EventClass {
public:
	EventClass(ALLEGRO_EVENT_QUEUE* Queue_ = nullptr);
	bool createEventQueue(void);

	int getNextEventType();
	ALLEGRO_EVENT_QUEUE* getQueue(void);
	~EventClass();
	ALLEGRO_EVENT getEvent();
	bool dispatch(Simulation* sim);

private:
	ALLEGRO_EVENT Event;
	ALLEGRO_EVENT_QUEUE* Queue;
};
