#include "stdafx.h"
#include "sellTable.h"

sellTable::sellTable()
{
}

sellTable::~sellTable()
{
}

HRESULT sellTable::init()
{
	_sellMainImg = IMAGEMANAGER->findImage("판매창");

	//렉트초기화
	_tableRc = RectMakeCenter(WINSIZEX / 2 -350, WINSIZEY / 2+200, 100,100);

	_slot[0] = RectMake(_sellMainImg->getWidth() + 83, _sellMainImg->getHeight() -305, 40, 40);
	_slot[1] = RectMake(_sellMainImg->getWidth() + 312, _sellMainImg->getHeight() - 305, 40, 40);
	_slot[2] = RectMake(_sellMainImg->getWidth() + 83, _sellMainImg->getHeight() - 100, 40, 40);
	_slot[3] = RectMake(_sellMainImg->getWidth() + 312, _sellMainImg->getHeight() - 100, 40, 40);
	for (int i = 0; i < SLOTNUM; i++)
	{
		_slotImage[i] = IMAGEMANAGER->findImage("판매슬롯이미지");
		_sellInfo[i] = RectMakeCenter(_slot[i].left + (_slot[i].right - _slot[i].left) / 2, _slot[i].top + (_slot[i].bottom - _slot[i].top) / 2+80, 180, 90);
	}

	//커서 초기화
	_cursorNum = 0;
	_cursorSlot = _slot[_cursorNum];
	_cursor = new cursor;
	_cursor->init();
	_grab = new image;
	_grab = IMAGEMANAGER->findImage("커서그랩");
	_choiceItem = false;

	//비어있음으로 초기화
	_vSellItem.push_back(ITEMMANAGER->addItem("비어있음"));
	_vSellItem.push_back(ITEMMANAGER->addItem("비어있음"));
	_vSellItem.push_back(ITEMMANAGER->addItem("비어있음"));
	_vSellItem.push_back(ITEMMANAGER->addItem("비어있음"));
	for (int i = 0; i < _vSellItem.size(); i++)
	{
		_vSellItem[i].setRect(_slot[i]);
	}
	return S_OK;
}

 void sellTable::release()
{
	 SAFE_DELETE(_cursor);
}

void sellTable::update()
{
	for (int i = 0; i < _vSellItem.size(); i++)
	{
		if (IntersectRect(&temp, &_cursorSlot, &_vSellItem[i].getRECT()))
		{
			//커서와 판매하는곳이 닿아있으면 선택되어있다고 바꿔줌
			_choiceItem = true;
		}
	}

	playerCollision();
	cursorControl();
}

void sellTable::render()
{
	IMAGEMANAGER->render("판매테이블", getMemDC(), _tableRc.left, _tableRc.top);
	if (!_showWindow)
	{
		if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &_tableRc))
		{
			IMAGEMANAGER->render("열기", getMemDC(), _tableRc.right, _tableRc.top - 20);
		}
	}
	if (_showWindow)
	{
		_sellMainImg->render(getMemDC(), WINSIZEX / 2 - 70, 100, _sellMainImg->getWidth(), _sellMainImg->getHeight());
		for (int i = 0; i < SLOTNUM; i++)
		{
			_slotImage[i]->render(getMemDC(), _slot[i].left, _slot[i].top);
			Rectangle(getMemDC(), _sellInfo[i].left, _sellInfo[i].top, _sellInfo[i].right, _sellInfo[i].bottom);
		}
		_cursor->render();
	}
}

void sellTable::cursorControl()
{
	if (_showWindow)
	{
		if (KEYMANAGER->isOnceKeyDown('A'))
		{
			//커서가 옆으로 못나가게
			_cursorNum--;
			if (_cursorNum < 0) _cursorNum = 0;

			_cursorSlot = RectMake(_slot[_cursorNum].left, _slot[_cursorNum].top, 40, 40);
			_cursor->getAni()->start();
		}
		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			//커서가 옆으로 못나가게
			_cursorNum++;
			if (_cursorNum >= SLOTNUM) _cursorNum = SLOTNUM-1;

			_cursorSlot = RectMake(_slot[_cursorNum].left, _slot[_cursorNum].top, 40, 40);
			_cursor->getAni()->start();
		}
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			//커서가 위로못나가게
			int temp;
			temp = _cursorNum;
			_cursorNum -= 2;
			if (_cursorNum < 0)_cursorNum = temp;

			_cursorSlot = RectMake(_slot[_cursorNum].left, _slot[_cursorNum].top, 40, 40);
			_cursor->getAni()->start();
		}
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			//커서가 아래로 못나가게
			int temp;
			temp = _cursorNum;
			_cursorNum += 2;
			if (_cursorNum >= SLOTNUM)_cursorNum = temp;

			_cursorSlot = RectMake(_slot[_cursorNum].left, _slot[_cursorNum].top, 40, 40);
			_cursor->getAni()->start();
		}
		_cursor->setRc(_cursorSlot);

		if (KEYMANAGER->isOnceKeyDown('I'))
		{
			_cursor->getAni()->start();
		}
	}
}

void sellTable::playerCollision()
{
	if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &_tableRc))
	{
		if (!_showWindow)
		{
			if (KEYMANAGER->isOnceKeyDown('J'))_showWindow = true;
		}
		if (_showWindow)
		{
			if (KEYMANAGER->isOnceKeyDown('I'))_showWindow = false;
		}
	}
}
