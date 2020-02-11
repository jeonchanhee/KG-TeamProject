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
	_armorTab = RectMakeCenter(WINSIZEX / 2 - 160, WINSIZEY / 2 - 280, _armorTabImg->getWidth(), _armorTabImg->getWidth());
	_swordTab = RectMakeCenter(WINSIZEX / 2 - 100, WINSIZEY / 2 - 280, _swordTabImg->getWidth(), _swordTabImg->getHeight());
	_bowTab = RectMakeCenter(WINSIZEX / 2 - 40, WINSIZEY / 2 - 280, _bowTabImg->getWidth(), _bowTabImg->getHeight());

	_itemSlot[0]= RectMakeCenter(WINSIZEX / 2 - 160, WINSIZEY / 2 - 170, _itemSlotImg[0]->getWidth(), _itemSlotImg[0]->getHeight());

	//업그레이드 템 보여주는 슬롯의 렉트초기화
	for (int i = 1; i < 9; i++)
	{
		if (i < 5)
		{
			_itemSlot[i] = RectMakeCenter(_itemSlot[0].right-20 + (i * 60), _itemSlot[0].top - 10, _itemSlotImg[i]->getWidth(), _itemSlotImg[i]->getWidth());
		}
		if (i >= 5)
		{
			_itemSlot[i] = RectMakeCenter(_itemSlot[0].right-20 + ((i%5+1)* 60), _itemSlot[0].bottom +10, _itemSlotImg[i]->getWidth(), _itemSlotImg[i]->getWidth());
		}
	}

	_npcRc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 - 200, 100, 100);
	_itemSetSlot = 0;
	_currentTab = 0;  //현재탭

	//커서초기화
	_cursorNum = 1;
	_cursorSlot = _itemSlot[_cursorNum];
	_cursor = new cursor;
	_cursor->init();
	_grab = new image;
	_grab = IMAGEMANAGER->addImage("커서그랩", "images/shop/grab.bmp", 50, 52, true, RGB(255, 0, 255));

	//벡터초기화
	_vShowItem.push_back(ITEMMANAGER->addItem("훈련용 단검"));
	_vShowItem.push_back(ITEMMANAGER->addItem("흡혈귀의 단검"));
	_vShowItem.push_back(ITEMMANAGER->addItem("캐터펄트 보우"));
	_vShowItem.push_back(ITEMMANAGER->addItem("플레임 보우"));
	_vShowItem.push_back(ITEMMANAGER->addItem("천 반다나"));
	_vShowItem.push_back(ITEMMANAGER->addItem("천 흉갑"));

	return S_OK;
}

void blacksmith::release()
{
}

void blacksmith::update()
{
	cursorControl();
	tabControl();
	setRecipeItem();
}

void blacksmith::render()
{
	Rectangle(getMemDC(), _npcRc.left, _npcRc.top, _npcRc.right, _npcRc.bottom);

	if (_showWindow)
	{
		//기본적인 렌더
		_armorTabImg->render(getMemDC(), _armorTab.left, _armorTab.top);
		_swordTabImg->render(getMemDC(), _swordTab.left, _swordTab.top);
		_bowTabImg->render(getMemDC(), _bowTab.left, _bowTab.top);
		_showImg->render(getMemDC(), WINSIZEX / 2-250, WINSIZEY / 2-300);
		_recipeImg->render(getMemDC(), WINSIZEX - 350, 60);

		for (int i = 0 ; i < 3; i++)
		{
			_recipeSlotImg[i]->render(getMemDC(), WINSIZEX/2 + 200, WINSIZEY/2+ 50+(i* 70));
			if (_vShowRecipe.size()-1 >= i && _vShowRecipe.size()>0)
			{
				_vShowRecipe[i].getItemInfo().image->render(getMemDC(), WINSIZEX / 2 + 200, WINSIZEY / 2 + 50 + (i * 70));
			}
		}

		//현재 보고있는 탭에 관한 렌더.(0방어구 1검 2활)
		switch (_currentTab)
		{
		case 0:
			for (int i = 1; i < 9; i++)
			{
				_itemSlotImg[i]->render(getMemDC(), _itemSlot[i].left, _itemSlot[i].top);
			}
			TextOut(getMemDC(), WINSIZEX / 2- 180, 110, "방어구", strlen("방어구"));
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
			}
			break;
		case 1:
			for (int i = 0; i < 9; i++)
			{
				_itemSlotImg[i]->render(getMemDC(), _itemSlot[i].left, _itemSlot[i].top);
			}
			TextOut(getMemDC(), WINSIZEX / 2- 180, 110, "검과 방패", strlen("검과 방패"));
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
			TextOut(getMemDC(), WINSIZEX/2-180, 110, "활", strlen("활"));
			for (int i = 0; i < _vShowItem.size(); i++)
			{
				if (_vShowItem[i].getItemInfo().type == ITEM_BOW)
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
		TextOut(getMemDC(), WINSIZEX - 250 ,150, str, strlen(str));
		wsprintf(str, "%d", _temp.getItemInfo().atk);
		TextOut(getMemDC(), WINSIZEX - 250, 190, str, strlen(str));
		wsprintf(str, "%d", _temp.getItemInfo().def);
		TextOut(getMemDC(), WINSIZEX - 250, 230, str, strlen(str));
		wsprintf(str, "%d", _temp.getItemInfo().speed);
		TextOut(getMemDC(), WINSIZEX - 250, 270, str, strlen(str));
		wsprintf(str, "%d", _temp.getItemInfo().orignalPrice/2);
		TextOut(getMemDC(), WINSIZEX - 130, 370, str, strlen(str));
		for (int i = 0; i < _vShowRecipe.size(); i++)
		{
			wsprintf(str, "필요 : %d", _vShowRecipe[i].getItemInfo().cnt);
			TextOut(getMemDC(), WINSIZEX - 250, WINSIZEY/2 +70 + (i*60), str, strlen(str));
		}

		_cursor->render();
	}
}

void blacksmith::cursorControl()
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

void blacksmith::tabControl()
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
		if (KEYMANAGER->isOnceKeyDown('C'))//탭을 옮기면 커서 위치 초기화
		{
			_currentTab++;
			if (_currentTab >= 1) 
			{
				_cursorNum = 0;
				_cursorSlot = _itemSlot[_cursorNum];
			}
			if (_currentTab >= 2)_currentTab = 2;
		}
	}
	_armorTab = RectMakeCenter(WINSIZEX / 2 - 160, WINSIZEY / 2 - 280, _armorTabImg->getWidth(), _armorTabImg->getWidth());
	_swordTab = RectMakeCenter(WINSIZEX / 2 - 100, WINSIZEY / 2 - 280, _swordTabImg->getWidth(), _swordTabImg->getHeight());
	_bowTab = RectMakeCenter(WINSIZEX / 2 -40, WINSIZEY / 2 - 280, _bowTabImg->getWidth(), _bowTabImg->getHeight());

	switch (_currentTab)  //이부분 야매임... 미완성
	{
	case 0:
		_armorTab = RectMakeCenter(WINSIZEX / 2 - 160, WINSIZEY / 2 - 300, _armorTabImg->getWidth(), _armorTabImg->getWidth());
		_itemSetSlot = 1;
		for (int i = 0; i < _vShowItem.size(); i++)
		{
			if (_vShowItem[i].getItemInfo().type == ITEM_ARMOR)
			{
				_vShowItem[i].setRect(_itemSlot[_itemSetSlot]);

				_itemSetSlot += 4;
			}
			if (_vShowItem[i].getItemInfo().type == ITEM_HELMET)
			{
				_vShowItem[i].setRect(_itemSlot[_itemSetSlot]);
				_itemSetSlot += 4;
			}
			if (_vShowItem[i].getItemInfo().type == ITEM_BOOTS)
			{
				_vShowItem[i].setRect(_itemSlot[_itemSetSlot]);
				_itemSetSlot += 4;
			}
			else if(_vShowItem[i].getItemInfo().type != ITEM_BOOTS && _vShowItem[i].getItemInfo().type != ITEM_HELMET && _vShowItem[i].getItemInfo().type != ITEM_ARMOR)
				_vShowItem[i].setRect(_itemSlot[99]);
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
			else _vShowItem[i].setRect(_itemSlot[99]);
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
			else _vShowItem[i].setRect(_itemSlot[99]);
		}
		break;
	}
}

void blacksmith::setRecipeItem()
{
	for (int i = 0; i < _vShowItem.size(); i++)
	{
		//커서가 업그레이드 아이템을 지정하면(만나면) 재료아이템이 결정된다
		if (IntersectRect(&temp, &_cursorSlot, &_vShowItem[i].getRECT()))
		{
			makeRecipe("훈련용 단검", "나뭇가지", "비어있음", "비어있음", i, 3, 0, 0);
			makeRecipe("흡혈귀의 단검", "나뭇가지", "수정화 된 에너지", "비어있음", i, 10, 3, 0);
			makeRecipe("캐터펄트 보우", "골렘코어", "비어있음", "비어있음", i, 5, 0, 0);
			makeRecipe("플레임 보우", "골렘코어", "이빨석", "비어있음", i, 10, 5, 0);
			makeRecipe("천 반다나", "천", "비어있음", "비어있음", i, 10, 0, 0);
			makeRecipe("천 흉갑", "숫돌", "비어있음", "비어있음", i, 7, 0, 0);
		}
	}
}

void blacksmith::makeRecipe(string makeItemName, string RecipeItemName1, string RecipeItemName2, string RecipeItemName3, int forNum, int itemCnt1, int itemCnt2, int itemCnt3)
{
	if (_vShowItem[forNum].getItemInfo().itemName == makeItemName)
	{
		_temp = _vShowItem[forNum];			//템프 = 커서가 가리키고 있는 아이템
		_vShowRecipe.clear();				//혹시 저번 기록이 남아 있을 지 모르니 한번 지워줌
		_vShowRecipe.push_back(ITEMMANAGER->addItem(RecipeItemName1)); //벡터에 재료를 넣음
		_vShowRecipe.push_back(ITEMMANAGER->addItem(RecipeItemName2));
		_vShowRecipe.push_back(ITEMMANAGER->addItem(RecipeItemName3));
		_vShowRecipe[0].setItemCnt_equal(itemCnt1);					   //재료들의 갯수를 정해줌
		_vShowRecipe[1].setItemCnt_equal(itemCnt2);
		_vShowRecipe[2].setItemCnt_equal(itemCnt3);

		//재료의 갯수(제작에 필요한 갯수)를 OKcnt에 집어넣어 구매를 처리하도록 밑준비
		for (int i = 0; i < _vShowRecipe.size(); i++) 
		{
			if (_vShowRecipe[i].getItemInfo().type != ITEM_EMPTY)
			{
				OKcnt[i] = _vShowRecipe[i].getItemInfo().cnt;
			}
			else if (_vShowRecipe[i].getItemInfo().type == ITEM_EMPTY)
			{
				OKcnt[i] = 0;
			}
		}
	}
}

void blacksmith::buy(vector<item> &storage)
{
	if (_showWindow)
	{
		if (KEYMANAGER->isOnceKeyDown('0')  )
		{
			int test[3] = {0,0,0};
			if (PLAYER->getMoney() >= _temp.getItemInfo().orignalPrice / 2)
			{
				for (int j = 0; j < _vShowRecipe.size(); j++)
				{
					for (int k = 0; k < storage.size(); k++)
					{
						if (_vShowRecipe[j].getItemInfo().itemName == storage[k].getItemInfo().itemName)
						{
							//OKcnt = 재료템의 갯수. 일단 창고 안의 아이템이 만족하는지 확인한다.
							if (OKcnt[j] >= test[j])
							{
								test[j] += storage[k].getItemInfo().cnt;
							}
							//만약 OKcnt가 0이하가 되면 다음 OKcnt로 넘어간다.
							if (OKcnt[j] <= test[j])
							{
								break;
							}
						}
					}
				}//for끝
			}

			//재료템이 전부 충족되면(OKcnt가 모두 0이하면) 아이템구매가 실행된다.
			if (OKcnt[0] <= test[0]&& OKcnt[1] <= test[1]&& OKcnt[2] <= test[2] && PLAYER->getMoney() >= _temp.getItemInfo().orignalPrice / 2)
			{
				buyItem(storage);
			}
			//아니면 구매가 안됨
			else
			{
				TextOut(getMemDC(), WINSIZEX/2, WINSIZEY/2, "돈이나 템이 부족해용", strlen("돈이나 템이 부족해용"));
			}
		}
	}
}

void blacksmith::buyItem(vector<item>& storage)
{
	for (int j = 0; j < _vShowRecipe.size(); j++)
	{
		for (int k = 0; k < storage.size(); k++)
		{
			if (_vShowRecipe[j].getItemInfo().itemName == storage[k].getItemInfo().itemName)
			{
				//OKcnt = 재료템의 갯수. 갯수가 0이 될때까지 벡터 앞부터 계속 검사해서 계속 뺴냄
				if (OKcnt[j] > 0)
				{
					OKcnt[j] -= storage[k].getItemInfo().cnt;
					storage[k].setItemCnt(-storage[k].getItemInfo().cnt);
				}
				//만약 OKcnt가 0이하가 되면 다음 OKcnt로 넘어간다.
				//혹시 재료템이 넘치도록 빠질수도 있으니 넘치면 넘친만큼 다시 더해준다
				if (OKcnt[j] <= 0)
				{
					storage[k].setItemCnt(abs(0 - OKcnt[j]));
					break;
				}
			}
		}
	}//for끝

	//재료템이 전부 충족되면(OKcnt가 모두 0이하면) 벡터에 아이템을 추가한다.
	if (OKcnt[0] <= 0 && OKcnt[1] <= 0 && OKcnt[2] <= 0)
	{
		for (int k = 0; k < storage.size(); k++)
		{
			if (storage[k].getItemInfo().itemName == "비어있음" || storage[k].getItemInfo().cnt <= 0)
			{
				PLAYER->setMoney(PLAYER->getMoney() - _temp.getItemInfo().orignalPrice / 2);
				storage.erase(storage.begin() + k);
				storage.insert(storage.begin() + k, _temp);
				break;
			}
		}
	}

}
