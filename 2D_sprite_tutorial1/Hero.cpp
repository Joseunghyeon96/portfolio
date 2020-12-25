#include "stdafx.h"
#include "Hero.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "Bullet.h"


Hero::Hero()
{
}


Hero::~Hero()
{
}

void Hero::fire()
{
	if (autoMove)return;

	if (bullets.size() < 50) //50발이하일때만 생성
	{
		if (power == 1) {
			Bullet* bullet = new Bullet;
			bullet->init(xPos + imageSizeX / 2-8, yPos, power);
		}
		else if (power == 2) {
			Bullet* bullet = new Bullet;
			bullet->init(xPos + imageSizeX / 2 - 16, yPos, power);
		}
		else if (power == 3) {
			Bullet* bullet = new Bullet;
			bullet->init(xPos , yPos-32, power);
		}
		shotDelayStart = GetTickCount();
		score++;
	}
}

void Hero::super_fire()
{
	if (autoMove)return;
	if (superBullet < 1) return;

	for (EnemyBullet* eBullet : enemyBullets)
	{
		eBullet->setCol(false);
	}
	shotDelayStart = GetTickCount();
	Bullet* speBullet = new Bullet;
	speBullet->init(xPos, yPos - 32, 3);
	speBullet->setSpecial();
	superBullet--;
}

void Hero::move(int i)
{
	if (autoMove)
	{
		yPos -= 10;
		if (yPos < 900) {
			autoMove = false;
		}
		return;
	}
	switch (i)
	{
	case MOVE_UP:
		if(yPos>0)
		yPos -= speed;
		break;

	case MOVE_DOWN:
		if(yPos<SCREEN_HEIGHT-250)
		yPos += speed;
		break;


	case MOVE_LEFT:
		if(xPos>0)
		xPos -= speed;
		break;


	case MOVE_RIGHT:
		if(xPos<SCREEN_WIDTH-32)
		xPos += speed;
		break;

	}
}

void Hero::init(float x, float y)
{
	enabled = true;
	autoMove = true;
	moveCheck = false;
	cheat = false;
	superBullet = 3;
	power = 1;
	xPos = x;
	speed = 2;
	yPos = 1200;
	imageSizeX = 24; imageSizeY = 24;
	life = 3;
	score = 0;
	canPowerUp = true;
	shotDelayEnd = GetTickCount();
	immortStart = GetTickCount();
	shotDelayStart=GetTickCount();
}
void Hero::collisionCheck()
{
	if (autoMove)return;
	if (cheat) return;

	if (GetTickCount() - immortStart < 3300) return; // 맞은지 3.3초이하 면 충돌체크 x

	for (auto enemy : enemies) //모든적과 충돌체크
	{
		if (!enemy->getCol()) break;

		if (onCollision(enemy) == true) {
			destroy(enemy); // 충돌된 적 없어짐
			power = 1;
			yPos = 2100;
			autoMove = true;
			immortStart = GetTickCount();
			life--;
			break;
		}
	}


	for (auto enemyBullet : enemyBullets) //모든적 총알 과 충돌체크
	{
		if (!enemyBullet->getCol())break;

		if (onCollision(enemyBullet) == true) {
			enemyBullet->setActive(false); // 충돌된 적 총알 없어짐
			power = 1;
			life--;
			yPos = 2100;
			autoMove = true;
			immortStart = GetTickCount();
			break;
		}
	}
}



void Hero::update()
{
	if (enabled == false)
	{
		if (KEY_DOWN(0x52))
		{
			init(xPos, yPos);
		}
		return;
	}
	shotDelayEnd = GetTickCount();

	if (autoMove)
		move(0);

	if (KEY_DOWN(VK_UP)) {
		move(MOVE_UP);
	}

	if (KEY_DOWN(VK_DOWN))
		move(MOVE_DOWN);

	if (KEY_DOWN(VK_LEFT))
		move(MOVE_LEFT);

	if (KEY_DOWN(VK_RIGHT))
		move(MOVE_RIGHT);

	cheating();

	if (moveCheck == true) return;

	if (KEY_DOWN(VK_SPACE))
	{
		if(shotDelayEnd-shotDelayStart>200)
		fire();
	}
	if (KEY_DOWN(VK_SHIFT))
	{
		if (shotDelayEnd - shotDelayStart > 100)
			super_fire();
	}
	powerUp();
	collisionCheck();
	if (life < 1)
		enabled = false;
}

void Hero::powerUp()
{
	if (score < 20) return;
	static DWORD temp;

	if (score % 500 < 20)
	{
		if (power < 3) {
			if (canPowerUp) {
				canPowerUp = false;
				temp = GetTickCount();
				if (superBullet < 3)
				{
					superBullet++;
				}
				power++;
			}
		}
	}

	else if(GetTickCount() - temp > 2000)
	{
		canPowerUp = true;
	}
}

void Hero::cheating()
{
	if (KEY_DOWN(VK_F1))
		cheat = true;
	else if (KEY_DOWN(VK_F2))
		cheat = false;
}
