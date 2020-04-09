#define _USE_MATH_DEFINES

#include "Worm.h"
#include <iostream>
#include <cmath>

#define STARTINGY 616
#define MODULE 4.5
#define GRAVITY 0.24
#define MINX 701
#define LEFT_SIDE_OFFSET -20
#define RIGHT_SIDE_OFFSET -39
#define MAXX 1212
#define IDLEFRAMES 8.0
#define CHECKINGFRAMES 5
#define MOVEMENT 9
#define ANGLE M_PI/3
#define INITIALYSPEED -sin(ANGLE)*MODULE
#define FALLFRAMES ((-1*INITIALYSPEED)/(0.5*GRAVITY))
#define FPS 50.0

using namespace std;

/*Worm constructor. Sets variables to initial values.*/
Worm::Worm() {
	isMoving = false;
	isJumping = false;
	isJumpPressed = false;
	//timer = 0;

	stepCountMove = 0;
	stepCountJump = 0;
	tempStepCountMove = 0;
	tempStepCountJump = 0;

	xPos = rand() % (MAXX - MINX + 1) + MINX;
	yPos = STARTINGY;
	ySpeed = INITIALYSPEED ;

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

	/*If user pressed moving key...*/
	if (whichMove == -1) {
		if (!isJumping && !isMoving) {
			isMoving = true;
			isMovePressed = true;
			/*If it's to the left, direction = -1. Otherwise, direction = 1.*/
			if (keyCode == *moveKeys)
				direction = -1;
			else {
				direction = 1;
			}
			stepCountMove = 0;
		}
	}

	/*If user pressed jumping key...*/
	else {
		if (!isMoving && !isJumping) {
			isJumping = true;
			isJumpPressed = true;
			stepCountJump++;
		}
	}
}

/*Sets corresponding key state to false.*/
void Worm::stop(int keyCode, int whichMove) {

	/*If moving key was released...*/
	if (whichMove == -1) {

		/*Sets key state to false.*/
		isMovePressed = false;

		/*If the 100ms hadn't elapsed...*/
		if (tempStepCountMove< CHECKINGFRAMES) {

			/*The worm isn't moving, so it resets isMoving and stepCount Move.
			The worm's direction changes to its opposite.*/
			isMoving = false;
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
int Worm::getDirection() { return direction; }


/*If the worm was moving/jumping, it updates the corresponding stepCount 
and returns true. Otherwise, it returns false.*/
void Worm::updateStep(void) {

	/*If worm is moving horizontally...*/
	if (isMoving) {

		/*If worm is still in first five ticks + 3 warm-up, it doesn't update stepCountMove.*/
		if (tempStepCountMove < IDLEFRAMES)
			tempStepCountMove++;
		
		/*Afterwards, stepCountMove is updated every tick.*/
		else
			stepCountMove++;

		/*Once stepCountMove reached limit, it's reset (without the 3 warm-up).
		Also, worm's position is updated.*/
		if (stepCountMove == XFRAMES) {
			stepCountMove = 3;

			/*Checks if worm is within allowed range.*/
			xPos += MOVEMENT * direction;		
			if (xPos > MAXX + RIGHT_SIDE_OFFSET || xPos < MINX + LEFT_SIDE_OFFSET)
				xPos -= MOVEMENT * direction;
			tempStepCountMove++;
		}

		/*After full cycle (50 ticks), it resets all flags.*/
		if (tempStepCountMove == IDLEFRAMES + 3) {
			isMoving = isMovePressed;
			tempStepCountMove = 0;
			stepCountMove = 0;
		}
	}

	/*If worm is jumping...*/
	else if (isJumping) {

		tempStepCountJump++;

		/*Until the 4th image, the position doesn't change.
		The image is updated every 2 frames. */
		if (tempStepCountJump <= IDLEFRAMES) {
			if (!(tempStepCountJump % 2))
				stepCountJump++;
		}

		//Then, there are approximately 34 more cycles of position change.
		else if (tempStepCountJump <= ((IDLEFRAMES + FALLFRAMES+2))) {

			/*Updates position, checking and correcting if it's gone out of range.*/
			xPos += direction * cos(ANGLE) * MODULE;
			
			if (xPos > MAXX + RIGHT_SIDE_OFFSET || xPos < MINX + LEFT_SIDE_OFFSET)
				xPos -= direction * cos(ANGLE) * MODULE;

			yPos += ySpeed;
			if (yPos > STARTINGY)
				yPos = STARTINGY;
			ySpeed += GRAVITY;
		}
		//After the fall, the image is updated every 2 frames.
		else if (tempStepCountJump<=FPS){
			if (tempStepCountJump % 2)
				stepCountJump++;
		}

		/*After the full 50 frames, everything goes back to original values. */
		else{
			isJumping = isJumpPressed;
			yPos = STARTINGY;
			ySpeed = INITIALYSPEED;
			tempStepCountJump = 0;
			stepCountJump = 0;
		}

	}
}