#include "TimeClass.h"

//TimeClass constructor.
TimeClass::TimeClass(ALLEGRO_TIMER* timer_) : Timer(timer_) {};

//Starts timer.
void TimeClass::startTimer(void) { al_start_timer(Timer); }

//Class getter.
ALLEGRO_TIMER* TimeClass::getTimer(void) { return Timer; }

//Creates timer.
bool TimeClass::createTimer(double FPS_) {
	return (Timer = al_create_timer(1 / FPS_));
}

//Frees memory.
TimeClass::~TimeClass() {
	if (Timer)
		al_destroy_timer(Timer);
}