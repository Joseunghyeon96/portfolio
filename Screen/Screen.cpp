#include "stdafx.h"
#include "Screen.h"



Screen* Screen::instance = nullptr;


Screen & Screen::getInstance()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	if (instance == nullptr) {
		instance = new Screen();
	}
	return *instance;

}

Screen::~Screen()
{
	if (instance) {
		delete[] canvas;
		instance = nullptr;
	}
}

void Screen::drawRect(const Vector2& pos, int w, int h)
{

	canvas[pos.X()] = '\xDA';
	canvas[pos.X() + w - 1] = '\xBF';
	memset(&canvas[pos.X() + 1], '\xC4', w - 2);
	canvas[pos.X() + (pos.Y() + (h - 1))*(width + 1)] = '\xC0';
	canvas[pos.X() + (pos.Y() + (h - 1))*(width + 1) + w - 1] = '\xD9';
	memset(&canvas[pos.X() + 1 + (pos.Y() + (h - 1))*(width + 1)], '\xC4', w - 2);
	for (int i = 1; i < h - 1; i++) {
		canvas[pos.X() + (pos.Y() + i)*(width + 1)] = '\xB3';
		canvas[pos.X() + w - 1 + (pos.Y() + i)*(width + 1)] = '\xB3';
	}

}

void Screen::draw(const char * shape, int w, int h, const Vector2& pos)
{
	if (!shape) return;
	for (int i = 0; i < h; i++)
	{
		strncpy(&canvas[pos.X() + (pos.Y() + i)*(width + 1)], &shape[i*w], w);
	}
}

void Screen::blockDraw(const char * shape, int width, int height, const Vector2 & pos)
{

	if (!shape) return;
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			if (shape[w + (width*h)] != '\xDB') continue;


			canvas[pos.X() + w + (pos.Y()+ h)*(this->width+1)] = shape[w + (width*h)];
		}
	}

}

void Screen::ghostBlockDraw(const char * shape, int width, int height, const Vector2 & pos)
{
	if (!shape) return;
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			if (shape[w + (width*h)] != '\xDB') continue;


			canvas[pos.X() + w + (pos.Y() + h)*(this->width + 1)] = '\xB0';
		}
	}
}

void Screen::render()
{
	for (int i = 0; i < height; i++)
		canvas[width + i * (width + 1)] = '\n';
	canvas[width + (height - 1) * (width + 1)] = '\0';
	Borland::gotoxy(0, 0);
	cout << canvas;
}

void Screen::clear()
{

	memset(canvas, ' ', (width + 1)*height);
	canvas[width + (height - 1)*(width + 1)] = '\0';

}
