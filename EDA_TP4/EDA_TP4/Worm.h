#pragma once

#define MAXKEYS 4
class Worm{
public:
	Worm();

	void setJumpKeys(const int* validEvents_, int amount);
	void setMoveKeys(const int* validEvents_, int amount);

	int checkKeyCode (int keyCode);

	void jump(void);
	void walk(void);

	void move(int keyCode, int whichMove);

private:
	bool isMoving;
	int stepCount;
	int numJumpKeys, numMoveKeys;
	int jumpKeys[MAXKEYS];
	int moveKeys[MAXKEYS];
};

