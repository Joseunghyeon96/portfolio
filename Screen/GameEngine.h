#pragma once

class GameEngine
{
	Screen& screen;

	static GameEngine* instance;

	GameEngine() : screen(Screen::getInstance()) {
		string mode = "mode con cols=" + to_string(screen.getWidth() + 10);
		mode += " lines=" + to_string(screen.getHeight() + 5);

		std::system(mode.c_str());
		std::system("chcp 437");
		screen.clear();// screen.render();
	}

public:

	static GameEngine& getInstance();

	void mainLoop();

};

