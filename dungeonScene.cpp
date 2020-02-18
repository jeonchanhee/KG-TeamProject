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
	_storage->init("Ã¢°í1", PointMake(WINSIZEX / 2, WINSIZEY / 2));
	_sell = new sellTable;
	_sell->init();
	_black = new NPCblacksmith;
	_black->init(PointMake(WINSIZEX / 2 + 100, WINSIZEY / 2));
	_potion = new NPCpotionShop;
	_potion->init(PointMake(WINSIZEX / 2 - 100, WINSIZEY / 2));
	_girlNPC = new buyNPC;
	_girlNPC->init(_sell->getTableRc());
	
	return S_OK;
}

void dungeonScene::relaese()
{
	_storage->release();
}

void dungeonScene::update()
{
	ANIMATIONMANAGER->update();
	PLAYER->update();
	_storage->update();
	_sell->update();
	_black->update();
	if (_black->getOpen())_black->buy();
	_potion->update();
	if (_potion->getOpen())_potion->buy();
	_girlNPC->update(_sell->getSellItem(0), _sell->getSellItem(1), _sell->getSellItem(2), _sell->getSellItem(3));

}

void dungeonScene::render()
{
	PLAYER->render(getMemDC());
	_storage->render();
	_sell->render();
	_black->render();
	_potion->render();
	_girlNPC->render();
}
