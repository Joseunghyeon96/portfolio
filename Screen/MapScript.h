#pragma once
#include "Component.h"
class MapScript :
	public Component
{
	char* map;
	Screen& screen;
public:
	MapScript(GameObject* gameObject);
	~MapScript();

	void start();
	void update();
	void draw(); 
	void changeMap(const char* shape, int width, int height, const Vector2& pos);
	char* getMap() { return (this->map); }
	void deleteLine();
	void underingLine(int y);
	void lateUpdate();
};

