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

/* �ʱ�ȭ */
void BlockScript::start()
{
	block = static_cast<ShapeScript*>(gameObject->getComponent<ShapeScript>())->getRandomBlock();
	nextBlock = static_cast<ShapeScript*>(gameObject->getComponent<ShapeScript>())->getRandomBlock();
	iter = block.begin();
	gameObject->setScale((*iter)->size);
	gameObject->setShape((*iter)->shape);
}

/* ��ũ���� �׷��ִ� �Լ� */
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

/* �� ȸ�� �Լ�*/
void BlockScript::rotationBlock()
{
	Vector2& pos = gameObject->getPosition();

	/* ������ �ҷ�����*/
	vector<Block* >::iterator rotatedBlock;
	if (iter + 1 == block.end())
		rotatedBlock = block.begin();
	else
		rotatedBlock = iter + 1;

	/* ȸ���� �� Y�� �Ѿ�� ȸ�� x*/
	if (pos.Y() + (*rotatedBlock)->size.Y() - 1 > MAP_SIZE_Y)
		return;

	/* ȸ�������� ��(X��)�� �Ѿ���� Ȯ��  �� �� ���� ����� �������� ȸ���ϱ⶧���� ������ üũ x*/
	if (pos.X() + (*rotatedBlock)->size.X() - 1 > MAP_SIZE_X)
	{
		for (int w = 1; w < (*rotatedBlock)->size.X(); w++)
		{
			if (canMoveCheck(pos + Vector2(-w, 0))) //�������� �̵����� �Ѱ�쿡�� ȸ�����ɿ��� üũ
			{
				pos += Vector2(-w, 0); // �������� ��ġ�̵�
				if (canRotation()) //�̵��ÿ� ȸ�������ϸ� ȸ��
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
				else // �̵��ص� ȸ���� �Ұ����ϸ�
				{
					pos -= Vector2(-w, 0); // �̵�������� ����ġ �����ش�.
				}
			}
		}
	}
	
	/* ���� �ȳѾ� ���� ��� */
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

/* ���� �״� �Լ� 
   ���� �� ��ũ���� �ƴ� �ʿ� �׷��� */
void BlockScript::buildBlock()
{

	MapScript* mapScript = 
		static_cast<MapScript *>(gameObject->Find("map")->getComponent<MapScript>());


	mapScript->changeMap(gameObject->getShape().c_str()
		, gameObject->getScale().X(), gameObject->getScale().Y(),
		gameObject->getPosition());
}

/* ���� ���� �� �ִ��� üũ*/
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
			if (blockShape[w + h * size.X()] != '\xDB') continue; // ������� �ƴϸ� üũ x

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


/* �̵��Ŀ� �ʾȿ� ��ġ�ϴ��� üũ*/
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

/* �̵��Ŀ� �ٸ� ������ ��ġ���� üũ*/
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
			if (blockShape[w + h * size.X()] != '\xDB') continue; // ������� �ƴϸ� üũ x

			if (mapShape[afterMovePos.X() - 1 + w + (afterMovePos.Y() + h - 1)*MAP_SIZE_X] == '\xDB')
				return false;
		}
	}

	return true;
}

/* ȸ���� �������� üũ*/
bool BlockScript::canRotation()
{
	if (gameObject->Find("map") == nullptr) return false;

	GameObject* map = gameObject->Find("map");;
	const char* mapShape = (map->getShape()).c_str();
	Vector2& pos = gameObject->getPosition();

	/* ������ �ҷ�����*/
	vector<Block* >::iterator rotatedBlock;
	if (iter + 1 == block.end())
		rotatedBlock = block.begin();
	else
		rotatedBlock = iter + 1;

	/* ȸ���� ���� �Ѿ�� ȸ�� x*/
	if (pos.Y() + (*rotatedBlock)->size.Y() - 1 > MAP_SIZE_Y  
		|| pos.X() + (*rotatedBlock)->size.X() - 1 > MAP_SIZE_X)
		return false;





	/* ȸ�� �� ����ġ�� �ٸ����� �ֳ� üũ */
	for (int h = 0; h < (*rotatedBlock)->size.Y(); h++)
	{
		for (int w = 0; w < (*rotatedBlock)->size.X(); w++)
		{
			// ��ĭ�� �ƴϸ� üũ x
			if ((*rotatedBlock)->shape[w + h * (*rotatedBlock)->size.X()] != '\xDB') continue; // ������� �ƴϸ� üũ x

			/* ȸ�� ����ġ�� �̹� ���� �����Ѵٸ� */
			if (mapShape[pos.X() - 1 + w + (pos.Y() - 1 + h)*MAP_SIZE_X] == '\xDB')
			{
				/* ���� �������� 1~ x �����ŭ �Űܺ��� 
				�׷��� �Ұ����ϴٸ� false ���� 
				�Ű����� �����ϴٸ� �ű�� true����*/
				for (int w = 1; w < (*rotatedBlock)->size.X(); w++)
				{
					if (canMoveCheck(pos + Vector2(-w, 0))) //�������� �̵����� ���� üũ
					{
						pos += Vector2(-w, 0); // �������� ��ġ�̵�
						if (canRotation()) //�̵��ÿ� ȸ�������ϸ�
						{
							return true;
						}
						else // �̵��ص� ȸ���� �Ұ����ϸ�
						{
							pos -= Vector2(-w, 0); // �̵�������� ����ġ �����ش�.
							return false;
						}
					}
				}
			}
		}
	}

	return true;
}
