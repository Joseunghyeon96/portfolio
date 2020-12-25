#include "stdafx.h"
#include "MainGame.h"
#include "GameObject.h"
#include "Hero.h"
#include "Bullet.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "Boss.h"
#include "UI.h"

MainGame::MainGame()
{

	isPlay = false;
}


MainGame::~MainGame()
{
}

void MainGame::initGame()
{
	//��ü �ʱ�ȭ 
	hero = new Hero;
	hero->init(400, 700);

	//�����ʱ�ȭ 
	boss = new Boss;
	boss->init(400, 100 ,hero);

	ui = UI::GetSingleton();
	ui->init(hero, boss);


}

void MainGame::renderFrame()
{


	// clear the window to a deep blue
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	d3ddev->BeginScene();    // begins the 3D scene

	d3dspt->Begin(D3DXSPRITE_ALPHABLEND);    // // begin sprite drawing with transparency
	
	// ���
	RECT part0;
	SetRect(&part0, 0, 0, 1024, 1024);
	D3DXVECTOR3 center0(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
	D3DXVECTOR3 position0(0.0f, 0.0f, 0.0f);    // position at 50, 50 with no depth
	d3dspt->Draw(sprite, &part0, &center0, &position0, D3DCOLOR_ARGB(255, 255, 255, 255));

	if (isPlay == true)
	{
		if (boss->enabled)
		{
			auto& enemies = GameObject::getEnemies();
			auto& bullets = GameObject::getBullets();
			auto& enemyBullets = GameObject::getEnemyBullets();

			//���ΰ� 
			RECT part;
			SetRect(&part, 0, 0, 64, 50);
			D3DXVECTOR3 center(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			D3DXVECTOR3 position = D3DXVECTOR3(hero->getXPos() - 20.5, hero->getYPos() - 10, 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(sprite_hero, &part, &center, &position, D3DCOLOR_ARGB(255, 255, 255, 255));

			RECT hitBoxRt;
			SetRect(&hitBoxRt, 0, 0, 24, 24);
			D3DXVECTOR3 hitBoxCenter(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			D3DXVECTOR3 hitBoxPos = D3DXVECTOR3(hero->getXPos(), hero->getYPos(), 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(hitBox, &hitBoxRt, &hitBoxCenter, &hitBoxPos, D3DCOLOR_ARGB(255, 255, 255, 255));

			////�Ѿ� 
			for (Bullet* bullet : bullets) {

				RECT part1;
				D3DXVECTOR3 center1(0.0f, 0.0f, 0.0f);
				D3DXVECTOR3 position1(bullet->getXPos(), bullet->getYPos(), 0.0f);
				switch (bullet->getDamage())
				{

				case 1:
					SetRect(&part1, 0, 0, 16, 16);
					if (bullet->getEnabled())
						d3dspt->Draw(sprite_bullet[0], &part1, &center1, &position1, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				case 2:
					SetRect(&part1, 0, 0, 32, 32);
					if (bullet->getEnabled())
						d3dspt->Draw(sprite_bullet[1], &part1, &center1, &position1, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				case 3:
					SetRect(&part1, 0, 0, 64, 64);
					if (bullet->getSpecial())
					{
						d3dspt->Draw(speBullet, &part1, &center1, &position1, D3DCOLOR_ARGB(255, 255, 255, 255));
					}
					if (bullet->getEnabled())
						d3dspt->Draw(sprite_bullet[2], &part1, &center1, &position1, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				}
			}

			//����
			RECT bossRect;
			SetRect(&bossRect, 0, 0, 80, 136);
			D3DXVECTOR3 bossCenter(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			D3DXVECTOR3 bossPos(boss->getXPos(), boss->getYPos(), 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(spriteBoss, &bossRect, &bossCenter, &bossPos, D3DCOLOR_ARGB(255, 255, 255, 255));

			////�� 
			RECT part2;
			SetRect(&part2, 0, 0, 64, 64);
			D3DXVECTOR3 center2(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			for (Enemy* enemy : enemies)
			{
				D3DXVECTOR3 position2(enemy->getXPos(), enemy->getYPos(), 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_enemy, &part2, &center2, &position2, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
			//�� �Ѿ�

			RECT eBulletRect;
			SetRect(&eBulletRect, 0, 0, 20, 20);
			D3DXVECTOR3 eBulletCenter(0.0f, 0.0f, 0.0f);
			for (EnemyBullet* eBullet : enemyBullets)
			{
				if (eBullet->getCol()) {
					D3DXVECTOR3 eBulletPos(eBullet->getXPos(), eBullet->getYPos(), 0.0f);    // position at 50, 50 with no depth
					d3dspt->Draw(enemyBullet, &eBulletRect, &eBulletCenter, &eBulletPos, D3DCOLOR_ARGB(255, 255, 255, 255));
				}
				else
				{
					SetRect(&eBulletRect, 0, 0, 32, 32);
					D3DXVECTOR3 eBulletPos(eBullet->getXPos() - 6, eBullet->getYPos() - 6, 0.0f);
					d3dspt->Draw(eBullet2, &eBulletRect, &eBulletCenter, &eBulletPos, D3DCOLOR_ARGB(127, 255, 255, 255));
				}
			}

			//����
			RECT explosionRect;
			SetRect(&explosionRect, 0, 0, 64, 64);
			D3DXVECTOR3 explosionCenter(0.0f, 0.0f, 0.0f);
			for (Bullet* bullet : bullets) {
				D3DXVECTOR3 explosionPos(bullet->getXPos() - 32, bullet->getYPos(), 0.0f);    // position at 50, 50 with no depth
				if (bullet->getExplosion()) {
					if (bullet->getRePaint() == true) {
						d3dspt->Draw(bulletExplosion, &explosionRect, &explosionCenter, &explosionPos, D3DCOLOR_ARGB(255, 255, 255, 255));
						bullet->setRePaint(true);
					}
				}
			}

		}

		ui->renderUI(d3dspt);

	}

	else
	{
	RECT startRect;
	SetRect(&startRect, 0, 0, 800, 600);
	D3DXVECTOR3 startCenter(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
	D3DXVECTOR3 startRectPos(100.0f, 200.0f, 0.0f);    // position at 50, 50 with no depth
	d3dspt->Draw(gameStart, &startRect, &startCenter, &startRectPos, D3DCOLOR_ARGB(255, 255, 255, 255));

	 }
	d3dspt->End();    // end sprite drawing

	d3ddev->EndScene();    // ends the 3D scene

	d3ddev->Present(NULL, NULL, NULL, NULL);

	return;
}

void MainGame::Release()
{
	delete hero;
	delete boss;
	this->ReleaseSingleton();
	ui->ReleaseSingleton();
}

void MainGame::update()
{
	
	if (isPlay == false)
	{
		if (KEY_DOWN(VK_RETURN))
		{
			isPlay = true;
			initGame();
		}

		return;
	}
	//���ΰ� ó�� 
	hero->update(); // ��ü ������Ʈ
	hero->setMoveCheck(true); // �̵��� 2�� �������ӿ� �ִ� 12ĭ���� �����ϱ�����

	//�Ѿ� ó�� 
	auto& bullets = GameObject::getBullets();
	for (Bullet* bullet : bullets) {
		bullet->update();
	}

	hero->update(); // �̵��� ������Ʈ1

	//����
	boss->update();

	hero->update();// �̵��� ������Ʈ2

	//���� ó�� 
	auto& enemies = GameObject::getEnemies();
	for (Enemy* enemy : enemies)
	{
		enemy->update();
	}

	hero->update();// �̵��� ������Ʈ3


	auto& enemyBullets = GameObject::getEnemyBullets();
	for (EnemyBullet* eBullet : enemyBullets)
	{
		eBullet->update();
	}

	hero->update();// �̵��� ������Ʈ4
	hero->update();// �̵��� ������Ʈ5
	hero->setMoveCheck(false); // ����üũ�� false�϶��� ��ü������Ʈ .. �� �������ӿ� ��ü������Ʈ
	                           //1�� ���������Ʈ 6�� �̷����

}
