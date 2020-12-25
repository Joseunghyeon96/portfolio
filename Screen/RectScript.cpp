#include "stdafx.h"
#include "GameObject.h"
#include "RectScript.h"


RectScript::RectScript(GameObject* gameObject)
	:Component(gameObject),rect(new char[(MAP_SIZE_X+2)*(MAP_SIZE_Y+2)+1]),screen(Screen::getInstance())
{
	memset(rect, ' ', (MAP_SIZE_X + 2)*(MAP_SIZE_Y+2));
	rect[(MAP_SIZE_X + 2)*(MAP_SIZE_Y + 2)] = '\0';
}


RectScript::~RectScript()
{
}

void RectScript::start()
{
	memset(rect, '\xCD', MAP_SIZE_X + 2);
	rect[0] = '\xC9';
	rect[MAP_SIZE_X+ 2-1] = '\xBB';

	for (int i = 1; i < MAP_SIZE_Y+2; i++)
	{
		rect[(MAP_SIZE_X + 2)*i] = '\xBA';
		rect[(MAP_SIZE_X + 2)*i + MAP_SIZE_X + 1] = '\xBA';
	}

	memset(&rect[(MAP_SIZE_X + 2)*(MAP_SIZE_Y + 1)], '\xCD', MAP_SIZE_X + 2);
	rect[(MAP_SIZE_X + 2)*(MAP_SIZE_Y + 1)] = '\xC8';
	rect[(MAP_SIZE_X + 2)*(MAP_SIZE_Y + 2)-1] = '\xBC';

	gameObject->setPosition(Vector2(0, 0));
	gameObject->setShape(rect);
	gameObject->setScale(Vector2(MAP_SIZE_X+2, MAP_SIZE_Y+2));
}

void RectScript::draw()
{
	screen.draw(gameObject->getShape().c_str()
				, gameObject->getScale().X(), gameObject->getScale().Y(),
				gameObject->getPosition());
}
