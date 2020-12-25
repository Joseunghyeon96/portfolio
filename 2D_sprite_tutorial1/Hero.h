#pragma once
#include "GameObject.h"
class Hero :
	public GameObject
{
	int power;
	int superBullet;
	bool canPowerUp;
	bool autoMove;
	float speed;
	bool cheat;
	bool moveCheck;
	DWORD shotDelayEnd;
	DWORD shotDelayStart;
	DWORD immortStart;
public:
	Hero();
	~Hero();

	void fire();
	void super_fire();
	int getLife() { return life; }
	int getPower() { return power; }
	void move(int i);
	void init(float x, float y);
	void collisionCheck();
	void update();
	void powerUp();
	void setMoveCheck(bool key) { moveCheck = key; }
	bool getPowerUp() { return canPowerUp; }
	bool getCheat() { return cheat; }
	void cheating();
	int getSB() { return superBullet; }
};

