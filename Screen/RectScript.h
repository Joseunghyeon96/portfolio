#pragma once
#include "Component.h"
class RectScript :
	public Component
{
	char* rect;
	Screen& screen;
public:
	RectScript(GameObject* gameObject);
	~RectScript();

	void start();
	void draw();
};

