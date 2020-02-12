#include "stdafx.h"
#include "mainGame.h"


mainGame::mainGame()
{
}


mainGame::~mainGame()
{
}

HRESULT mainGame::init()
{
	gameNode::init(true);
	imagesInit();


	_mapTool = new mapTool;
	_mapTool->init();
	_playerShop = new playerShop;
	ITEMMANAGER->init();
	_playerShop->init();
	PLAYER->init();
	//
	//_monsterManager = new monsterManager;
//	_monsterManager->init();
	//_invenotry = new inventory;
	//_invenotry->init();
	//�ȳ�
	//��������


	return S_OK;
}

void mainGame::release()
{
	gameNode::release();

}

void mainGame::update()
{
	gameNode::update();
	_mapTool->update();
	//_monsterManager->update();
	_playerShop->update();
	//ANIMATIONMANAGER->update(); //�ִϸ��̼��� ���� ����� ��
	//_monsterManager->update();

	PLAYER->update();

	ANIMATIONMANAGER->update(); //�ִϸ��̼��� ���� ����� ��
	if (KEYMANAGER->isOnceKeyDown('T'))
	{
		//PLAYER->setHP(PLAYER->getHP() - 10);

	}
	//	_invenotry->update();
}

void mainGame::render(/*HDC hdc*/)
{
	//��� ��Ʈ��
	//PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	PatBlt(getMemDC(), CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2, WINSIZEX, WINSIZEY, WHITENESS);
	PatBlt(CAMERAMANAGER->getCameraDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);


	_mapTool->render();
	ITEMMANAGER->render();
	PLAYER->render(DC);
	_playerShop->render();
	//_invenotry->render();
	TIMEMANAGER->render(CAMERAMANAGER->getCameraDC());
	//=====================================================
	//������� ������ HDC�� �׸���.(��������!!)
	//this->getBackBuffer()->render(getHDC(), 0, 0);
	CAMERAMANAGER->render(this->getBackBuffer());
	this->getBackBuffer()->render(getHDC(), 0, 0, CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2, WINSIZEX, WINSIZEY);
}











