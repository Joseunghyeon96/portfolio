#pragma once
#include "Component.h"

struct Block
{
	string shape;
	Vector2 size;

	Block(const string shape, Vector2 size) { this->shape = shape; this->size = size; }
};
class ShapeScript :
	public Component
{
	vector<vector<Block*>> blocks;
public:
	ShapeScript(GameObject* gameObject);
	~ShapeScript();

	void start();
	vector<Block*> getRandomBlock() { return blocks[rand()%7]; }
};

