#pragma once
#include "Singleton.h"
class Hero;
class Boss;

class UI : public SingletonBase<UI>
{

	Hero* hero;
	Boss* boss;
	DWORD frameStart;
	DWORD frameEnd;
	char frameString[100];
	char score[30];
	ID3DXFont* font;
	ID3DXSprite* fontSprite;
	LPDIRECT3DTEXTURE9 alphabetSprite[7];
	LPDIRECT3DTEXTURE9 lifeSprite;
	LPDIRECT3DTEXTURE9 sBulletUI;
	LPDIRECT3DTEXTURE9 powerUp;
	LPDIRECT3DTEXTURE9 bulletUI;
	LPDIRECT3DTEXTURE9 white;
	LPDIRECT3DTEXTURE9 backGround;
public:
	UI();
	~UI();
	void init(Hero* hero,Boss* boss);

	void renderUI(LPD3DXSPRITE d3dspt);
};

