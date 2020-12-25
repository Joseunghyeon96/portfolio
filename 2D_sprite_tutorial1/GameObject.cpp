#include "stdafx.h"
#include "GameObject.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "Bullet.h"

vector<Enemy*> GameObject::enemies;
vector<Bullet*> GameObject::bullets;
vector<EnemyBullet*> GameObject::enemyBullets;
int GameObject::score = 0;

GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

float GameObject::getXPos()
{
	return xPos;
}

float GameObject::getYPos()
{
  	return yPos;
}

void GameObject::destroy(GameObject * gameObject)
{
	gameObject->enabled = false;
	int i = 0;
	if (dynamic_cast<Enemy *>(gameObject) != nullptr)
	{
		enemies.erase(remove_if(enemies.begin(), enemies.end(),
			[gameObject](GameObject* obj) {return obj == gameObject;})
			, enemies.end());

		delete gameObject;
		gameObject = nullptr;
		return;
	}
	if (dynamic_cast<Bullet *>(gameObject) != nullptr)
	{
		bullets.erase(remove_if(bullets.begin(), bullets.end(),
			[gameObject](GameObject* obj) {return obj == gameObject; })
			, bullets.end());

		delete gameObject;
		gameObject = nullptr;
		return;
	}
}

void GameObject::decreaseLife(int x)
{
	life -= x;
}

// 충돌시 true 리턴함수 
bool GameObject::onCollision(GameObject * gameObject)
{
	if (enabled == false) return false;


	float x, y;
	x = xPos + imageSizeX / 2;
	y = yPos + imageSizeY / 2;
	if (gameObject->getXPos() < x&& gameObject->getYPos() < y) // 인자로 들어온 오브젝트의 위치가 내위치 기준 2사분면
	{
		if (gameObject->getXPos() + gameObject->getSizeX() > x - imageSizeX / 2)
		{
			if (gameObject->getYPos() + gameObject->getSizeY() > y - imageSizeY / 2)
			{
				return true;
			}
		}
	}
	else if (gameObject->getXPos() < x&&gameObject->getYPos() > y) // 인자로 들어온 오브젝트의 위치가 내위치 기준 3사분면
	{
		if (gameObject->getXPos() + gameObject->getSizeX() > x - imageSizeX / 2)
		{
			if (gameObject->getYPos() < y + imageSizeY / 2)
			{
				return true;
			}
		}

	}
	else if (gameObject->getXPos() > x&&gameObject->getYPos() > y) // 인자로 들어온 오브젝트의 위치가 내위치 기준 4사분면
	{
		if (gameObject->getXPos() < x + imageSizeX / 2)
		{
			if (gameObject->getYPos() < y + imageSizeY / 2)
			{
				return true;
			}
		}

	}
	else if (gameObject->getXPos() > x&&gameObject->getYPos() < y) // 인자로 들어온 오브젝트의 위치가 내위치 기준 1사분면
	{
		if (gameObject->getXPos() < x + imageSizeX / 2)
		{
			if (gameObject->getYPos() + imageSizeY > y - imageSizeY / 2)
			{
				return true;
			}
		}
	}

	return false;
}

void GameObject::init(float x, float y)
{
	enabled = true;
	xPos = x;
	yPos = y;
}

void GameObject::update()
{
}

vector<Enemy*> GameObject::getEnemies()
{
	return enemies;
}

vector<Bullet*> GameObject::getBullets()
{
	return bullets;
}

vector<EnemyBullet*> GameObject::getEnemyBullets()
{
	return enemyBullets;
}
