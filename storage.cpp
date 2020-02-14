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
	_name = storageName;
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
	_cursorNum = 0;
	_cursorSlot = _slot[_cursorNum];
	_cursor = new cursor;
	_cursor->init();
	_grab = new image;
	_grab = IMAGEMANAGER->findImage("커서그랩");


	//비어있는 상태로 초기화
	for (int i = 0; i < 28; i++)
	{
		_vStorage.push_back(ITEMMANAGER->addItem("비어있음"));
	}

	return S_OK;
}

void storage::release()
{
	SAFE_DELETE(_cursor);
}

void storage::update()
{
	if (KEYMANAGER->isOnceKeyDown('5'))
	{
		for (int k = 0; k < _vStorage.size(); k++)
		{
			if (_vStorage[k].getItemInfo().itemName == "비어있음" || _vStorage[k].getItemInfo().cnt <= 0)
			{
				_vStorage.erase(_vStorage.begin() + k);
				_vStorage.insert(_vStorage.begin() + k, ITEMMANAGER->addItem("나뭇가지"));
				_vStorage[k].setItemCnt_equal(10);
				break;
			}
		}
		for (int k = 0; k < _vStorage.size(); k++)
		{
			if (_vStorage[k].getItemInfo().itemName == "비어있음" || _vStorage[k].getItemInfo().cnt <= 0)
			{
				_vStorage.erase(_vStorage.begin() + k);
				_vStorage.insert(_vStorage.begin() + k, ITEMMANAGER->addItem("숫돌"));
				_vStorage[k].setItemCnt_equal(10);
				break;
			}
		}
		for (int k = 0; k < _vStorage.size(); k++)
		{
			if (_vStorage[k].getItemInfo().itemName == "비어있음" || _vStorage[k].getItemInfo().cnt <= 0)
			{
				_vStorage.erase(_vStorage.begin() + k);
				_vStorage.insert(_vStorage.begin() + k, ITEMMANAGER->addItem("수정화 된 에너지"));
				_vStorage[k].setItemCnt_equal(10);
				break;
			}
		}
		for (int k = 0; k < _vStorage.size(); k++)
		{
			if (_vStorage[k].getItemInfo().itemName == "비어있음" || _vStorage[k].getItemInfo().cnt <= 0)
			{
				_vStorage.erase(_vStorage.begin() + k);
				_vStorage.insert(_vStorage.begin() + k, ITEMMANAGER->addItem("천"));
				_vStorage[k].setItemCnt_equal(10);
				break;
			}
		}
		for (int k = 0; k < _vStorage.size(); k++)
		{
			if (_vStorage[k].getItemInfo().itemName == "비어있음" || _vStorage[k].getItemInfo().cnt <= 0)
			{
				_vStorage.erase(_vStorage.begin() + k);
				_vStorage.insert(_vStorage.begin() + k, ITEMMANAGER->addItem("골렘코어"));
				_vStorage[k].setItemCnt_equal(10);
				break;
			}
		}
		for (int k = 0; k < _vStorage.size(); k++)
		{
			if (_vStorage[k].getItemInfo().itemName == "비어있음" || _vStorage[k].getItemInfo().cnt <= 0)
			{
				_vStorage.erase(_vStorage.begin() + k);
				_vStorage.insert(_vStorage.begin() + k, ITEMMANAGER->addItem("이빨석"));
				_vStorage[k].setItemCnt_equal(10);
				break;
			}
		}
	}
	playerCollision(); //열기닫기
	//itemArrange();	   //Z버튼을 누르면 창고에 들어있는 것들을 자동으로 정렬해주는 함수...미완성
	if (!PLAYER->getinventory()->getTest()) cursorControl();   //-->커서컨트롤 WASD버튼
	else PLAYER->getinventory()->cursormove();				//-->커서컨트롤 WASD버튼
	cursorControl();   //커서컨트롤 WASD버튼
	setStorageItem();  //창고안의 아이템 위치를 업데이트
	removeItem();	   //카운트가 0으로 떨어진 아이템들을 계속 지워준다. 지워준 다음에는 다시 '비어있음'을 넣어줌
	PLAYER->getinventory()->inventoryItem();						//			---> 창고에서 인벤토리의 상태를 보여줘야하며 
	PLAYER->getinventory()->grabitemremove();					//			--->  창고에서 (창고용)인벤토리 아이템을 버리는 상태를 알아야한다. 
	//invenplayer();				//    -->창고랑 인벤토리랑 주고 받는 함수
	//invenplayermove(); //-->인벤토리 아이템이 창고로 넘어갔을 때 비어있음 자리로  채워지는 함수
}

void storage::render()
{
	PLAYER->getinventory()->moverender(getMemDC());
	storageRender();
	//Rectangle(getMemDC(), _cursorSlot.left, _cursorSlot.top, _cursorSlot.right, _cursorSlot.bottom);
	if (!_showWindow)
	{
		if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &_boxRc))
		{
			IMAGEMANAGER->render("열기", getMemDC(), _boxRc.right, _boxRc.top - 20);
		}
	}
	
	if (_vTemp.size() > 0)	//템프가 비어있지 않다면(커서가 템을 잡고 있다면)
	{
		char str[128];
		IMAGEMANAGER->render("커서그랩", getMemDC(), _cursorSlot.left, _cursorSlot.top - 60);
		_vTemp[0].getItemInfo().image->render(getMemDC(), _cursorSlot.left, _cursorSlot.top - 50);
		wsprintf(str, "%d", _vTemp[0].getItemInfo().cnt);
		TextOut(getMemDC(), _cursorSlot.right, _cursorSlot.top - 40, str, strlen(str));
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

	if (_showWindow)//열려있을때
	{
		char str[128];

		//창고내부
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
				// 커서와 아이템이 충돌된 상태라면 추가로 옆칸에 이미지를 띄워줌
				if (IntersectRect(&temp, &_cursorSlot, &_vStorage[i].getRECT()))
				{
					_vStorage[i].getItemInfo().image->render(getMemDC(), _showItemRc.left+10, _showItemRc.top+10);
				}
			}
		}
		if(!PLAYER->getinventory()->getTest()) _cursor->render();
	}
}

void storage::cursorControl()
{
	if (_showWindow)
	{
		if (KEYMANAGER->isOnceKeyDown('A'))
		{
			//커서가 옆으로 못나가게
			_cursorNum--;
			if (_cursorNum < 0)
			{
				_cursorNum = 0;
				PLAYER->getinventory()->setTest(true); //옆으로 인벤토리로 옮기기
				if(_vTemp.size()!=0) PLAYER->getinventory()->swapItem(_vTemp[0]);
			//	PLAYER->getinventory()->getvTemp()[0];
			}
			/*	if (_cursorNum = 7 && KEYMANAGER->isOnceKeyDown('A'))
				{
					PLAYER->getinventory()->setTest(true);
				}*/

			_cursorSlot = RectMake(_slot[_cursorNum].left, _slot[_cursorNum].top, 40, 40);
			_cursor->getAni()->start();
		}
		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			//커서가 옆으로 못나가게
			_cursorNum++;
			if (_cursorNum > SLOTNUM) _cursorNum = SLOTNUM;

			_cursorSlot = RectMake(_slot[_cursorNum].left, _slot[_cursorNum].top, 40, 40);
			_cursor->getAni()->start();
		}
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			//커서가 위로못나가게
			int temp;
			temp = _cursorNum;
			_cursorNum-=7;
			if (_cursorNum < 0)_cursorNum = temp;

			_cursorSlot = RectMake(_slot[_cursorNum].left, _slot[_cursorNum].top, 40, 40);
			_cursor->getAni()->start();
		}
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			//커서가 아래로 못나가게
			int temp;
			temp = _cursorNum;
			_cursorNum+=7;
			if (_cursorNum > SLOTNUM)_cursorNum = temp;

			_cursorSlot = RectMake(_slot[_cursorNum].left, _slot[_cursorNum].top, 40, 40);
			_cursor->getAni()->start();
		}
		_cursor->setRc(_cursorSlot);

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

void storage::resetCursor()
{
	//창고 창이 껏다켜지면 커서위치 초기화
	_cursorNum = 0; 
	_cursorSlot = _slot[_cursorNum];
}

void storage::removeItem()
{
	for (int i = 0; i < _vStorage.size(); i++)
	{
		if(_vStorage[i].getItemInfo().cnt == 0)
		{
			_vStorage.erase(_vStorage.begin() + i);
			_vStorage.insert(_vStorage.begin() + i , ITEMMANAGER->addItem("비어있음"));
		}
	}
}

void storage::grab()
{
	for (int i = 0; i < _vStorage.size(); i++)
	{
		if (_vStorage[i].getItemInfo().itemName != "비어있음") //창고 안이 비어있지 않고
		{
			if ((_cursorNum == i )&& KEYMANAGER->isOnceKeyDown('J'))// 커서와 아이템이 충돌된 상태라면
			{
				_cursor->getAni()->start();
	
				//임시벡터가 비어있을시 벡터에 추가
				if (_vTemp.size() <= 0) 
				{
					_vTemp.push_back(_vStorage[i]);
					_vTemp[0].setItemCnt_equal(1);
					_vStorage[i].setItemCnt(-1);
					//_vStorage.erase(_vStorage.begin() + i);
					//_vStorage.insert(_vStorage.begin() + i, ITEMMANAGER->addItem("비어있음"));
					break;
				}

				//임시벡터에 이미 같은 이름의 아이템이 있으면 카운트를 올려줌
				if (_vTemp[0].getItemInfo().itemName == _vStorage[i].getItemInfo().itemName &&
					(_vStorage[i].getItemInfo().cnt+_vTemp[0].getItemInfo().cnt)<= _vTemp[0].getItemInfo().maxCnt) 
				{
					_vTemp[0].setItemCnt();
					_vStorage[i].setItemCnt(-1);
					break;
				}
			}
			//if ((_cursorNum == i) && KEYMANAGER->isStayKeyDown('J'))
			//{
			//	allGrab = true;
			//	if (allGrab)
			//	{
			//		_cursor->getAni()->start();

			//		//임시벡터가 비어있을시 벡터에 추가
			//		if (_vTemp.size() <= 0)
			//		{
			//			_vTemp.push_back(_vStorage[i]);
			//			_vStorage.erase(_vStorage.begin() + i);
			//			_vStorage.insert(_vStorage.begin() + i, ITEMMANAGER->addItem("비어있음"));
			//			break;
			//		}

			//		//임시벡터에 이미 같은 이름의 아이템이 있으면 카운트를 올려줌
			//		if (_vTemp[0].getItemInfo().itemName == _vStorage[i].getItemInfo().itemName &&
			//			(_vStorage[i].getItemInfo().cnt + _vTemp[0].getItemInfo().cnt) <= _vTemp[0].getItemInfo().maxCnt)
			//		{
			//			_vTemp[0].setItemCnt(_vStorage[i].getItemInfo().cnt);
			//			_vStorage.erase(_vStorage.begin() + i);
			//			_vStorage.insert(_vStorage.begin() + i, ITEMMANAGER->addItem("비어있음"));
			//			break;
			//		}
			//		allGrab = false;
			//	}
			//}
		}
		
		if (_vTemp.size() > 0)	//템프가 비어있지 않다면(아이템을 잡고 있다면)
		{
			if (_vStorage[i].getItemInfo().itemName == "비어있음") //비어있는 곳에
			{
				if ((_cursorNum == i) && KEYMANAGER->isOnceKeyDown('J'))//j를 누르면 아이템을 그 자리에 놓음
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


void storage::invenplayer()   //-->
{
	if (PLAYER->getinventory()->getTest() == true)						//인벤용으로 넘어온 상태에서
	{
		for (int i = 0; i < PLAYER->getinventory()->getvInven().size(); i++)				//전체 상태 확인하기
		{
			if (PLAYER->getinventory()->getvInven()[i].getItemInfo().itemName != "비어있음")
			{
				if ((PLAYER->getinventory()->getcusornumber() == i) && KEYMANAGER->isOnceKeyDown('U'))
				{
					_cursor->getAni()->start();

					if (_vTemp.empty())
					{
						_vTemp.push_back(PLAYER->getinventory()->getvInven()[i]);
						_vTemp[0].setItemCnt_equal(1);
						PLAYER->getinventory()->getvInven()[i].setItemCnt(-1);
						break;
					}
					if ((_vTemp[0].getItemInfo().itemName == PLAYER->getinventory()->getvInven()[i].getItemInfo().itemName))
					{
						_vTemp[0].setItemCnt();
						PLAYER->getinventory()->getvInven()[i].setItemCnt(-1);
						break;
					}
				}
			}
			if (!_vTemp.empty())
			{
				if (i < 20)
				{
					if (PLAYER->getinventory()->getvInven()[i].getItemInfo().itemName == "비어있음")
					{
						if ((PLAYER->getinventory()->getcusornumber() == i) && KEYMANAGER->isOnceKeyDown('U'))
						{
							_cursor->getAni()->start();

							PLAYER->getinventory()->getvInven().erase(PLAYER->getinventory()->getvInven().begin() + i);
							PLAYER->getinventory()->getvInven().insert(PLAYER->getinventory()->getvInven().begin() + i, _vTemp[0]);
							_vTemp.pop_back();
							break;
						}
					}
				}
			}
		}
	}
}

void storage::invenplayermove()
{
	for (int i = 0; i < PLAYER->getinventory()->getvInven().size(); i++)
	{
		if (PLAYER->getinventory()->getvInven()[i].getItemInfo().cnt == 0)
		{
			PLAYER->getinventory()->getvInven().erase(PLAYER->getinventory()->getvInven().begin() + i);
			PLAYER->getinventory()->getvInven().insert(PLAYER->getinventory()->getvInven().begin() + i, ITEMMANAGER->addItem("비어있음"));
		}
	}
}


void storage::playerCollision()//열기닫기
{
	if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &_boxRc))
	{
		if (!_showWindow)
		{
			if (KEYMANAGER->isOnceKeyDown('J'))
			{
				if (_name == "창고1")_storageAni = ANIMATIONMANAGER->findAnimation("창고1오픈");
				if (_name == "창고2")_storageAni = ANIMATIONMANAGER->findAnimation("창고2오픈");
				resetCursor();
				_storageAni->start();
				PLAYER->getinventory()->setStprageOpen(true);  //--->아이템 창(인벤) 오픈 
				_showWindow = true;
			}
		}
		if (_showWindow)
		{
			if (KEYMANAGER->isOnceKeyDown('I'))
			{
				if (_name == "창고1")_storageAni = ANIMATIONMANAGER->findAnimation("창고1클로즈");
				if (_name == "창고2")_storageAni = ANIMATIONMANAGER->findAnimation("창고2클로즈");
				
				_storageAni->start();
				PLAYER->getinventory()->setStprageOpen(false);			//--> 아이템창(인벤) 닫기
				_showWindow = false;
			}
		}
	}
}
