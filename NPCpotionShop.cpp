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

	//_recipeImg = IMAGEMANAGER->findImage("업그레이드레시피_포션");

	NPCshopBase::init();
	_vItemSlot[0].item = ITEMMANAGER->addItem("작은 포션");
	_vItemSlot[1].item = ITEMMANAGER->addItem("중간 포션");
	_vItemSlot[2].item = ITEMMANAGER->addItem("큰 포션");
	for (int i = 3; i < _vItemSlot.size(); i++)
	{
		_vItemSlot[i].item = ITEMMANAGER->addItem("비어있음");
	}

	_npcRc = RectMakeCenter(npcXY.x, npcXY.y, _npcImg->getFrameWidth(), _npcImg->getFrameHeight()+70);


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
	if (_showWindow) //렌더순서때매 얘를 위에 놓음
	{
		IMAGEMANAGER->render("업그레이드레시피_포션", getMemDC(), WINSIZEX - 350, 60);
	}

	NPCshopBase::render();

	if (_showWindow)
	{
		TextOut(getMemDC(), WINSIZEX / 2 - 70, 20, "나무모자", strlen("나무모자"));
		TextOut(getMemDC(), WINSIZEX / 2 - 180, 110, "포션", strlen("포션"));
		IMAGEMANAGER->render("위치큰이미지", getMemDC(), 10, 100);
		for (int i = 0; i < _vItemSlot.size(); i++)
		{
			_vItemSlot[i].item.getItemInfo().image->render(getMemDC(), _vItemSlot[i].rc.left, _vItemSlot[i].rc.top);
		}
		if (_temp.getItemInfo().type != ITEM_EMPTY)  // <- 이부분의 _temp값이 제대로 안들어가는것같음
		{
			//템프=현재 커서가 가리키고 있는 아이템.
			_temp.getItemInfo().image->render(getMemDC(), WINSIZEX - 120, 80);

			//오른쪽 부분에 현재 커서가 가리키고 있는 업그레이드 아이템의 스탯,재료 등등을 렌더
			TextOut(getMemDC(), WINSIZEX - 220, 30, _temp.getItemInfo().itemName.c_str(), _temp.getItemInfo().itemName.length());
			wsprintf(str, "%d", _temp.getItemInfo().orignalPrice / 2);
			TextOut(getMemDC(), WINSIZEX - 130, 370, str, strlen(str));
			for (int i = 0; i < _vRecipeSlot.size(); i++)
			{
				wsprintf(str, "필요 : %d", _vRecipeSlot[i].item.getItemInfo().cnt);
				TextOut(getMemDC(), WINSIZEX - 250, WINSIZEY / 2 + 70 + (i * 60), str, strlen(str));
			}
			for (int i = 0; i < _vItemSlot.size(); i++)
			{
				if (i == _cursorNum)
				{
					wsprintf(str, "체력 회복량: %d", _vItemSlot[i].item.getItemInfo().heal);
					TextOut(getMemDC(), WINSIZEX - 300,150, str, strlen(str));
				}
			}
		}
		_cursor->render();
	}
}

void NPCpotionShop::tabControl()
{
	//_vItemSlot[0].item = ITEMMANAGER->addItem("작은 포션");
	//_vItemSlot[1].item = ITEMMANAGER->addItem("중간 포션");
	//_vItemSlot[2].item = ITEMMANAGER->addItem("큰 포션");
	//for (int i = 3; i < _vItemSlot.size(); i++)
	//{
	//	_vItemSlot[i].item = ITEMMANAGER->addItem("비어있음");
	//}
}

void NPCpotionShop::cursorControl()
{

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		//커서가 옆으로 못나가게
		_cursorNum--;
		if (_cursorNum < 0) _cursorNum = 0;
		if (_currentTab == 0 && _cursorNum <= 0)_cursorNum = 0;

		_cursorSlot = _vItemSlot[_cursorNum].rc;
		_cursor->getAni()->start();
	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		//커서가 옆으로 못나가게
		int temp;
		temp = _cursorNum;
		_cursorNum++;
		if (_cursorNum >= SLOTNUM) _cursorNum = temp;

		_cursorSlot = _vItemSlot[_cursorNum].rc;
		_cursor->getAni()->start();
	}
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		//커서가 위로못나가게
		int temp;
		temp = _cursorNum;
		_cursorNum -= 4;
		if (_cursorNum < 0)_cursorNum = temp;

		_cursorSlot = _vItemSlot[_cursorNum].rc;
		_cursor->getAni()->start();
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		//커서가 아래로 못나가게
		int temp;
		temp = _cursorNum;
		_cursorNum += 4;
		if (_cursorNum >= SLOTNUM)_cursorNum = temp;

		_cursorSlot = _vItemSlot[_cursorNum].rc;
		_cursor->getAni()->start();
	}
	_cursor->setRc(_cursorSlot);
}
