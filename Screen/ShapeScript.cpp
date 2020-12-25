#include "stdafx.h"
#include "ShapeScript.h"
#include "GameObject.h"


ShapeScript::ShapeScript(GameObject* gameObject)
	:Component(gameObject)
{
}


ShapeScript::~ShapeScript()
{
}

void ShapeScript::start()
{
	/*   블록 만들기  */
	
	vector<Block* > LShape;  // L 모양 블럭
	Block* LShape1 = new Block("\xDB\xDB\xDB\xDB--",Vector2(3,2));
	Block* LShape2 = new Block("\xDB-\xDB-\xDB\xDB",Vector2(2,3));
	Block* LShape3 = new Block("--\xDB\xDB\xDB\xDB",Vector2(3, 2));
	Block* LShape4 = new Block("\xDB\xDB-\xDB-\xDB",Vector2(2, 3));
	LShape.push_back(LShape1);
	LShape.push_back(LShape2);
	LShape.push_back(LShape3);
	LShape.push_back(LShape4);

	vector<Block* > JShape; //J모양블럭
	Block* JShape1 = new Block("\xDB\xDB\xDB--\xDB", Vector2(3, 2));
	Block* JShape2 = new Block("\xDB\xDB\xDB-\xDB-", Vector2(2, 3));
	Block* JShape3 = new Block("\xDB--\xDB\xDB\xDB", Vector2(3, 2));
	Block* JShape4 = new Block("-\xDB-\xDB\xDB\xDB", Vector2(2, 3));
	JShape.push_back(JShape1);
	JShape.push_back(JShape2);
	JShape.push_back(JShape3);
	JShape.push_back(JShape4);

	vector<Block*> IShape; // I모양 블럭
	Block* IShape1 = new Block("\xDB\xDB\xDB\xDB", Vector2(4, 1));
	Block* IShape2 = new Block("\xDB\xDB\xDB\xDB", Vector2(1, 4));
	IShape.push_back(IShape1);
	IShape.push_back(IShape2);

	vector<Block*> OShape; // ㅁ모양 블럭
	Block* OShape1 = new Block("\xDB\xDB\xDB\xDB", Vector2(2, 2));
	OShape.push_back(OShape1);

	vector<Block*> ZShape;// Z모양 블럭
	Block* ZShape1 = new Block("\xDB\xDB--\xDB\xDB", Vector2(3, 2));
	Block* ZShape2 = new Block("-\xDB\xDB\xDB\xDB-", Vector2(2, 3));
	ZShape.push_back(ZShape1);
	ZShape.push_back(ZShape2);


	vector<Block*> SShape;// S모양 블럭
	Block* SShape1 = new Block("-\xDB\xDB\xDB\xDB-", Vector2(3, 2));
	Block* SShape2 = new Block("\xDB-\xDB\xDB-\xDB", Vector2(2, 3));
	SShape.push_back(SShape1);
	SShape.push_back(SShape2);

	vector<Block*> TShape;// T모양 블럭
	Block* TShape1 = new Block("\xDB\xDB\xDB-\xDB-", Vector2(3, 2));
	Block* TShape2 = new Block("\xDB-\xDB\xDB\xDB-", Vector2(2, 3));
	Block* TShape3 = new Block("-\xDB-\xDB\xDB\xDB", Vector2(3, 2));
	Block* TShape4 = new Block("-\xDB\xDB\xDB-\xDB", Vector2(2, 3));
	TShape.push_back(TShape1);
	TShape.push_back(TShape2);
	TShape.push_back(TShape3);
	TShape.push_back(TShape4);


	//vector<Block*> lShape;
	//Block* lShape1 = new Block("\xDB\xDB\xDB  \xDB", (3, 2));
	blocks.push_back(LShape);
	blocks.push_back(OShape);
	blocks.push_back(ZShape);
	blocks.push_back(SShape);
	blocks.push_back(JShape);
	blocks.push_back(IShape);
	blocks.push_back(TShape);
}
