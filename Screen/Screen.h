#pragma once

class Screen
{
	int width;
	int height;
	char* canvas;

	static Screen* instance;
	Screen(int width = 70, int height = 40)
		: width(width), height(height),
		canvas(new char[(width + 1)*height])

	{
		Input::Initialize();
	}
public:
	static Screen& getInstance();
	~Screen();
	void drawRect(const Vector2& pos, int w, int h);
	void draw(const char* shape, int w, int h, const Vector2& pos);
	void blockDraw(const char* shape, int width, int height, const Vector2& pos);
	void ghostBlockDraw(const char* shape, int width, int height, const Vector2& pos);
	void render();
	void clear();


	int getWidth() const { return width; }
	int getHeight() const { return height; }
};