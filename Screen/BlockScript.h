#pragma once
#include "Component.h"

struct Block;

class BlockScript :
	public Component
{
	vector<Block* > block;
	vector<Block* > nextBlock;
	vector<Block* >::iterator iter;

	Screen& screen;

	friend class UIScript;
public:
	BlockScript(GameObject* gameObject);
	~BlockScript();

	void start();
	void draw();
	void ghostDraw();
	void update();
	void lateUpdate();
	void setRandomBlock();
	bool inMapCheck(Vector2 afterMovePos);
	bool canMoveCheck(Vector2 afterMovePos);
	bool canRotation();
	void rotationBlock();
	void buildBlock();
	bool buildCheck();

	Block* getNextBlockToUI();
};

