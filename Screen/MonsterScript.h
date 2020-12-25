#pragma once
#include "Component.h"
class MonsterScript :
	public Component
{
	int score;
public:
	MonsterScript(GameObject* gameObject);
	~MonsterScript();

	void increaseScore(int x = 1);
	int getScore() { return score; }
	void start();
	void update();
};

