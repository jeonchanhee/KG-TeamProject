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
	_open = IMAGEMANAGER->findImage("����");

	//â�� 2�� �ʱ�ȭ
	int arrlen1[] = { 0,1,2 };
	int arrlen2[] = { 3,4,5 };
	ANIMATIONMANAGER->addAnimation("â��1����", "â��1", arrlen1, 3, 10, false);
	ANIMATIONMANAGER->addAnimation("â��1Ŭ����", "â��1", arrlen2, 3, 10, false);

	int arrlen3[] = { 0,1,2,3 };
	int arrlen4[] = { 4,5,6,7 };
	ANIMATIONMANAGER->addAnimation("â��2����", "â��2", arrlen3, 4, 10, false);
	ANIMATIONMANAGER->addAnimation("â��2Ŭ����", "â��2", arrlen4, 4, 10, false);

	_storage1 = new storage;
	_storage1->init("â��1",PointMake(WINSIZEX / 2 / 2, WINSIZEY / 2 / 2 + 150));
	_storage2 = new storage;
	_storage2->init("â��2", PointMake(WINSIZEX / 2 / 2, WINSIZEY / 2 / 2));

	//���尣�ʱ�ȭ
	_blacksmith = new blacksmith;
	_blacksmith->init();
	//�ǸŴ� �ʱ�ȭ
	_sellStand = new sellStand;
	_sellStand->init();


	return S_OK;
}

void playerShop::release()
{
	SAFE_DELETE(_storage1);
	SAFE_DELETE(_storage2);
	SAFE_DELETE(_sellStand);
	SAFE_DELETE(_blacksmith);
}

void playerShop::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))_storage2->addItem(ITEMMANAGER->addItem("õ �ݴٳ�"));

	//�ǸŴ� ����ݱ�
	if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &_sellStand->getRECT()))
	{
		if (!_showWindow)
		{
			if (KEYMANAGER->isOnceKeyDown('J'))
				_showWindow = true;
		}
		if (_showWindow)
		{
			if (KEYMANAGER->isOnceKeyDown('I') )
				_showWindow = false;
		}
		_sellStand->setShow(_showWindow);
	}

	//���尣����ݱ�
	if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &_blacksmith->getRECT()))
	{
		if (!_showWindow)
		{
			if (KEYMANAGER->isOnceKeyDown('J'))
				_showWindow = true;
		}
		if (_showWindow)
		{
			if (KEYMANAGER->isOnceKeyDown('I'))
				_showWindow = false;
		}
		_blacksmith->setShow(_showWindow);
	}

	//â��1 ����ݱ�
	if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &_storage1->getRECT()))
	{
		if (!_showWindow)
		{
			if (KEYMANAGER->isOnceKeyDown('J'))
			{
				_storage1->resetChoiceNum();
				_storage1->setAni("â��1����");
				_storage1->getAni()->start();
				_showWindow = true;
			}
		}
		if (_showWindow)
		{
			if (KEYMANAGER->isOnceKeyDown('I'))
			{
				_storage1->setAni("â��1Ŭ����");
				_storage1->getAni()->start();
				_showWindow = false;
			}
		}
		_storage1->setShow(_showWindow);
	}

	//â��2 ����ݱ�
	if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &_storage2->getRECT()))
	{
		if (!_showWindow)
		{
			if (KEYMANAGER->isOnceKeyDown('J'))
			{
				_storage2->resetChoiceNum();
				_storage2->setAni("â��2����");
				_storage2->getAni()->start();
				_showWindow = true;
			}
		}
		if (_showWindow)
		{
			if (KEYMANAGER->isOnceKeyDown('I'))
			{
				_storage2->setAni("â��2Ŭ����");
				_storage2->getAni()->start();
				_showWindow = false;
			}
		}
		_storage2->setShow(_showWindow);
	}
	//if(KEYMANAGER->isOnceKeyDown('0'))
	
	_storage1->update();
	_storage2->update();
	_sellStand->update();
	_blacksmith->update();
	_blacksmith->buyItem(_storage1->getStorage1());

}

void playerShop::render()
{

	if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &_sellStand->getRECT()))
	{
		_open->render(getMemDC(), _sellStand->getRECT().right, _sellStand->getRECT().top-50);
	}
	if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &_storage1->getRECT()))
	{
		_open->render(getMemDC(), _storage1->getRECT().right, _storage1->getRECT().top - 50);
	}
	if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &_storage2->getRECT()))
	{
		_open->render(getMemDC(), _storage2->getRECT().right, _storage2->getRECT().top - 50);
	}
	if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &_blacksmith->getRECT()))
	{
		_open->render(getMemDC(), _blacksmith->getRECT().right, _blacksmith->getRECT().top - 50);
	}


	_sellStand->render();
	_storage1->render();
	_storage2->render();
	_blacksmith->render();
}
