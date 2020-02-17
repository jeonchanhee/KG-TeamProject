#include "stdafx.h"
#include "villageScene.h"

villageScene::villageScene()
{
}

villageScene::~villageScene()
{
}

HRESULT villageScene::init()
{
	PLAYER->setPlayerLocation(SHOP_PLAYER_VERSION);
	PLAYER->setPlayerMoving(PLAYER_DOWN_IDLE);

	return S_OK;
}

void villageScene::relaese()
{
}

void villageScene::update()
{
	PLAYER->update();

	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		SCENEMANAGER->changeScene("´øÀü¾À");
	}
}

void villageScene::render()
{
	PLAYER->render(getMemDC());
}
