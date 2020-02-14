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



	return S_OK;
}

void dungeonScene::relaese()
{


}

void dungeonScene::update()
{
	PLAYER->update();
}

void dungeonScene::render()
{
	PLAYER->render(getMemDC());
}
