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

	_storage = new storage;
	_storage->init("â��1", PointMake(WINSIZEX/2, WINSIZEY/2));

	return S_OK;
}

void dungeonScene::relaese()
{
	_storage->release();

}

void dungeonScene::update()
{
	PLAYER->update();
	_storage->update();

}

void dungeonScene::render()
{
	PLAYER->render(getMemDC());
	_storage->render();

}
