#include "stdafx.h"
#include "Bullet.h"
#include "Enemy.h"
#include "EnemyBullet.h"

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}


void Enemy::init(float x, float y, D3DXVECTOR2 moveDir, D3DXVECTOR2 bulletDir)
{
	enabled = true;
	onCol = true;
	life = 3;
	enemies.push_back(this);
	D3DXVec2Normalize(&this->moveDir, &moveDir);
	D3DXVec2Normalize(&this->bulletDir, &bulletDir);
	imageSizeX = 64; imageSizeY = 64;
	xPos = x;
	yPos = y;
	shotDelayStart = GetTickCount();

}

void Enemy::fire()
{
	if (shotDelayEnd - shotDelayStart > 2000) // 2초마다 fire
	{
		shotDelayStart = GetTickCount();
		EnemyBullet *bullet = new EnemyBullet;
		bullet->init(xPos + 20, yPos + 32,bulletDir);
	}
}
void Enemy::move()
{
	xPos += moveDir.x * 4.0f;
	yPos += moveDir.y * 4.0f;
	if (xPos < 0 || xPos > SCREEN_WIDTH - 64
		|| yPos < 0 || yPos > SCREEN_HEIGHT - 280)
		enabled = false;

}
void Enemy::update()
{
	shotDelayEnd = GetTickCount();
	if (enabled == false) {
		destroy(this);
		return;
	}
	move();
	fire();
	for (auto bullet : bullets) // 모든총알과 충돌체크
	{
		if (bullet->getEnabled() == false) continue;
		if (bullet->getSpecial()) continue;
		if (onCollision(bullet) == true)
		{

			decreaseLife(bullet->getDamage());
			score += 5;
			bullet->setActive(false);
			bullet->setExplosion(true);
			break;
		}
	}
	if (life < 1)
		destroy(this);
}
void Enemy::dead()
{
	destroy(this);
}



