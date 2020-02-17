#include "stdafx.h"
#include "dungeonScene.h"

dungeonScene::dungeonScene()
{
}

dungeonScene::~dungeonScene()
{
}

HRESULT dungeonScene::init()
{
	PLAYER->setPlayerLocation(DUNGEON_PLAYER_VERSION);
	PLAYER->setPlayerMoving(PLAYER_DOWN_IDLE);

	return S_OK;
}

void dungeonScene::relaese()
{


}

void dungeonScene::update()
{
	PLAYER->update();

	if (PLAYER->getHP() <= 0)
	{
		SCENEMANAGER->changeScene("¸¶À»¾À");
	}

	if (KEYMANAGER->isOnceKeyDown('M'))
	{
		SCENEMANAGER->changeScene("¸¶À»¾À");
	}
}

void dungeonScene::render()
{
	PLAYER->render(getMemDC());
}
