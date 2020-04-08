#pragma once

#define MAXKEYS 4
class Worm{
public:
	Worm();

	void setJumpKey(int validEvent_);
	void setMoveKeys(const int* validEvents_, int amount);

	int checkKeyCode (int keyCode);

	void stop(int keyCode, int whichMove);

	float getXPos(void);
	float getYPos(void);
	int getStepMove(void);
	int getStepJump(void);
	void updateStep(void);

	bool getMovementState(void);
	bool getJumpState(void);

	void start(int keyCode, int whichMove);

private:
	bool isMoving, isJumping;
	int stepCountMove, stepCountJump;
	//int numJumpKeys, numMoveKeys;
	int jumpKey;
	int moveKeys[MAXKEYS];
	float xPos, yPos;
};

