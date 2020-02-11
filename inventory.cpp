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
	_grab._isopen = false;

	_openinventorywin = false;
	_itemcount = 0;

	//for (int i = 0; i < 20; i++) // 사이즈 초기화 임시로 넣음
	//{
	//	_vInven.push_back(ITEMMANAGER->addItem("덩쿨"));						//덩쿨 있음

	//}

	return S_OK;
}
void inventory::release()
{

}

void inventory::update()
{
	inventoryItem();

	for (_viInven = _vInven.begin(); _viInven != _vInven.end(); ++_viInven)  //임시로 추가해놓음
	{
		_vInven[0].setRect(_invenotryelement[0]._inventoryrect.left + 22, _invenotryelement[0]._inventoryrect.top + 22);
	}

		//_cursor->update();
	if (!_openinventorywin)   // 인벤토리 비활성화
	{
		if (KEYMANAGER->isOnceKeyDown('I'))				//I 인벤토리 누르기
		{
			_openinventorywin = true; // 인벤토리활성화
	  cursormove();
		}
	}
	else  // 인벤토리활성화
	{
		if (KEYMANAGER->isOnceKeyDown('I'))
		{
			_openinventorywin = false;    // 인벤토리 비활성화
		}
	}
	ANIMATIONMANAGER->update();
	cursormove();  //커서 이동 

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
	if (KEYMANAGER->isOnceKeyDown('J'))
	{
		_grab._isopen = true;
		/*
		if (_grab._isopen)
		{
		}

		_itemcount++;

		if()//일치한다
		{

		}

		*/
	}
	grabmove();
}

void inventory::grabmove()
{


}

void inventory::moneyitem()
{
}

void inventory::inventoryItem()				//인벤토리 요소칸(_invenotryelement[i])과 벡터 (_vInven[i])칸의 위치를 동일시키기 위한 함수
{
	if (_openinventorywin)
	{
		for (int i = 0; i < 20; i++)
		{
			if (i < _vInven.size())		//벡터 인벤토리 칸 전체 크기 조건 
				_vInven[i].setRect(_invenotryelement[i]._inventoryrect); // 인벤토리 칸 요소 위치 = 벡터 인벤토리 칸 위치를 동일 시킴

			for (int j = _vInven.size(); j < 21; j++)
			{
				_vInven.push_back(ITEMMANAGER->addItem("비어있음"));   // 22칸을 모두 비어있는 요소를 전부 비어있음으로 처리한다.
			}
		}
	}

}
void inventory::render()
{
	if (_openinventorywin)
	{
	char str[128];
	char moneystr[128];					//플레이어 돈 
	_bgimag->alphaRender(getMemDC(), 1000);   // 알파랜더 처리할 배경화면
	_playerinventory._inventoryimg->render(getMemDC(), _playerinventory._inventoryrect.left, _playerinventory._inventoryrect.top);   //플레이어 인벤토리

	IMAGEMANAGER->render("돈주머니", getMemDC(), _moneyicon.x, _moneyicon.y);

	IMAGEMANAGER->render("돋보기", getMemDC(), _removeGlass._inventoryrect.left, _removeGlass._inventoryrect.top);

	for (int i = 0; i < 21; i++)
	{
		IMAGEMANAGER->render("요소", getMemDC(), _invenotryelement[i]._inventoryrect.left, _invenotryelement[i]._inventoryrect.top);
	}

	for (int i = 0; i < _vInven.size(); i++) // 인벤토리 안에 아이템을 보여주는 for문 
	{
		if (_vInven[i].getItemInfo().itemName != "비어있음")     // 아이템이 있으면
		{
			wsprintf(str, "%d", _vInven[i].getItemInfo().cnt);
			TextOut(getMemDC(), _vInven[i].getRECT().right, _vInven[i].getRECT().bottom, str, strlen(str));
			SetBkMode(getMemDC(), TRANSPARENT);				//글자 뒷배경 처리
			//충돌처리

		}
	}
	_cursor->render();


	//Rectangle(getMemDC(), _cursorrect.left, _cursorrect.top, _cursorrect.right, _cursorrect.bottom);
	if (KEYMANAGER->isToggleKey('1'))
	{
		Rectangle(getMemDC(), _cursorrect.left, _cursorrect.top, _cursorrect.right, _cursorrect.bottom);
		//Rectangle(getMemDC(), _invenotryelement[i]._inventoryrect.left, _invenotryelement[i]._inventoryrect.top, _invenotryelement[i]._inventoryrect.right, _invenotryelement[i]._inventoryrect.bottom);
	}


	if (_grab._isopen) //커서그랩 띄우기 위한 bool  true일  경우 띄어짐
	{
		_grab._grabimg->render(getMemDC(), _invenotryelement[_cursorNumber]._inventoryrect.left - 4, _invenotryelement[_cursorNumber]._inventoryrect.top - 50);

	}

	wsprintf(moneystr, "%d", PLAYER->getMoney());
	SetTextColor(CAMERAMANAGER->getCameraDC(), RGB(41, 41, 41));
	TextOut(CAMERAMANAGER->getCameraDC(), 304, 540, moneystr, strlen(moneystr));

	}
	itemrender();
}

void inventory::itemrender()  //item벡터만 넣을 랜더들
{
	for (_viInven = _vInven.begin(); _viInven != _vInven.end(); ++_viInven)
	{
		(*_viInven).render();
	}


}


/*
  인벤토리 설정
 덩쿨 10 나뭇가지 2개 쇠막대기 2 천 1 쇠막대기 1

*/