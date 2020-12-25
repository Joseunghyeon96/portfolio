#pragma once
#include "GameObject.h"
class EnemyBullet :
	public GameObject
{
	D3DXVECTOR2 direction;
	bool curve;
	bool onCol;
	float speed;
	float curveAngle;
	float startAngle;
public:
	EnemyBullet();
	~EnemyBullet();

	void init(float x, float y, D3DXVECTOR2 dir);
	void init(float x, float y, D3DXVECTOR2 dir,float speed);
	void init(float x, float y, D3DXVECTOR2 dir, float speed,bool curve,float angle);
	void move();
	void update();
	void setCol(bool key) { onCol = key; }
	bool getCol() { return onCol; }
	void destroy(GameObject* gameObject);
};

