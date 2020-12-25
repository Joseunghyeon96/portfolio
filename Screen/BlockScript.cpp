#include "stdafx.h"
#include "BlockScript.h"
#include "GameObject.h"
#include "ShapeScript.h"
#include "MapScript.h"
#include "UIScript.h"
#include "MoveScript.h"


BlockScript::BlockScript(GameObject* gameObject)
	:Component(gameObject),screen(Screen::getInstance())
{
}


BlockScript::~BlockScript()
{
}

/* 초기화 */
void BlockScript::start()
{
	block = static_cast<ShapeScript*>(gameObject->getComponent<ShapeScript>())->getRandomBlock();
	nextBlock = static_cast<ShapeScript*>(gameObject->getComponent<ShapeScript>())->getRandomBlock();
	iter = block.begin();
	gameObject->setScale((*iter)->size);
	gameObject->setShape((*iter)->shape);
}

/* 스크린에 그려주는 함수 */
void BlockScript::draw()
{
	screen.blockDraw(gameObject->getShape().c_str()
		, gameObject->getScale().X(), gameObject->getScale().Y(),
		gameObject->getPosition());

	ghostDraw();
}

void BlockScript::ghostDraw()
{
	Vector2 pos = gameObject->getPosition();


	static_cast<MoveScript*>(gameObject->getComponent<MoveScript>())->dropBlock(pos);
	screen.ghostBlockDraw(gameObject->getShape().c_str()
		, gameObject->getScale().X(), gameObject->getScale().Y(),
		pos);
}

void BlockScript::update()
{

	if (Input::GetKeyDown(KeyCode::Up))
	{
		rotationBlock();
	}

}

void BlockScript::lateUpdate()
{
	if (buildCheck()) {
		buildBlock();
		setRandomBlock();
	}
}

void BlockScript::setRandomBlock()
{
	block = nextBlock;
	nextBlock = static_cast<ShapeScript*>(gameObject->getComponent<ShapeScript>())->getRandomBlock();
	iter = block.begin();
	gameObject->setScale((*iter)->size);
	gameObject->setShape((*iter)->shape);
	gameObject->setPosition(Vector2(MAP_SIZE_X/2, 1));
}

/* 블럭 회전 함수*/
void BlockScript::rotationBlock()
{
	Vector2& pos = gameObject->getPosition();

	/* 다음블럭 불러오기*/
	vector<Block* >::iterator rotatedBlock;
	if (iter + 1 == block.end())
		rotatedBlock = block.begin();
	else
		rotatedBlock = iter + 1;

	/* 회전시 맵 Y를 넘어가면 회전 x*/
	if (pos.Y() + (*rotatedBlock)->size.Y() - 1 > MAP_SIZE_Y)
		return;

	/* 회전했을때 맵(X축)을 넘어가는지 확인  이 때 왼쪽 상단을 기준으로 회전하기때문에 왼쪽은 체크 x*/
	if (pos.X() + (*rotatedBlock)->size.X() - 1 > MAP_SIZE_X)
	{
		for (int w = 1; w < (*rotatedBlock)->size.X(); w++)
		{
			if (canMoveCheck(pos + Vector2(-w, 0))) //왼쪽으로 이동가능 한경우에만 회전가능여부 체크
			{
				pos += Vector2(-w, 0); // 왼쪽으로 위치이동
				if (canRotation()) //이동시에 회전가능하면 회전
				{
					iter++;
					if (iter == block.end())
					{
						iter = block.begin();
					}
					gameObject->setScale((*iter)->size);
					gameObject->setShape((*iter)->shape);
					return;
				}
				else // 이동해도 회전이 불가능하면
				{
					pos -= Vector2(-w, 0); // 이동해줬던걸 원위치 시켜준다.
				}
			}
		}
	}
	
	/* 맵을 안넘어 가는 경우 */
	else
	{
		if (canRotation() == false) return;

		iter++;
		if (iter == block.end())
		{
			iter = block.begin();
		}
		gameObject->setScale((*iter)->size);
		gameObject->setShape((*iter)->shape);
	}
}

/* 블럭을 쌓는 함수 
   쌓을 때 스크린이 아닌 맵에 그려줌 */
void BlockScript::buildBlock()
{

	MapScript* mapScript = 
		static_cast<MapScript *>(gameObject->Find("map")->getComponent<MapScript>());


	mapScript->changeMap(gameObject->getShape().c_str()
		, gameObject->getScale().X(), gameObject->getScale().Y(),
		gameObject->getPosition());
}

/* 블럭을 쌓을 수 있는지 체크*/
bool BlockScript::buildCheck()
{
	if (gameObject->Find("map") == nullptr) return false;

	GameObject* map = gameObject->Find("map");;
	const char* mapShape = (map->getShape()).c_str();


	Vector2 pos = gameObject->getPosition();
	Vector2 size = (*iter)->size;
	if (pos.y + size.y == MAP_SIZE_Y + 1)
		return true;


	if (mapShape[pos.X() + MAP_SIZE_X] == '\xDB')
		return true;


	const char* blockShape = (gameObject->getShape()).c_str();
	for (int h = 0; h < size.Y(); h++)
	{
		for (int w = 0; w < size.X(); w++)
		{
			if (blockShape[w + h * size.X()] != '\xDB') continue; // 블럭모양이 아니면 체크 x

			if (mapShape[pos.X() -1 + w + (pos.Y() + h )*MAP_SIZE_X] == '\xDB')
				return true;
		}
	}


	return false;
}

Block* BlockScript::getNextBlockToUI()
{
	return nextBlock[0];
}


/* 이동후에 맵안에 위치하는지 체크*/
bool BlockScript::inMapCheck(Vector2 afterMovePos)
{
	Vector2 size = (*iter)->size;
	if (afterMovePos.x + size.x <= MAP_SIZE_X + 1
		&& afterMovePos.x >0
		&& afterMovePos.y + size.y <= MAP_SIZE_Y + 1) return true;

	else
	{
		return false;
	}
}

/* 이동후에 다른 블럭위에 겹치는지 체크*/
bool BlockScript::canMoveCheck(Vector2 afterMovePos)
{
	const char* blockShape = (gameObject->getShape()).c_str();
	Vector2 size = (*iter)->size;
	GameObject* map = gameObject->Find("map");
	MapScript* mapScript = static_cast<MapScript *>(map->getComponent<MapScript>());
	char* mapShape = mapScript->getMap();

	for (int h = 0; h < size.Y(); h++)
	{
		for (int w = 0; w < size.X(); w++)
		{
			if (blockShape[w + h * size.X()] != '\xDB') continue; // 블럭모양이 아니면 체크 x

			if (mapShape[afterMovePos.X() - 1 + w + (afterMovePos.Y() + h - 1)*MAP_SIZE_X] == '\xDB')
				return false;
		}
	}

	return true;
}

/* 회전이 가능한지 체크*/
bool BlockScript::canRotation()
{
	if (gameObject->Find("map") == nullptr) return false;

	GameObject* map = gameObject->Find("map");;
	const char* mapShape = (map->getShape()).c_str();
	Vector2& pos = gameObject->getPosition();

	/* 다음블럭 불러오기*/
	vector<Block* >::iterator rotatedBlock;
	if (iter + 1 == block.end())
		rotatedBlock = block.begin();
	else
		rotatedBlock = iter + 1;

	/* 회전시 맵을 넘어가면 회전 x*/
	if (pos.Y() + (*rotatedBlock)->size.Y() - 1 > MAP_SIZE_Y  
		|| pos.X() + (*rotatedBlock)->size.X() - 1 > MAP_SIZE_X)
		return false;





	/* 회전 후 블럭위치에 다른블럭이 있나 체크 */
	for (int h = 0; h < (*rotatedBlock)->size.Y(); h++)
	{
		for (int w = 0; w < (*rotatedBlock)->size.X(); w++)
		{
			// 블럭칸이 아니면 체크 x
			if ((*rotatedBlock)->shape[w + h * (*rotatedBlock)->size.X()] != '\xDB') continue; // 블럭모양이 아니면 체크 x

			/* 회전 블럭위치에 이미 블럭이 존재한다면 */
			if (mapShape[pos.X() - 1 + w + (pos.Y() - 1 + h)*MAP_SIZE_X] == '\xDB')
			{
				/* 블럭을 왼쪽으로 1~ x 사이즈만큼 옮겨보고 
				그래도 불가능하다면 false 리턴 
				옮겼을때 가능하다면 옮기고 true리턴*/
				for (int w = 1; w < (*rotatedBlock)->size.X(); w++)
				{
					if (canMoveCheck(pos + Vector2(-w, 0))) //왼쪽으로 이동가능 한지 체크
					{
						pos += Vector2(-w, 0); // 왼쪽으로 위치이동
						if (canRotation()) //이동시에 회전가능하면
						{
							return true;
						}
						else // 이동해도 회전이 불가능하면
						{
							pos -= Vector2(-w, 0); // 이동해줬던걸 원위치 시켜준다.
							return false;
						}
					}
				}
			}
		}
	}

	return true;
}
