#include "Simulation.h"
#include <iostream>

using namespace std;

int main() {
	Simulation mySim;
	int result = 0;
	bool endOfInput = false;

	srand(time(NULL));

	//First simulation initialization.
	if (!mySim.initializeAll()) {
		cout << "Failed to initialize simulation.\n";
		result = -1;
		endOfInput = true;
	}

	//If everything was initialized correctly...
	if (!endOfInput) {
		//Starts timer.
		mySim.getTimeControl()->startTimer();

		//Game loop.
		while (!endOfInput) {
			if (mySim.getEventControl()->getNextEventType()) {
				if (!mySim.dispatch())
					endOfInput = true;
			}
		}
	}

	return result;
}