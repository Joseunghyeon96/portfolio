#pragma once
#include "Singleton.h"

class Hero;
class Boss;
class UI;

class MainGame 
	: public SingletonBase <MainGame>
{
	Hero* hero;
	Boss* boss;

	bool isPlay;
	UI* ui;
public:
	MainGame();
	~MainGame();
	
	void initGame();
	void renderFrame();
	void Release();
	void update();

};

