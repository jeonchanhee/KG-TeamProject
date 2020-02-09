#include "stdafx.h"
#include "blacksmith.h"

blacksmith::blacksmith()
{
}

blacksmith::~blacksmith()
{
}

HRESULT blacksmith::init()
{
	//이미지 초기화
	_armorTabImg = IMAGEMANAGER->findImage("아머슬롯");
	_bowTabImg = IMAGEMANAGER->findImage("보우슬롯");
	_swordTabImg = IMAGEMANAGER->findImage("소드슬롯");
	_titleImg = IMAGEMANAGER->findImage("타이틀");
	_showImg = IMAGEMANAGER->findImage("아이템보여주는창");
	_npcImg = IMAGEMANAGER->findImage("벌컨");
	_recipeImg = IMAGEMANAGER->findImage("업그레이드레시피");

	for (int i = 0; i < 9; i++)
	{
		_itemSlotImg[i] = IMAGEMANAGER->findImage("슬롯이미지");
	}
	for (int i = 0; i < 3; i++)
	{
		_recipeSlotImg[i] = IMAGEMANAGER->findImage("슬롯이미지");
	}

	//렉트초기화
	_armorTab = RectMakeCenter(WINSIZEX / 2-100, WINSIZEY / 2 - 290, _armorTabImg->getWidth(), _armorTabImg->getWidth());
	_swordTab = RectMakeCenter(WINSIZEX / 2 -30,    WINSIZEY / 2 - 290, _swordTabImg->getWidth(), _swordTabImg->getHeight());
	_bowTab = RectMakeCenter(WINSIZEX / 2 + 40, WINSIZEY / 2 - 290, _bowTabImg->getWidth(), _bowTabImg->getHeight());
	
	_itemSlot[0]= RectMakeCenter(WINSIZEX / 2 - 100, WINSIZEY / 2 - 170, _itemSlotImg[0]->getWidth(), _itemSlotImg[0]->getHeight());

	//업그레이드 템 보여주는 슬롯의 렉트
	for (int i = 1; i < 9; i++)
	{
		if (i < 5)
		{
			_itemSlot[i] = RectMakeCenter(_itemSlot[0].right-30 + (i * 60), _itemSlot[0].top - 10, _itemSlotImg[i]->getWidth(), _itemSlotImg[i]->getWidth());
		}
		if (i >= 5)
		{
			_itemSlot[i] = RectMakeCenter(_itemSlot[0].right-30 + ((i%5+1)* 60), _itemSlot[0].bottom +10, _itemSlotImg[i]->getWidth(), _itemSlotImg[i]->getWidth());
		}
	}


	_npcRc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 - 200, 100, 100);

	_currentTab = 0;  //현재탭

	//커서초기화
	_choiceNum = 0;
	_choiceSlot = _itemSlot[_choiceNum];
	_cursor = new cursor;
	_cursor->init();
	_grab = new image;
	_grab = IMAGEMANAGER->addImage("커서그랩", "images/shop/grab.bmp", 50, 52, true, RGB(255, 0, 255));

	return S_OK;
}

void blacksmith::release()
{
}

void blacksmith::update()
{
	tabControl();		
	cursorControl();
}

void blacksmith::render()
{
	Rectangle(getMemDC(), _npcRc.left, _npcRc.top, _npcRc.right, _npcRc.bottom);

	if (_showWindow)
	{
		_armorTabImg->render(getMemDC(), _armorTab.left, _armorTab.top);
		_swordTabImg->render(getMemDC(), _swordTab.left, _swordTab.top);
		_bowTabImg->render(getMemDC(), _bowTab.left, _bowTab.top);
		_showImg->render(getMemDC(), WINSIZEX / 2-200, WINSIZEY / 2-300);

		for (int i = 0; i < 9; i++)
		{
			_itemSlotImg[i]->render(getMemDC(), _itemSlot[i].left, _itemSlot[i].top);
		}

		_cursor->render();
	}
}

void blacksmith::cursorControl()
{
	if (_showWindow)
	{
		_cursor->update(_choiceSlot);
		if (KEYMANAGER->isOnceKeyDown('A'))
		{
			//커서가 옆으로 못나가게
			_choiceNum--;
			if (_choiceNum < 0) _choiceNum = 0;

			_choiceSlot = RectMake(_itemSlot[_choiceNum].left, _itemSlot[_choiceNum].top, 40, 40);
			_cursor->setRc(_choiceSlot);
			_cursor->getAni()->start();
		}
		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			//커서가 옆으로 못나가게
			_choiceNum++;
			if (_choiceNum > SLOTNUM) _choiceNum = SLOTNUM;

			_choiceSlot = RectMake(_itemSlot[_choiceNum].left, _itemSlot[_choiceNum].top, 40, 40);
			_cursor->setRc(_choiceSlot);
			_cursor->getAni()->start();
		}
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			//커서가 위로못나가게
			int temp;
			temp = _choiceNum;
			_choiceNum -= 4;
			if (_choiceNum < 0)_choiceNum = temp;

			_choiceSlot = RectMake(_itemSlot[_choiceNum].left, _itemSlot[_choiceNum].top, 40, 40);
			_cursor->setRc(_choiceSlot);
			_cursor->getAni()->start();
		}
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			//커서가 아래로 못나가게
			int temp;
			temp = _choiceNum;
			_choiceNum += 4;
			if (_choiceNum > SLOTNUM)_choiceNum = temp;

			_choiceSlot = RectMake(_itemSlot[_choiceNum].left, _itemSlot[_choiceNum].top, 40, 40);
			_cursor->setRc(_choiceSlot);
			_cursor->getAni()->start();
		}

		if (KEYMANAGER->isOnceKeyDown('I'))
		{
			_cursor->getAni()->start();
		}
		//grab();
	}
}

void blacksmith::tabControl()
{
	if (_showWindow)
	{
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			_currentTab--;
			if (_currentTab <= 0)_currentTab = 0;
		}
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			_currentTab++;
			if (_currentTab >= 2)_currentTab = 2;
		}
	}
	_armorTab = RectMakeCenter(WINSIZEX / 2 - 100, WINSIZEY / 2 - 280, _armorTabImg->getWidth(), _armorTabImg->getWidth());
	_swordTab = RectMakeCenter(WINSIZEX / 2 - 30, WINSIZEY / 2 - 280, _swordTabImg->getWidth(), _swordTabImg->getHeight());
	_bowTab = RectMakeCenter(WINSIZEX / 2 + 40, WINSIZEY / 2 - 280, _bowTabImg->getWidth(), _bowTabImg->getHeight());

	switch (_currentTab)
	{
	case 0:
		_armorTab = RectMakeCenter(WINSIZEX / 2 - 100, WINSIZEY / 2 - 300, _armorTabImg->getWidth(), _armorTabImg->getWidth());
		break;
	case 1:
		_swordTab = RectMakeCenter(WINSIZEX / 2 - 30, WINSIZEY / 2 - 300, _swordTabImg->getWidth(), _swordTabImg->getHeight());
		break;
	case 2:
		_bowTab = RectMakeCenter(WINSIZEX / 2 + 40, WINSIZEY / 2 - 300, _bowTabImg->getWidth(), _bowTabImg->getHeight());
		break;
	}
}
