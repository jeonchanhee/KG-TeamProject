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
	if (SOUNDMANAGER->getCurrentSong() != "�������")
	{
		SOUNDMANAGER->stop(SOUNDMANAGER->getCurrentSong());
		SOUNDMANAGER->setCurrentNum(3);
		SOUNDMANAGER->play(SOUNDMANAGER->getCurrentSong(), 1);
	}
	PLAYER->setPlayerLocation(SHOP_PLAYER_VERSION);
	PLAYER->setPlayerMoving(PLAYER_DOWN_IDLE);
	//â�� 2�� �ʱ�ȭ
	_storage1 = new storage;
	_storage1->init("â��1",PointMake(WINSIZEX / 2+255 , 280));
	_storage2 = new storage;
	_storage2->init("â��2", PointMake(WINSIZEX / 2-180, 200));
	
	//�ǸŴ� �ʱ�ȭ
	_sellStand = new sellTable;
	_sellStand->init();
	_girlNPC = new buyNPC;
	_girlNPC->init(_sellStand->getTableRc());
	villageRc = RectMakeCenter(WINSIZEX / 2+100, WINSIZEY / 2+220, 100,100);
	return S_OK;
}

void playerShop::release()
{
	SAFE_DELETE(_storage1);
	SAFE_DELETE(_storage2);
	SAFE_DELETE(_sellStand);
	SAFE_DELETE(_girlNPC);
}

void playerShop::update()
{
	PLAYER->update();
	ANIMATIONMANAGER->update();
	_sellStand->update();

	_storage1->update();
	_storage2->update();

	_storage1->removeItem();
	_storage2->removeItem();
	_girlNPC->update(_sellStand->getSellItem(0), _sellStand->getSellItem(1), _sellStand->getSellItem(2), _sellStand->getSellItem(3));
	
	if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &villageRc))
	{
		PLAYER->setXY(WINSIZEX / 2 - 30, WINSIZEY / 2 - 10);
		SCENEMANAGER->changeScene("������");
	}
	
}

void playerShop::render()
{
	IMAGEMANAGER->render("������", getMemDC(), 0, 0);
	_sellStand->render();
	if(KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(getMemDC(), villageRc.left, villageRc.top, villageRc.right, villageRc.bottom);

	_storage1->render();
	_storage2->render();
	PLAYER->render(getMemDC());
	_girlNPC->render();
}
