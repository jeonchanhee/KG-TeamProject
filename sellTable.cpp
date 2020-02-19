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
	_tableRc = RectMakeCenter(WINSIZEX / 2 - 100, WINSIZEY / 2 + 70, 100, 20);

	for (int i = 0; i < 2; i++)
	{
		for (int k = 0; k < 2; k++)
		{
			_sellSlot.img = IMAGEMANAGER->findImage("판매슬롯이미지");
			_sellSlot.x = _sellMainImg->getWidth() + 103 + (k * 229);
			_sellSlot.y = _sellMainImg->getHeight() - 283 + (i * 205);
			_sellSlot.rc = RectMakeCenter(_sellSlot.x, _sellSlot.y, _sellSlot.img->getWidth(), _sellSlot.img->getHeight());
			_sellSlot.item = ITEMMANAGER->addItem("나뭇가지");
			_sellSlot.item.setRect(_tableRc.left + 30 + (k* 40) , _tableRc.top + 20 + (i* 40));
			_sellSlot.item.setItemCnt_equal(9);
			_sellSlot.item.setWave(true);
			_vSlot.push_back(_sellSlot);
		}
	}

	for (int i = 0; i < SLOTNUM; i++)
	{
		_sellInfo[i] = RectMakeCenter(_vSlot[i].rc.left + (_vSlot[i].rc.right - _vSlot[i].rc.left) / 2, _vSlot[i].rc.top + (_vSlot[i].rc.bottom - _vSlot[i].rc.top) / 2 + 80, 180, 90);
	}

	//커서 초기화
	_cursorNum = 0;
	_cursorSlot = _vSlot[_cursorNum].rc;
	_cursor = new cursor;
	_cursor->init();
	_grab = new image;
	_grab = IMAGEMANAGER->findImage("커서그랩");
	_BoxChoiceNum = 7;

	return S_OK;
}

void sellTable::release()
{
	SAFE_DELETE(_cursor);
}

void sellTable::update()
{
	removeItem();
	for (int i = 0; i < _vSlot.size(); i++)
	{
		_vSlot[i].item.update();
	}

	if (!_showWindow)
	{
		if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &_tableRc)) //열기닫기
		{
			if (KEYMANAGER->isOnceKeyDown('J'))
			{
				_showWindow = true;
				_test = true;
				PLAYER->getinventory()->setStprageOpen(true);
				PLAYER->setstop(true);
			}
		}
	}
	else
	{
		if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &_tableRc)) //열기닫기
		{
			if (KEYMANAGER->isOnceKeyDown('6'))
			{
				_showWindow = false;
				_test = false;
				SetTextAlign(getMemDC(), TA_LEFT);
				PLAYER->getinventory()->setStprageOpen(false);
				PLAYER->setstop(false);
			}
		}
		if (!PLAYER->getinventory()->getstorgeuding()) cursorControl();   //-->커서컨트롤 WASD버튼
		else PLAYER->getinventory()->cursormove();				//-->커서컨트롤 WASD버튼
		if (!PLAYER->getinventory()->getstorgeuding() && !PLAYER->getinventory()->getvTemp().empty())
		{
			sellSlot temp;

			temp.img = PLAYER->getinventory()->getvTemp()[0]._inventoryimg;
			temp.item = PLAYER->getinventory()->getvTemp()[0]._item;

			_vTemp.push_back(temp);

			PLAYER->getinventory()->tempClear();
		}
		PLAYER->getinventory()->inventoryItem();
		PLAYER->getinventory()->grabitemremove();
		selectPrice();
		grab();
		_vSlot[_cursorNum].item.setPlayerPrice(_playerPrice[_cursorNum][0]);
	}
}

void sellTable::render()
{
	//아이템을 올려두는 테이블과 그 위에 놓여진 아이템 렌더
	IMAGEMANAGER->render("판매테이블", getMemDC(), _tableRc.left, _tableRc.top);
	PLAYER->getinventory()->moverender(getMemDC());
	//PLAYER->getinventory()->invenanditemcollision(getMemDC());
	for (int i = 0; i < _vSlot.size(); i++)
	{
		_vSlot[i].item.render(getMemDC());
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
	else
	{
		//_sellMainImg = 판매테이블 열면 뜨는 창
		_sellMainImg->render(getMemDC(), WINSIZEX / 2 - 70, 100, _sellMainImg->getWidth(), _sellMainImg->getHeight());

		//슬롯의 이미지와 템 가격,갯수,총가격 렌더 
		for (int i = 0; i < SLOTNUM; i++)
		{
			_vSlot[i].img->render(getMemDC(), _vSlot[i].rc.left, _vSlot[i].rc.top);
			if (_vSlot[i].item.getItemInfo().itemName != "비어있음")
			{
				int k;
				k = i + 2;
				SetTextAlign(getMemDC(), TA_RIGHT);

				if (i < 2)
				{
					wsprintf(str, "%d", _playerPrice[i][0]);
					TextOut(getMemDC(), _sellInfo[i].right - 30 , _sellInfo[i].top + (k / 2 * 30)-10 , str, strlen(str));
					wsprintf(str, "x%d", _vSlot[i].item.getItemInfo().cnt);
					TextOut(getMemDC(), _sellInfo[i].right - 5 , _sellInfo[i].top + (k / 2 * 30) + 5, str, strlen(str));
					wsprintf(str, "%d", _vSlot[i].item.getItemInfo().cnt * _playerPrice[i][0]);
					TextOut(getMemDC(), _sellInfo[i].right - 30 , _sellInfo[i].top + (k / 2 * 30) + 30, str, strlen(str));
				}
				else
				{
					wsprintf(str, "%d", _playerPrice[i][0]);
					TextOut(getMemDC(), _sellInfo[i].right - 30, _sellInfo[i].top + (k / 2 * 30) - 40, str, strlen(str));
					wsprintf(str, "x%d", _vSlot[i].item.getItemInfo().cnt);
					TextOut(getMemDC(), _sellInfo[i].right - 5, _sellInfo[i].top + (k / 2 * 30)-25, str, strlen(str));
					wsprintf(str, "%d", _vSlot[i].item.getItemInfo().cnt * _playerPrice[i][0]);
					TextOut(getMemDC(), _sellInfo[i].right - 30, _sellInfo[i].top + (k / 2 * 30), str, strlen(str));
				}
				
			}
		}
		// 가격정하는 부분의 위아래 화살표
		if (_selectNum)_selectUpdownImg->render(getMemDC(), _selectUpdownRc.left, _selectUpdownRc.top);

		//슬롯 안에 들어가는 아이템 이미지
		for (int i = 0; i < _vSlot.size(); i++)
		{
			_vSlot[i].item.getItemInfo().image->render(getMemDC(), _vSlot[i].rc.left, _vSlot[i].rc.top);
		}

		if (!PLAYER->getinventory()->getstorgeuding()) _cursor->render();
	}

	if (!_vTemp.empty())//템프가 비어있지 않다면(커서가 템을 잡고 있다면)
	{
		char str[128];
		IMAGEMANAGER->render("커서그랩", getMemDC(), _cursorSlot.left, _cursorSlot.top - 60);
		_vTemp[0].item.getItemInfo().image->render(getMemDC(), _cursorSlot.left, _cursorSlot.top - 50);
		wsprintf(str, "%d", _vTemp[0].item.getItemInfo().cnt);
		TextOut(getMemDC(), _cursorSlot.right, _cursorSlot.top - 40, str, strlen(str));
	}
}

void sellTable::cursorControl()
{
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		_cursorNum--;
		//커서가 인벤토리로 넘어가면 (_cursorNum이 0이 되면)
		if (_cursorNum < 1)
		{
			_cursorNum = 0;
			PLAYER->getinventory()->setstorgeuding(true); //옆으로 인벤토리로 옮기기
			if (!_vTemp.empty()) PLAYER->getinventory()->swapItem(_vTemp[0].item);
			_vTemp.clear();
		}

		//커서를 옆 칸으로 옮긴다
		_cursorSlot = RectMake(_vSlot[_cursorNum].rc.left, _vSlot[_cursorNum].rc.top, 40, 40);
		_cursor->setSmallCursor();      //커서 크기를 작게하는 함수
		_cursor->getAni()->start();
	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		//커서가 옆으로 못나가게
		_cursorNum++;
		if (_cursorNum >= SLOTNUM) _cursorNum = SLOTNUM - 1;

		_cursorSlot = RectMake(_vSlot[_cursorNum].rc.left, _vSlot[_cursorNum].rc.top, 40, 40);
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
			_cursorSlot = _vSlot[_cursorNum].rc;     //_slot - 아이템 올려놓는 렉트
		}
		if (!_vTemp.empty())//아이템을 들고있으면 가격정하는 렉트로 가지않도록 예외처리
		{
			_cursorSlot = _vSlot[_cursorNum].rc;     //_slot - 아이템 올려놓는 렉트
		}
		else
		{
			_cursorSlot = _sellInfo[_cursorNum];  //_sellInfo - 아이템가격 정하는 렉트
			_cursor->setBigCursor();           //커서 크기를 크게하는함수
		}
		_cursor->getAni()->start();
	}

	if (IntersectRect(&temp, &_cursorSlot, &_sellInfo[_cursorNum]) && KEYMANAGER->isOnceKeyDown('W'))
	{
		_cursorSlot = _vSlot[_cursorNum].rc;
		_cursor->setSmallCursor();
		_cursor->getAni()->start();
	}

	//아래로
	if (!IntersectRect(&temp, &_cursorSlot, &_sellInfo[_cursorNum]) && KEYMANAGER->isOnceKeyDown('S'))
	{

		if (!_vTemp.empty()) //아이템을 들고있으면 가격정하는 렉트로 가지않도록 예외처리
		{
			int temp;
			temp = _cursorNum;
			_cursorNum += 2;
			if (_cursorNum >= 4)
			{
				_cursorNum = temp;
			}
			_cursorSlot = _vSlot[_cursorNum].rc;     //_slot - 아이템 올려놓는 렉트
		}
		else
		{
			_cursorSlot = _sellInfo[_cursorNum];
			_cursor->update(_sellInfo[_cursorNum]);
			_cursor->setBigCursor();
		}
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
			_cursorSlot = _vSlot[_cursorNum].rc;
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

		//총 가격을 구하기 전에 0으로 초기화. 안그러면 계속 더해짐
		_playerPrice[_cursorNum][0] = 0;

		for (int k = 1; k < 8; k++)
		{
			//모든 자릿수를 더해서 0번칸에 넣어준다. 0번칸이 플레이어가 정한 가격이 된다.
			_playerPrice[_cursorNum][0] += _playerPrice[_cursorNum][k];
			if (_playerPrice[_cursorNum][0] <= 0)_playerPrice[_cursorNum][0] = 0;
		}
	}
}

void sellTable::removeItem()
{
	for (int i = 0; i < _vSlot.size(); i++)
	{
		if (_vSlot[i].item.getItemInfo().cnt <= 0)
		{
			//템 갯수가 0이 되면 자동으로 삭제된다
			_vSlot[i].item = ITEMMANAGER->addItem("비어있음");
			_vSlot[i].item.setItemCnt_equal(1);
		}
		_vSlot[i].item.setRect(_tableRc.left + 30 + (i % 2 * 40), _tableRc.top + 20 + (i / 2 * 40)); //아이템위치 업데이트
	}
}

void sellTable::grab()
{
	for (int i = 0; i < _vSlot.size(); i++)
	{
		if (_vSlot[i].item.getItemInfo().itemName != "비어있음") //창고 안이 비어있지 않고
		{
			if ((_cursorNum == i) && KEYMANAGER->isOnceKeyDown('J'))// 커서와 아이템이 충돌된 상태라면
			{
				_cursor->getAni()->start();

				//임시벡터가 비어있을시 벡터에 추가
				if (_vTemp.size() <= 0)
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

		if (_vTemp.size() > 0)   //템프가 비어있지 않다면(아이템을 잡고 있다면)
		{
			if (_vSlot[i].item.getItemInfo().itemName == "비어있음") //비어있는 곳에
			{
				if ((_cursorNum == i) && KEYMANAGER->isOnceKeyDown('J'))//j를 누르면 아이템을 그 자리에 놓음
				{
					_cursor->getAni()->start();
					_vSlot[i].item = _vTemp[0].item;
					_vSlot[i].item.setWave(true);
					_vTemp.pop_back();

					//그 다음 아이템 위치를 다시 정해주어 판매대에 올려진 아이템의 위치를 잡아줌
					for (int i = 0; i < 2; i++)
					{
						for (int k = 0; k < 2; k++)
						{
							_vSlot[i].item.setRect(_tableRc.left + 30 + (k * 40), _tableRc.top + 20 + (i * 40));
						}
					}

					break;
				}
			}
		}
	}
}