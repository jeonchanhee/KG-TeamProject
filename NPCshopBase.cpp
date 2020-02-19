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
	//_showImg = IMAGEMANAGER->findImage("아이템보여주는창");


	//업글템 보여주는 슬롯 초기화
	//_vItemSlot 0번칸만 위치가 달라서 따로 초기화

	for (int i = 0; i < 2; i++)
	{
		for (int k = 0; k < 4; k++)
		{

			_itemInfo.img = IMAGEMANAGER->findImage("요소");

			_itemInfo.x = WINSIZEX / 2 - 130 + (k * 70);
			_itemInfo.y = WINSIZEY / 2 - 180 + (i * 50);
			_itemInfo.rc = RectMakeCenter(_itemInfo.x, _itemInfo.y, _itemInfo.img->getWidth(), _itemInfo.img->getHeight());

			_itemInfo.item = ITEMMANAGER->addItem("비어있음");
			_vItemSlot.push_back(_itemInfo);
		}
	}

	//레시피 슬롯 초기화
	for (int i = 0; i < 3; i++)
	{
		_itemInfo.img = IMAGEMANAGER->findImage("요소");
		_itemInfo.x = WINSIZEX / 2 + (i * 30);
		_itemInfo.y = WINSIZEY / 2 + (i * 30);
		_itemInfo.rc = RectMakeCenter(_itemInfo.x, _itemInfo.y, _itemInfo.img->getWidth(), _itemInfo.img->getHeight());
		_itemInfo.item = ITEMMANAGER->addItem("비어있음");
		_vRecipeSlot.push_back(_itemInfo);

	}
	//업그레이드 템 보여주는 슬롯의 렉트초기화
	_itemSetSlot = 0;

	//커서초기화
	_cursorNum = 1;
	_cursorSlot = _vItemSlot[_cursorNum].rc;
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

	if (!_showWindow)
	{
		if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &_npcRc) && KEYMANAGER->isOnceKeyDown('J'))
		{
			_showWindow = true;

			//창이 껏다켜지면 커서위치 초기화
			_cursorNum = 0;
			_cursorSlot = _vItemSlot[_cursorNum].rc;
			PLAYER->setstop(true);
		}
	}
	else
	{
		if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &_npcRc) && KEYMANAGER->isOnceKeyDown('6'))
		{
			_showWindow = false;
			PLAYER->setstop(false);

		}
		cursorControl();
		tabControl();
		setRecipeItem();
	}
}

void NPCshopBase::render()
{
	//_npcImg->aniRender(getMemDC(), _npcRc.left, _npcRc.top, _npcAni);
	if (KEYMANAGER->isToggleKey(VK_TAB))Rectangle(getMemDC(), _npcRc.left, _npcRc.top, _npcRc.right, _npcRc.bottom);
	if (!_showWindow)
	{
		if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &_npcRc))
		{
			IMAGEMANAGER->render("열기", getMemDC(), _npcRc.right, _npcRc.top - 20);
		}
	}
	else
	{
		//기본적인 렌더

		//_showImg->render(getMemDC(), WINSIZEX / 2 - 250, WINSIZEY / 2 - 300);
		//_recipeImg->render(getMemDC(), WINSIZEX - 350, 60);
		IMAGEMANAGER->render("타이틀", getMemDC(), WINSIZEX / 2 - 200, 0);
		IMAGEMANAGER->render("이름칸", getMemDC(), WINSIZEX - 300, 20);
		IMAGEMANAGER->render("아이템보여주는창", getMemDC(), WINSIZEX / 2 - 250, WINSIZEY / 2 - 300);

		for (int i = 0; i < 8; i++)
		{
			_vItemSlot[i].img->render(getMemDC(), _vItemSlot[i].rc.left, _vItemSlot[i].rc.top);
		}
		for (int i = 0; i < 3; i++)
		{
			//레시피 슬롯의 이미지와 레시피 템들의 이미지
			_vRecipeSlot[i].img->render(getMemDC(), WINSIZEX / 2 + 200, WINSIZEY / 2 + 50 + (i * 70));
			if (!_vRecipeSlot.empty())
			{
				_vRecipeSlot[i].item.getItemInfo().image->render(getMemDC(), WINSIZEX / 2 + 200, WINSIZEY / 2 + 50 + (i * 70));
			}
		}
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
	//레시피에 혹시 저번 기록이 남아 있을 지 모르니 한번 지워줌
	_temp = ITEMMANAGER->addItem("비어있음");
	for (int i = 0; i < 3; i++)
	{
		_vRecipeSlot[i].item = ITEMMANAGER->addItem("비어있음");
	}

	for (int i = 0; i < _vItemSlot.size(); i++)
	{
		//커서가 업그레이드 아이템을 지정하면(만나면) 재료아이템이 결정된다
		if (_cursorNum == i)
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
		}
	}
}

void NPCshopBase::makeRecipe(string makeItemName, string RecipeItemName1, string RecipeItemName2, string RecipeItemName3, int forNum, int itemCnt1, int itemCnt2, int itemCnt3)
{
	if (_vItemSlot[forNum].item.getItemInfo().itemName == makeItemName)
	{
		_temp = _vItemSlot[forNum].item;         //템프 = 커서가 가리키고 있는 아이템

		_vRecipeSlot[0].item = ITEMMANAGER->addItem(RecipeItemName1);
		_vRecipeSlot[0].item.setItemCnt_equal(itemCnt1);

		_vRecipeSlot[1].item = ITEMMANAGER->addItem(RecipeItemName2);
		_vRecipeSlot[1].item.setItemCnt_equal(itemCnt2);

		_vRecipeSlot[2].item = ITEMMANAGER->addItem(RecipeItemName3);
		_vRecipeSlot[2].item.setItemCnt_equal(itemCnt3);

		//재료템의 갯수(제작에 필요한 갯수)를 _OKcnt에 집어넣어 구매를 처리하도록 밑준비
		for (int i = 0; i < _vRecipeSlot.size(); i++)
		{
			if (_vRecipeSlot[i].item.getItemInfo().type != ITEM_EMPTY)
			{
				_OKcnt[i] = _vRecipeSlot[i].item.getItemInfo().cnt;
			}
			else if (_vRecipeSlot[i].item.getItemInfo().type == ITEM_EMPTY)
			{
				_OKcnt[i] = 0;
			}
		}
	}
}

void NPCshopBase::buy()   //상태가 많이 안좋은 함수
{
	if (KEYMANAGER->isOnceKeyDown('0'))
	{
		//test는 인벤토리 안의 제작에 필요한 재료의 갯수를 전부 더할 변수
		int test[3] = { 0,0,0 };

		//먼저 돈이 있는지 없는지부터 확인.   원가의 절반인 이유는 제작시 필요한 돈이 아이템 원가의 절반이기때문
		if (PLAYER->getMoney() >= _temp.getItemInfo().orignalPrice / 2)
		{
			for (int j = 0; j < _vRecipeSlot.size(); j++)
			{
				for (int k = 0; k < PLAYER->getinventory()->getvInven().size(); k++)
				{
					//인벤토리를 전부 돌며 재료템을 확인한다.
					if (_vRecipeSlot[j].item.getItemInfo().itemName == PLAYER->getinventory()->getvInven()[k]._item.getItemInfo().itemName)
					{
						//_OKcnt = 재료템의 갯수. test = 인벤토리 안의 재료템의 갯수.
						if (_OKcnt[j] >= test[j])
						{
							test[j] += PLAYER->getinventory()->getvInven()[k]._item.getItemInfo().cnt;
						}
						//만약 인벤토리 안의 재료템이 충족된다면 다음 재료템을 찾으러 떠난다.
						if (_OKcnt[j] <= test[j])
						{
							break;
						}
					}
				}
			}   //for끝
		}

		//재료템이 전부 충족되면(모두 OKcnt <= test일 경우) + 그리고 소지금이 충족되면 아이템구매가 실행된다.
		if (_OKcnt[0] <= test[0] && _OKcnt[1] <= test[1] && _OKcnt[2] <= test[2] && PLAYER->getMoney() >= _temp.getItemInfo().orignalPrice / 2)
		{
			buyItem();
		}
		//아니면 구매가 안됨
		else
		{
			TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, "돈이나 템이 부족해용", strlen("돈이나 템이 부족해용"));
		}
	}
}

void NPCshopBase::buyItem()
{
	for (int j = 0; j < _vRecipeSlot.size(); j++)
	{
		for (int k = 0; k < PLAYER->getinventory()->getvInven().size(); k++)
		{
			if (_vRecipeSlot[j].item.getItemInfo().itemName == PLAYER->getinventory()->getvInven()[k]._item.getItemInfo().itemName)
			{
				//_OKcnt = 재료템의 갯수. 갯수가 0이 될때까지 인벤토리 벡터의 앞부터 계속 검사해서 계속 뺴냄
				if (_OKcnt[j] > 0)
				{
					// PLAYER->getinventory()->setItemCnt는 _vInven[forNum].setItemCnt(itemCnt) 와 같다
					_OKcnt[j] -= PLAYER->getinventory()->getvInven()[k]._item.getItemInfo().cnt;
					PLAYER->getinventory()->setItemCnt(k, -PLAYER->getinventory()->getvInven()[k]._item.getItemInfo().cnt);
				}

				//만약 _OKcnt가 0이하가 되면 다음 _OKcnt로 넘어간다.(최대 3개까지)
				//혹시 재료 아이템이 넘치도록 빠질수도 있으니 넘치면 넘친만큼 다시 더해준다
				if (_OKcnt[j] <= 0)
				{
					PLAYER->getinventory()->setItemCnt(k, abs(0 - _OKcnt[j]));
					break;
				}
			}
		}
	}//for끝

	//재료템이 전부 충족되면(_OKcnt가 모두 0이하면) 인벤토리 벡터에 아이템을 추가한다.
	if (_OKcnt[0] <= 0 && _OKcnt[1] <= 0 && _OKcnt[2] <= 0)
	{
		for (int k = 0; k < PLAYER->getinventory()->getvInven().size(); k++)
		{
			if (PLAYER->getinventory()->getvInven()[k]._item.getItemInfo().itemName == "비어있음" || PLAYER->getinventory()->getvInven()[k]._item.getItemInfo().cnt <= 0)
			{
				PLAYER->setMoney(PLAYER->getMoney() - _temp.getItemInfo().orignalPrice / 2);

				PLAYER->getinventory()->addItem(k, _temp);
				break;
			}
		}
	}
}
