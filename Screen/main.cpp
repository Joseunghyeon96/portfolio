// Screen.cpp : �� ���Ͽ��� 'main' �Լ��� ���Ե˴ϴ�. �ű⼭ ���α׷� ������ ���۵ǰ� ����˴ϴ�.
//

#include "stdafx.h"
#include "GameEngine.h"

int main()
{
	GameEngine& engine = GameEngine::getInstance();
	
	engine.mainLoop();
	
	return 0;
}