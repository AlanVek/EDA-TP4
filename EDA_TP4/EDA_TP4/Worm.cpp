#include "Worm.h"

#define STARTINGY 616

/*Worm constructor. Sets variables to initial values.*/
Worm::Worm() {
	isMoving = false;
	stepCount = 0;
	xPos = 100;
	yPos = STARTINGY;
};

/* Recieves an array of keys and sets them to jumping keys.*/
void Worm::setJumpKeys(const int* validEvents_, int amount) {
	for (int i = 0; i < amount; i++)
		jumpKeys[i] = validEvents_[i];

	numJumpKeys = amount;
}
/* Recieves an array of keys and sets them to moving keys.*/
void Worm::setMoveKeys(const int* validEvents_, int amount) {
	for (int i = 0; i < amount; i++)
		moveKeys[i] = validEvents_[i];

	numMoveKeys = amount;
}

/*Checks if the given keyCode is linked to any movement.
If it's jumping, it returns 1. If it's moving, it returns -1.
If it's neither, it returns 0.*/
int Worm::checkKeyCode(int keyCode) {
	for (int i = 0; i < numJumpKeys; i++) {
		if (jumpKeys[i] == keyCode)
			return 1;
	}
	for (int i = 0; i < numMoveKeys; i++) {
		if (moveKeys[i] == keyCode)
			return -1;
	}

	return 0;
}

/*If it has to start a jump, it jumps. Otherwise, if it has
to move, it sets isMoving to true, so that refresh can later update stepCount.*/
void Worm::start(int keyCode, int whichMove) {

	if (whichMove == 1)
		jump();

	isMoving = true;
}

/*Sets isMoving to false, and resets stepCount to 0.*/
void Worm::stop(int keyCode, int whichMove) {
	if (whichMove == -1) {
		isMoving = false;
		stepCount = 0;
	}
}

/*Class getters.*/
float Worm::getXPos(void) { return xPos; }
float Worm::getYPos(void) { return yPos; }
int Worm::getStep(void) { return stepCount; }

/*If the worm was moving, it updates the stepCount and returns true.
Otherwise, it returns false.*/
bool Worm::updateStep(void) {
	if (isMoving) {
		stepCount++;
		return true;
	}
	return false;
}

void Worm::jump(void) {
	//
}
