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

	//â�� 2�� �ʱ�ȭ
	_storage1 = new storage;
	_storage1->init("â��1",PointMake(WINSIZEX / 2 / 2/2, WINSIZEY / 2 / 2 + 150));
	_storage2 = new storage;
	_storage2->init("â��2", PointMake(WINSIZEX / 2 / 2/2, WINSIZEY / 2 / 2));
	
	//npc���� 2�� �ʱ�ȭ
	_potionShop = new NPCpotionShop;
	_potionShop->init(PointMake(100, 100));
	_blacksmith = new NPCblacksmith;
	_blacksmith->init(PointMake(100, 500));

	//�ǸŴ� �ʱ�ȭ
	_sellStand = new sellTable;
	_sellStand->init();

	return S_OK;
}

void playerShop::release()
{
	SAFE_DELETE(_storage1);
	SAFE_DELETE(_storage2);
	SAFE_DELETE(_sellStand);
	SAFE_DELETE(_potionShop);
	SAFE_DELETE(_blacksmith);
}

void playerShop::update()
{
	_potionShop->update();
	_blacksmith->update();

	_sellStand->update();

	_storage1->update();
	_storage2->update();

	_potionShop->buy();
	_blacksmith->buy();

	_storage1->removeItem();
	_storage2->removeItem();
}

void playerShop::render()
{
	_potionShop->render();
	_blacksmith->render();

	_sellStand->render();

	_storage1->render();
	_storage2->render();
}
