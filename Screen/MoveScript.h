#pragma once
#include "Component.h"
class MoveScript :
	public Component
{
public:
	MoveScript(GameObject* gameObject);
	~MoveScript();

	void start();
	void move(Vector2& pos , Vector2 direction);
	void update();
	void dropBlock(Vector2& pos);
};

