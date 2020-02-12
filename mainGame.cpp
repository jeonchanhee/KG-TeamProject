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
<<<<<<< HEAD
	_playerShop = new playerShop;
	ITEMMANAGER->init();
	_playerShop->init();
	PLAYER->init();
	//
	//_monsterManager = new monsterManager;
//	_monsterManager->init();
	//_invenotry = new inventory;
	//_invenotry->init();
=======


	/*_player = new player;
	_player->init();*/
	ITEMMANAGER->init();
	PLAYER->init();

	_playerShop = new playerShop;
	_playerShop->init();
	_monsterManager = new monsterManager;
	_monsterManager->init();
	_invenotry = new inventory;
	_invenotry->init();
>>>>>>> 46506dbf4095b4026a947b643eb23efcd95ceb36
	//안녕
	//하이하이


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
<<<<<<< HEAD
	//_monsterManager->update();
	_playerShop->update();
	//ANIMATIONMANAGER->update(); //애니메이션을 위해 사용한 것
	//_monsterManager->update();
=======
	PLAYER->update();
	//ANIMATIONMANAGER->update(); //애니메이션을 위해 사용한 것
	_monsterManager->update();
	_playerShop->update();
>>>>>>> 46506dbf4095b4026a947b643eb23efcd95ceb36

	//PLAYER->update();

	ANIMATIONMANAGER->update(); //애니메이션을 위해 사용한 것
	if (KEYMANAGER->isOnceKeyDown('T'))
	{
		//PLAYER->setHP(PLAYER->getHP() - 10);

	}
	//	_invenotry->update();
}

void mainGame::render(/*HDC hdc*/)
{
	//흰색 비트맵
	//PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	PatBlt(getMemDC(), CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2, WINSIZEX, WINSIZEY, WHITENESS);
	PatBlt(CAMERAMANAGER->getCameraDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	_mapTool->render();
	ITEMMANAGER->render();
	PLAYER->render(DC);
<<<<<<< HEAD
	_playerShop->render();
	//_invenotry->render();
=======
	_monsterManager->render();
	_invenotry->render();
	_playerShop->render();
>>>>>>> 46506dbf4095b4026a947b643eb23efcd95ceb36
	TIMEMANAGER->render(CAMERAMANAGER->getCameraDC());
	//=====================================================
	//백버퍼의 내용을 HDC에 그린다.(지우지마!!)
	//this->getBackBuffer()->render(getHDC(), 0, 0);
	CAMERAMANAGER->render(this->getBackBuffer());
	this->getBackBuffer()->render(getHDC(), 0, 0, CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2, WINSIZEX, WINSIZEY);
}











