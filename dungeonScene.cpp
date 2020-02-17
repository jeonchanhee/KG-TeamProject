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



	_storage = new storage;
	_storage->init("Ã¢°í1", PointMake(WINSIZEX/2, WINSIZEY/2));

	return S_OK;
}

void dungeonScene::relaese()
{
	_storage->release();

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

	_storage->update();


}

void dungeonScene::render()
{
	PLAYER->render(getMemDC());
	_storage->render();

}
