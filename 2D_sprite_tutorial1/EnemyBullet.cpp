#include "stdafx.h"
#include "EnemyBullet.h"


EnemyBullet::EnemyBullet()
{
}


EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::init(float x, float y, D3DXVECTOR2 dir)
{
	enabled = true;
	onCol = true;
	curve = false;
	enemyBullets.push_back(this);
	D3DXVec2Normalize(&direction, &dir);
	imageSizeX = 10; imageSizeY = 10;
	speed = 12;
	curveAngle = 0;
	xPos = x;
	yPos = y;
}

void EnemyBullet::init(float x, float y, D3DXVECTOR2 dir, float speed)
{
	enabled = true;
	onCol = true;
	curve = false;
	curveAngle = 0;
	enemyBullets.push_back(this);
	D3DXVec2Normalize(&direction, &dir);
	imageSizeX = 10; imageSizeY = 10;
	this->speed = speed;
	xPos = x;
	yPos = y;
}

void EnemyBullet::init(float x, float y, D3DXVECTOR2 dir, float speed, bool curve,float angle)
{
	enabled = true;
	onCol = true;
	enemyBullets.push_back(this);
	D3DXVec2Normalize(&direction, &dir);
	imageSizeX = 10; imageSizeY = 10;
	curveAngle = angle;
	startAngle = angle;
	this->speed = speed;
	this->curve = curve;
	xPos = x;
	yPos = y;
}

void EnemyBullet::move()
{
	if (curve) // 커브형 총알이면 방향 게속바꿔주기
	{
		if (startAngle + 180 > curveAngle)
		{
			direction.x += cos(D3DXToRadian(curveAngle += 0.3));
			direction.y -= sin(D3DXToRadian(curveAngle += 0.3));
			D3DXVec2Normalize(&direction, &direction);
		}

	}
	xPos += direction.x*speed; yPos += direction.y*speed;
	if (yPos > SCREEN_HEIGHT - 200 || yPos < -3 || xPos<-3 || xPos>SCREEN_WIDTH)
		enabled = false;
}

void EnemyBullet::update()
{
	if (enabled == false)
		destroy(this);
	move();
}

void EnemyBullet::destroy(GameObject * gameObject)
{

	int i = 0;
	if (dynamic_cast<EnemyBullet *>(gameObject) != nullptr)
	{
		enemyBullets.erase(remove_if(enemyBullets.begin(), enemyBullets.end(),
				[gameObject](GameObject* obj) {return obj == gameObject; })
				, enemyBullets.end());

			delete gameObject;
			gameObject = nullptr;
			return;
	}
}
