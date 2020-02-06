#include "stdafx.h"
#include "item.h"

item::item()
{
}

item::~item()
{
}

HRESULT item::init(const char* name, itemType type , bool move, int orignalPrice, int playerPrice, int atk , int def , int speed, int hp ,int heal , int cnt, int maxCnt)
{


	_item.itemName = name;
	_item.image = IMAGEMANAGER->findImage(name);
	_item.type = type;
	_item.move = true;
	_item.orignalPrice = orignalPrice;
	_item.playerPrice = playerPrice;
	_item.rc = RectMakeCenter(0, 0, _item.image->getWidth(), _item.image->getHeight());
	_item.magnetRc = RectMakeCenter(_item.rc.left, _item.rc.top, _item.image->getWidth() * 5, _item.image->getHeight() * 5);
	_item.atk = atk;
	_item.def = def;
	_item.speed = speed;
	_item.hp = hp;
	_item.heal = heal;
	_item.cnt = cnt;
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
	_item.magnetRc = RectMakeCenter(_item.rc.left, _item.rc.top, _item.image->getWidth() * 5, _item.image->getHeight() * 5);

	
	wave();
	//magnet(PLAYER->getRect());
}

void item::render()
{
	//Rectangle(getMemDC(), _magnetRc.left, _magnetRc.top, _magnetRc.right, _magnetRc.bottom);
	_item.image->render(CAMERAMANAGER->getCameraDC(), _item.rc.left, _item.rc.top);
}

void item::magnet(RECT playerRc)
{
	RECT temp;

	//���°� �����϶�, �׸��� �÷��̾ �����ϴ� ��Ʈ�� �÷��̾��� ��Ʈ�� �浹������
	if (_item.move&& (IntersectRect(&temp, &_item.magnetRc, &playerRc)))
	{
		//���׳ݷ�Ʈ�� x,y
		int magetX = _item.magnetRc.left + (_item.magnetRc.right - _item.magnetRc.left) / 2;
		int magetY = _item.magnetRc.top + (_item.magnetRc.bottom - _item.magnetRc.top) / 2;
		//�÷��̾��� x,y
		int playerX = playerRc.left + (playerRc.right - playerRc.left) / 2;
		int playerY = playerRc.top + (playerRc.bottom - playerRc.top) / 2;

		//�÷��̾������� ������
		if (magetX <= playerX && magetY >= playerY) //����
		{
			_item.rc.left += MAGNETPOWER;
			_item.rc.right += MAGNETPOWER;
			_item.rc.top -= MAGNETPOWER;
			_item.rc.bottom -= MAGNETPOWER;
		}
		if (magetX <= playerX && magetY <= playerY) //���ϴ�
		{
			_item.rc.left += MAGNETPOWER;
			_item.rc.right += MAGNETPOWER;
			_item.rc.top += MAGNETPOWER;
			_item.rc.bottom += MAGNETPOWER;
		}
		if (magetX >= playerX && magetY >= playerY) //�»��
		{
			_item.rc.left -= MAGNETPOWER;
			_item.rc.right -= MAGNETPOWER;
			_item.rc.top -= MAGNETPOWER;
			_item.rc.bottom -= MAGNETPOWER;
		}
		if (magetX >= playerX && magetY <= playerY) //���ϴ�
		{
			_item.rc.left -= MAGNETPOWER;
			_item.rc.right -= MAGNETPOWER;
			_item.rc.top += MAGNETPOWER;
			_item.rc.bottom += MAGNETPOWER;
		}
	}

	//�ڼ��� �������� �÷��̾�� �������� ������� �κ��丮�� ������
	if (_item.move && (IntersectRect(&temp, &_item.rc, &playerRc)))
	{
		
		
	}


}

void item::wave()
{
	if (_item.move)
	{
		waveCnt++;

		if(updown)
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


