#include "stdafx.h"
#include "NPCpotionShop.h"

NPCpotionShop::NPCpotionShop()
{
}

NPCpotionShop::~NPCpotionShop()
{
}


HRESULT NPCpotionShop::init(POINT npcXY)
{
	_npcImg = IMAGEMANAGER->findImage("위치");
	_npcAni = ANIMATIONMANAGER->findAnimation("위치기본모션");

	_recipeImg = IMAGEMANAGER->findImage("업그레이드레시피_포션");
	_vShowItem.push_back(ITEMMANAGER->addItem("작은 포션"));
	_vShowItem.push_back(ITEMMANAGER->addItem("중간 포션"));
	_vShowItem.push_back(ITEMMANAGER->addItem("큰 포션"));
	_npcRc = RectMakeCenter(npcXY.x, npcXY.y, _npcImg->getFrameWidth(), _npcImg->getFrameHeight());

	NPCshopBase::init();

	return S_OK;
}

void NPCpotionShop::release()
{
}

void NPCpotionShop::update()
{
	NPCshopBase::update();
}

void NPCpotionShop::render()
{
	NPCshopBase::render();

	if (_showWindow)
	{
		//템프=현재 커서가 가리키고 있는 아이템.
		_temp.getItemInfo().image->render(getMemDC(), WINSIZEX - 120, 80);

		//오른쪽 부분에 현재 커서가 가리키고 있는 업그레이드 아이템의 스탯,재료 등등을 렌더
		TextOut(getMemDC(), WINSIZEX / 2 - 180, 110, "포션", strlen("포션"));
		wsprintf(str, "%d", _temp.getItemInfo().orignalPrice / 2);
		TextOut(getMemDC(), WINSIZEX - 130, 370, str, strlen(str));
		for (int i = 0; i < _vShowRecipe.size(); i++)
		{
			wsprintf(str, "필요 : %d", _vShowRecipe[i].getItemInfo().cnt);
			TextOut(getMemDC(), WINSIZEX - 250, WINSIZEY / 2 + 70 + (i * 60), str, strlen(str));
		}
		for (int i = 0; i < _vShowItem.size(); i++)
		{
			_vShowItem[i].render();
			if (i + 1 == _cursorNum)
			{
				wsprintf(str, "체력 회복량: %d", _vShowItem[i].getItemInfo().heal);
				TextOut(getMemDC(), WINSIZEX - 250, WINSIZEY / 2 - 100, str, strlen(str));
			}
		}
	}
}

void NPCpotionShop::tabControl()
{
	for (int i = 0; i < _vShowItem.size(); i++) //이부분 야매임.. 미완성
	{
		_vShowItem[i].setRect(_itemSlot[i + 1]);
	}
}

void NPCpotionShop::cursorControl()
{
	if (_showWindow)
	{
		if (KEYMANAGER->isOnceKeyDown('A'))
		{
			//커서가 옆으로 못나가게
			_cursorNum--;
			if (_cursorNum < 0) _cursorNum = 0;
			if (_currentTab == 0 && _cursorNum <= 1)_cursorNum = 1;

			_cursorSlot = RectMake(_itemSlot[_cursorNum].left, _itemSlot[_cursorNum].top, 40, 40);
			_cursor->getAni()->start();
		}
		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			//커서가 옆으로 못나가게
			int temp;
			temp = _cursorNum;
			_cursorNum++;
			if (_cursorNum >= SLOTNUM) _cursorNum = temp;

			_cursorSlot = RectMake(_itemSlot[_cursorNum].left, _itemSlot[_cursorNum].top, 40, 40);
			_cursor->getAni()->start();
		}
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			//커서가 위로못나가게
			int temp;
			temp = _cursorNum;
			_cursorNum -= 4;
			if (_cursorNum <= 0)_cursorNum = temp;

			_cursorSlot = RectMake(_itemSlot[_cursorNum].left, _itemSlot[_cursorNum].top, 40, 40);
			_cursor->getAni()->start();
		}
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			//커서가 아래로 못나가게
			int temp;
			temp = _cursorNum;
			_cursorNum += 4;
			if (_cursorNum >= SLOTNUM)_cursorNum = temp;

			_cursorSlot = RectMake(_itemSlot[_cursorNum].left, _itemSlot[_cursorNum].top, 40, 40);
			_cursor->getAni()->start();
		}
		_cursor->setRc(_cursorSlot);
	}
}
