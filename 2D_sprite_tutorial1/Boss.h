#pragma once
#include "GameObject.h"

class Hero;

class Boss :
	public GameObject
{
	float ySpeed;
	float xSpeed;
	bool easy2;
	bool easy3;
	bool hard_3;
	bool hard_4;
	bool hard_5;
	bool hard_6;
	Hero* target;
	DWORD pattern;
	D3DXVECTOR2 moveDir;
public:
	Boss();
	~Boss();
	void init(float x, float y,Hero* hero);
	void update();
	void move();
	void hit();
	int getLife() { return life; }
	void easyPattern_1();
	void easyPattern_2();
	void easyPattern_3();
	void hardPattern_1();
	void hardPattern_2();
	void hardPattern_3();
	void hardPattern_4();
	void hardPattern_5();
	void hardPattern_6();
};

