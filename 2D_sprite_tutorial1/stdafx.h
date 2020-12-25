#pragma once

// include the basic windows header files and the Direct3D header file
#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// define the screen resolution and keyboard macros
#define SCREEN_WIDTH  1024
#define SCREEN_HEIGHT 1156
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)
#define ENEMY_NUM 10 


// include the Direct3D Library file
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

#include "MainGame.h"
// global declarations
float randomRange(float min, float max);

extern LPDIRECT3D9 d3d;    // the pointer to our Direct3D interface
extern LPDIRECT3DDEVICE9 d3ddev;    // the pointer to the device class
extern LPD3DXSPRITE d3dspt;    // the pointer to our Direct3D Sprite interface
extern LPDIRECT3DTEXTURE9 sprite;    // the pointer to the sprite
extern LPDIRECT3DTEXTURE9 sprite_hero;    // the pointer to the sprite
extern LPDIRECT3DTEXTURE9 sprite_enemy;    // the pointer to the spriteextern 
extern LPDIRECT3DTEXTURE9* sprite_bullet;
extern LPDIRECT3DTEXTURE9 enemyBullet;
extern LPDIRECT3DTEXTURE9 spriteBoss;
extern LPDIRECT3DTEXTURE9 bulletExplosion;
extern LPDIRECT3DTEXTURE9 hitBox;
extern LPDIRECT3DTEXTURE9 eBullet2;
extern LPDIRECT3DTEXTURE9 speBullet;
extern LPDIRECT3DTEXTURE9 gameStart;
extern LPDIRECT3DTEXTURE9 gameClear;

enum { MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT };

