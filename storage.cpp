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
	_bgimag = IMAGEMANAGER->findImage("배경");								//뒤에 배경

	_name = storageName;
	_boxImg = IMAGEMANAGER->findImage(storageName);
	_boxRc = RectMakeCenter(xy.x, xy.y, _boxImg->getFrameWidth(), _boxImg->getFrameHeight());

	if (storageName == "창고1")_storageAni = ANIMATIONMANAGER->findAnimation("창고1오픈");
	if (storageName == "창고2")_storageAni = ANIMATIONMANAGER->findAnimation("창고2오픈");

	_mainImage = IMAGEMANAGER->findImage("창고내부");

	_showItem = IMAGEMANAGER->findImage("템보여주기");
	_showItemRc = RectMakeCenter(WINSIZEX - 70, 250, _showItem->getWidth(), _showItem->getHeight());

	//슬롯벡터 초기화
	for (int i = 0; i < SLOTNUM; i++)
	{
		int x, y;
		x = i % 7;
		y = i / 7;
		_slotInfo.img = IMAGEMANAGER->findImage("슬롯이미지");
		_slotInfo.x = WINSIZEX / 2 + (x * 60) + 20;
		_slotInfo.y = WINSIZEY / 2 - 80 + (y * 60) + 20;
		_slotInfo.rc = RectMakeCenter(_slotInfo.x, _slotInfo.y, _slotInfo.img->getWidth(), _slotInfo.img->getHeight());
		_slotInfo.item = ITEMMANAGER->addItem("비어있음");
		_slotInfo.item.setItemCnt(1);
		_slotInfo.item.setRect(_slotInfo.rc);
		_vSlot.push_back(_slotInfo);
	}
	//커서 초기화
	_cursor = new cursor;
	_cursor->init();
	_cursorNum = 0;
	_cursorSlot = _vSlot[_cursorNum].rc;
	_cursor->setRc(_cursorSlot);
	_grab = new image;
	_grab = IMAGEMANAGER->findImage("커서그랩");


	return S_OK;
}

void storage::release()
{
	SAFE_DELETE(_cursor);
}

void storage::update()
{
	if (KEYMANAGER->isOnceKeyDown('8'))
	{
		for (int i = 0; i < _vSlot.size(); i++)
		{
			if (_vSlot[i].item.getItemInfo().itemName == "비어있음")
			{
				_vSlot[i].item = ITEMMANAGER->addItem("천");
				_vSlot[i].item.setItemCnt_equal(9);
				break;
			}
		}
		for (int i = 0; i < _vSlot.size(); i++)
		{
			if (_vSlot[i].item.getItemInfo().itemName == "비어있음")
			{
				_vSlot[i].item = ITEMMANAGER->addItem("골렘코어");
				_vSlot[i].item.setItemCnt_equal(9);
				break;
			}
		}
		for (int i = 0; i < _vSlot.size(); i++)
		{
			if (_vSlot[i].item.getItemInfo().itemName == "비어있음")
			{
				_vSlot[i].item = ITEMMANAGER->addItem("이빨석");
				_vSlot[i].item.setItemCnt_equal(9);
				break;
			}
		}
		for (int i = 0; i < _vSlot.size(); i++)
		{
			if (_vSlot[i].item.getItemInfo().itemName == "비어있음")
			{
				_vSlot[i].item = ITEMMANAGER->addItem("나뭇가지");
				_vSlot[i].item.setItemCnt_equal(9);
				break;
			}
		}
		for (int i = 0; i < _vSlot.size(); i++)
		{
			if (_vSlot[i].item.getItemInfo().itemName == "비어있음")
			{
				_vSlot[i].item = ITEMMANAGER->addItem("숫돌");
				_vSlot[i].item.setItemCnt_equal(9);
				break;
			}
		}
		for (int i = 0; i < _vSlot.size(); i++)
		{
			if (_vSlot[i].item.getItemInfo().itemName == "비어있음")
			{
				_vSlot[i].item = ITEMMANAGER->addItem("강화수정");
				_vSlot[i].item.setItemCnt_equal(9);
				break;
			}
		}
		setStorageItem();
	}
	if (!_showWindow)
	{
		if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &_boxRc))
		{
			if (KEYMANAGER->isOnceKeyDown('J')) //열기
			{
				if (_name == "창고1")_storageAni = ANIMATIONMANAGER->findAnimation("창고1오픈");
				if (_name == "창고2")_storageAni = ANIMATIONMANAGER->findAnimation("창고2오픈");
				_storageAni->start();

				_showWindow = true;
				_cursor->update(_cursorSlot);
				_cursorNum = 0;
				_cursorSlot = _vSlot[_cursorNum].rc;
				_cursor->setRc(_cursorSlot);
				PLAYER->getinventory()->setStprageOpen(true);  //--->아이템 창(인벤) 오픈 
				PLAYER->setstop(true);
			}
		}
	}
	else
	{
		if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &_boxRc))
		{
			if (KEYMANAGER->isOnceKeyDown('6')) //닫기
			{
				if (_name == "창고1")_storageAni = ANIMATIONMANAGER->findAnimation("창고1클로즈");
				if (_name == "창고2")_storageAni = ANIMATIONMANAGER->findAnimation("창고2클로즈");

				_storageAni->start();
				PLAYER->getinventory()->setStprageOpen(false);			//--> 아이템창(인벤) 닫기
				PLAYER->setstop(false);
				_showWindow = false;
			}
		}
		//playerCollision(); //열기닫기
		//itemArrange();	   //Z버튼을 누르면 창고에 들어있는 것들을 자동으로 정렬해주는 함수...미완성
		if (!PLAYER->getinventory()->getstorgeuding()) cursorControl();   //-->커서컨트롤 WASD버튼
		else PLAYER->getinventory()->cursormove();				//-->커서컨트롤 WASD버튼


		if (!PLAYER->getinventory()->getstorgeuding() && !PLAYER->getinventory()->getvTemp().empty())
		{
			slot temp;

			temp.img = PLAYER->getinventory()->getvTemp()[0]._inventoryimg;
			temp.item = PLAYER->getinventory()->getvTemp()[0]._item;

			_vTemp.push_back(temp);

			PLAYER->getinventory()->tempClear();
		}

		cursorControl();   //커서컨트롤 WASD버튼
		grab();
		removeItem();	   //카운트가 0으로 떨어진 아이템들을 계속 지워준다. 지워준 다음에는 다시 '비어있음'을 넣어줌
		setStorageItem();  //창고안의 아이템 위치를 업데이트

		PLAYER->getinventory()->inventoryItem();						//			---> 창고에서 인벤토리의 상태를 보여줘야하며 
		PLAYER->getinventory()->grabitemremove();					//			--->  창고에서 (창고용)인벤토리 아이템을 버리는 상태를 알아야한다. 

	}
}

void storage::render()
{
	PLAYER->getinventory()->moverender(getMemDC());
	_boxImg->aniRender(getMemDC(), _boxRc.left, _boxRc.top, _storageAni);
	//Rectangle(getMemDC(), _cursorSlot.left, _cursorSlot.top, _cursorSlot.right, _cursorSlot.bottom);

	if (!_showWindow)
	{
		if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &_boxRc))
		{
			IMAGEMANAGER->render("열기", getMemDC(), _boxRc.right, _boxRc.top - 20);
		}
	}
	else
	{
		_bgimag->alphaRender(getMemDC(), 1000);   // 알파랜더 처리할 배경화면
		storageRender();
		if (_vTemp.size() > 0)	//템프가 비어있지 않다면(커서가 템을 잡고 있다면)
		{
			char str[128];
			IMAGEMANAGER->render("커서그랩", getMemDC(), _cursorSlot.left, _cursorSlot.top - 60);
			_vTemp[0].item.getItemInfo().image->render(getMemDC(), _cursorSlot.left, _cursorSlot.top - 50);
			wsprintf(str, "%d", _vTemp[0].item.getItemInfo().cnt);
			TextOut(getMemDC(), _cursorSlot.right, _cursorSlot.top - 40, str, strlen(str));
		}
	}
}


void storage::setStorageItem()
{
	for (int i = 0; i < SLOTNUM; i++)
	{
		//창고가 열리면 아이템의 렉트를 슬롯에 맞게 초기화
		if (i < _vSlot.size())
		{
			_vSlot[i].item.setRect(_vSlot[i].rc);
		}
	}
}

void storage::storageRender()
{
	char str[128];

	//창고내부
	_mainImage->render(getMemDC(), WINSIZEX / 2 - 70, 100, _mainImage->getWidth(), _mainImage->getHeight());
	_showItem->render(getMemDC(), _showItemRc.left, _showItemRc.top, _showItem->getWidth(), _showItem->getHeight());

	//아이템칸 렌더. [] <<이렇게생긴거
	for (int i = 0; i < SLOTNUM; i++)
	{
		_vSlot[i].img->render(getMemDC(), _vSlot[i].rc.left, _vSlot[i].rc.top);
	}

	//만약 창고 안에 아이템이 있으면 슬롯에 아이템을 보여줌.
	for (int i = 0; i < _vSlot.size(); i++)
	{
		if (_vSlot[i].item.getItemInfo().itemName != "비어있음") //아이템이 있으면 렌더
		{
			_vSlot[i].item.render(getMemDC());

			wsprintf(str, "%d", _vSlot[i].item.getItemInfo().cnt);
			TextOut(getMemDC(), _vSlot[i].rc.right, _vSlot[i].rc.bottom, str, strlen(str));
		}
	}

	if (!PLAYER->getinventory()->getstorgeuding()) _cursor->render();

}

void storage::cursorControl()
{
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		//커서가 옆으로 못나가게
		_cursorNum--;
		if (_cursorNum < 0)
		{
			_cursorNum = 0;
			PLAYER->getinventory()->setstorgeuding(true); //옆으로 인벤토리로 옮기기
			if (_vTemp.size() != 0) PLAYER->getinventory()->swapItem(_vTemp[0].item);
			_vTemp.clear();
		}
		_cursorSlot = _vSlot[_cursorNum].rc;
		_cursor->getAni()->start();
	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		//커서가 옆으로 못나가게
		_cursorNum++;
		if (_cursorNum > SLOTNUM) _cursorNum = SLOTNUM;
		_cursorSlot = _vSlot[_cursorNum].rc;
		_cursor->getAni()->start();
	}
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		//커서가 위로못나가게
		int temp;
		temp = _cursorNum;
		_cursorNum -= 7;
		if (_cursorNum < 0)_cursorNum = temp;
		_cursorSlot = _vSlot[_cursorNum].rc;
		_cursor->getAni()->start();
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		//커서가 아래로 못나가게
		int temp;
		temp = _cursorNum;
		_cursorNum += 7;
		if (_cursorNum > SLOTNUM)_cursorNum = temp;

		_cursorSlot = _vSlot[_cursorNum].rc;
		_cursor->getAni()->start();
	}
	_cursor->setRc(_cursorSlot);

	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		_cursor->getAni()->start();
	}
}

void storage::itemArrange() //미완성
{
	//if (KEYMANAGER->isOnceKeyDown('1'))
	//{
	//	for (int k = 0; k < _vStorage.size(); k++)//아이템 벡터의 끝까지 돌아서
	//	{
	//		if (_vStorage[k].maxItem() == false) // 만약 아이템이 최대갯수가 아니라면 
	//		{
	//			for (int j = k + 1; j < _vStorage.size(); j++) //그 아이템부터 시작해서 끝까지 돌아서 
	//			{
	//				if (_vStorage[k].getItemInfo().itemName == _vStorage[j].getItemInfo().itemName)
	//				{
	//					//같은 아이템이 있으면 정리해줌
	//					_vStorage[k].setItemCnt();
	//					_vStorage.erase(_vStorage.begin() + j);
	//					if (_vStorage[k].getItemInfo().cnt >= _vStorage[k].getItemInfo().maxCnt)
	//					{
	//						//그렇게 최대갯수에 도달하면 최대갯수로 바꿔주어 빠져나감
	//						_vStorage[k].maxItem();
	//					}
	//					//break;
	//				}
	//			}
	//		}
	//	}
	//}
}

void storage::removeItem()
{
	for (int i = 0; i < _vSlot.size(); i++)
	{
		if (_vSlot[i].item.getItemInfo().cnt <= 0)
		{
			_vSlot[i].item = ITEMMANAGER->addItem("비어있음");
			_vSlot[i].item.setItemCnt_equal(1);
		}
	}
}

void storage::grab()
{
	for (int i = 0; i < _vSlot.size(); i++)
	{
		if (_vSlot[i].item.getItemInfo().itemName != "비어있음") //창고 안이 비어있지 않고
		{
			if ((_cursorNum == i) && KEYMANAGER->isOnceKeyDown('J'))// 커서와 아이템이 충돌된 상태라면
			{
				_cursor->getAni()->start();

				//임시벡터가 비어있을시 벡터에 추가
				if (_vTemp.empty())
				{
					_vTemp.push_back(_vSlot[i]);
					_vTemp[0].item.setItemCnt_equal(1);
					_vSlot[i].item.setItemCnt(-1);
					break;
				}

				//임시벡터에 이미 같은 이름의 아이템이 있으면 카운트를 올려줌
				if (_vTemp[0].item.getItemInfo().itemName == _vSlot[i].item.getItemInfo().itemName &&
					(_vSlot[i].item.getItemInfo().cnt + _vTemp[0].item.getItemInfo().cnt) <= _vTemp[0].item.getItemInfo().maxCnt)
				{
					_vTemp[0].item.setItemCnt();
					_vSlot[i].item.setItemCnt(-1);
					break;
				}
			}
		}

		if (!_vTemp.empty())	//템프가 비어있지 않다면(아이템을 잡고 있다면)
		{
			if (_vSlot[i].item.getItemInfo().itemName == "비어있음") //비어있는 곳에
			{
				if ((_cursorNum == i) && KEYMANAGER->isOnceKeyDown('J'))//j를 누르면 아이템을 그 자리에 놓음
				{
					_cursor->getAni()->start();
					_vSlot[i].item = _vTemp[0].item;

					_vTemp.pop_back();
					break;
				}
			}
		}

	}
}

