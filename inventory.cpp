#include "stdafx.h"
#include "inventory.h"


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

	//돈주머니 위치 이미지
	_moneyicon._inventoryimg = IMAGEMANAGER->findImage("돈주머니");
	_moneyicon.x = 270;
	_moneyicon.y = 480;

	//아이템을 돈으로 반환하는 이미지
	_removeGlass._inventoryimg = IMAGEMANAGER->findImage("돋보기");
	_removeGlass.x = 170;
	_removeGlass.y = 550;
	_removeGlass._inventoryrect = RectMakeCenter(_removeGlass.x, _removeGlass.y, _removeGlass._inventoryimg->getWidth(), _removeGlass._inventoryimg->getHeight());

	//템 보여주는 곳
	_showitem._showitemimg = IMAGEMANAGER->findImage("템보여주기");					//아이템 클릭하면 뜨는 원 오른쪽 끝에 있음
	_showitem._showitemrc = RectMakeCenter(WINSIZEX - 70, WINSIZEY / 2, _showitem._showitemimg->getWidth(), _showitem._showitemimg->getHeight());
	//bkrender()에 들어가는 이미지들
	//============================================================================================================

	//인벤토리 요소들
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			_invenotryelement[0].x = 210;
			_invenotryelement[0].y = 250;
			_invenotryelement[i + 5 * j]._inventoryrect = RectMakeCenter(_invenotryelement[0].x + i * 55, _invenotryelement[0].y + j * 60, 40, 40);	 // 디버깅 상으로 1~2번째 줄 인벤토리 요소는
			if (j >= 2)   // 디버깅 상 3~4번째 줄 인벤토리 요소는
			{
				_invenotryelement[i + 5 * j]._inventoryimg = IMAGEMANAGER->findImage("요소");										// 인벤토리 요소 불러오기 이미지  
				_invenotryelement[i + 5 * j]._inventoryrect = RectMakeCenter(_invenotryelement[0].x + i * 55, _invenotryelement[0].y + j * 60, 40, 40);				//인벤토리 위치 설정
			}
		}
	}
	_invenotryelement[20]._inventoryrect = RectMakeCenter((_removeGlass._inventoryrect.left + _removeGlass._inventoryrect.right) / 2 + 15, (_removeGlass._inventoryrect.top + _removeGlass._inventoryrect.bottom) / 2 - 22, 40, 40);			// 아이템을 돈으로 반환하는 인벤토리 요소 돋보기위치

	//커서 클래스 이용하기
	_cursor = new cursor;
	_cursor->init();
	_cursorNumber = 0;
	_cursorrect = _invenotryelement[_cursorNumber]._inventoryrect;

	//커서 그랩
	_grab._grabimg = IMAGEMANAGER->addImage("커서그랩", "images/shop/grab.bmp", 50, 52, true, RGB(255, 0, 255));


	_openinventorywin = false;
	_itemcount = 0;



	//임시용으로 만듬 
	_vInven.push_back(ITEMMANAGER->addItem("나뭇가지"));// 임시로 추가해 놓은 것 
	_vInven.push_back(ITEMMANAGER->addItem("강화수정"));// 임시로 추가해 놓은 것 
	_vInven.push_back(ITEMMANAGER->addItem("쇠막대기"));// 임시로 추가해 놓은 것 
	_vInven.push_back(ITEMMANAGER->addItem("덩쿨"));// 임시로 추가해 놓은 것 
	_vInven.push_back(ITEMMANAGER->addItem("천"));// 임시로 추가해 놓은 것 
	_vInven[4].setItemCnt(5);
	_vInven.push_back(ITEMMANAGER->addItem("천"));// 임시로 추가해 놓은 것 
	_vInven[5].setItemCnt(4);


	return S_OK;
}
void inventory::release()
{

}

void inventory::update()
{
	ANIMATIONMANAGER->update();				//커서 애니메이션 움직이기 위한 매니저 함수 
	if (!_openinventorywin)   // 인벤토리 비활성화
	{
		if (KEYMANAGER->isOnceKeyDown('I')) { _openinventorywin = true; } // 인벤토리활성화
	}
	else // 인벤토리활성화
	{
		if (KEYMANAGER->isOnceKeyDown('I')) // 인벤토리활성화
			_openinventorywin = false;
		cursormove();//커서 움직이기 
		inventoryItem();
		grabitemremove();  //J를 눌렀을 때 아이템을 빼기


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
		if (_cursorNumber > 20) _cursorNumber = 20;
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
	if (_openinventorywin)
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
					//_vInven.erase(_vInven.begin() + i);
					//_vInven.insert(_vInven.begin() + i, ITEMMANAGER->addItem("비어있음"));
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

void inventory::moneyitem()					//아이템 삭제
{
	for (int i = 0; i < _vInven.size(); i++)
	{
		if (_vTemp.size() > 0)
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
	}
}


void inventory::render()
{
	if (_openinventorywin)
	{
		bkrender();
		char str[128];


		for (int i = 0; i < 21; i++)				//요소 크기 설정
		{
			IMAGEMANAGER->render("요소", getMemDC(), _invenotryelement[i]._inventoryrect.left, _invenotryelement[i]._inventoryrect.top);
		}
		_cursor->render();				//커서 클래스 랜더 
		for (int i = 0; i < _vInven.size(); i++) // 인벤토리 안에 아이템을 보여주는 for문 
		{
			if (_vInven[i].getItemInfo().itemName != "비어있음")     // 아이템이 있으면
			{
				wsprintf(str, "%d", _vInven[i].getItemInfo().cnt);
				SetTextColor(getMemDC(), RGB(41, 41, 41));
				TextOut(getMemDC(), _vInven[i].getRECT().right, _vInven[i].getRECT().bottom, str, strlen(str));
				SetBkMode(getMemDC(), TRANSPARENT);				//글자 뒷배경 처리
				//충돌처리
				if (IntersectRect(&_temp, &_cursorrect, &_vInven[i].getRECT()))
				{
					_vInven[i].getItemInfo().image->render(getMemDC(), _showitem._showitemrc.left + 10, _showitem._showitemrc.top + 10);    //충돌된 상태에 
				}
			}
		}
		//아이템 저장소 
		itemrender();
	}
}				//render()의 끝

void inventory::bkrender()									//이미지만 붙이기 위한 것들 별로 필요없는 것들 
{
	if (_openinventorywin)
	{
		char moneystr[128];					//플레이어 돈 
		_bgimag->alphaRender(getMemDC(), 1000);   // 알파랜더 처리할 배경화면
		_playerinventory._inventoryimg->render(getMemDC(), _playerinventory._inventoryrect.left, _playerinventory._inventoryrect.top);   //플레이어 인벤토리
		IMAGEMANAGER->render("돈주머니", getMemDC(), _moneyicon.x, _moneyicon.y);

		IMAGEMANAGER->render("돋보기", getMemDC(), _removeGlass._inventoryrect.left, _removeGlass._inventoryrect.top);

		_showitem._showitemimg->render(getMemDC(), _showitem._showitemrc.left, _showitem._showitemrc.top, _showitem._showitemimg->getWidth(), _showitem._showitemimg->getHeight());					 //선택한 아이템을 보여주는 이미지.  

		wsprintf(moneystr, "%d", PLAYER->getMoney());					//현재 가지고 있는 돈 
		SetTextColor(getMemDC(), RGB(41, 41, 41));					// 색 지정
		TextOut(getMemDC(), 304, 540, moneystr, strlen(moneystr));			// 위치 조정 
	}
}

void inventory::itemrender()  //item벡터만 넣을 랜더들
{
	for (_viInven = _vInven.begin(); _viInven != _vInven.end(); ++_viInven)
	{
		(*_viInven).render();
	}

	if (_vTemp.size() > 0)
	{
		char str[128];
		_grab._grabimg->render(getMemDC(), _cursorrect.left - 4, _cursorrect.top - 50);
		_vTemp[0].getItemInfo().image->render(getMemDC(), _cursorrect.left - 4, _cursorrect.top - 40);
		wsprintf(str, "%d", _vTemp[0].getItemInfo().cnt);
		SetTextColor(getMemDC(), RGB(41, 41, 41));
		TextOut(getMemDC(), _cursorrect.right, _cursorrect.top - 40, str, strlen(str));
	}
}
