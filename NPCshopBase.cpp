#include "stdafx.h"
#include "NPCshopBase.h"

NPCshopBase::NPCshopBase()
{
}

NPCshopBase::~NPCshopBase()
{
}

HRESULT NPCshopBase::init()
{
	_titleImg = IMAGEMANAGER->findImage("타이틀");
	_showImg = IMAGEMANAGER->findImage("아이템보여주는창");
	for (int i = 0; i < 9; i++)
	{
		_itemSlotImg[i] = IMAGEMANAGER->findImage("슬롯이미지");
		if(i<3) _recipeSlotImg[i] = IMAGEMANAGER->findImage("슬롯이미지");
	}

	//업그레이드 템 보여주는 슬롯의 렉트초기화
	_itemSetSlot = 0;
	_itemSlot[0] = RectMakeCenter(WINSIZEX / 2 - 160, WINSIZEY / 2 - 170, _itemSlotImg[0]->getWidth(), _itemSlotImg[0]->getHeight());
	for (int i = 1; i < 9; i++)
	{
		if (i < 5)
		{
			_itemSlot[i] = RectMakeCenter(_itemSlot[0].right - 20 + (i * 60), _itemSlot[0].top - 10, _itemSlotImg[i]->getWidth(), _itemSlotImg[i]->getHeight());
		}
		if (i >= 5)
		{
			_itemSlot[i] = RectMakeCenter(_itemSlot[0].right - 20 + ((i % 5 + 1) * 60), _itemSlot[0].bottom + 10, _itemSlotImg[i]->getWidth(), _itemSlotImg[i]->getHeight());
		}
	}

	//커서초기화
	_cursorNum = 1;
	_cursorSlot = _itemSlot[_cursorNum];
	_cursor = new cursor;
	_cursor->init();
	_grab = new image;
	_grab = IMAGEMANAGER->addImage("커서그랩", "images/shop/grab.bmp", 50, 52, true, RGB(255, 0, 255));

	return S_OK;
}

void NPCshopBase::release()
{
	SAFE_DELETE(_cursor);
}

void NPCshopBase::update()
{
	_index++;
	if (_index % 200 == 0) _npcAni->start();

	playerCollision();
	cursorControl();
	setRecipeItem();
	tabControl();
}

void NPCshopBase::render()
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
		baseRender();
	}
}

void NPCshopBase::tabControl()
{
}

void NPCshopBase::cursorControl()
{
}

void NPCshopBase::setRecipeItem()
{
	_vShowRecipe.clear();//혹시 저번 기록이 남아 있을 지 모르니 한번 지워줌
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
			makeRecipe("천 부츠", "숫돌", "천", "비어있음", i, 2, 2, 0);
			makeRecipe("훈련용 창", "덩쿨", "비어있음", "비어있음", i, 7, 0, 0);
			makeRecipe("골렘 드릴 창", "덩쿨", "강화수정", "비어있음", i, 7, 5, 0);
			makeRecipe("작은 포션", "나뭇가지", "비어있음", "비어있음", i, 7, 0, 0);
			makeRecipe("중간 포션", "이빨석", "비어있음", "비어있음", i, 8, 0, 0);
			makeRecipe("큰 포션", "골렘코어", "비어있음", "비어있음", i, 9, 0, 0);
			makeRecipe("비어있음", "비어있음", "비어있음", "비어있음", i, 0, 0, 0);

		}
	}
}

void NPCshopBase::makeRecipe(string makeItemName, string RecipeItemName1, string RecipeItemName2, string RecipeItemName3, int forNum, int itemCnt1, int itemCnt2, int itemCnt3)
{
	if (_vShowItem[forNum].getItemInfo().itemName == makeItemName)
	{
		_temp = _vShowItem[forNum];			//템프 = 커서가 가리키고 있는 아이템
		_vShowRecipe.push_back(ITEMMANAGER->addItem(RecipeItemName1)); //벡터에 재료를 넣음
		_vShowRecipe.push_back(ITEMMANAGER->addItem(RecipeItemName2));
		_vShowRecipe.push_back(ITEMMANAGER->addItem(RecipeItemName3));
		_vShowRecipe[0].setItemCnt_equal(itemCnt1);					   //재료들의 갯수를 정해줌
		_vShowRecipe[1].setItemCnt_equal(itemCnt2);
		_vShowRecipe[2].setItemCnt_equal(itemCnt3);

		//재료의 갯수(제작에 필요한 갯수)를 _OKcnt에 집어넣어 구매를 처리하도록 밑준비
		for (int i = 0; i < _vShowRecipe.size(); i++)
		{
			if (_vShowRecipe[i].getItemInfo().type != ITEM_EMPTY)
			{
				_OKcnt[i] = _vShowRecipe[i].getItemInfo().cnt;
			}
			else if (_vShowRecipe[i].getItemInfo().type == ITEM_EMPTY)
			{
				_OKcnt[i] = 0;
			}
		}
	}
}

void NPCshopBase::buy(vector<item> &storage)
{
	if (_showWindow)
	{
		if (KEYMANAGER->isOnceKeyDown('0'))
		{
			int test[3] = { 0,0,0 };
			if (PLAYER->getMoney() >= _temp.getItemInfo().orignalPrice / 2)
			{
				for (int j = 0; j < _vShowRecipe.size(); j++)
				{
					for (int k = 0; k < storage.size(); k++)
					{
						if (_vShowRecipe[j].getItemInfo().itemName == storage[k].getItemInfo().itemName)
						{
							//_OKcnt = 재료템의 갯수. 일단 창고 안의 아이템이 만족하는지 확인한다.
							if (_OKcnt[j] >= test[j])
							{
								test[j] += storage[k].getItemInfo().cnt;
							}
							//만약 _OKcnt가 0이하가 되면 다음 _OKcnt로 넘어간다.
							if (_OKcnt[j] <= test[j])
							{
								break;
							}
						}
					}
				}//for끝
			}

			//재료템이 전부 충족되면(_OKcnt가 모두 0이하면) 아이템구매가 실행된다.
			if (_OKcnt[0] <= test[0] && _OKcnt[1] <= test[1] && _OKcnt[2] <= test[2] && PLAYER->getMoney() >= _temp.getItemInfo().orignalPrice / 2)
			{
				buyItem(storage);
			}
			//아니면 구매가 안됨
			else
			{
				TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, "돈이나 템이 부족해용", strlen("돈이나 템이 부족해용"));
			}
		}
	}
}

void NPCshopBase::buyItem(vector<item>& storage)
{
	for (int j = 0; j < _vShowRecipe.size(); j++)
	{
		for (int k = 0; k < storage.size(); k++)
		{
			if (_vShowRecipe[j].getItemInfo().itemName == storage[k].getItemInfo().itemName)
			{
				//_OKcnt = 재료템의 갯수. 갯수가 0이 될때까지 벡터 앞부터 계속 검사해서 계속 뺴냄
				if (_OKcnt[j] > 0)
				{
					_OKcnt[j] -= storage[k].getItemInfo().cnt;
					storage[k].setItemCnt(-storage[k].getItemInfo().cnt);
				}
				//만약 _OKcnt가 0이하가 되면 다음 _OKcnt로 넘어간다.
				//혹시 재료템이 넘치도록 빠질수도 있으니 넘치면 넘친만큼 다시 더해준다
				if (_OKcnt[j] <= 0)
				{
					storage[k].setItemCnt(abs(0 - _OKcnt[j]));
					break;
				}
			}
		}
	}//for끝

	//재료템이 전부 충족되면(_OKcnt가 모두 0이하면) 벡터에 아이템을 추가한다.
	if (_OKcnt[0] <= 0 && _OKcnt[1] <= 0 && _OKcnt[2] <= 0)
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

void NPCshopBase::baseRender()
{
	//기본적인 렌더
	_showImg->render(getMemDC(), WINSIZEX / 2 - 250, WINSIZEY / 2 - 300);
	_recipeImg->render(getMemDC(), WINSIZEX - 350, 60);

	for (int i = 1; i < 9; i++)
	{
		_itemSlotImg[i]->render(getMemDC(), _itemSlot[i].left, _itemSlot[i].top);
	}
	for (int i = 0; i < 3; i++)
	{
		_recipeSlotImg[i]->render(getMemDC(), WINSIZEX / 2 + 200, WINSIZEY / 2 + 50 + (i * 70));
	}
	for (int i = 0; i < 3; i++)
	{
		_recipeSlotImg[i]->render(getMemDC(), WINSIZEX / 2 + 200, WINSIZEY / 2 + 50 + (i * 70));
		if (_vShowRecipe.size() - 1 >= i && _vShowRecipe.size() > 0)
		{
			_vShowRecipe[i].getItemInfo().image->render(getMemDC(), WINSIZEX / 2 + 200, WINSIZEY / 2 + 50 + (i * 70));
		}
	}
	_cursor->render();
}

void NPCshopBase::playerCollision()
{
	if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &_npcRc))
	{
		if (!_showWindow)
		{
			if (KEYMANAGER->isOnceKeyDown('J'))
			{
				_showWindow = true;

				//창고 창이 껏다켜지면 커서위치 초기화
				_cursorNum = 1;
				_cursorSlot = _itemSlot[_cursorNum];
			}
		}
		if (_showWindow)
		{
			if (KEYMANAGER->isOnceKeyDown('I'))_showWindow = false;
		}
	}
}
