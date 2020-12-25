#include "stdafx.h"
#include "GameObject.h"
#include "Transform.h"
#include "BlockScript.h"
#include "MoveScript.h"


MoveScript::MoveScript(GameObject* gameObject)
	: Component(gameObject)
{

}


MoveScript::~MoveScript()
{
}

void MoveScript::start()
{
	gameObject->setPosition(Vector2(1,1));
}

void MoveScript::move(Vector2& pos, Vector2 direction)
{
	if(	(gameObject->getComponent<BlockScript>() == nullptr) )return;

	BlockScript* bScript 
		= dynamic_cast<BlockScript*>(gameObject->getComponent<BlockScript>());


	if (bScript	->canMoveCheck(pos + direction) == true
		&&
		bScript	->inMapCheck(pos + direction) == true)

		pos += direction;

}

void MoveScript::update()
{

	Vector2& pos = gameObject->getPosition();

	move(pos, Vector2(0, 0.5));
	if (Input::GetKeyDown(KeyCode::Left))
	{
		move(pos, Vector2(-1, 0));
	}

	if (Input::GetKeyDown(KeyCode::Right))
	{
		move(pos, Vector2(1, 0));
	}
	if (Input::GetKeyDown(KeyCode::Down))
	{
		move(pos, Vector2(0, 1));
	}
	if (Input::GetKeyDown(KeyCode::Space))
	{
		dropBlock(pos);
	}

}

void MoveScript::dropBlock(Vector2& pos)
{
	if ((gameObject->getComponent<BlockScript>() == nullptr))return;

	BlockScript* bScript
		= dynamic_cast<BlockScript*>(gameObject->getComponent<BlockScript>());


	if (bScript->canMoveCheck(pos + Vector2(0, 0.5)) == true
		&&
		bScript->inMapCheck(pos + Vector2(0, 0.5)) == true)
	{
		pos += Vector2(0, 0.5);
		dropBlock(pos);
	}

}
