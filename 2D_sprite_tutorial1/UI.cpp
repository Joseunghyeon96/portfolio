#include "stdafx.h"
#include "UI.h"
#include "Boss.h"
#include "Hero.h"


UI::UI()
{
}


UI::~UI()
{
}

void UI::init(Hero * hero,Boss* boss)
{
	this->hero = hero;
	this->boss = boss;
	frameStart = GetTickCount();
	frameEnd = GetTickCount();
	sprintf(frameString, "FPS : %d \n", 0);
	sprintf(score, "score : %d \n", 0);
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"life.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&lifeSprite);    // load to sprite
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"white.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&white);    // load to sprite
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"sBulletUI.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sBulletUI);    // load to sprite
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"BulletUI.png",    // the file name
		D3DX_DEFAULT_NONPOW2,    // default width
		D3DX_DEFAULT_NONPOW2,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&bulletUI);    // load to sprite
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"powerup.png",    // the file name
		D3DX_DEFAULT_NONPOW2,    // default width
		D3DX_DEFAULT_NONPOW2,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&powerUp);    // load to sprite
#pragma region 알파벳 텍스쳐
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"G.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&alphabetSprite[0]);    // load to sprite
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"A.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&alphabetSprite[1]);    // load to sprite
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"M.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&alphabetSprite[2]);    // load to sprite
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"E.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&alphabetSprite[3]);    // load to sprite
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"O.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&alphabetSprite[4]);    // load to sprite
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"V.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&alphabetSprite[5]);    // load to sprite
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"R.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&alphabetSprite[6]);    // load to sprite

#pragma endregion


	D3DXCreateFont(d3ddev,
		24,
		0,
		FW_BOLD,
		1,
		false,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		L"BankGothic Lt BT",
		&font);
	D3DXCreateSprite(d3ddev, &fontSprite);

}

void UI::renderUI(LPD3DXSPRITE d3dspt)
{

	frameEnd = GetTickCount();

	//유저 UI

	//life
	RECT lifeRect;
	SetRect(&lifeRect, 0, 0, 32,32);
	D3DXVECTOR3 lifeCenter(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < hero->getLife(); i++)
	{
		D3DXVECTOR3 lifePos(10 + 34*i, 970 , 0.0f);
		d3dspt->Draw(lifeSprite, &lifeRect, &lifeCenter, &lifePos, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	// superBullet UI
	for (int i = 0; i < hero->getSB(); i++)
	{
		D3DXVECTOR3 lifePos(160 + 34 * i, 970, 0.0f);
		d3dspt->Draw(sBulletUI, &lifeRect, &lifeCenter, &lifePos, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	// Bullet : text
	RECT bulletTextRect;
	SetRect(&bulletTextRect, 0, 0, 120, 40);
	D3DXVECTOR3 bulletTextCenter(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 bulletTextPos(10, 900, 0.0f);
	d3dspt->Draw(bulletUI, &bulletTextRect, &bulletTextCenter, &bulletTextPos, D3DCOLOR_ARGB(255, 255, 255, 255));


	// power
	RECT powerRect;
	D3DXVECTOR3 powerCenter(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 powerPos;
	switch (hero->getPower())
	{
	case 1:
		powerPos= D3DXVECTOR3(140, 915, 0.0f);
		SetRect(&powerRect, 0, 0, 16, 16);
		d3dspt->Draw(sprite_bullet[0], &powerRect, &powerCenter, &powerPos, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case 2:
		powerPos = D3DXVECTOR3(140, 905, 0.0f);
		SetRect(&powerRect, 0, 0, 32, 32);
		d3dspt->Draw(sprite_bullet[1], &powerRect, &powerCenter, &powerPos, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case 3:
		powerPos = D3DXVECTOR3(140, 890, 0.0f);
		SetRect(&powerRect, 0, 0, 64, 64);
		d3dspt->Draw(sprite_bullet[2], &powerRect, &powerCenter, &powerPos, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	}
	// powerUp 표시
	if (hero->getPowerUp()==false)
	{
		RECT powerUpRect;
		SetRect(&powerUpRect, 0, 0, 128, 64);
		D3DXVECTOR3 powerUpCenter(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 powerUpPos(hero->getXPos() - 32, hero->getYPos() - 64, 0);
		d3dspt->Draw(powerUp, &powerUpRect, &powerUpCenter, &powerUpPos, D3DCOLOR_ARGB(255, 255, 150, 255));
	}

	//보스 UI

	RECT bossHpBar;
	SetRect(&bossHpBar, 0, 0, 800, 8);
	D3DXVECTOR3 bossHpCenter(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
	D3DXVECTOR3 hpBarPos(100, 3, 0.0f);
	d3dspt->Draw(white, &bossHpBar, &bossHpCenter, &hpBarPos, D3DCOLOR_ARGB(255, 255, 0, 0));

	RECT bossHp;
	SetRect(&bossHp, 0, 0, 1, 8);
	for (int i = 0; i < boss->getLife(); i++)
	{
		D3DXVECTOR3 hpPos(100 + i, 3, 0.0f);
		d3dspt->Draw(white, &bossHp, &bossHpCenter, &hpPos, D3DCOLOR_ARGB(255, 0, 255, 0));
	}


	//게임종료시 GAMEOVER 출력
	if (hero->getEnabled() == false)
	{
		RECT endRect;
		SetRect(&endRect, 0, 0, 128, 128);
		D3DXVECTOR3 endCenter(0.0f, 0.0f, 0.0f);
		for (int i = 0; i < 8; i++)
		{
			D3DXVECTOR3 endPos(230 + 128 * (i % 4), SCREEN_HEIGHT / 2 -194 + 128 * (i / 4), 0.0f);
			if (i == 6)
				d3dspt->Draw(alphabetSprite[3], &endRect, &endCenter, &endPos, D3DCOLOR_ARGB(255, 255, 255, 255));
			else if(i==7)
				d3dspt->Draw(alphabetSprite[6], &endRect, &endCenter, &endPos, D3DCOLOR_ARGB(255, 255, 255, 255));
			else
				d3dspt->Draw(alphabetSprite[i], &endRect, &endCenter, &endPos, D3DCOLOR_ARGB(255, 255, 255, 255));

		}
	}
	if (boss->getEnabled() == false)
	{
		RECT clearRect;
		SetRect(&clearRect, 0, 0, 600, 400);
		D3DXVECTOR3 clearCenter(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 clearPos(200.0f, 300.0f, 0.0f);
		d3dspt->Draw(gameClear, &clearRect, &clearCenter, &clearPos, D3DCOLOR_ARGB(255, 255, 255, 255));


	}
	if (fontSprite)
	{
		int frame = 0;
		static int frameCount = 0;
		frameCount++;

		//프레임계산
		if (frameEnd - frameStart > 1000)
		{
			frame = frameCount;
			frameCount = 0;
			frameStart = GetTickCount();
			sprintf(frameString, "FPS : %d \n", frame);
		}


		//조작법 표시
		bool cheat = hero->getCheat();

		fontSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		RECT fontRT = { 0,1024,0,0 };
		if(cheat)
		font->DrawTextW(fontSprite
		,L"  조작법   이동 : 방향키 , 공격 : SPACE , 특수 공격: SHIFT , 이어하기 : R  CheatMode : ON\n게임종료 : ESC"
		, -1, &fontRT, DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		else
		font->DrawTextW(fontSprite
		, L"  조작법   이동 : 방향키 , 공격 : SPACE , 특수 공격: SHIFT , 이어하기 : R  CheatMode : OFF\n게임종료 : ESC"
		, -1, &fontRT, DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));


		//프레임표시
		fontRT = { 900,1064,0,0 };
		font->DrawTextA(fontSprite
			, frameString
			, -1, &fontRT, DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));


		// 점수표시
		sprintf(score, "score : %d \n", hero->getScore());
		fontRT = { 500,1064,0,0 };
		font->DrawTextA(fontSprite
			, score
			, -1, &fontRT, DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		fontSprite->End();
	}
	
}
