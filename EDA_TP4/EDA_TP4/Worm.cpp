#include "Worm.h"

#define STARTINGY 616

Worm::Worm() {
	isMoving = false;
	stepCount = 0;
	xPos = 100;
	yPos = STARTINGY;
};

void Worm::setJumpKeys(const int* validEvents_, int amount) {
	for (int i = 0; i < amount; i++)
		jumpKeys[i] = validEvents_[i];

	numJumpKeys = amount;
}
void Worm::setMoveKeys(const int* validEvents_, int amount) {
	for (int i = 0; i < amount; i++)
		moveKeys[i] = validEvents_[i];

	numMoveKeys = amount;
}

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

void Worm::start(int keyCode, int whichMove) {

	if (whichMove == 1)
		jump();

	isMoving = true;
}

void Worm::stop(int keyCode, int whichMove) {
	if (whichMove == -1) {
		isMoving = false;
		stepCount = 0;
	}
}

float Worm::getXPos(void) { return xPos; }
float Worm::getYPos(void) { return yPos; }
int Worm::getStep(void) { return stepCount; }

void Worm::updateStep(void) {
	if (isMoving)
		stepCount++;
}

void Worm::jump(void) {
	//
}
