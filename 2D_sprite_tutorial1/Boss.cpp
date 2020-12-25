#include "stdafx.h"
#include <time.h>
#include "Boss.h"
#include "Hero.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "Bullet.h"


Boss::Boss()
{
}


Boss::~Boss()
{
}

void Boss::init(float x, float y,Hero* hero)
{
	enabled = true;
	hard_3 = false;
	hard_4 = false;
	hard_5 = false;
	hard_6 = false;
	easy2 = false;
	easy3 = false;
	target = hero;
	pattern = GetTickCount();
	imageSizeX = 80;
	imageSizeY = 136;
	ySpeed = 2.5f;
	xSpeed = 3.0f;
	life = 800;
	D3DXVECTOR2 moveDir(randomRange(-10, 10), randomRange(-10, 10));
	D3DXVec2Normalize(&moveDir, &moveDir);

	xPos = x;
	yPos = y;
}

void Boss::update()
{
	if (enabled == false) return;
	

	if(life<0) 
	{
		enabled = false;
	}

#pragma region 패턴 테스트
	if (KEY_DOWN(VK_NUMPAD0)) {
		hardPattern_2();
	}
	if (KEY_DOWN(VK_NUMPAD1)) {
		if (hard_3 == false)
		hardPattern_3();
	}
	if (KEY_DOWN(VK_NUMPAD2)) {
		hard_4 = true;
	}
	if (KEY_DOWN(VK_NUMPAD3)) {
		hardPattern_1();
	}
	if (KEY_DOWN(VK_NUMPAD4)) {
		if(hard_5==false)
		hardPattern_5();
	}
	if (KEY_DOWN(VK_NUMPAD5)) {
		hard_6 = true;
	}
	if (KEY_DOWN(VK_NUMPAD6)) {
		easyPattern_1();
	}
	if (KEY_DOWN(VK_NUMPAD7)) {
		easyPattern_2();
	}
	if (KEY_DOWN(VK_NUMPAD8)) {
		easyPattern_3();
	}


#pragma endregion

	if (KEY_DOWN(VK_F4))
		life -= 50;


	DWORD playTime = GetTickCount();
	//if (hard_6 == false) // 6번째 패턴중일땐 안움직임
	move();
	hit();

	if (life <= 400) hardPattern_2();
#pragma region 보스 패턴
	if (hard_6)
	{
		if ((playTime - pattern) > 150) {
			pattern = GetTickCount();
			hardPattern_6();
			return;
		}
	}
	if (hard_5)
	{
		if ((playTime - pattern) > 10000) {
			pattern = GetTickCount();
			hard_5 = false;
		}
		return;
	}
	if (hard_3) {
		if ((playTime - pattern) > 500) {
			pattern = GetTickCount();
			hardPattern_3();
		}
		return;
	}
	if (hard_4)
	{
		hardPattern_4();
		if ((playTime - pattern) > 3000) {
			pattern = GetTickCount();
			hard_4 = false;
		}
	}

	if (easy2) { 
		if ((playTime - pattern) > 200) {
			pattern = GetTickCount();
			easyPattern_2();
		}
		return; 
	}
	if (easy3) {
		if ((playTime - pattern) > 400) {
			pattern = GetTickCount();
			easyPattern_3();
		}
		return;
	}
	if (life < 780 && life>700) {
		if ((playTime -pattern) > 2000) //2초마다 소환
		{
			pattern = GetTickCount();
			easyPattern_1();
		}
	}
	else if (life <= 700 && life > 620)
	{
		if ((playTime - pattern) > 2000)//2초마다
		{
			pattern = GetTickCount();
			switch (rand() % 2)
			{
			case 0:
				easyPattern_1();
				break;
			case 1:
				easyPattern_2();
				break;
			}
		}
	}
	else if (life <= 620 && life > 500)
	{
		if ((playTime - pattern) > 2000)//2초마다
		{
			pattern = GetTickCount();
			switch (rand() % 3)
			{
			case 0:
				easyPattern_1();
				easyPattern_2();
				break;
			case 1:
				easyPattern_3();
				break;
			case 2:
				hardPattern_1();
				break;

			}
		}
	}
	else if (life <= 500&&life>400)
	{
		if ((playTime - pattern) > 3000)//3초마다
		{
			pattern = GetTickCount();
			switch (rand() % 3)
			{
			case 0:
				easyPattern_1();
				easyPattern_2();
				hardPattern_1();
				break;
			case 1:
				hardPattern_3();
				break;
			case 2:
				hardPattern_4();
				hard_4 = true;
				break;
			}
		}
	}
	else if (life <=400 && life >320)
	{
		if ((playTime - pattern) > 3000)//3초마다
		{
			pattern = GetTickCount();
			switch (rand() % 3)
			{
			case 0:
				hardPattern_1();
				break;
			case 1:
				hardPattern_3();
				break;
			case 2:
				hardPattern_4();
				hard_4 = true;
				break;
			}
		}
	}
	else if (life <= 320)
	{
		if ((playTime - pattern) > 3000)//3초마다
		{

			pattern = GetTickCount();
			switch (rand() % 6)
			{
			case 0:
				hardPattern_1();
				break;
			case 1:
				hardPattern_3();
				break;
			case 2:
				hardPattern_4();
				hard_4 = true;
				break;
			case 3:
				hardPattern_1();
				hardPattern_5();
				break;
			case 4:
				hardPattern_5();
				break;
			case 5:
				hard_6 = true;

			}
		}
	}
	#pragma endregion
}

void Boss::move()
{

	if (xPos + (moveDir.x*xSpeed) > 0 && xPos + (moveDir.x*xSpeed) < SCREEN_WIDTH - 110)
		xPos += moveDir.x*xSpeed;
	else {
		moveDir = D3DXVECTOR2(randomRange(-10, 10), randomRange(-10, 10));
		D3DXVec2Normalize(&moveDir, &moveDir);
	}

	if (yPos + (moveDir.y*ySpeed) > 0 && yPos + (moveDir.y*ySpeed) < 300)
		yPos += moveDir.y*ySpeed;
	else
	{
		moveDir = D3DXVECTOR2(randomRange(-10, 10), randomRange(-10, 10));
		D3DXVec2Normalize(&moveDir, &moveDir);
	}
}
void Boss::easyPattern_1()
{
	for (int i = 0; i < 7; i++)
	{
		Enemy* enemy = new Enemy;
		enemy->init(50 + i*150, 30 , D3DXVECTOR2(0,1), D3DXVECTOR2(0,1));
	}
}
void Boss::easyPattern_2()
{
	static int i=0;
	easy2 = true;
	EnemyBullet* eBullet = new EnemyBullet;
	eBullet->init(100*i, 20, D3DXVECTOR2(0, 1));
	i++;
	if (i == 11) { easy2 = false; i = 0; }

}
void Boss::easyPattern_3()
{
	static int i = 0;
	easy3 = true;
	EnemyBullet* eBullet = new EnemyBullet;
	eBullet->init(1000 - (100 * i), 0, D3DXVECTOR2(0, 1));
	EnemyBullet* eBullet2 = new EnemyBullet;
	eBullet2->init(0, 1000 - (100*i), D3DXVECTOR2(1, 0));
	i++;
	if (i == 11) { easy3 = false; i = 0; }
}
void Boss::hardPattern_1()
{
	for (int i = 0; i <7; i++)
	{
		EnemyBullet* eBullet = new EnemyBullet;
		eBullet->init(100+143 * i, 0, D3DXVECTOR2(412-(143 *i), 512),8);
	}
	for (int i = 0; i < 7; i++)
	{
		EnemyBullet* eBullet = new EnemyBullet;
		eBullet->init(SCREEN_WIDTH - 30, 143 * i, D3DXVECTOR2(-512, 512 - (143 * i)), 8);
	}
	for (int i = 0; i < 7; i++)
	{
		EnemyBullet* eBullet = new EnemyBullet;
		eBullet->init(100+143 *i, SCREEN_HEIGHT - 205, D3DXVECTOR2(412-(143 *i), -512), 8);
	}
	for (int i = 0; i < 7; i++)
	{
		EnemyBullet* eBullet = new EnemyBullet;
		eBullet->init(0, 143 * i, D3DXVECTOR2(512, 512 - (143 * i)), 8);
	}
}
void Boss::hardPattern_2() // 상시발동형 패턴
{
	static int i = 0;
	i++;
	if (i%25 != 0) {
		return;
	}
	for (int radian = 0; radian < 21; radian++)
	{
		EnemyBullet* eBullet = new EnemyBullet;
		eBullet->init(xPos + 35 + cos(D3DXToRadian(17.1 * radian)) * 50
			, yPos + 64 + sin(D3DXToRadian(17.1 * radian)) * 50
			, D3DXVECTOR2(cos(D3DXToRadian(17.1 * radian)), sin(D3DXToRadian(17.1 * radian))));
	}
	i = 0;
}
void Boss::hardPattern_3()
{
	static int i = 0;
	hard_3 = true;
	for (int z = 0; z < 20; z++)
	{
		EnemyBullet* eBullet = new EnemyBullet;
		eBullet->init(SCREEN_WIDTH/20*z, yPos + 128,
			D3DXVECTOR2((SCREEN_WIDTH/5 * i)- (SCREEN_WIDTH / 20 * z),
				600- (yPos + 128)) , 6);
	}
	i++;
	if (i == 6) { hard_3 = false; i = 0; }
}
void Boss::hardPattern_4()
{
	static int i = 0;
	i++;
	if (i % 15 != 0) {
		return;
	}
	for (int radian = 0; radian < 11; radian++)
	{
		EnemyBullet* eBullet = new EnemyBullet;
		eBullet->init(xPos + 35 + cos(D3DXToRadian(17.1 * radian)) * 150
			, yPos + 64 + sin(D3DXToRadian(17.1 * radian)) *150
			, D3DXVECTOR2(target->getXPos() - (xPos + 35 + cos(D3DXToRadian(17.1 * radian)) *150)
				, target->getYPos() - (yPos + 64 + sin(D3DXToRadian(17.1 * radian)) * 150)));
	}
	i = 0;
}
void Boss::hardPattern_5()
{
	if (hard_5) return; //이미패턴5가 실행중이면 리턴


	hard_5 = true;

	// 위쪽 
	for (int i = 0; i < 10; i++)
	{
		EnemyBullet* eBullet = new EnemyBullet;
		eBullet->init(100 * i, 20,
			D3DXVECTOR2((1000 - 100 * i) - 100 * i, 512),4);
	}
	for (int i = 0; i < 10; i++)
	{
		EnemyBullet* eBullet = new EnemyBullet;
		eBullet->init(100 * i, 40,
			D3DXVECTOR2((1000 - 100 * i) - 100 * i, 562), 4);
	}
	for (int i = 0; i < 10; i++)
	{
		EnemyBullet* eBullet = new EnemyBullet;
		eBullet->init(100 * i, 60,
			D3DXVECTOR2((1000 - 100 * i) - 100 * i, 562), 4);
	}

	for (int i = 0; i < 10; i++)
	{
		EnemyBullet* eBullet = new EnemyBullet;
		eBullet->init(100 * i, 80,
			D3DXVECTOR2((1000 - 100 * i) - 100 * i, 612), 4);
	}
	for (int i = 0; i < 10; i++)
	{
		EnemyBullet* eBullet = new EnemyBullet;
		eBullet->init(100 * i, 90,
			D3DXVECTOR2((1000 - 100 * i) - 100 * i, 562), 4);
	}
	for (int i = 0; i < 10; i++)
	{
		EnemyBullet* eBullet = new EnemyBullet;
		eBullet->init(100 * i, 110,
			D3DXVECTOR2((1000 - 100 * i) - 100 * i, 662), 4);
	}
	for (int i = 0; i < 10; i++)
	{
		EnemyBullet* eBullet = new EnemyBullet;
		eBullet->init(100 * i, 125,
			D3DXVECTOR2((1000 - 100 * i) - 100 * i, 562), 4);
	}
	for (int i = 0; i < 10; i++)
	{
		EnemyBullet* eBullet = new EnemyBullet;
		eBullet->init(100 * i, 140,
			D3DXVECTOR2((1000 - 100 * i) - 100 * i, 712), 4);
	}
	for (int i = 0; i < 10; i++)
	{
		EnemyBullet* eBullet = new EnemyBullet;
		eBullet->init(100 * i, 160,
			D3DXVECTOR2((1000 - 100 * i) - 100 * i, 562), 4);
	}
	for (int i = 0; i < 10; i++)
	{
		EnemyBullet* eBullet = new EnemyBullet;
		eBullet->init(100 * i, 180,
			D3DXVECTOR2((1000 - 100 * i) - 100 * i, 762), 4);
	}

	//왼쪽
	for (int i = 0; i < 10; i++)
	{
		EnemyBullet* eBullet = new EnemyBullet;
		eBullet->init(0, 100*i,
			D3DXVECTOR2(512, (1000 - 100 * i) - 100 * i), 4);
	}
	for (int i = 0; i < 10; i++)
	{
		EnemyBullet* eBullet = new EnemyBullet;
		eBullet->init(20, 100 * i,
			D3DXVECTOR2(512, (1000 - 100 * i) - 100 * i), 4);
	}
	for (int i = 0; i < 10; i++)
	{
		EnemyBullet* eBullet = new EnemyBullet;
		eBullet->init(40, 100 * i,
			D3DXVECTOR2(562, (1000 - 100 * i) - 100 * i), 4);
	}
	for (int i = 0; i < 10; i++)
	{
		EnemyBullet* eBullet = new EnemyBullet;
		eBullet->init(70, 100 * i,
			D3DXVECTOR2(512, (1000 - 100 * i) - 100 * i), 4);
	}
	for (int i = 0; i < 10; i++)
	{
		EnemyBullet* eBullet = new EnemyBullet;
		eBullet->init(90, 100 * i,
			D3DXVECTOR2(622, (1000 - 100 * i) - 100 * i), 4);
	}
	for (int i = 0; i < 10; i++)
	{
		EnemyBullet* eBullet = new EnemyBullet;
		eBullet->init(105, 100 * i,
			D3DXVECTOR2(512, (1000 - 100 * i) - 100 * i), 4);
	}
	for (int i = 0; i < 10; i++)
	{
		EnemyBullet* eBullet = new EnemyBullet;
		eBullet->init(120, 100 * i,
			D3DXVECTOR2(672, (1000 - 100 * i) - 100 * i), 4);
	}
	for (int i = 0; i < 10; i++)
	{
		EnemyBullet* eBullet = new EnemyBullet;
		eBullet->init(135, 100 * i,
			D3DXVECTOR2(512, (1000 - 100 * i) - 100 * i), 4);
	}
	for (int i = 0; i < 10; i++)
	{
		EnemyBullet* eBullet = new EnemyBullet;
		eBullet->init(150, 100 * i,
			D3DXVECTOR2(722, (1000 - 100 * i) - 100 * i), 4);
	}

	//오른쪽
	for (int i = 0; i < 10; i++)
	{
		EnemyBullet* eBullet = new EnemyBullet;
		eBullet->init(1020, 100 * i,
			D3DXVECTOR2(-512, (1000 - 100 * i) - 100 * i), 4);
	}
	for (int i = 0; i < 10; i++)
	{
		EnemyBullet* eBullet = new EnemyBullet;
		eBullet->init(990, 100 * i,
			D3DXVECTOR2(-512, (1000 - 100 * i) - 100 * i), 4);
	}
	for (int i = 0; i < 10; i++)
	{
		EnemyBullet* eBullet = new EnemyBullet;
		eBullet->init(960, 100 * i,
			D3DXVECTOR2(-562, (1000 - 100 * i) - 100 * i), 4);
	}
	for (int i = 0; i < 10; i++)
	{
		EnemyBullet* eBullet = new EnemyBullet;
		eBullet->init(935, 100 * i,
			D3DXVECTOR2(-512, (1000 - 100 * i) - 100 * i), 4);
	}
	for (int i = 0; i < 10; i++)
	{
		EnemyBullet* eBullet = new EnemyBullet;
		eBullet->init(910, 100 * i,
			D3DXVECTOR2(-622, (1000 - 100 * i) - 100 * i), 4);
	}
	for (int i = 0; i < 10; i++)
	{
		EnemyBullet* eBullet = new EnemyBullet;
		eBullet->init(880, 100 * i,
			D3DXVECTOR2(-512, (1000 - 100 * i) - 100 * i), 4);
	}
	for (int i = 0; i < 10; i++)
	{
		EnemyBullet* eBullet = new EnemyBullet;
		eBullet->init(860, 100 * i,
			D3DXVECTOR2(-672, (1000 - 100 * i) - 100 * i), 4);
	}
	for (int i = 0; i < 10; i++)
	{
		EnemyBullet* eBullet = new EnemyBullet;
		eBullet->init(840, 100 * i,
			D3DXVECTOR2(-512, (1000 - 100 * i) - 100 * i), 4);
	}
	for (int i = 0; i < 10; i++)
	{
		EnemyBullet* eBullet = new EnemyBullet;
		eBullet->init(910, 100 * i,
			D3DXVECTOR2(-722, (1000 - 100 * i) - 100 * i), 4);
	}


}
void Boss::hardPattern_6()
{

	static int start = 0;
	for (int radian = 0; radian < 21; radian++)
	{
		EnemyBullet* eBullet = new EnemyBullet;
		eBullet->init(xPos + 35 + cos(D3DXToRadian(start + 17.1 * radian)) * 50
			, yPos + 64 + sin(D3DXToRadian(start +17.1 * radian)) * 50
			, D3DXVECTOR2(cos(D3DXToRadian(start +17.1 * radian)), sin(D3DXToRadian(start + 17.1 * radian)))
			,8,true,17.1*radian);
	}
	start += 10;
	if (start == 190) {
		start = 0;
		hard_6 = false;
	}
}
void Boss::hit()
{
	for (auto bullet : bullets) // 모든총알과 충돌체크
	{
		if (bullet->getSpecial()) continue;
		if (bullet->getEnabled() == false) continue;

		if (onCollision(bullet) == true)
		{
			decreaseLife(bullet->getDamage());
			score += 5 * bullet->getDamage();
			bullet->setActive(false);
			bullet->setExplosion(true);
			return;
		}
	}
	return;
}

