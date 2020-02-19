#include "stdafx.h"
#include "playerShop.h"

playerShop::playerShop()
{
}

playerShop::~playerShop()
{
}

HRESULT playerShop::init()
{
	PLAYER->setPlayerLocation(DUNGEON_PLAYER_VERSION);
	//창고 2개 초기화
	_storage1 = new storage;
	_storage1->init("창고1",PointMake(WINSIZEX / 2 / 2/2, WINSIZEY / 2 / 2 + 150));
	_storage2 = new storage;
	_storage2->init("창고2", PointMake(WINSIZEX / 2 / 2/2, WINSIZEY / 2 / 2));
	
	//판매대 초기화
	_sellStand = new sellTable;
	_sellStand->init();

	return S_OK;
}

void playerShop::release()
{
	SAFE_DELETE(_storage1);
	SAFE_DELETE(_storage2);
	SAFE_DELETE(_sellStand);
}

void playerShop::update()
{
	PLAYER->update();

	_sellStand->update();

	_storage1->update();
	_storage2->update();


	_storage1->removeItem();
	_storage2->removeItem();
}

void playerShop::render()
{
	PLAYER->render(getMemDC());

	_sellStand->render();

	_storage1->render();
	_storage2->render();
}
