#pragma once
#include "Component.h"
class FoodScript :
	public Component
{

	vector<GameObject*> objs;
public:
	FoodScript(GameObject* gameObject);
	~FoodScript();

	void start();
	void update();
	void onCollision();
};

