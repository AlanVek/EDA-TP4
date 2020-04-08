#include "Worm.h"

#define STARTINGY 616

/*Worm constructor. Sets variables to initial values.*/
Worm::Worm() {
	isMoving = false;
	isJumping = false;
	stepCountMove = 0;
	stepCountJump = 0;
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

/*Sets isMoving/isJumping to true (if user pressed to move or jump,
respectively). */
void Worm::start(int keyCode, int whichMove) {

	if (whichMove == 1)
		isJumping = true;

	else
		isMoving = true;
}

/*Sets isMoving/isJumping to false, and resets corresponding stepCount to 0.*/
void Worm::stop(int keyCode, int whichMove) {
	if (whichMove == -1) {
		isMoving = false;
		stepCountMove = 0;
	}
	else {
		isJumping = false;
		stepCountJump = 0;
	}
}

/*Class getters.*/
float Worm::getXPos(void) { return xPos; }
float Worm::getYPos(void) { return yPos; }
int Worm::getStepMove(void) { return stepCountMove; }
int Worm::getStepJump(void) { return stepCountJump; }
bool Worm::getMovementState(void) { return isMoving; }
bool Worm::getJumpState(void) { return isJumping; }

/*If the worm was moving/jumping, it updates the corresponding stepCount 
and returns true. Otherwise, it returns false.*/
void Worm::updateStep(void) {

	if (isMoving)
		stepCountMove++;

	else if (isJumping)
		stepCountJump++;
}

