#include "stdafx.h"
#include "GameObject.h"
#include "MonsterScript.h"


MonsterScript::MonsterScript(GameObject* gameObject)
	:Component(gameObject),score(0)
{
}


MonsterScript::~MonsterScript()
{
}

void MonsterScript::increaseScore(int x)
{
	score += x;
}

void MonsterScript::start()
{
	int posX;
	int posY;
	if(gameObject->getName()=="monster")
	{
		posX = MAP_SIZE_X / 2;
		posY = MAP_SIZE_Y / 2;
	}
	else if (gameObject->getName() == "hellBoy")
	{
		posX = MAP_SIZE_X / 2+1;
		posY = MAP_SIZE_Y / 2;
	}
	else if (gameObject->getName() == "king")
	{
		posX = MAP_SIZE_X / 2;
		posY = MAP_SIZE_Y / 2+1;
	}
	else if (gameObject->getName() == "ghost")
	{
		posX = MAP_SIZE_X / 2+1;
		posY = MAP_SIZE_Y / 2+1;
	}

	gameObject->setPosition(Vector2(posX, posY));
	gameObject->setScale(Vector2(1, 1));
}

void MonsterScript::update()
{
	//cout << gameObject->getName() << "update function complete!" << endl;
}


