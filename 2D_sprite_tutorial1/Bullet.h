#pragma once
#include "GameObject.h"

class Bullet
	: public GameObject
{
	bool explosion;
	bool rePaint;
	int damage;
	float speed;
	bool special;
	DWORD start = GetTickCount();

public:
	Bullet();
	~Bullet();

	void init(float x, float y,int power);
	void move();
	void update();
	int getDamage() { return damage; }
	void setRePaint(bool key) { rePaint = key; }
	bool getRePaint() { return rePaint; }
	bool getExplosion();
	void setExplosion(bool key);
	void setSpecial() {  special = true; }
	bool getSpecial() { return special; }
};

