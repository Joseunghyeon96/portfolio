#pragma once
#include "Component.h"

struct Block;

class UIScript :
	public Component
{
	char* ui;
	Block* nextBlockInUI;
	Screen& screen;
public:
	UIScript(GameObject* gameObject);
	~UIScript();

	void start();
	void update();
	void lateUpdate();
	void draw();
};

