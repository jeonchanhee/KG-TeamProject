#include "stdafx.h"
#include "mainGame.h"


mainGame::mainGame(){}

mainGame::~mainGame(){}

HRESULT mainGame::init()
{
	gameNode::init(true);
	imagesInit();

	PLAYER->init();


	SCENEMANAGER->addScene("맵툴", new mapTool);
	SCENEMANAGER->addScene("인트로", new introScene);
	SCENEMANAGER->addScene("던전씬", new dungeonScene);
	SCENEMANAGER->addScene("마을씬", new villageScene);

	SCENEMANAGER->changeScene("인트로");


	return S_OK;
}

void mainGame::release()
{
	gameNode::release();

}

void mainGame::update()
{
	gameNode::update();

	SCENEMANAGER->update();
}

void mainGame::render(/*HDC hdc*/)
{
	//흰색 비트맵
	//PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	PatBlt(getMemDC(), CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2, WINSIZEX, WINSIZEY, WHITENESS);
	PatBlt(CAMERAMANAGER->getCameraDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//============================================================================이 위로 건드리면 뒤짐=======================================================================================
	
	SCENEMANAGER->render();


	char str[128];
	sprintf_s(str, "FPS :  %d", PLAYER->getPlayerLocation());
	TextOut(CAMERAMANAGER->getCameraDC(), 200, 0, str, strlen(str));

	TIMEMANAGER->render(CAMERAMANAGER->getCameraDC());
	//============================================================================이 밑으로 건드리면 뒤짐=======================================================================================
	//백버퍼의 내용을 HDC에 그린다.(지우지마!!)
	//this->getBackBuffer()->render(getHDC(), 0, 0);
	CAMERAMANAGER->render(this->getBackBuffer());
	this->getBackBuffer()->render(getHDC(), 0, 0, CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2, WINSIZEX, WINSIZEY);
}











