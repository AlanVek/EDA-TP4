#pragma once
#define CHANGEDIR 1
#define STOPMOVING 2
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
	void setTimer(int);
	void addTimer(int);
	int getTimer(void);

	bool getMovementState(void);
	bool getJumpState(void);

	void start(int keyCode, int whichMove);

private:
	int timer;
	bool isMoving, isJumping, isJumpPressed, isMovePressed;
	int stepCountMove, stepCountJump;
	//int numJumpKeys, numMoveKeys;
	int jumpKey;
	int moveKeys[MAXKEYS];
	float xPos, yPos, ySpeed;
	int direction;
};

