#define _USE_MATH_DEFINES

#include "Worm.h"
#include <iostream>
#include <cmath>

#define STARTINGY 616
#define MODULE 4.5
#define GRAVITY 0.24
#define MINX 701
#define MAXX 1212


/*#define INITIALYSPEED (FROM FORMULA)*/
/*Worm constructor. Sets variables to initial values.*/
Worm::Worm() {
	isMoving = false;
	isJumping = false;
	isJumpPressed = false;
	timer = 0;

	stepCountMove = 0;
	stepCountJump = 0;

	xPos = rand() % (MAXX - MINX + 1) + MINX;
	yPos = STARTINGY;
	/*ySpeed = INITIALYSPEED*/ ;

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
// sets timer
void Worm::setTimer(int MSECS) {
	timer = MSECS;
}
// adds to timer
void Worm::addTimer(int MSECS) {
	timer += MSECS;
}
// gets timer 
int Worm::getTimer(void) {
	return timer;
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

	/*If user pressed moving key...*/
	if (whichMove == -1) {
		if (!isJumping) {
			isMoving = true;

			/*If it's to the left, direction = -1. Otherwise, direction = 1.*/
			if (keyCode == *moveKeys)
				direction = -1;
			else
				direction = 1;
		}
	}

	/*If user pressed jumping key...*/
	else {
		if (!isMoving) {
			isJumping = true;
			isJumpPressed = true;
		}
	}
}



/*Sets corresponding key state to false.*/
void Worm::stop(int keyCode, int whichMove) {
	int HHH = 3; //Define actual value.

	/*If moving key was released...*/
	if (whichMove == -1) {

		/*Sets key state to false.*/
		isMovePressed = false;

		/*If the 100ms hadn't elapsed...*/
		if (stepCountMove < HHH) {

			/*The worm isn't moving, so it resets isMoving and stepCount Move.
			The worm's direction changes to its opposite.*/
			isMoving = false;
			stepCountMove = 0;
			direction *= -1;
		}
	}
	else
		isJumpPressed = false;
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
	int XXX = 15, YYY = 5,WWW = 50; //Define actual step values for position change.
	
	/*If worm is moving horizontally...*/
	if (isMoving) {

		/*If it has to move, it updates xPos.*/
		if (stepCountMove == XXX)
			xPos += direction * 9;

		/*If movement has finished, it resets stepCountMove and isMoving.*/
		if (stepCountMove == 15) {
			isMoving = isMovePressed;
			stepCountMove = 0;
		}

		/*If not, then it increases stepCountMove. */
		else
			stepCountMove++;
	}

	/*If worm is jumping...*/
	else if (isJumping) {

		/*If jump has finished, it resets stepCountMove and isJumping.*/
		if (stepCountJump == YYY) {
			isJumping = isJumpPressed;
			stepCountJump = 0;
			/*ySpeed = INITIALYSPEED*/
		}

		/*If worm has to move, then it updates xPos, yPos, ySpeed and stepCountJump. */
		else {
			xPos += direction * cos(M_PI / 3) * MODULE /* /FRAMES*/;
			yPos += direction * ySpeed;
			ySpeed -= GRAVITY;
			stepCountJump++;
		}

	}
}
