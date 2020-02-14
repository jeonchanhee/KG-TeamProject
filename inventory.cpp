#include "stdafx.h"
#include "inventory.h"


/*
캐릭터프로필
무기 전환
무기 넣었다 빼기, 무기 교환
*/

/*
창고에서는
인벤에 있는 물건 주고 받기
*/

inventory::inventory()
{
}

inventory::~inventory()
{
}

HRESULT inventory::init()
{
	ITEMMANAGER->init();

	//=================================================사진만 있는 이미지들=====================================================
	//bkrender()에 들어가는 이미지들
	_bgimag = IMAGEMANAGER->findImage("배경");								//뒤에 배경

	//인벤토리 북
	_playerinventory._inventoryimg = IMAGEMANAGER->findImage("인벤토리북");
	_playerinventory.x = WINSIZEX / 2;
	_playerinventory.y = WINSIZEY / 2;
	_playerinventory._inventoryrect = RectMakeCenter(_playerinventory.x, _playerinventory.y, _playerinventory._inventoryimg->getWidth(), _playerinventory._inventoryimg->getHeight());

	//아이템을 돈으로 반환하는 이미지
	_removeGlass._inventoryimg = IMAGEMANAGER->findImage("돋보기");
	_removeGlass.x = 170;
	_removeGlass.y = 550;
	_removeGlass._inventoryrect = RectMakeCenter(_removeGlass.x, _removeGlass.y, _removeGlass._inventoryimg->getWidth(), _removeGlass._inventoryimg->getHeight());

	//템 보여주는 곳
	_showitem._showitemimg = IMAGEMANAGER->findImage("템보여주기");					//아이템 클릭하면 뜨는 원 오른쪽 끝에 있음
	_showitem._showitemrc = RectMakeCenter(WINSIZEX - 70, 250, _showitem._showitemimg->getWidth(), _showitem._showitemimg->getHeight());

	_zbutton._inventoryimg = IMAGEMANAGER->findImage("Z버튼");
	_zbutton.x = 660;
	_zbutton.y = 225;

	_weaponiright._inventoryimg = IMAGEMANAGER->findImage("z비활성화오");
	_weaponiright.x = 637;
	_weaponiright.y = 235;
	_weaponileft._inventoryimg = IMAGEMANAGER->findImage("z버전활성화왼");
	_weaponileft.x = 700;
	_weaponileft.y = 235;

	//z버전활성화왼,
	_weaponirighting._inventoryimg = IMAGEMANAGER->findImage("z버전활성화왼");
	_weaponirighting.x = 700;
	_weaponirighting.y = 235;

	//활성화오
	_weaponilefting._inventoryimg = IMAGEMANAGER->findImage("z활성화오");
	_weaponilefting.x = 637;
	_weaponilefting.y = 235;

	//bkrender()에 들어가는 이미지들
	//============================================================================================================
	_inventorybg._inventoryimg = IMAGEMANAGER->findImage("인벤토리종이");
	_inventorybg.x = WINSIZEX / 2 - 410;
	_inventorybg.y = WINSIZEY / 2 - 215;

	//인벤토리 요소들
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			_invenotryelement[i + 5 * j]._inventoryimg = IMAGEMANAGER->findImage("요소");
			_invenotryelement[i + 5 * j]._inventoryrect = RectMakeCenter(190 + i * 55, 240 + j * 60, 40, 40);	 // 디버깅 상으로 1~2번째 줄 인벤토리 요소는
			if (j >= 2)   // 디버깅 상 3~4번째 줄 인벤토리 요소는
			{
				// 인벤토리 요소 불러오기 이미지  
				_invenotryelement[i + 5 * j]._inventoryrect = RectMakeCenter(190 + i * 55, 240 + j * 60, 40, 40);				//인벤토리 위치 설정
			}
		}
	}
	_invenotryelement[20]._inventoryrect = RectMakeCenter((_removeGlass._inventoryrect.left + _removeGlass._inventoryrect.right) / 2 + 15, (_removeGlass._inventoryrect.top + _removeGlass._inventoryrect.bottom) / 2 - 22, 40, 40);			// 아이템을 돈으로 반환하는 인벤토리 요소 돋보기위치



	//커서 클래스 이용하기
	_cursor = new cursor;
	_cursor->init();
	_cursorNumber = 0;
	_cursorrect = _invenotryelement[_cursorNumber]._inventoryrect;
	_cursor->setRc(_cursorrect);

	//_cursorrect = RectMakeCenter(190, 240, 40, 40);
	//커서 그랩
	_grab._grabimg = IMAGEMANAGER->addImage("커서그랩", "images/shop/grab.bmp", 50, 52, true, RGB(255, 0, 255));

	_openinventorywin = false;

	//임시용으로 만듬 
	_vInven.push_back(ITEMMANAGER->addItem("나뭇가지"));// 임시로 추가해 놓은 것 
	_vInven.push_back(ITEMMANAGER->addItem("강화수정"));// 임시로 추가해 놓은 것 
	_vInven.push_back(ITEMMANAGER->addItem("쇠막대기"));// 임시로 추가해 놓은 것 
	_vInven.push_back(ITEMMANAGER->addItem("덩쿨"));// 임시로 추가해 놓은 것 
	_vInven.push_back(ITEMMANAGER->addItem("천"));// 임시로 추가해 놓은 것 
	_vInven[4].setItemCnt(5);
	_vInven.push_back(ITEMMANAGER->addItem("천"));// 임시로 추가해 놓은 것 
	_vInven[5].setItemCnt(4);

	test = false;
	_storageOpen = false;
	_isweapon = false;			//무기 전환하기 위한 불값.. 이미지로만

	return S_OK;
}
void inventory::release()
{
	SAFE_DELETE(_cursor);
}

void inventory::update()
{
	ANIMATIONMANAGER->update();				//커서 애니메이션 움직이기 위한 매니저 함수 
	if (!_openinventorywin)   // 인벤토리 비활성화
	{
		if (KEYMANAGER->isOnceKeyDown('6'))
		{
			_openinventorywin = true;
			_cursor->update(_cursorrect);
			_cursorNumber = 0;
			_cursorrect = _invenotryelement[_cursorNumber]._inventoryrect;
			_cursor->setRc(_cursorrect);
		} // 인벤토리활성화
	}
	else // 인벤토리활성화
	{
		if (KEYMANAGER->isOnceKeyDown('6')) // 인벤토리활성화
			_openinventorywin = false;
		cursormove();//커서 움직이기 
		inventoryItem();
		grabitemremove();  //J를 눌렀을 때 아이템을 빼기
		isweaponing();
	}
}

void inventory::cursormove()   //커서 이동  함수
{
	_cursor->update(_cursorrect);						//먼저 초기화
	if (KEYMANAGER->isOnceKeyDown('A'))		//왼쪽
	{
		_cursorNumber--;
		if (_cursorNumber < 0)_cursorNumber = 0;
		_cursorrect = RectMake(_invenotryelement[_cursorNumber]._inventoryrect.left, _invenotryelement[_cursorNumber]._inventoryrect.top, 40, 40);
		_cursor->setRc(_cursorrect);
		_cursor->getAni()->start();
	}
	if (KEYMANAGER->isOnceKeyDown('D'))			//오른쪽
	{
		_cursorNumber++;

		if (!_storageOpen)
		{
			if (_cursorNumber > 20);//_cursorNumber = 20;
		}
		else
		{
			if (_cursorNumber > 19)
			{
				test = false;
				_cursorNumber = 0;

			}
		}
		_cursorrect = RectMake(_invenotryelement[_cursorNumber]._inventoryrect.left, _invenotryelement[_cursorNumber]._inventoryrect.top, 40, 40);
		_cursor->setRc(_cursorrect);
		_cursor->getAni()->start();
	}
	if (KEYMANAGER->isOnceKeyDown('W'))			//위
	{
		int temp;
		temp = _cursorNumber;
		_cursorNumber -= 5;
		if (_cursorNumber < 0)  _cursorNumber = temp;
		_cursorrect = RectMake(_invenotryelement[_cursorNumber]._inventoryrect.left, _invenotryelement[_cursorNumber]._inventoryrect.top, 40, 40);
		_cursor->setRc(_cursorrect);
		_cursor->getAni()->start();

	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		int temp;
		temp = _cursorNumber;
		_cursorNumber += 5;
		if (_cursorNumber > 20) _cursorNumber = temp;
		_cursorrect = RectMake(_invenotryelement[_cursorNumber]._inventoryrect.left, _invenotryelement[_cursorNumber]._inventoryrect.top, 40, 40);
		_cursor->setRc(_cursorrect);
		_cursor->getAni()->start();
	}
	grabmove();
}

void inventory::inventoryItem()				//인벤토리 요소칸(_invenotryelement[i])과 벡터 (_vInven[i])칸의 위치를 동일시키기 위한 함수
{
	if (_openinventorywin || _storageOpen)
	{
		for (int i = 0; i < 21; i++)
		{
			if (i < _vInven.size())		//벡터 인벤토리 칸 전체 크기 조건 
				_vInven[i].setRect(_invenotryelement[i]._inventoryrect); // 인벤토리 칸 요소 위치 = 벡터 인벤토리 칸 위치를 동일 시킴
			for (int j = _vInven.size(); j < 21; j++)
			{
				_vInven.push_back(ITEMMANAGER->addItem("비어있음"));
			}
		}
	}
}

void inventory::grabmove()
{
	for (int i = 0; i < _vInven.size(); i++)			//벡터 사이즈를 for문으로 돌고  
	{
		if (_vInven[i].getItemInfo().itemName != "비어있음")  // 조건으로 비어있지 않은 칸을 확인한다.
		{
			if ((_cursorNumber == i) && KEYMANAGER->isOnceKeyDown('J'))   //커서 번호(_cursorNumber)와 벡터 요소 i와 겹치면  J누른다
			{
				_cursor->getAni()->start();
				if (_vTemp.empty())
				{
					_vTemp.push_back(_vInven[i]); //임시로 담을 벡터에 인벤토리에 있던 벡터 요소를 담는다. 
					_vTemp[0].setItemCnt_equal(1);
					_vInven[i].setItemCnt(-1);
					break;
				}
				if (_vTemp[0].getItemInfo().itemName == _vInven[i].getItemInfo().itemName &&
					(_vInven[i].getItemInfo().cnt + _vTemp[0].getItemInfo().cnt) <= _vTemp[0].getItemInfo().maxCnt)
				{
					_vTemp[0].setItemCnt();
					_vInven[i].setItemCnt(-1);
					break;
				}
			}
		}
		if (!_vTemp.empty())     //삭제
		{
			if (i < 20)
			{
				if (_vInven[i].getItemInfo().itemName == "비어있음")
				{
					if ((_cursorNumber == i) && KEYMANAGER->isOnceKeyDown('J'))
					{
						_cursor->getAni()->start();

						_vInven.erase(_vInven.begin() + i);
						_vInven.insert(_vInven.begin() + i, _vTemp[0]);
						_vTemp.pop_back();
						break;
					}
				}
			}
			else   // 20 칸이면 삭제 처리
			{
				//쓰레기통
				if (_vInven[i].getItemInfo().itemName == "비어있음")
				{
					if ((_cursorNumber == i) && KEYMANAGER->isOnceKeyDown('J'))
					{
						_cursor->getAni()->start();

						PLAYER->sellplayermoney((_vTemp[0].getItemInfo().cnt*_vTemp[0].getItemInfo().orignalPrice) / 5);
						_vInven.erase(_vInven.begin() + i);
						_vInven.insert(_vInven.begin() + i, ITEMMANAGER->addItem("비어있음"));
						_vTemp.pop_back();
						break;
					}
				}
			}
		}
	}
}

void inventory::grabitemremove()
{
	for (int i = 0; i < _vInven.size(); i++)
	{
		if (_vInven[i].getItemInfo().cnt == 0)
		{
			_vInven.erase(_vInven.begin() + i);
			_vInven.insert(_vInven.begin() + i, ITEMMANAGER->addItem("비어있음"));
		}
	}
}

void inventory::isweaponing()
{
	if (!_isweapon)
	{
		if (KEYMANAGER->isOnceKeyDown('O'))					//임시로 
		{
			_isweapon = true;
		}
	}
	else
	{
		if (KEYMANAGER->isOnceKeyDown('O'))					//임시로 
		{
			_isweapon = false;
		}
	}
}

void inventory::swapItem(item swapItem)
{
	_vTemp.push_back(swapItem);
	_vTemp[0].setRect(_invenotryelement[4]._inventoryrect);
	_cursor->setRc(_invenotryelement[4]._inventoryrect);
}


void inventory::render(HDC hdc)						// 랜더 순서 -> render>moverender()> bgrender()
{
	if (_openinventorywin)
	{
		bkrender(hdc);
		itemrender(hdc);//아이템 저장소 
		_cursor->render();				//커서 클래스 랜더 
	}
	//storageopen 이랑 연결된 인벤토리
	if (_storageOpen)
	{
		moverender(hdc);
	}
}				//render()의 끝

void inventory::moverender(HDC hdc)
{
	if (_storageOpen || _openinventorywin)
	{
		char str[128];
		char moneystr[128];					//플레이어 돈 
		_inventorybg._inventoryimg->render(hdc, _inventorybg.x, _inventorybg.y);
		IMAGEMANAGER->render("돋보기", hdc, _removeGlass._inventoryrect.left, _removeGlass._inventoryrect.top);

		wsprintf(moneystr, "%d", PLAYER->getMoney());					//현재 가지고 있는 돈 
		SetTextColor(hdc, RGB(41, 41, 41));					// 색 지정
		TextOut(hdc, 285, 540, moneystr, strlen(moneystr));			// 위치 조정 


		for (int i = 0; i < 21; i++)				//요소 크기 설정
		{
			IMAGEMANAGER->render("요소", hdc, _invenotryelement[i]._inventoryrect.left, _invenotryelement[i]._inventoryrect.top);
		}
		itemrender(hdc);
		for (int i = 0; i < _vInven.size(); i++) // 인벤토리 안에 아이템을 보여주는 for문 
		{
			if (_vInven[i].getItemInfo().itemName != "비어있음")     // 아이템이 있으면
			{
				//if (i==5 && i ==6 && i ==12&& i==19)
				//{
				wsprintf(str, "%d", _vInven[i].getItemInfo().cnt);
				SetTextColor(hdc, RGB(41, 41, 41));
				TextOut(hdc, _vInven[i].getRECT().right, _vInven[i].getRECT().bottom, str, strlen(str));
				SetBkMode(hdc, TRANSPARENT);				//글자 뒷배경 처리
			//	}
							//충돌처리
				if (IntersectRect(&_temp, &_cursorrect, &_vInven[i].getRECT()))
				{
					_vInven[i].getItemInfo().image->render(hdc, _showitem._showitemrc.left + 10, _showitem._showitemrc.top + 10);
				}
			}
		}
		if (_openinventorywin)_cursor->render();					//플레이어가 가지고 있는 인벤토리안에 있는 커서만 뜰 수 있게금
		if (test) _cursor->render();												//창고랑 인벤토리랑 연결될 부분
	}
}

void inventory::bkrender(HDC hdc)									//이미지만 붙이기 위한 것들 별로 필요없는 것들 
{
	if (_openinventorywin)
	{
		char str[128];
		_bgimag->alphaRender(hdc, 1000);   // 알파랜더 처리할 배경화면
		_playerinventory._inventoryimg->render(hdc, _playerinventory._inventoryrect.left, _playerinventory._inventoryrect.top);   //플레이어 인벤토리

		IMAGEMANAGER->render("Z버튼", getMemDC(), _zbutton.x, _zbutton.y);
		IMAGEMANAGER->render("z버전비활성화왼", hdc, _weaponiright.x, _weaponiright.y);
		IMAGEMANAGER->render("z비활성화오", hdc, _weaponileft.x, _weaponileft.y);
		if (!_isweapon)
		{
			IMAGEMANAGER->render("z버전활성화왼", getMemDC(), _weaponilefting.x, _weaponilefting.y);
		}
		if (_isweapon)
		{
			IMAGEMANAGER->render("z활성화오", getMemDC(), _weaponirighting.x, _weaponirighting.y);
		}

		_showitem._showitemimg->render(hdc, _showitem._showitemrc.left, _showitem._showitemrc.top, _showitem._showitemimg->getWidth(), _showitem._showitemimg->getHeight());					 //선택한 아이템을 보여주는 이미지.  
	}

}

void inventory::itemrender(HDC hdc)  //item벡터만 넣을 랜더들
{
	for (_viInven = _vInven.begin(); _viInven != _vInven.end(); ++_viInven)
	{
		(*_viInven).render();
	}

	if (_vTemp.size() > 0)					//임시 커서 그랩 뜨는 것
	{
		char str[128];
		_grab._grabimg->render(hdc, _cursorrect.left - 4, _cursorrect.top - 50);
		_vTemp[0].getItemInfo().image->render(hdc, _cursorrect.left - 4, _cursorrect.top - 40);
		wsprintf(str, "%d", _vTemp[0].getItemInfo().cnt);
		SetTextColor(hdc, RGB(41, 41, 41));
		TextOut(hdc, _cursorrect.right, _cursorrect.top - 40, str, strlen(str));
	}
}
