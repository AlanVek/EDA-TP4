#define _USE_MATH_DEFINES

#include "Worm.h"
#include <iostream>
#include <cmath>

#define STARTINGY 616
#define MODULE 4.5

/*Worm constructor. Sets variables to initial values.*/
Worm::Worm() {
	isMoving = false;
	isJumping = false;

	stepCountMove = 0;
	stepCountJump = 0;

	xPos = 100;
	yPos = STARTINGY;

	jumpKey = NULL;
	for (int i = 0; i < MAXKEYS; i++)
		moveKeys[i] = NULL;

	direction = 1;
};

/* Recieves a key and sets it to jumping key.*/
void Worm::setJumpKey(int validEvent_) {
	jumpKey = validEvent_;
}
/* Recieves an array of keys and sets them to moving keys.*/
void Worm::setMoveKeys(const int* validEvents_, int amount) {
	for (int i = 0; i < amount; i++)
		moveKeys[i] = validEvents_[i];
}

/*Checks if the given keyCode is linked to any movement.
If it's jumping, it returns 1. If it's moving, it returns -1.
If it's neither, it returns 0.*/
int Worm::checkKeyCode(int keyCode) {
	if (keyCode == jumpKey)
		return 1;

	for (int i = 0; i < MAXKEYS; i++) {
		if (moveKeys[i] == keyCode)
			return -1;
	}

	return 0;
}

/*Sets isMoving/isJumping to true (if user pressed to move or jump,
respectively). */
void Worm::start(int keyCode, int whichMove) {

	if (whichMove == -1) {
		isMoving = true;
		if (keyCode == *moveKeys)
			direction = -1;
		else
			direction = 1;
	}

	else
		isJumping = true;
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
	int XXX = 0, YYY = 0; //Define actual step values for position change.
	if (isMoving) {
		stepCountMove++;
		if (stepCountMove == XXX)
			xPos += direction * 9;
	}

	else if (isJumping) {
		stepCountJump++;
		if (stepCountJump == YYY) {
			xPos += direction * cos(M_PI / 3) * MODULE;
			yPos += direction * sin(M_PI / 3) * MODULE;
		}
	}
}
