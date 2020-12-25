#pragma once
#include "GameObject.h"
class Enemy :
	public GameObject
{
	D3DXVECTOR2 bulletDir;
	D3DXVECTOR2 moveDir;
	bool onCol;
	DWORD shotDelayEnd;
	DWORD shotDelayStart;
public:
	Enemy();
	~Enemy();

	void init(float x, float y, D3DXVECTOR2 moveDir, D3DXVECTOR2 bulletDir);
	void fire();
	void move();
	void update();
	void dead();
	void setCol(bool key) { onCol = key; }
	bool getCol() { return onCol; }

};

