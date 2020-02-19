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

	villageRc = RectMakeCenter(WINSIZEX / 2+100, WINSIZEY / 2+220, 100,100);
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

	if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &villageRc))
	{
		SCENEMANAGER->changeScene("������");
	}
}

void playerShop::render()
{
	IMAGEMANAGER->render("������", getMemDC(), 0, 0);
	_sellStand->render();
	Rectangle(getMemDC(), villageRc.left, villageRc.top, villageRc.right, villageRc.bottom);

	_storage1->render();
	_storage2->render();
	PLAYER->render(getMemDC());

}
