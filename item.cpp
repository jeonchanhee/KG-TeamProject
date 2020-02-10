#include "stdafx.h"
#include "item.h"

item::item()
{
}

item::~item()
{
}

HRESULT item::init(const char* name, itemType type , int orignalPrice, int playerPrice, int atk , int def , int speed, int hp ,int heal , int maxCnt)
{

	_item.itemName = name;
	_item.image = IMAGEMANAGER->findImage(name);
	_item.type = type;
	_item.move = false;
	_item.orignalPrice = orignalPrice;
	_item.playerPrice = playerPrice;
	_item.rc = RectMakeCenter(0, 0, _item.image->getWidth(), _item.image->getHeight());
	_item.atk = atk;
	_item.def = def;
	_item.speed = speed;
	_item.hp = hp;
	_item.heal = heal;
	_item.cnt = 1;
	_item.maxCnt = maxCnt;

	waveCnt = 0;
	updown = true;
	return S_OK;
}

void item::release()
{
}

void item::update()
{
	wave();
	magnet(PointMake(PLAYER->getX(), PLAYER->getY()));
}

void item::render()
{
	if(KEYMANAGER->isToggleKey('T')) Rectangle(CAMERAMANAGER->getCameraDC(), _item.rc.left, _item.rc.top, _item.rc.right, _item.rc.bottom);
	
	_item.image->render(CAMERAMANAGER->getCameraDC(), _item.rc.left, _item.rc.top);
}

void item::magnet(POINT playerPoint)
{		
	_item.x = _item.rc.left + (_item.rc.right - _item.rc.left) / 2;
	_item.y = _item.rc.top + (_item.rc.bottom - _item.rc.top) / 2;
	//���°� �����϶�, �׸��� �÷��̾ �����ϴ� ��Ʈ�� �÷��̾��� ��Ʈ�� �浹������
	if (_item.move && getDistance(_item.x, _item.y, playerPoint.x, playerPoint.y) < 100)
	{
		if (_item.x < playerPoint.x) _item.x += 2;
		if (_item.x > playerPoint.x) _item.x -= 2;
		if (_item.y < playerPoint.y) _item.y += 2;
		if (_item.y < playerPoint.y) _item.y -= 2;
	}
	_item.rc = RectMakeCenter(_item.x, _item.y, _item.image->getWidth(), _item.image->getHeight());
}

void item::wave()
{
	if (_item.move)		//�ٴڿ� ������ ���̶��
	{
		waveCnt++;

		if(updown)		//���Ʒ��� ��鸲
		{
			_item.rc.top -= 1;
			_item.rc.bottom -= 1;
			if (waveCnt > 15) updown = false;
		}
		else if (!updown)
		{
			_item.rc.top += 1;
			_item.rc.bottom += 1;
			if (waveCnt > 30)
			{
				updown = true;
				waveCnt = 0;
			}
		}

	}
}

bool item::maxItem()
{
	if (_item.maxCnt <= _item.cnt)
	{
		_item.cnt = _item.maxCnt;
		return true;
	}
	else return false;
}


