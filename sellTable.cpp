#include "stdafx.h"
#include "sellTable.h"

sellTable::sellTable() {}

sellTable::~sellTable()
{
}

HRESULT sellTable::init()
{
	_sellMainImg = IMAGEMANAGER->findImage("판매창");
	_selectUpdownImg = IMAGEMANAGER->findImage("위아래화살표");

	//렉트초기화
	_tableRc = RectMakeCenter(WINSIZEX / 2 - 350, WINSIZEY / 2 + 200, 100, 100);

	_slot[0] = RectMake(_sellMainImg->getWidth() + 83, _sellMainImg->getHeight() - 305, 40, 40);
	_slot[1] = RectMake(_sellMainImg->getWidth() + 312, _sellMainImg->getHeight() - 305, 40, 40);
	_slot[2] = RectMake(_sellMainImg->getWidth() + 83, _sellMainImg->getHeight() - 100, 40, 40);
	_slot[3] = RectMake(_sellMainImg->getWidth() + 312, _sellMainImg->getHeight() - 100, 40, 40);

	for (int i = 0; i < SLOTNUM; i++)
	{
		_slotImage[i] = IMAGEMANAGER->findImage("판매슬롯이미지");
		_sellInfo[i] = RectMakeCenter(_slot[i].left + (_slot[i].right - _slot[i].left) / 2, _slot[i].top + (_slot[i].bottom - _slot[i].top) / 2 + 80, 180, 90);
	}

	//커서 초기화
	_cursorNum = 0;
	_cursorSlot = _slot[_cursorNum];
	_cursor = new cursor;
	_cursor->init();
	_grab = new image;
	_grab = IMAGEMANAGER->findImage("커서그랩");
	_BoxChoiceNum = 7;

	//비어있음으로 초기화
	_vSellItem.push_back(ITEMMANAGER->addItem("나뭇가지"));
	_vSellItem.push_back(ITEMMANAGER->addItem("나뭇가지"));
	_vSellItem.push_back(ITEMMANAGER->addItem("비어있음"));
	_vSellItem.push_back(ITEMMANAGER->addItem("골렘코어"));
	_vSellItem[0].setItemCnt_equal(9);

	for (int i = 0; i < _vSellItem.size(); i++)
	{
		//판매테이블에 올려진 아이템은 위아래로 웨이브함
		_vSellItem[i].setWave(true);
	}
	_vSellItem[0].setRect(_tableRc.left + 30, _tableRc.top + 10);
	_vSellItem[1].setRect(_tableRc.right - 30, _tableRc.top + 10);
	_vSellItem[2].setRect(_tableRc.left + 30, _tableRc.bottom - 40);
	_vSellItem[3].setRect(_tableRc.right - 30, _tableRc.bottom - 40);

	return S_OK;
}

void sellTable::release()
{
	SAFE_DELETE(_cursor);
}

void sellTable::update()
{
	for (int i = 0; i < _vSellItem.size(); i++)
	{
		_vSellItem[i].update();
	}
	if (!PLAYER->getinventory()->getTest()) cursorControl();   //-->커서컨트롤 WASD버튼
	else PLAYER->getinventory()->cursormove();				//-->커서컨트롤 WASD버튼

	playerCollision();
	cursorControl();
	selectPrice();
	removeItem();


	PLAYER->getinventory()->inventoryItem();
}

void sellTable::render()
{
	//아이템을 올려두는 테이블과 그 위에 놓여진 아이템 렌더
	IMAGEMANAGER->render("판매테이블", getMemDC(), _tableRc.left, _tableRc.top);
	PLAYER->getinventory()->moverender(getMemDC());
	for (int i = 0; i < _vSellItem.size(); i++)
	{
		_vSellItem[i].render();
	}

	//열기닫기
	if (!_showWindow)
	{
		if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &_tableRc))
		{
			IMAGEMANAGER->render("열기", getMemDC(), _tableRc.right, _tableRc.top - 20);
		}
	}

	//열렸을때
	if (_showWindow)
	{
		//_sellMainImg = 판매테이블 열면 뜨는 창
		_sellMainImg->render(getMemDC(), WINSIZEX / 2 - 70, 100, _sellMainImg->getWidth(), _sellMainImg->getHeight());

		//슬롯의 이미지와 템 가격,갯수,총가격 렌더 
		for (int i = 0; i < SLOTNUM; i++)
		{
			_slotImage[i]->render(getMemDC(), _slot[i].left, _slot[i].top);
			int k;
			k = i + 2;
			wsprintf(str, "%d", _playerPrice[i][0]);
			TextOut(getMemDC(), WINSIZEX / 2 + 100 + (k % 2 * 100), (k / 2 * 220) - 20, str, strlen(str));
			if (_vSellItem[i].getItemInfo().itemName != "비어있음")
			{
				wsprintf(str, "x%d", _vSellItem[i].getItemInfo().cnt);
				TextOut(getMemDC(), WINSIZEX / 2 + 100 + (k % 2 * 100), (k / 2 * 220) + 0, str, strlen(str));
			}
			wsprintf(str, "%d", _vSellItem[i].getItemInfo().cnt*_playerPrice[i][0]);
			TextOut(getMemDC(), WINSIZEX / 2 + 100 + (k % 2 * 100), (k / 2 * 220) + 20, str, strlen(str));
		}
		// 가격정하는 부분의 위아래 화살표
		if (_selectNum)_selectUpdownImg->render(getMemDC(), _selectUpdownRc.left, _selectUpdownRc.top);

		//슬롯 안에 들어가는 아이템 이미지
		for (int i = 0; i < _vSellItem.size(); i++)
		{
			_vSellItem[i].getItemInfo().image->render(getMemDC(), _slot[i].left, _slot[i].top);
		}

		if(_test)_cursor->render();
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

void sellTable::cursorControl()
{
	if (_showWindow)
	{
		//플레이어 인벤창에서 커서가 일정 칸을 넘어가면
		if (PLAYER->getinventory()->getcusornumber() > 18)
		{
			//플레이어상점의 커서 초기화. test는 커서의 렌더유무
			_cursorSlot = _slot[0];
			_test = true;

			//만약 인벤토리에서 아이템을 잡고 있는 상태라면 
			if (PLAYER->getinventory()->getvTemp().size() != 0)
			{
				//그 정보를 이쪽으로 가져오고 그쪽의 정보는 삭제.
				_vTemp.push_back(PLAYER->getinventory()->getvTemp()[0]);
				PLAYER->getinventory()->tempClear();
			}
		}
		if (KEYMANAGER->isOnceKeyDown('A'))
		{
			//커서가 옆으로 못나가게
			_cursorNum--;
			if (_cursorNum < 0)
			{
				_cursorNum = 0;

				//setTest가 true가 되면 인벤토리 창이 켜진다. test가 false가 되면 상점의 커서가 꺼짐
				PLAYER->getinventory()->setTest(true); 
				_test = false;

				//만약 상점에서 커서가 아이템을 잡은 상태라면
				if (_vTemp.size() != 0)
				{
					//인벤토리의 커서로 아이템을 보내주고 이쪽의 정보는 삭제.
					PLAYER->getinventory()->swapItem(_vTemp[0]);
					_vTemp.clear();
				}
			}
				
			//커서를 옆 칸으로 옮긴다
			_cursorSlot = RectMake(_slot[_cursorNum].left, _slot[_cursorNum].top, 40, 40);
			_cursor->setSmallCursor();		//커서 크기를 작게하는 함수
			_cursor->getAni()->start();
		}
		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			//커서가 옆으로 못나가게
			_cursorNum++;
			if (_cursorNum >= SLOTNUM) _cursorNum = SLOTNUM - 1;

			_cursorSlot = RectMake(_slot[_cursorNum].left, _slot[_cursorNum].top, 40, 40);
			_cursor->setSmallCursor();
			_cursor->getAni()->start();
		}

		//위로
		if (!IntersectRect(&temp, &_cursorSlot, &_sellInfo[_cursorNum]) && KEYMANAGER->isOnceKeyDown('W'))
		{
			//삐져나가기 방지용
			int temp;
			temp = _cursorNum;
			_cursorNum -= 2;


			if (_cursorNum < 0)
			{
				_cursorNum = temp;
				_cursorSlot = _slot[_cursorNum];	  //_slot - 아이템 올려놓는 렉트
			}
			else
			{
				_cursorSlot = _sellInfo[_cursorNum];  //_sellInfo - 아이템가격 정하는 렉트
				_cursor->setBigCursor();			  //커서 크기를 크게하는함수
			}

			_cursor->getAni()->start();
		}

		if (IntersectRect(&temp, &_cursorSlot, &_sellInfo[_cursorNum]) && KEYMANAGER->isOnceKeyDown('W'))
		{
			_cursorSlot = _slot[_cursorNum];
			_cursor->setSmallCursor();
			_cursor->getAni()->start();
		}

		//아래로
		if (!IntersectRect(&temp, &_cursorSlot, &_sellInfo[_cursorNum]) && KEYMANAGER->isOnceKeyDown('S'))
		{
			_cursorSlot = _sellInfo[_cursorNum];
			_cursor->update(_sellInfo[_cursorNum]);
			_cursor->setBigCursor();
			_cursor->getAni()->start();
		}

		if (IntersectRect(&temp, &_cursorSlot, &_sellInfo[_cursorNum]) && KEYMANAGER->isOnceKeyDown('S'))
		{
			int temp;
			temp = _cursorNum;
			_cursorNum += 2;

			if (_cursorNum >= 4)
			{
				_cursorNum = temp;
				_cursorSlot = _sellInfo[_cursorNum];
			}
			else
			{
				_cursorSlot = _slot[_cursorNum];
				_cursor->setSmallCursor();
			}
			_cursor->getAni()->start();
		}
		_cursor->setRc(_cursorSlot);


		//가격 정하는 렉트에서 J를 누르면 _selectNum이 true가 되어 가격을 정하는 함수로 넘어감
		if (IntersectRect(&temp, &_cursorSlot, &_sellInfo[_cursorNum]) && !_selectNum&& KEYMANAGER->isOnceKeyDown('J'))
		{
			_BoxChoiceNum = 7;
			_selectNum = true;
		}
		if (IntersectRect(&temp, &_cursorSlot, &_sellInfo[_cursorNum]) && _selectNum && KEYMANAGER->isOnceKeyDown('J'))
		{
			_selectNum = false;
		}

		//항시 가격을 업데이트해줌.
		_vSellItem[_cursorNum].setPlayerPrice(_playerPrice[_cursorNum][0]);
		grab();
	}
}

void sellTable::playerCollision()
{
	if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &_tableRc)) //열기닫기
	{
		if (!_showWindow)
		{
			if (KEYMANAGER->isOnceKeyDown('J'))
			{
				_showWindow = true;
				_test = true;
			PLAYER->getinventory()->setStprageOpen(true);
			//PLAYER->getinventory()->setTest(true);

			}
		}
		if (_showWindow)
		{
			if (KEYMANAGER->isOnceKeyDown('I'))
			{
				_showWindow = false;
				_test = false;
			PLAYER->getinventory()->setStprageOpen(false);
			PLAYER->getinventory()->setTest(false);

			}
		}
	}
}

void sellTable::selectPrice()
{
	if (_selectNum)
	{

		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			//_cursorNum = 현재 커서가 가리키고 있는 렉트(0,1,2,3), _BoxChoiceNum = 자릿수
			if (_BoxChoiceNum == 7) _playerPrice[_cursorNum][_BoxChoiceNum] ++;
			if (_BoxChoiceNum == 6) _playerPrice[_cursorNum][_BoxChoiceNum] += 10;
			if (_BoxChoiceNum == 5) _playerPrice[_cursorNum][_BoxChoiceNum] += 100;
			if (_BoxChoiceNum == 4) _playerPrice[_cursorNum][_BoxChoiceNum] += 1000;
			if (_BoxChoiceNum == 3) _playerPrice[_cursorNum][_BoxChoiceNum] += 10000;
			if (_BoxChoiceNum == 2) _playerPrice[_cursorNum][_BoxChoiceNum] += 100000;
			if (_BoxChoiceNum == 1) _playerPrice[_cursorNum][_BoxChoiceNum] += 1000000;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (_BoxChoiceNum == 7) _playerPrice[_cursorNum][_BoxChoiceNum] --;
			if (_BoxChoiceNum == 6) _playerPrice[_cursorNum][_BoxChoiceNum] -= 10;
			if (_BoxChoiceNum == 5) _playerPrice[_cursorNum][_BoxChoiceNum] -= 100;
			if (_BoxChoiceNum == 4) _playerPrice[_cursorNum][_BoxChoiceNum] -= 1000;
			if (_BoxChoiceNum == 3) _playerPrice[_cursorNum][_BoxChoiceNum] -= 10000;
			if (_BoxChoiceNum == 2) _playerPrice[_cursorNum][_BoxChoiceNum] -= 100000;
			if (_BoxChoiceNum == 1) _playerPrice[_cursorNum][_BoxChoiceNum] -= 1000000;
		}

		//_BoxChoiceNum을 조절하며 가격의 자릿수를 조정할수있따
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			_BoxChoiceNum--;
			if (_BoxChoiceNum <= 0)_BoxChoiceNum = 1;

		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			_BoxChoiceNum++;
			if (_BoxChoiceNum >= 7)_BoxChoiceNum = 7;
		}

		//가격정하는 위아래 화살표역시 _BoxChoiceNum을 따라간다
		_selectUpdownRc = RectMakeCenter(_sellInfo[_cursorNum].left + 10 + (_BoxChoiceNum * 20), _sellInfo[_cursorNum].top + 30, _selectUpdownImg->getWidth(), _selectUpdownImg->getHeight());

		//총 가격을 구하기 전에 0으로 초기화
		_playerPrice[_cursorNum][0] = 0;
		for (int k = 1; k < 8; k++)
		{
			//모든 자릿수를 더해서 0번칸에 넣어준다. 0번칸이 플레이어가 정한 가격이 된다.
			_playerPrice[_cursorNum][0] += _playerPrice[_cursorNum][k];
		}
	}
}

void sellTable::removeItem()
{
	for (int i = 0; i < _vSellItem.size(); i++)
	{
		if (_vSellItem[i].getItemInfo().cnt == 0)
		{
			//템 갯수가 0이 되면 삭제된다
			_vSellItem.erase(_vSellItem.begin() + i);
			_vSellItem.insert(_vSellItem.begin() + i, ITEMMANAGER->addItem("비어있음"));
		}
	}
}

void sellTable::grab()
{
	for (int i = 0; i < _vSellItem.size(); i++)
	{
		if (_vSellItem[i].getItemInfo().itemName != "비어있음") //창고 안이 비어있지 않고
		{
			if ((_cursorNum == i) && KEYMANAGER->isOnceKeyDown('J'))// 커서와 아이템이 충돌된 상태라면
			{
				_cursor->getAni()->start();

				//임시벡터가 비어있을시 벡터에 추가
				if (_vTemp.size() <= 0)
				{
					_vTemp.push_back(_vSellItem[i]);
					_vTemp[0].setItemCnt_equal(1);
					_vSellItem[i].setItemCnt(-1);
					break;
				}

				//임시벡터에 이미 같은 이름의 아이템이 있으면 카운트를 올려줌
				if (_vTemp[0].getItemInfo().itemName == _vSellItem[i].getItemInfo().itemName &&
					(_vSellItem[i].getItemInfo().cnt + _vTemp[0].getItemInfo().cnt) <= _vTemp[0].getItemInfo().maxCnt)
				{
					_vTemp[0].setItemCnt();
					_vSellItem[i].setItemCnt(-1);
					break;
				}
			}
		}

		if (_vTemp.size() > 0)	//템프가 비어있지 않다면(아이템을 잡고 있다면)
		{
			if (_vSellItem[i].getItemInfo().itemName == "비어있음") //비어있는 곳에
			{
				if ((_cursorNum == i) && KEYMANAGER->isOnceKeyDown('J'))//j를 누르면 아이템을 그 자리에 놓음
				{
					_cursor->getAni()->start();

					_vSellItem.erase(_vSellItem.begin() + i);
					_vSellItem.insert(_vSellItem.begin() + i, _vTemp[0]);
					_vTemp.pop_back();

					//그 다음 아이템 위치를 다시 정해주어 판매대에 올려진 아이템의 위치를 잡아줌
					_vSellItem[0].setRect(_tableRc.left + 30, _tableRc.top + 10);
					_vSellItem[1].setRect(_tableRc.right - 30, _tableRc.top + 10);
					_vSellItem[2].setRect(_tableRc.left + 30, _tableRc.bottom - 40);
					_vSellItem[3].setRect(_tableRc.right - 30, _tableRc.bottom - 40);
					break;
				}
			}
		}
	}
}
