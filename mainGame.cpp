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
=======

<<<<<<< HEAD
	_mapTool = new mapTool;
	_mapTool->init();

=======
>>>>>>> 5001e4eff0c23d1813e7a24b65d9e226632545b8
	//�ȳ�
	//��������
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
	//��� ��Ʈ��
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

<<<<<<< HEAD
=======
	_mapTool->render();

>>>>>>> 5001e4eff0c23d1813e7a24b65d9e226632545b8
	TIMEMANAGER->render(getMemDC());
	//=====================================================
	//������� ������ HDC�� �׸���.(��������!!)
	this->getBackBuffer()->render(getHDC(), 0, 0);
	
}









