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
<<<<<<< HEAD


	_player = new player;
	_player->init();
<<<<<<< HEAD
=======

<<<<<<< HEAD
=======
>>>>>>> 0e80ddae0a3757d2c371d7e2ebb66f8ee3e82212
	_mapTool = new mapTool;
	_mapTool->init();

	//안녕
	//하이하이
<<<<<<< HEAD
>>>>>>> 617bbebdd44421d6d7eb8c2d5342c22fecbd27d5

=======
>>>>>>> 0e80ddae0a3757d2c371d7e2ebb66f8ee3e82212
	return S_OK;
}

void mainGame::release()
{
	gameNode::release();
	_player->release();
}

void mainGame::update()
{
	gameNode::update();
<<<<<<< HEAD
	ANIMATIONMANAGER->update(); //애니메이션매니저를 움직이기 위해
	_player->update();

=======

	_mapTool->update();
>>>>>>> 0e80ddae0a3757d2c371d7e2ebb66f8ee3e82212
}

void mainGame::render(/*HDC hdc*/)
{
	//흰색 비트맵
<<<<<<< HEAD
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	_player->render();
<<<<<<< HEAD
=======
=======
	//PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	PatBlt(getMemDC(), CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2, WINSIZEX, WINSIZEY, WHITENESS);
	PatBlt(CAMERAMANAGER->getCameraDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

>>>>>>> 0e80ddae0a3757d2c371d7e2ebb66f8ee3e82212
	_mapTool->render();

	TIMEMANAGER->render(CAMERAMANAGER->getCameraDC());
	//=====================================================
	//백버퍼의 내용을 HDC에 그린다.(지우지마!!)
	//this->getBackBuffer()->render(getHDC(), 0, 0);
	CAMERAMANAGER->render(this->getBackBuffer());
	this->getBackBuffer()->render(getHDC(), 0, 0, CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2, WINSIZEX, WINSIZEY);
}









