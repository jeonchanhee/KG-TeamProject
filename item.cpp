#include "stdafx.h"
#include "item.h"

item::item()
{
}

item::~item()
{
}

HRESULT item::init(const char* name, itemType type, int orignalPrice, int playerPrice, int atk, int def, int speed, int hp, int heal, int maxCnt)
{

	_item.itemName = name;
	_item.image = IMAGEMANAGER->findImage(name);
	_item.type = type;
	_item.move = false;
	_item.wave = false;
	_item.orignalPrice = orignalPrice;
	_item.playerPrice = playerPrice;
	_item.rc = RectMakeCenter(-50,-50, _item.image->getWidth(), _item.image->getHeight());
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
	if (KEYMANAGER->isToggleKey('T')) Rectangle(CAMERAMANAGER->getCameraDC(), _item.rc.left, _item.rc.top, _item.rc.right, _item.rc.bottom);

	//_item.image->render(CAMERAMANAGER->getCameraDC(), _item.rc.left, _item.rc.top);
	_item.image->render(CAMERAMANAGER->getCameraDC(), _item.rc.left, _item.rc.top);
}

void item::render(HDC hdc)
{
	if (KEYMANAGER->isToggleKey('T')) Rectangle(CAMERAMANAGER->getCameraDC(), _item.rc.left, _item.rc.top, _item.rc.right, _item.rc.bottom);

	//_item.image->render(CAMERAMANAGER->getCameraDC(), _item.rc.left, _item.rc.top);
	_item.image->render(hdc, _item.rc.left, _item.rc.top);
}

void item::magnet(POINT playerPoint)
{
	_item.x = _item.rc.left + (_item.rc.right - _item.rc.left) / 2;
	_item.y = _item.rc.top + (_item.rc.bottom - _item.rc.top) / 2;
	//상태가 무브일때, 그리고 플레이어를 감지하는 렉트와 플레이어의 렉트가 충돌했을때
	if (_item.move && getDistance(_item.x, _item.y, playerPoint.x, playerPoint.y) < 50)
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
	if (_item.wave)		//바닥에 떨어진 템이라면
	{
		waveCnt++;

		if (updown)		//위아래로 흔들림
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
				waveCnt = 1;
			}
		}

	}
}

bool item::maxItem()//미완성
{
	if (_item.maxCnt <= _item.cnt)
	{
		_item.cnt = _item.maxCnt;
		return true;
	}
	else return false;
}


