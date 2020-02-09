#include "stdafx.h"
#include "sellStand.h"

sellStand::sellStand()
{
}

sellStand::~sellStand()
{
}

HRESULT sellStand::init()
{
	//_img = IMAGEMANAGER->findImage("판매창");
	_rc = RectMakeCenter(WINSIZEX / 2 -350, WINSIZEY / 2, 100,100);

	_sellImag = IMAGEMANAGER->findImage("판매창");

	for (int i = 0; i < SLOTNUM; i++)
	{
		_slotImage[i] = IMAGEMANAGER->findImage("판매슬롯이미지");

	}

	_slot[0] = RectMake(_sellImag->getWidth() + 35, _sellImag->getHeight() - 369, 55, 55);
	_slot[1] = RectMake(_sellImag->getWidth() + 289, _sellImag->getHeight() - 369, 50, 50);
	_slot[2] = RectMake(_sellImag->getWidth() + 35, _sellImag->getHeight() - 140, 50, 50);
	_slot[3] = RectMake(_sellImag->getWidth() + 289, _sellImag->getHeight() - 140, 50, 50);

	return S_OK;
}

 void sellStand::release()
{
}

void sellStand::update()
{
}

void sellStand::render()
{
	Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);

	if (_showWindow)
	{
		_sellImag->render(getMemDC(), WINSIZEX / 2 - 70, 100, _sellImag->getWidth(), _sellImag->getHeight());
		for (int i = 0; i < 4; i++)
		{
			_slotImage[i]->render(getMemDC(), _slot[i].left, _slot[i].top);
		}
	
	
	}


}
