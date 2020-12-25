#include "stdafx.h"
#include "GameObject.h"
#include "MapScript.h"


MapScript::MapScript(GameObject* gameObject)
	:Component(gameObject), map(new char[MAP_SIZE_X*MAP_SIZE_Y]), screen(Screen::getInstance())
{
	memset(map, ' ', MAP_SIZE_X*MAP_SIZE_Y);
}


MapScript::~MapScript()
{
}

void MapScript::start()
{
	gameObject->setPosition(Vector2(1, 1));
	gameObject->setShape(map);
	gameObject->setScale(Vector2(MAP_SIZE_X, MAP_SIZE_Y));
}

void MapScript::update()
{
}

void MapScript::draw()
{
	screen.draw(gameObject->getShape().c_str()
		, gameObject->getScale().X(), gameObject->getScale().Y(),
		gameObject->getPosition());

}

void MapScript::changeMap(const char * shape, int width, int height, const Vector2 & pos)
{
	if (!shape) return;
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			if (shape[w + (width*h)] != '\xDB') continue;


			map[pos.X() - 1 + w + (pos.Y() - 1 + h)*MAP_SIZE_X] = shape[w + (width*h)];
		}
	}

	gameObject->setShape(map);
}

/* 줄이 제거가 되야하는 줄이면 지워줌*/
void MapScript::deleteLine()
{
	for (int y = MAP_SIZE_Y -1; y >-1; y--) // 아래줄부터 체크
	{
		for (int x = 0; x <	MAP_SIZE_X	; x++)
		{
			if (map[x + y * MAP_SIZE_X] != '\xDB') // 한줄에 블럭아닌게 하나라도 있으면 그 줄 삭제 x
				break;
		
			if (x == MAP_SIZE_X - 1)
			{
				underingLine(y);
			}
		}
	}

	gameObject->setShape(map);
}

/* 줄을 한줄씩 아래로 밈*/
void MapScript::underingLine(int y)
{
	int startY = y;

	if (startY == 0) {
		memset(map, ' ', MAP_SIZE_X);
		return;
	}

	strncpy(&map[y*MAP_SIZE_X], &map[(y - 1)*MAP_SIZE_X], MAP_SIZE_X);
	underingLine(y-1);
}

void MapScript::lateUpdate()
{
	deleteLine();
}
