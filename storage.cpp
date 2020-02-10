#include "stdafx.h"
#include "storage.h"

storage::storage()
{
}

storage::~storage()
{
}

HRESULT storage::init(string storageName, POINT xy)
{
	//창고 초기화
	_boxImg = IMAGEMANAGER->findImage(storageName);
	_boxRc = RectMakeCenter(xy.x,xy.y , _boxImg->getFrameWidth(), _boxImg->getFrameHeight());

	if(storageName=="창고1")_storageAni = ANIMATIONMANAGER->findAnimation("창고1오픈");
	if(storageName=="창고2")_storageAni = ANIMATIONMANAGER->findAnimation("창고2오픈");

	_mainImage = IMAGEMANAGER->findImage("창고내부");

	_showItem = IMAGEMANAGER->findImage("템보여주기");
	_showItemRc = RectMakeCenter(WINSIZEX - 70, 250, _showItem->getWidth(), _showItem->getHeight());

	//창고인벤토리 슬롯 초기화
	for (int i = 0; i < SLOTNUM; i++)
	{
		int k, j;
		k = i % 7;
		j = i / 7;
		_slot[i] = RectMakeCenter(WINSIZEX / 2 + 20 + (k * 60), WINSIZEY / 2 - 60 + (j * 60), 40, 40);
		_slotImage[i] = IMAGEMANAGER->findImage("슬롯이미지");
	}

	//커서 초기화
	_choiceNum = 0;
	_choiceSlot = _slot[_choiceNum];
	_cursor = new cursor;
	_cursor->init();
	_grab = new image;
	_grab = IMAGEMANAGER->addImage("커서그랩", "images/shop/grab.bmp", 50, 52, true, RGB(255, 0, 255));


	//임시로 넣어둠
	_vStorage.push_back(ITEMMANAGER->addItem("나뭇가지"));
	_vStorage.push_back(ITEMMANAGER->addItem("나뭇가지"));
	_vStorage.push_back(ITEMMANAGER->addItem("나뭇가지"));
	_vStorage.push_back(ITEMMANAGER->addItem("나뭇가지"));
	_vStorage.push_back(ITEMMANAGER->addItem("나뭇가지"));
	_vStorage.push_back(ITEMMANAGER->addItem("나뭇가지"));
	_vStorage.push_back(ITEMMANAGER->addItem("나뭇가지"));
	_vStorage.push_back(ITEMMANAGER->addItem("나뭇가지"));
	_vStorage.push_back(ITEMMANAGER->addItem("나뭇가지"));
	_vStorage.push_back(ITEMMANAGER->addItem("나뭇가지"));
	_vStorage.push_back(ITEMMANAGER->addItem("나뭇가지"));
	_vStorage.push_back(ITEMMANAGER->addItem("나뭇가지"));
	_vStorage.push_back(ITEMMANAGER->addItem("천"));
	_vStorage.push_back(ITEMMANAGER->addItem("천"));
	_vStorage.push_back(ITEMMANAGER->addItem("천"));
	_vStorage.push_back(ITEMMANAGER->addItem("천"));




	return S_OK;
}

void storage::release()
{
}

void storage::update()
{
	itemArrange();	   //Z버튼을 누르면 창고에 들어있는 것들을 자동으로 정렬해주는 함수...미완성
	cursorControl();   //커서컨트롤 WASD버튼
	setStorageItem();  // 창고안의 아이템 위치를 업데이트
	removeItem();
}

void storage::render()
{
	storageRender();
	//Rectangle(getMemDC(), _choiceSlot.left, _choiceSlot.top, _choiceSlot.right, _choiceSlot.bottom);
	if (_vTemp.size() > 0)
	{
		char str[128];
		IMAGEMANAGER->render("커서그랩", getMemDC(), _choiceSlot.left, _choiceSlot.top - 60);
		_vTemp[0].getItemInfo().image->render(getMemDC(), _choiceSlot.left, _choiceSlot.top - 50);
		wsprintf(str, "%d", _vTemp[0].getItemInfo().cnt);
		TextOut(getMemDC(), _choiceSlot.right, _choiceSlot.top - 40, str, strlen(str));
	}
}


void storage::setStorageItem()
{

	if (_showWindow)
	{
		for (int i = 0; i < SLOTNUM; i++)
		{
			//창고가 열리면 아이템의 렉트를 슬롯에 맞게 초기화
			if (i < _vStorage.size())
			{
				_vStorage[i].setRect(_slot[i]);
			}

		}
	}
}

void storage::storageRender()
{
	_boxImg->aniRender(getMemDC(), _boxRc.left, _boxRc.top, _storageAni);

	if (_showWindow)
	{
		//창고내부와 옆에 아이템이미지 띄워주는창
		char str[128];
		_mainImage->render(getMemDC(), WINSIZEX / 2 - 70, 100, _mainImage->getWidth(), _mainImage->getHeight());
		_showItem->render(getMemDC(), _showItemRc.left, _showItemRc.top, _showItem->getWidth(), _showItem->getHeight());

		//아이템칸 렌더. [] <<이렇게생긴거
		for (int i = 0; i < SLOTNUM; i++)
		{
			_slotImage[i]->render(getMemDC(), _slot[i].left, _slot[i].top);
		}

		//만약 창고 안에 아이템이 있으면 슬롯에 아이템을 보여줌.
		for (int i = 0; i < _vStorage.size(); i++)
		{
			if (_vStorage[i].getItemInfo().itemName != "비어있음") //아이템이 있으면 렌더
			{
				_vStorage[i].render();

				wsprintf(str, "%d", _vStorage[i].getItemInfo().cnt);
				TextOut(getMemDC(), _vStorage[i].getRECT().right, _vStorage[i].getRECT().bottom, str, strlen(str));
				if (IntersectRect(&temp, &_choiceSlot, &_vStorage[i].getRECT()))// 커서와 아이템이 충돌된 상태라면 
				{
					_vStorage[i].getItemInfo().image->render(getMemDC(), _showItemRc.left+10, _showItemRc.top+10);
				}
			}
		}

		_cursor->render();

		if (KEYMANAGER->isToggleKey('T'))//디버그
		{
			Rectangle(getMemDC(), _choiceSlot.left, _choiceSlot.top, _choiceSlot.right, _choiceSlot.bottom);
		}
	}
}

void storage::cursorControl()
{
	if (_showWindow)
	{
		_cursor->update(_choiceSlot);
		if (KEYMANAGER->isOnceKeyDown('A'))
		{
			//커서가 옆으로 못나가게
			_choiceNum--;
			if (_choiceNum < 0) _choiceNum = 0;

			_choiceSlot = RectMake(_slot[_choiceNum].left, _slot[_choiceNum].top, 40, 40);
			_cursor->setRc(_choiceSlot);
			_cursor->getAni()->start();
		}
		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			//커서가 옆으로 못나가게
			_choiceNum++;
			if (_choiceNum > SLOTNUM) _choiceNum = SLOTNUM;

			_choiceSlot = RectMake(_slot[_choiceNum].left, _slot[_choiceNum].top, 40, 40);
			_cursor->setRc(_choiceSlot);
			_cursor->getAni()->start();
		}
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			//커서가 위로못나가게
			int temp;
			temp = _choiceNum;
			_choiceNum-=7;
			if (_choiceNum < 0)_choiceNum = temp;

			_choiceSlot = RectMake(_slot[_choiceNum].left, _slot[_choiceNum].top, 40, 40);
			_cursor->setRc(_choiceSlot);
			_cursor->getAni()->start();
		}
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			//커서가 아래로 못나가게
			int temp;
			temp = _choiceNum;
			_choiceNum+=7;
			if (_choiceNum > SLOTNUM)_choiceNum = temp;

			_choiceSlot = RectMake(_slot[_choiceNum].left, _slot[_choiceNum].top, 40, 40);
			_cursor->setRc(_choiceSlot);
			_cursor->getAni()->start();
		}

		if (KEYMANAGER->isOnceKeyDown('I'))
		{
			_cursor->getAni()->start();
		}
		grab();
	}
}

void storage::itemArrange() //미완성
{
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		for (int k = 0; k < _vStorage.size(); k++)//아이템 벡터의 끝까지 돌아서
		{
			if (_vStorage[k].maxItem() == false) // 만약 아이템이 최대갯수가 아니라면 
			{
				for (int j = k + 1; j < _vStorage.size(); j++) //그 아이템부터 시작해서 끝까지 돌아서 
				{
					if (_vStorage[k].getItemInfo().itemName == _vStorage[j].getItemInfo().itemName)
					{
						//같은 아이템이 있으면 정리해줌
						_vStorage[k].setItemCnt();
						_vStorage.erase(_vStorage.begin() + j);
						if (_vStorage[k].getItemInfo().cnt >= _vStorage[k].getItemInfo().maxCnt)
						{
							//그렇게 최대갯수에 도달하면 최대갯수로 바꿔주어 빠져나감
							_vStorage[k].maxItem();
						}
						//break;
					}
				}
			}
		}
	}
}

void storage::resetChoiceNum()
{
	//창고 창이 껏다켜지면 커서위치 초기화
	_choiceNum = 0; 
	_choiceSlot = _slot[_choiceNum];
}

void storage::removeItem()
{
	for (int i = 0; i < _vStorage.size(); i++)
	{
		if(_vStorage[i].getItemInfo().cnt == 0)
		{
			_vStorage.erase(_vStorage.begin() + i);
		}
	}
}

void storage::grab()
{

	for (int i = 0; i < _vStorage.size(); i++)
	{
		if (_vStorage[i].getItemInfo().itemName != "비어있음") //창고 안이 비어있지 않고
		{
			if ((_choiceNum == i )&& KEYMANAGER->isOnceKeyDown('J'))// 커서와 아이템이 충돌된 상태라면
			{
					_cursor->getAni()->start();
		
					//임시벡터가 비어있을시 벡터에 추가
					if (_vTemp.size() <= 0) 
					{
						_vTemp.push_back(_vStorage[i]);
						_vStorage.erase(_vStorage.begin() + i);
						_vStorage.insert(_vStorage.begin() + i, ITEMMANAGER->addItem("비어있음"));
						break;
					}

					//임시벡터에 이미 같은 이름의 아이템이 있으면 카운트를 올려줌
					if (_vTemp[0].getItemInfo().itemName == _vStorage[i].getItemInfo().itemName &&
						(_vStorage[i].getItemInfo().cnt+_vTemp[0].getItemInfo().cnt)<= _vTemp[0].getItemInfo().maxCnt) 
					{
						_vTemp[0].setItemCnt(_vStorage[i].getItemInfo().cnt);
						_vStorage.erase(_vStorage.begin() + i);
						_vStorage.insert(_vStorage.begin() + i, ITEMMANAGER->addItem("비어있음"));
						break;
					}
			}
		}

		if (_vTemp.size() > 0)
		{
			if (_vStorage[i].getItemInfo().itemName == "비어있음") //비어있는 곳에
			{
				if ((_choiceNum == i) && KEYMANAGER->isOnceKeyDown('J'))//j를 누르면 아이템을 그 자리에 놓음
				{
					_cursor->getAni()->start();

					_vStorage.erase(_vStorage.begin() + i);
					_vStorage.insert(_vStorage.begin() + i, _vTemp[0]);
					_vTemp.pop_back();
					break;
				}
			}
		}

	}
}
