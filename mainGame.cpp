#include "stdafx.h"
#include "mainGame.h"


mainGame::mainGame(){}

mainGame::~mainGame(){}

HRESULT mainGame::init()
{
	gameNode::init(true);

	SOUNDMANAGER->addSound("인트로브금", "sound/introBGM.mp3", true, true);
	SOUNDMANAGER->addSound("마을브금", "sound/townBGM.mp3", true, true);
	SOUNDMANAGER->addSound("던전브금", "sound/dungeonBGM.mp3", true, true);
	SOUNDMANAGER->addSound("상점브금", "sound/shopBGM.mp3", true, true);
	SOUNDMANAGER->addSound("회복방브금", "sound/poolRoomBGM.mp3", true, true);
	SOUNDMANAGER->addSound("보스방브금", "sound/bossRoomBGM.mp3", true, true);
	SOUNDMANAGER->addSound("칼질", "sound/will_shortSwordAttack.wav", false, false);
	SOUNDMANAGER->addSound("활질", "sound/will_bowAttack.wav", false, false);
	SOUNDMANAGER->setSongName();


	imagesInit();

	PLAYER->init();


	SCENEMANAGER->addScene("맵툴", new mapTool);
	SCENEMANAGER->addScene("인트로", new introScene);
	SCENEMANAGER->addScene("던전1", new dungeonScene);
	SCENEMANAGER->addScene("던전2", new dungeonScene2);
	SCENEMANAGER->addScene("던전3", new dungeonScene3);
	SCENEMANAGER->addScene("던전4", new dungeonScene4);
	SCENEMANAGER->addScene("던전5", new dungeonScene5);

	SCENEMANAGER->addScene("마을씬", new villageScene);
	SCENEMANAGER->addScene("플레이어상점씬", new playerShop);

	SCENEMANAGER->changeScene("인트로");


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











