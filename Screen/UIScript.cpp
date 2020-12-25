#include "stdafx.h"
#include "UIScript.h"
#include "BlockScript.h"
#include "GameObject.h"
#include "ShapeScript.h"


UIScript::UIScript(GameObject* gameObject)
	:Component(gameObject),ui(new char[UI_SIZE_X*UI_SIZE_Y+1]),screen(Screen::getInstance())
{

}


UIScript::~UIScript()
{
}

void UIScript::start()
{	
	memset(ui, ' ', UI_SIZE_X * UI_SIZE_Y);

	nextBlockInUI=static_cast<BlockScript*>(gameObject->Find("block")->getComponent<BlockScript>())->nextBlock[0];
	gameObject->setPosition(Vector2(16, 1));
	gameObject->setShape(ui);
	gameObject->setScale(Vector2(UI_SIZE_X, UI_SIZE_Y));
	
}

void UIScript::update()
{
	memset(ui, ' ', UI_SIZE_X *UI_SIZE_Y);
	nextBlockInUI = static_cast<BlockScript*>(gameObject->Find("block")->getComponent<BlockScript>())->nextBlock[0];

	strncpy(&ui[10], nextBlockInUI->shape.c_str(), nextBlockInUI->size.X());
	strncpy(&ui[UI_SIZE_X], "NEXT :", 6);
	if (nextBlockInUI->size.Y() == 2)
		strncpy(&ui[UI_SIZE_X + 10], &(nextBlockInUI->shape[nextBlockInUI->size.X()]), nextBlockInUI->size.X());

	for (int i = 0; i < UI_SIZE_X * 2; i++)
	{
		if (ui[i] == '-')
			ui[i] = ' ';
	}
	gameObject->setShape(ui);
	
}

void UIScript::lateUpdate()
{
}

void UIScript::draw()
{
		screen.draw(gameObject->getShape().c_str()
		, gameObject->getScale().X(), gameObject->getScale().Y(),
		gameObject->getPosition());
}

