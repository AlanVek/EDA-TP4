#include "Worm.h"

Worm::Worm() {
	isMoving = false;
	stepCount = 0;
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

void Worm::move(int keyCode, int whichMove) {

	if (whichMove == 1)
		jump();

	walk();
}