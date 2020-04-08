#include "Simulation.h"
#include <iostream>

using namespace std;

int main() {

	Simulation mySim;
	int result = 0;
	bool endOfInput = false;

	//First simulation initialization.
	if (!mySim.initializeAll()) {
		cout << "Failed to initialize simulation.\n";
		result = -1;
	}

	while (!endOfInput) {
		if (mySim.getEventControl()->getNextEventType()) {
			//mySim.dispatch();
		}
	}



	return 0;
}