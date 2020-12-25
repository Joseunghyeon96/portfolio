#include "stdafx.h"
#include "GameObject.h"
#include "MapScript.h"
#include "Transform.h"
#include "MonsterScript.h"
#include "UIScript.h"
#include "FoodScript.h"


FoodScript::FoodScript(GameObject* gameObject)
	:Component(gameObject),objs(GameObject::getObjs())
{
}


FoodScript::~FoodScript()
{
}

void FoodScript::start()
{

	static int xPos=1;
	static int yPos=1;

	gameObject->setPosition(Vector2(xPos, yPos));
	gameObject->setScale(Vector2(1, 1));

	xPos++;

	if (xPos > MAP_SIZE_X)
	{
		xPos = 1;
		yPos++;
	}

}

void FoodScript::update()
{
	onCollision();
}

void FoodScript::onCollision()
{

	vector<GameObject*> monsters = GameObject::allFind("monster");

	for (auto monster : monsters)
	{
		if (monster->getTransform()->getPos() == gameObject->getTransform()->getPos())
		{
			gameObject->destroy(gameObject);
			static_cast<MonsterScript*>(monster->getComponent<MonsterScript>())->increaseScore(1);
			static_cast<UIScript*>(GameObject::Find("UI")->getComponent<UIScript>())->decreaseFoodNum();
			return;
		}
		
	}
}
