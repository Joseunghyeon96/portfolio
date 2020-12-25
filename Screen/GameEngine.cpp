#include "stdafx.h"
#include "GameEngine.h"
#include "GameObject.h"
#include "MoveScript.h"
#include "MapScript.h"
#include "UIScript.h"
#include "RectScript.h"
#include "BlockScript.h"
#include "ShapeScript.h"


GameEngine* GameEngine::instance = nullptr;

GameEngine & GameEngine::getInstance()
{
	if (instance == nullptr) {
		instance = new GameEngine();
	}
	return *instance;
}


void GameEngine::mainLoop()
{
	auto& objs = GameObject::gameObjects;


	GameObject rect("rect", nullptr,"rect");
	rect.addComponent<RectScript>();
	objs.push_back(&rect);

	GameObject map("map",nullptr,"map");
	map.addComponent<MapScript>();
	objs.push_back(&map);

	GameObject block("block", &map, "block");
	block.addComponent<ShapeScript>();
	block.addComponent<BlockScript>();
	block.addComponent<MoveScript>();
	objs.push_back(&block);

	GameObject UI("UI", nullptr, "UI");
	UI.addComponent<UIScript>();
	objs.push_back(&UI);

	for (auto obj : objs)
	{
		obj->traverseStart();
	}

	while (!Input::GetKeyDown(KeyCode::Esc)) {
		screen.clear();
		// update		
		for (auto obj : objs)
		{
			obj->traverseUpdate();
		}
		// lateUpdate
		for (auto obj : objs)
		{
			obj->traverseLateUpdate();
		}

		// draw
		for (auto obj : objs)
		{
			obj->traverseDraw();
		
		}
		screen.render();
		Sleep(80);

		Input::EndOfFrame();
	}

	Borland::gotoxy(Vector2(20, 20));
	int i = 0;
	for (auto obj : objs)
	{
		i++;
		cout << obj->getName() << "  ";
	}
	cout<<endl;
	cout << i << endl;
	system("pause");
	return;
}
