#include "stdafx.h"
#include "NPCblacksmith.h"

NPCblacksmith::NPCblacksmith()
{
}

NPCblacksmith::~NPCblacksmith()
{
}

HRESULT NPCblacksmith::init(POINT npcXY)
{
	_npcImg = IMAGEMANAGER->findImage("벌컨");
	_npcAni = ANIMATIONMANAGER->findAnimation("벌컨기본모션");

	_recipeImg = IMAGEMANAGER->findImage("업그레이드레시피");
	_vShowItem.push_back(ITEMMANAGER->addItem("훈련용 단검"));
	_vShowItem.push_back(ITEMMANAGER->addItem("흡혈귀의 단검"));
	_vShowItem.push_back(ITEMMANAGER->addItem("캐터펄트 보우"));
	_vShowItem.push_back(ITEMMANAGER->addItem("플레임 보우"));
	_vShowItem.push_back(ITEMMANAGER->addItem("천 반다나"));
	_vShowItem.push_back(ITEMMANAGER->addItem("천 흉갑"));
	_vShowItem.push_back(ITEMMANAGER->addItem("천 부츠"));
	_vShowItem.push_back(ITEMMANAGER->addItem("훈련용 창"));
	_vShowItem.push_back(ITEMMANAGER->addItem("골렘 드릴 창"));

	_armorTabImg = IMAGEMANAGER->findImage("아머슬롯");
	_armorTab = RectMakeCenter(WINSIZEX / 2 - 160, WINSIZEY / 2 - 280, _armorTabImg->getWidth(), _armorTabImg->getWidth());
	_bowTabImg = IMAGEMANAGER->findImage("보우슬롯");
	_bowTab = RectMakeCenter(WINSIZEX / 2 - 40, WINSIZEY / 2 - 280, _bowTabImg->getWidth(), _bowTabImg->getHeight());
	_swordTabImg = IMAGEMANAGER->findImage("소드슬롯");
	_swordTab = RectMakeCenter(WINSIZEX / 2 - 100, WINSIZEY / 2 - 280, _swordTabImg->getWidth(), _swordTabImg->getHeight());
	_spearTabImg = IMAGEMANAGER->findImage("스피어슬롯");
	_spearTab = RectMakeCenter(WINSIZEX / 2 + 20, WINSIZEY / 2 - 280, _spearTabImg->getWidth(), _spearTabImg->getHeight());

	_currentTab = 0;  //현재탭

	_npcRc = RectMakeCenter(npcXY.x, npcXY.y, _npcImg->getFrameWidth(), _npcImg->getFrameHeight());

	NPCshopBase::init();

	return S_OK;
}

void NPCblacksmith::release()
{
}

void NPCblacksmith::update()
{
	NPCshopBase::update();
}

void NPCblacksmith::render()
{
	_npcImg->aniRender(getMemDC(), _npcRc.left, _npcRc.top, _npcAni);
	if (!_showWindow)
	{
		if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &_npcRc))
		{
			IMAGEMANAGER->render("열기", getMemDC(), _npcRc.right, _npcRc.top - 20);
		}
	}

	if (_showWindow)
	{
		_armorTabImg->render(getMemDC(), _armorTab.left, _armorTab.top);
		_swordTabImg->render(getMemDC(), _swordTab.left, _swordTab.top);
		_bowTabImg->render(getMemDC(), _bowTab.left, _bowTab.top);
		_spearTabImg->render(getMemDC(), _spearTab.left, _spearTab.top);

		baseRender();

		for (int i = 0; i < 3; i++)
		{
			_recipeSlotImg[i]->render(getMemDC(), WINSIZEX / 2 + 200, WINSIZEY / 2 + 50 + (i * 70));
			if (_vShowRecipe.size() - 1 >= i && _vShowRecipe.size() > 0)
			{
				_vShowRecipe[i].getItemInfo().image->render(getMemDC(), WINSIZEX / 2 + 200, WINSIZEY / 2 + 50 + (i * 70));
			}
		}
		switch (_currentTab)
		{
		case 0:
			for (int i = 1; i < 9; i++)
			{
				_itemSlotImg[i]->render(getMemDC(), _itemSlot[i].left, _itemSlot[i].top);
			}
			TextOut(getMemDC(), WINSIZEX / 2 - 180, 110, "방어구", strlen("방어구"));
			for (int i = 0; i < _vShowItem.size(); i++)
			{
				if (_vShowItem[i].getItemInfo().type == ITEM_ARMOR)
				{
					_vShowItem[i].render();
				}
				if (_vShowItem[i].getItemInfo().type == ITEM_HELMET)
				{
					_vShowItem[i].render();
				}
				if (_vShowItem[i].getItemInfo().type == ITEM_BOOTS)
				{
					_vShowItem[i].render();
				}
			}
			break;
		case 1:
			for (int i = 0; i < 9; i++)
			{
				_itemSlotImg[i]->render(getMemDC(), _itemSlot[i].left, _itemSlot[i].top);
			}
			TextOut(getMemDC(), WINSIZEX / 2 - 180, 110, "검과 방패", strlen("검과 방패"));
			for (int i = 0; i < _vShowItem.size(); i++)
			{
				if (_vShowItem[i].getItemInfo().type == ITEM_SWORD)
				{
					_vShowItem[i].render();
				}
			}
			break;
		case 2:
			for (int i = 0; i < 9; i++)
			{
				_itemSlotImg[i]->render(getMemDC(), _itemSlot[i].left, _itemSlot[i].top);
			}
			TextOut(getMemDC(), WINSIZEX / 2 - 180, 110, "활", strlen("활"));
			for (int i = 0; i < _vShowItem.size(); i++)
			{
				if (_vShowItem[i].getItemInfo().type == ITEM_BOW)
				{
					_vShowItem[i].render();
				}
			}
			break;
		case 3:
			for (int i = 0; i < 9; i++)
			{
				_itemSlotImg[i]->render(getMemDC(), _itemSlot[i].left, _itemSlot[i].top);
			}
			TextOut(getMemDC(), WINSIZEX / 2 - 180, 110, "창", strlen("창"));
			for (int i = 0; i < _vShowItem.size(); i++)
			{
				if (_vShowItem[i].getItemInfo().type == ITEM_SPEAR)
				{
					_vShowItem[i].render();
				}
			}
			break;
		}



		//템프=현재 커서가 가리키고 있는 아이템.
		_temp.getItemInfo().image->render(getMemDC(), WINSIZEX - 120, 80);

		//오른쪽 부분에 현재 커서가 가리키고 있는 업그레이드 아이템의 스탯,재료 등등을 렌더
		wsprintf(str, "%d", _temp.getItemInfo().hp);
		TextOut(getMemDC(), WINSIZEX - 250, 150, str, strlen(str));
		wsprintf(str, "%d", _temp.getItemInfo().atk);
		TextOut(getMemDC(), WINSIZEX - 250, 190, str, strlen(str));
		wsprintf(str, "%d", _temp.getItemInfo().def);
		TextOut(getMemDC(), WINSIZEX - 250, 230, str, strlen(str));
		wsprintf(str, "%d", _temp.getItemInfo().speed);
		TextOut(getMemDC(), WINSIZEX - 250, 270, str, strlen(str));
		wsprintf(str, "%d", _temp.getItemInfo().orignalPrice / 2);
		TextOut(getMemDC(), WINSIZEX - 130, 370, str, strlen(str));
		for (int i = 0; i < _vShowRecipe.size(); i++)
		{
			wsprintf(str, "필요 : %d", _vShowRecipe[i].getItemInfo().cnt);
			TextOut(getMemDC(), WINSIZEX - 250, WINSIZEY / 2 + 70 + (i * 60), str, strlen(str));
		}
	}
}

void NPCblacksmith::tabControl()
{
	if (_showWindow)
	{
		if (KEYMANAGER->isOnceKeyDown('X')) //탭을 옮기면 커서 위치 초기화
		{
			_currentTab--;

			if (_currentTab <= 0)
			{
				_currentTab = 0;
				_cursorNum = 1;
				_cursorSlot = _itemSlot[_cursorNum];
				//방어구 탭은 커서가 0번 칸부터가 아닌 1번칸부터 시작함..
			}
		}
		if (KEYMANAGER->isOnceKeyDown('V'))//탭을 옮기면 커서 위치 초기화
		{
			_currentTab++;
			if (_currentTab >= 1)
			{
				_cursorNum = 0;
				_cursorSlot = _itemSlot[_cursorNum];
			}
			if (_currentTab >= 3)_currentTab = 3;
		}
	}
	_armorTab = RectMakeCenter(WINSIZEX / 2 - 160, WINSIZEY / 2 - 280, _armorTabImg->getWidth(), _armorTabImg->getWidth());
	_swordTab = RectMakeCenter(WINSIZEX / 2 - 100, WINSIZEY / 2 - 280, _swordTabImg->getWidth(), _swordTabImg->getHeight());
	_bowTab = RectMakeCenter(WINSIZEX / 2 - 40, WINSIZEY / 2 - 280, _bowTabImg->getWidth(), _bowTabImg->getHeight());
	_spearTab = RectMakeCenter(WINSIZEX / 2 + 20, WINSIZEY / 2 - 280, _spearTabImg->getWidth(), _spearTabImg->getHeight());

	switch (_currentTab)  //이부분 야매임... 미완성
	{
	case 0:
		_armorTab = RectMakeCenter(WINSIZEX / 2 - 160, WINSIZEY / 2 - 300, _armorTabImg->getWidth(), _armorTabImg->getWidth());
		_itemSetSlot = 1;
		for (int i = 0; i < _vShowItem.size(); i++)
		{
			if (_vShowItem[i].getItemInfo().type == ITEM_ARMOR)
			{
				_vShowItem[i].setRect(_itemSlot[1]);
			}
			if (_vShowItem[i].getItemInfo().type == ITEM_HELMET)
			{
				_vShowItem[i].setRect(_itemSlot[3]);
			}
			if (_vShowItem[i].getItemInfo().type == ITEM_BOOTS)
			{
				_vShowItem[i].setRect(_itemSlot[5]);
			}
			else if (_vShowItem[i].getItemInfo().type != ITEM_BOOTS && _vShowItem[i].getItemInfo().type != ITEM_HELMET && _vShowItem[i].getItemInfo().type != ITEM_ARMOR)
				_vShowItem[i].setRect(WINSIZEX, WINSIZEY * 2);
		}
		break;
	case 1:
		_swordTab = RectMakeCenter(WINSIZEX / 2 - 100, WINSIZEY / 2 - 300, _swordTabImg->getWidth(), _swordTabImg->getHeight());
		_itemSetSlot = 0;
		for (int i = 0; i < _vShowItem.size(); i++)
		{
			if (_vShowItem[i].getItemInfo().type == ITEM_SWORD)
			{
				_vShowItem[i].setRect(_itemSlot[_itemSetSlot]);
				_itemSetSlot++;
			}
			else _vShowItem[i].setRect(WINSIZEX, WINSIZEY * 2);
		}
		break;
	case 2:
		_bowTab = RectMakeCenter(WINSIZEX / 2 - 40, WINSIZEY / 2 - 300, _bowTabImg->getWidth(), _bowTabImg->getHeight());
		_itemSetSlot = 0;
		for (int i = 0; i < _vShowItem.size(); i++)
		{
			if (_vShowItem[i].getItemInfo().type == ITEM_BOW)
			{
				_vShowItem[i].setRect(_itemSlot[_itemSetSlot]);
				_itemSetSlot++;
			}
			else _vShowItem[i].setRect(WINSIZEX, WINSIZEY * 2);
		}
		break;
	case 3:
		_spearTab = RectMakeCenter(WINSIZEX / 2 + 20, WINSIZEY / 2 - 300, _spearTabImg->getWidth(), _spearTabImg->getHeight());
		_itemSetSlot = 0;
		for (int i = 0; i < _vShowItem.size(); i++)
		{
			if (_vShowItem[i].getItemInfo().type == ITEM_SPEAR)
			{
				_vShowItem[i].setRect(_itemSlot[_itemSetSlot]);
				_itemSetSlot++;
			}
			else _vShowItem[i].setRect(WINSIZEX, WINSIZEY * 2);
		}
		break;
	}
}

void NPCblacksmith::cursorControl()
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
