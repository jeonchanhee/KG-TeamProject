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

	//_recipeImg = IMAGEMANAGER->findImage("업그레이드레시피");

	NPCshopBase::init();

	_armorTabImg = IMAGEMANAGER->findImage("아머슬롯");
	_armorTab = RectMakeCenter(WINSIZEX / 2 - 160, WINSIZEY / 2 - 280, _armorTabImg->getWidth(), _armorTabImg->getWidth());
	_bowTabImg = IMAGEMANAGER->findImage("보우슬롯");
	_bowTab = RectMakeCenter(WINSIZEX / 2 - 40, WINSIZEY / 2 - 280, _bowTabImg->getWidth(), _bowTabImg->getHeight());
	_swordTabImg = IMAGEMANAGER->findImage("소드슬롯");
	_swordTab = RectMakeCenter(WINSIZEX / 2 - 100, WINSIZEY / 2 - 280, _swordTabImg->getWidth(), _swordTabImg->getHeight());
	_spearTabImg = IMAGEMANAGER->findImage("스피어슬롯");
	_spearTab = RectMakeCenter(WINSIZEX / 2 + 20, WINSIZEY / 2 - 280, _spearTabImg->getWidth(), _spearTabImg->getHeight());

	_currentTab = 0;  //현재탭

	_npcRc = RectMakeCenter(npcXY.x, npcXY.y, _npcImg->getFrameWidth(), _npcImg->getFrameHeight()+70);


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
	if (_showWindow) //렌더순서때매 얘내먼저
	{
		_armorTabImg->render(getMemDC(), _armorTab.left, _armorTab.top);
		_swordTabImg->render(getMemDC(), _swordTab.left, _swordTab.top);
		_bowTabImg->render(getMemDC(), _bowTab.left, _bowTab.top);
		_spearTabImg->render(getMemDC(), _spearTab.left, _spearTab.top);
		IMAGEMANAGER->render("업그레이드레시피", getMemDC(), WINSIZEX - 350, 60);
	}
	NPCshopBase::render();

	if (_showWindow)
	{
		TextOut(getMemDC(), WINSIZEX / 2 - 70, 20, "벌컨의 대장간", strlen("벌컨의 대장간"));
		IMAGEMANAGER->render("벌컨큰이미지", getMemDC(), 10, 100);
		for (int i = 0; i < 8; i++)
		{
			_vItemSlot[i].img->render(getMemDC(), _vItemSlot[i].rc.left, _vItemSlot[i].rc.top);
			if (_vItemSlot[i].item.getItemInfo().type != ITEM_EMPTY)
			{
				_vItemSlot[i].item.getItemInfo().image->render(getMemDC(), _vItemSlot[i].rc.left, _vItemSlot[i].rc.top);
			}
		}
		switch (_currentTab)
		{
		case 0:
			TextOut(getMemDC(), WINSIZEX / 2 - 180, 110, "방어구", strlen("방어구"));
			break;
		case 1:
			TextOut(getMemDC(), WINSIZEX / 2 - 180, 110, "검과 방패", strlen("검과 방패"));
			break;
		case 2:
			TextOut(getMemDC(), WINSIZEX / 2 - 180, 110, "활", strlen("활"));
			break;
		case 3:
			TextOut(getMemDC(), WINSIZEX / 2 - 180, 110, "창", strlen("창"));
			break;
		}

		if (_temp.getItemInfo().type != ITEM_EMPTY) //템이 있으면 렌더
		{
			//템프=현재 커서가 가리키고 있는 아이템.
			_temp.getItemInfo().image->render(getMemDC(), WINSIZEX - 120, 80);

			//오른쪽 부분에 현재 커서가 가리키고 있는 업그레이드 아이템의 스탯,재료 등등을 렌더
			TextOut(getMemDC(), WINSIZEX - 220, 30, _temp.getItemInfo().itemName.c_str(), _temp.getItemInfo().itemName.length());
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
			for (int i = 0; i < _vRecipeSlot.size(); i++)
			{
				wsprintf(str, "필요 : %d", _vRecipeSlot[i].item.getItemInfo().cnt);
				TextOut(getMemDC(), WINSIZEX - 250, WINSIZEY / 2 + 70 + (i * 60), str, strlen(str));
			}
		}
		_cursor->render();
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
				_cursorNum = 0;
				_cursorSlot = _vItemSlot[_cursorNum].rc;
				//방어구 탭은 커서가 0번 칸부터가 아닌 1번칸부터 시작함..
			}
		}
		if (KEYMANAGER->isOnceKeyDown('V'))//탭을 옮기면 커서 위치 초기화
		{
			_currentTab++;
			if (_currentTab >= 1)
			{
				_cursorNum = 0;
				_cursorSlot = _vItemSlot[_cursorNum].rc;
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

		_vItemSlot[0].item = ITEMMANAGER->addItem("천 흉갑");
		_vItemSlot[1].item = ITEMMANAGER->addItem("천 부츠");
		_vItemSlot[2].item = ITEMMANAGER->addItem("천 반다나");
		for (int i = 3; i < _vItemSlot.size(); i++)
		{
			_vItemSlot[i].item = ITEMMANAGER->addItem("비어있음");
		}
		break;
	case 1:
		_swordTab = RectMakeCenter(WINSIZEX / 2 - 100, WINSIZEY / 2 - 300, _swordTabImg->getWidth(), _swordTabImg->getHeight());
		_vItemSlot[0].item = ITEMMANAGER->addItem("훈련용 단검");
		_vItemSlot[1].item = ITEMMANAGER->addItem("흡혈귀의 단검");
		for (int i = 2; i < _vItemSlot.size(); i++)
		{
			_vItemSlot[i].item = ITEMMANAGER->addItem("비어있음");
		}

		break;
	case 2:
		_bowTab = RectMakeCenter(WINSIZEX / 2 - 40, WINSIZEY / 2 - 300, _bowTabImg->getWidth(), _bowTabImg->getHeight());
		_vItemSlot[0].item = ITEMMANAGER->addItem("캐터펄트 보우");
		_vItemSlot[1].item = ITEMMANAGER->addItem("플레임 보우");
		for (int i = 2; i < _vItemSlot.size(); i++)
		{
			_vItemSlot[i].item = ITEMMANAGER->addItem("비어있음");
		}
		break;
	case 3:
		_spearTab = RectMakeCenter(WINSIZEX / 2 + 20, WINSIZEY / 2 - 300, _spearTabImg->getWidth(), _spearTabImg->getHeight());
		_vItemSlot[0].item = ITEMMANAGER->addItem("훈련용 창");
		_vItemSlot[1].item = ITEMMANAGER->addItem("골렘 드릴 창");
		for (int i = 2; i < _vItemSlot.size(); i++)
		{
			_vItemSlot[i].item = ITEMMANAGER->addItem("비어있음");
		}
		break;
	}
}

void NPCblacksmith::cursorControl()
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