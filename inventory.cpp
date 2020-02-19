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

	//아이템을 돈으로 반환하는 이미지
	_removeGlass._inventoryimg = IMAGEMANAGER->findImage("돋보기");
	_removeGlass.x = 170;
	_removeGlass.y = 550;
	_removeGlass._inventoryrect = RectMakeCenter(_removeGlass.x, _removeGlass.y, _removeGlass._inventoryimg->getWidth(), _removeGlass._inventoryimg->getHeight());

	//템 보여주는 곳
	_showitem._showitemimg = IMAGEMANAGER->findImage("템보여주기");					//아이템 클릭하면 뜨는 원 오른쪽 끝에 있음
	_showitem._showitemrc = RectMakeCenter(WINSIZEX - 70, 250, _showitem._showitemimg->getWidth(), _showitem._showitemimg->getHeight());

	_zbutton._inventoryimg = IMAGEMANAGER->findImage("Z버튼");

	_weaponiright._inventoryimg = IMAGEMANAGER->findImage("z비활성화오");

	_weaponileft._inventoryimg = IMAGEMANAGER->findImage("z버전활성화왼");

	//z버전활성화왼,
	_weaponirighting._inventoryimg = IMAGEMANAGER->findImage("z버전활성화왼");

	//활성화오
	_weaponilefting._inventoryimg = IMAGEMANAGER->findImage("z활성화오");

	_playerprofile._inventoryimg = IMAGEMANAGER->findImage("프로필");

	//bkrender()에 들어가는 이미지들
	//============================================================================================================
	_inventorybg._inventoryimg = IMAGEMANAGER->findImage("인벤토리종이");
	_inventorybg.x = WINSIZEX / 2 - 410;
	_inventorybg.y = WINSIZEY / 2 - 215;

	//인벤토리 요소들
	//인벤토리(플레이어용&창고용)	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			_inventoryelement._inventoryimg = IMAGEMANAGER->findImage("요소");
			_inventoryelement.x = 190 + j * 55;
			_inventoryelement.y = 240 + i * 60;
			_inventoryelement._inventoryrect = RectMakeCenter(_inventoryelement.x, _inventoryelement.y, _inventoryelement._inventoryimg->getWidth(), _inventoryelement._inventoryimg->getHeight());
			_inventoryelement._item = ITEMMANAGER->addItem("비어있음");
			_inventoryelement._item.setRect(_inventoryelement._inventoryrect);
			_vInven.push_back(_inventoryelement);
		}
	}
	_vInven[0]._item = ITEMMANAGER->addItem("나뭇가지");

	//쓰레기통
	_inventoryelement._inventoryrect = RectMakeCenter((_removeGlass._inventoryrect.left + _removeGlass._inventoryrect.right) / 2 + 15, (_removeGlass._inventoryrect.top + _removeGlass._inventoryrect.bottom) / 2 - 30, 40, 40);
	_inventoryelement._item = ITEMMANAGER->addItem("비어있음");
	_inventoryelement._item.setRect(_inventoryelement._inventoryrect);
	_vInven.push_back(_inventoryelement);

	//인벤토리(플레이어용)
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			_inventoryelement._inventoryrect = RectMakeCenter(612 + j * 132, 240, 40, 40);
			if (i >= 1)
			{
				_inventoryelement._inventoryrect = RectMakeCenter(555 + j * 50, 260 + i * 50, 40, 40);
			}
			_inventoryelement._item = ITEMMANAGER->addItem("비어있음");
			_inventoryelement._item.setRect(_inventoryelement._inventoryrect);
			_vInven.push_back(_inventoryelement);
		}
	}
	_vInven[21]._item = ITEMMANAGER->addItem("훈련용 단검");
	_vInven[22]._item = ITEMMANAGER->addItem("플레임 보우");
	_vInven[26]._item = ITEMMANAGER->addItem("작은 포션");
	_vInven[26]._item.setItemCnt(5);

	//커서 클래스 이용하기
	_cursor = new cursor;
	_cursor->init();
	_cursorNumber = 0;
	_cursorrect = _vInven[_cursorNumber]._inventoryrect;
	_cursor->setRc(_cursorrect);

	_grab._grabimg = IMAGEMANAGER->addImage("커서그랩", "images/shop/grab.bmp", 50, 52, true, RGB(255, 0, 255));

	_storageusing = true;				//아이템 창고 이용하기 위한 불값 bool test에서 대처
	_storageOpen = false;				//창고랑 
	_isweapon = false;					//무기 전환하기 위한 불값.. 이미지로만
	_openinventorywin = false;
	return S_OK;
}

void inventory::release()
{
	SAFE_DELETE(_cursor);
}

void inventory::update()
{
	ANIMATIONMANAGER->update();
	// 인벤토리 비활성화
	if (!_openinventorywin)
	{
		if (KEYMANAGER->isOnceKeyDown('6'))
		{
			_openinventorywin = true;
			_cursor->update(_cursorrect);
			_cursorNumber = 0;
			_cursorrect = _vInven[_cursorNumber]._inventoryrect;
			_cursor->setRc(_cursorrect);
		}
	}
	//인벤토리 활성화
	else
	{
		if (KEYMANAGER->isOnceKeyDown('6'))
		{
			_openinventorywin = false;
		}
		cursormove();														//커서 움직이기
		inventoryItem();
		grabitemremove();												 //J를 눌렀을 때 아이템을 빼기
		isweaponing();														//무기 체인지
	}
}
// 인벤토리 세팅하는 곳 오고가고 바꾸는 곳
void inventory::inventoryItem()
{
	for (int i = 0; i < 28; i++)
	{
		if (i < _vInven.size())
		{
			_vInven[i]._item.setRect(_vInven[i]._inventoryrect);
		}
	}
}

//커서 움직임
void inventory::cursormove()
{
	_cursor->update(_cursorrect);
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		_cursorNumber--;
		if (_cursorNumber < 0) _cursorNumber = 0;
		_cursorrect = RectMake(_vInven[_cursorNumber]._inventoryrect.left, _vInven[_cursorNumber]._inventoryrect.top, 40, 40);
		_cursor->setRc(_cursorrect);
		_cursor->getAni()->start();
	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		_cursorNumber++;
		if (_storageOpen)
		{
			if (_cursorNumber > 19)
			{
				_storageusing = false;
				_cursorNumber = 0;

			}
		}
		else						//인벤토리(플레이어용)
		{
			if (_cursorNumber < 28);
		}

		_cursorrect = RectMake(_vInven[_cursorNumber]._inventoryrect.left, _vInven[_cursorNumber]._inventoryrect.top, 40, 40);
		_cursor->setRc(_cursorrect);
		_cursor->getAni()->start();
	}
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		int temp = _cursorNumber;
		_cursorNumber -= 5;
		if (_cursorNumber > 0) 	_cursorNumber = temp;
		if (_cursorNumber < 0) _cursorNumber = temp;
		_cursorrect = RectMake(_vInven[_cursorNumber]._inventoryrect.left, _vInven[_cursorNumber]._inventoryrect.top, 40, 40);
		_cursor->setRc(_cursorrect);
		_cursor->getAni()->start();
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		if (!_storageOpen)
		{
			if (_cursorNumber < 25) _cursorNumber += 5;
		}
		else
		{
			if (_cursorNumber < 20)_cursorNumber += 5;
		}
		_cursorrect = RectMake(_vInven[_cursorNumber]._inventoryrect.left, _vInven[_cursorNumber]._inventoryrect.top, 40, 40);
		_cursor->setRc(_cursorrect);
		_cursor->getAni()->start();
	}
	grabmove();
}

void inventory::grabmove()
{
	for (int i = 0; i < _vInven.size(); i++)			//벡터 사이즈를 for문으로 돌고  
	{
		if (_vInven[i]._item.getItemInfo().itemName != "비어있음")  // 조건으로 비어있지 않은 칸을 확인한다.
		{
			if ((_cursorNumber == i) && KEYMANAGER->isOnceKeyDown('J'))   //커서 번호(_cursorNumber)와 벡터 요소 i와 겹치면  J누른다
			{
				_cursor->getAni()->start();
				if (_vTemp.empty())
				{
					_vTemp.push_back(_vInven[i]); //임시로 담을 벡터에 인벤토리에 있던 벡터 요소를 담는다. 
					_vTemp[0]._item.setItemCnt_equal(1);
					_vInven[i]._item.setItemCnt(-1);
					break;
				}
				if (_vTemp[0]._item.getItemInfo().itemName == _vInven[i]._item.getItemInfo().itemName &&
					(_vInven[i]._item.getItemInfo().cnt + _vTemp[0]._item.getItemInfo().cnt) <= _vTemp[0]._item.getItemInfo().maxCnt)
				{
					_vTemp[0]._item.setItemCnt(1);
					_vInven[i]._item.setItemCnt(-1);
					break;
				}
			}
		}
		if (!_vTemp.empty())											//빈값이 아니라면
		{
			if (i != 20)															//		i일 경우
			{
				if (_vInven[i]._item.getItemInfo().itemName == "비어있음")
				{
					if ((_cursorNumber == i) && KEYMANAGER->isOnceKeyDown('J'))
					{
						_cursor->getAni()->start();
						_vInven[i]._item = _vTemp[0]._item;
						_vTemp.pop_back();
						break;
					}
				}
			}
			else // 20 칸이면 삭제 처리
			{
				//쓰레기통
				if (_vInven[i]._item.getItemInfo().itemName == "비어있음")
				{
					if ((_cursorNumber == i) && KEYMANAGER->isOnceKeyDown('J'))
					{
						_cursor->getAni()->start();
						PLAYER->sellplayermoney((_vTemp[0]._item.getItemInfo().cnt*_vTemp[0]._item.getItemInfo().orignalPrice) / 5);
						_vInven[20]._item = ITEMMANAGER->addItem("비어있음");
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
		if (_vInven[i]._item.getItemInfo().cnt == 0)
		{
			_vInven[i]._item.setItemCnt_equal(-1);
			_vInven[i]._item = ITEMMANAGER->addItem("비어있음");
		}
	}
}

//무기활 성화 or 무기 비활성화
void inventory::isweaponing()
{
	if (!_isweapon)
	{
		if (KEYMANAGER->isOnceKeyDown('Z'))					//임시로 
		{
			_isweapon = true;
		}
	}
	else
	{
		if (KEYMANAGER->isOnceKeyDown('Z'))					//임시로 
		{
			_isweapon = false;
		}
	}
}

void inventory::resetelement()
{
	_inventoryelement._item = ITEMMANAGER->addItem("비어있음");
	_vInven.push_back(_inventoryelement);
}
//_vTemp[0].clear() 들어있음
void inventory::tempRelass()
{
	_vTemp.clear();
}
//아이템 포션 있는지 없는지 사용가능한지?
void inventory::itempotion()
{
	if (0 < _vInven[26]._item.getItemInfo().cnt)					//수량이 0보다 많으면
	{
		//PLAYER->setHP( _vInven[26]._item.getItemInfo().hp);				//피 량을 늘려준다
		PLAYER->setHP(100);				//피 량을 늘려준다
		_vInven[26]._item.setItemCnt(-1);
		if (_vInven[26]._item.getItemInfo().cnt == 0)
		{
			_vInven[26]._item = ITEMMANAGER->addItem("비어있음");
		}
	}
}
//아이템 먹기
void inventory::eatitem(item _item)
{
	for (int i = 0; i < _vInven.size(); i++)
	{
		if (_vInven[i]._item.getItemInfo().itemName == "비어있음")
		{

			_vInven[i]._item = _item;
			//_vInven.push_back(_vInven[i]);
			break;
		}
	}
}

void inventory::swapItem(item swapItem)
{
	_inventoryelement._item = swapItem;
	_vTemp.push_back(_inventoryelement);
	_cursor->setRc(_vInven[0]._inventoryrect);
}

void inventory::render(HDC hdc)							// 랜더 순서 -> render>moverender()> bgrender()
{
	if (_openinventorywin)
	{
		bkrender(hdc);
		moverender(hdc);
		_cursor->render();				//커서 클래스 랜더 
	}
	//storageopen 이랑 연결된 인벤토리
	if (_storageOpen)
	{
		moverender(hdc);
	}
}

//배경화면 랜더
void inventory::bkrender(HDC hdc)
{
	char str[128];
	char strspeed[128];				//스피드 텍스트용
	char strshield[128];				//방패 텍스트용
	char strattack[128];				//어택용 텍스트용			
	_bgimag->alphaRender(hdc, 1000);   // 알파랜더 처리할 배경화면
	_playerinventory._inventoryimg->render(hdc, _playerinventory._inventoryrect.left, _playerinventory._inventoryrect.top);   //플레이어 인벤토리

	IMAGEMANAGER->render("Z버튼", getMemDC(), 660, 225);
	IMAGEMANAGER->render("z버전비활성화왼", hdc, 637, 235);
	IMAGEMANAGER->render("z비활성화오", hdc, 700, 235);
	if (!_isweapon)
	{
		IMAGEMANAGER->render("z버전활성화왼", getMemDC(), 637, 235);
	}
	if (_isweapon)
	{
		IMAGEMANAGER->render("z활성화오", getMemDC(), 700, 235);
	}
//	_showitem._showitemimg->render(hdc, _showitem._showitemrc.left, _showitem._showitemrc.top, _showitem._showitemimg->getWidth(), _showitem._showitemimg->getHeight());					 //선택한 아이템을 보여주는 이미지.  
	for (int i = 0; i <= _vInven.size(); i++)									//장비만 있는 곳
	{
		if (21 <= i && i <= 28)
		{
			_vInven[i]._item.render();
			_vInven[i]._inventoryimg->render(hdc, _vInven[i]._inventoryrect.left, _vInven[i]._inventoryrect.top);
		}
	}
	IMAGEMANAGER->render("프로필", getMemDC(), WINSIZEX / 2 + 130, WINSIZEY / 2 - 97);
	PLAYER->invenRender(getMemDC());

	wsprintf(str, "%d", PLAYER->getHP());															//체력
	SetTextColor(hdc, RGB(255, 255, 255));
	TextOut(hdc, WINSIZEX / 2 + 340, WINSIZEY / 2 - 65, str, strlen(str));

	wsprintf(strattack, "%d", PLAYER->getattskill());															//공격력
	SetTextColor(hdc, RGB(255, 255, 255));
	TextOut(hdc, WINSIZEX / 2 + 340, WINSIZEY / 2 - 18, strattack, strlen(strattack));

	wsprintf(strshield, "%d", PLAYER->getshield());															//방패
	SetTextColor(hdc, RGB(255, 255, 255));
	TextOut(hdc, WINSIZEX / 2 + 340, WINSIZEY / 2 + 30, strshield, strlen(strshield));

	wsprintf(strspeed, "%d", PLAYER->getspeed());															//스피드
	SetTextColor(hdc, RGB(255, 255, 255));
	TextOut(hdc, WINSIZEX / 2 + 340, WINSIZEY / 2 + 75, strspeed, strlen(strspeed));

}

//(인벤토리(플레이어용) & 인벤토리(창고용))
void inventory::moverender(HDC hdc)
{
	if (_storageOpen || _openinventorywin)
	{
		char str[128];
		char moneystr[128];					//플레이어 돈 
		_inventorybg._inventoryimg->render(hdc, WINSIZEX / 2 - 410, WINSIZEY / 2 - 215);
		IMAGEMANAGER->render("돋보기", hdc, _removeGlass._inventoryrect.left, _removeGlass._inventoryrect.top);

		wsprintf(moneystr, "%d", PLAYER->getMoney());					//현재 가지고 있는 돈 
		SetTextColor(hdc, RGB(41, 41, 41));					// 색 지정
		TextOut(hdc, 285, 540, moneystr, strlen(moneystr));			// 위치 조정 
		itemrender(hdc);
		for (int i = 0; i < _vInven.size(); i++)						// 인벤토리 안에 아이템을 보여주는 for문 
		{
			if (_vInven[i]._item.getItemInfo().itemName != "비어있음")
			{
				if (i < 21)
				{
					wsprintf(str, "%d", _vInven[i]._item.getItemInfo().cnt);
					SetTextColor(hdc, RGB(41, 41, 41));
					TextOut(hdc, _vInven[i]._item.getRECT().right, _vInven[i]._item.getRECT().bottom, str, strlen(str));
					SetBkMode(hdc, TRANSPARENT);				//글자 뒷배경 처리
				}
			}
		}
		if (_openinventorywin)_cursor->render();					//플레이어가 가지고 있는 인벤토리안에 있는 커서만 뜰 수 있게금
		if (_storageusing) _cursor->render();
	}
}

//아이템만 생성되는 랜더 
void inventory::itemrender(HDC hdc)
{
	for (int i = 0; i < _vInven.size(); i++)
	{
		if (i < 21)
		{
			_vInven[i]._item.render();
			_vInven[i]._inventoryimg->render(hdc, _vInven[i]._inventoryrect.left, _vInven[i]._inventoryrect.top);
		}
	}
	if (_vTemp.size() > 0)					//임시 커서 그랩 뜨는 것
	{
		char str[128];
		_grab._grabimg->render(hdc, _cursorrect.left - 4, _cursorrect.top - 50);
		_vTemp[0]._item.getItemInfo().image->render(hdc, _cursorrect.left - 4, _cursorrect.top - 40);
		wsprintf(str, "%d", _vTemp[0]._item.getItemInfo().cnt);
		SetTextColor(hdc, RGB(41, 41, 41));
		TextOut(hdc, _cursorrect.right, _cursorrect.top - 40, str, strlen(str));
	}
}