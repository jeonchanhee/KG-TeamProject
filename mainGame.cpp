#include "stdafx.h"
#include "mainGame.h"


mainGame::mainGame(){}

mainGame::~mainGame(){}

HRESULT mainGame::init()
{
	gameNode::init(true);

	imagesInit();

	PLAYER->init();


	SCENEMANAGER->addScene("����", new mapTool);
	SCENEMANAGER->addScene("��Ʈ��", new introScene);
	SCENEMANAGER->addScene("����1", new dungeonScene);
	SCENEMANAGER->addScene("����2", new dungeonScene2);
	SCENEMANAGER->addScene("����3", new dungeonScene3);
	SCENEMANAGER->addScene("����4", new dungeonScene4);
	SCENEMANAGER->addScene("����5", new dungeonScene5);

	SCENEMANAGER->addScene("������", new villageScene);
	SCENEMANAGER->addScene("�÷��̾������", new playerShop);

	SCENEMANAGER->changeScene("��Ʈ��");


	return S_OK;
}

void mainGame::release()
{
	gameNode::release();

	SCENEMANAGER->release();

}

void mainGame::update()
{
	gameNode::update();

	SCENEMANAGER->update();
}

void mainGame::render(/*HDC hdc*/)
{
	//��� ��Ʈ��
	//PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	PatBlt(getMemDC(), CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2, WINSIZEX, WINSIZEY, WHITENESS);
	PatBlt(CAMERAMANAGER->getCameraDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//============================================================================�� ���� �ǵ帮�� ����=======================================================================================
	
	SCENEMANAGER->render();


	char str[128];
	sprintf_s(str, "FPS :  %d", PLAYER->getPlayerLocation());
	TextOut(CAMERAMANAGER->getCameraDC(), 200, 0, str, strlen(str));

	TIMEMANAGER->render(CAMERAMANAGER->getCameraDC());
	//============================================================================�� ������ �ǵ帮�� ����=======================================================================================
	//������� ������ HDC�� �׸���.(��������!!)
	//this->getBackBuffer()->render(getHDC(), 0, 0);
	CAMERAMANAGER->render(this->getBackBuffer());
	this->getBackBuffer()->render(getHDC(), 0, 0, CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2, WINSIZEX, WINSIZEY);
}











