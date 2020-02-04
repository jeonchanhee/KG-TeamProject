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
	_mapTool = new mapTool;
	_mapTool->init();

=======
	//안녕
	//하이하이
>>>>>>> 617bbebdd44421d6d7eb8c2d5342c22fecbd27d5
	return S_OK;
}

void mainGame::release()
{
	gameNode::release();

}

void mainGame::update()
{
	gameNode::update();
	
}

void mainGame::render(/*HDC hdc*/)
{
	//흰색 비트맵
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	_mapTool->render();

	TIMEMANAGER->render(getMemDC());
	//=====================================================
	//백버퍼의 내용을 HDC에 그린다.(지우지마!!)
	this->getBackBuffer()->render(getHDC(), 0, 0);
	
}









