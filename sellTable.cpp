#include "stdafx.h"
#include "sellTable.h"

sellTable::sellTable() {}

sellTable::~sellTable()
{
}

HRESULT sellTable::init()
{
	_sellMainImg = IMAGEMANAGER->findImage("�Ǹ�â");
	_selectUpdownImg = IMAGEMANAGER->findImage("���Ʒ�ȭ��ǥ");

	//��Ʈ�ʱ�ȭ
	_tableRc = RectMakeCenter(WINSIZEX / 2 - 100, WINSIZEY / 2 + 70, 100, 20);

	for (int i = 0; i < 2; i++)
	{
		for (int k = 0; k < 2; k++)
		{
			_sellSlot.img = IMAGEMANAGER->findImage("�ǸŽ����̹���");
			_sellSlot.x = _sellMainImg->getWidth() + 103 + (k * 229);
			_sellSlot.y = _sellMainImg->getHeight() - 283 + (i * 205);
			_sellSlot.rc = RectMakeCenter(_sellSlot.x, _sellSlot.y, _sellSlot.img->getWidth(), _sellSlot.img->getHeight());
			_sellSlot.item = ITEMMANAGER->addItem("��������");
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

	//Ŀ�� �ʱ�ȭ
	_cursorNum = 0;
	_cursorSlot = _vSlot[_cursorNum].rc;
	_cursor = new cursor;
	_cursor->init();
	_grab = new image;
	_grab = IMAGEMANAGER->findImage("Ŀ���׷�");
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
		if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &_tableRc)) //����ݱ�
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
		if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &_tableRc)) //����ݱ�
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
		if (!PLAYER->getinventory()->getstorgeuding()) cursorControl();   //-->Ŀ����Ʈ�� WASD��ư
		else PLAYER->getinventory()->cursormove();				//-->Ŀ����Ʈ�� WASD��ư
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
	//�������� �÷��δ� ���̺�� �� ���� ������ ������ ����
	IMAGEMANAGER->render("�Ǹ����̺�", getMemDC(), _tableRc.left, _tableRc.top);
	PLAYER->getinventory()->moverender(getMemDC());
	//PLAYER->getinventory()->invenanditemcollision(getMemDC());
	for (int i = 0; i < _vSlot.size(); i++)
	{
		_vSlot[i].item.render(getMemDC());
	}

	//����ݱ�
	if (!_showWindow)
	{
		if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &_tableRc))
		{
			IMAGEMANAGER->render("����", getMemDC(), _tableRc.right, _tableRc.top - 20);
		}
	}

	//��������
	else
	{
		//_sellMainImg = �Ǹ����̺� ���� �ߴ� â
		_sellMainImg->render(getMemDC(), WINSIZEX / 2 - 70, 100, _sellMainImg->getWidth(), _sellMainImg->getHeight());

		//������ �̹����� �� ����,����,�Ѱ��� ���� 
		for (int i = 0; i < SLOTNUM; i++)
		{
			_vSlot[i].img->render(getMemDC(), _vSlot[i].rc.left, _vSlot[i].rc.top);
			if (_vSlot[i].item.getItemInfo().itemName != "�������")
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
		// �������ϴ� �κ��� ���Ʒ� ȭ��ǥ
		if (_selectNum)_selectUpdownImg->render(getMemDC(), _selectUpdownRc.left, _selectUpdownRc.top);

		//���� �ȿ� ���� ������ �̹���
		for (int i = 0; i < _vSlot.size(); i++)
		{
			_vSlot[i].item.getItemInfo().image->render(getMemDC(), _vSlot[i].rc.left, _vSlot[i].rc.top);
		}

		if (!PLAYER->getinventory()->getstorgeuding()) _cursor->render();
	}

	if (!_vTemp.empty())//������ ������� �ʴٸ�(Ŀ���� ���� ��� �ִٸ�)
	{
		char str[128];
		IMAGEMANAGER->render("Ŀ���׷�", getMemDC(), _cursorSlot.left, _cursorSlot.top - 60);
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
		//Ŀ���� �κ��丮�� �Ѿ�� (_cursorNum�� 0�� �Ǹ�)
		if (_cursorNum < 1)
		{
			_cursorNum = 0;
			PLAYER->getinventory()->setstorgeuding(true); //������ �κ��丮�� �ű��
			if (!_vTemp.empty()) PLAYER->getinventory()->swapItem(_vTemp[0].item);
			_vTemp.clear();
		}

		//Ŀ���� �� ĭ���� �ű��
		_cursorSlot = RectMake(_vSlot[_cursorNum].rc.left, _vSlot[_cursorNum].rc.top, 40, 40);
		_cursor->setSmallCursor();      //Ŀ�� ũ�⸦ �۰��ϴ� �Լ�
		_cursor->getAni()->start();
	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		//Ŀ���� ������ ��������
		_cursorNum++;
		if (_cursorNum >= SLOTNUM) _cursorNum = SLOTNUM - 1;

		_cursorSlot = RectMake(_vSlot[_cursorNum].rc.left, _vSlot[_cursorNum].rc.top, 40, 40);
		_cursor->setSmallCursor();
		_cursor->getAni()->start();
	}

	//����
	if (!IntersectRect(&temp, &_cursorSlot, &_sellInfo[_cursorNum]) && KEYMANAGER->isOnceKeyDown('W'))
	{
		//���������� ������
		int temp;
		temp = _cursorNum;
		_cursorNum -= 2;

		if (_cursorNum < 0)
		{
			_cursorNum = temp;
			_cursorSlot = _vSlot[_cursorNum].rc;     //_slot - ������ �÷����� ��Ʈ
		}
		if (!_vTemp.empty())//�������� ��������� �������ϴ� ��Ʈ�� �����ʵ��� ����ó��
		{
			_cursorSlot = _vSlot[_cursorNum].rc;     //_slot - ������ �÷����� ��Ʈ
		}
		else
		{
			_cursorSlot = _sellInfo[_cursorNum];  //_sellInfo - �����۰��� ���ϴ� ��Ʈ
			_cursor->setBigCursor();           //Ŀ�� ũ�⸦ ũ���ϴ��Լ�
		}
		_cursor->getAni()->start();
	}

	if (IntersectRect(&temp, &_cursorSlot, &_sellInfo[_cursorNum]) && KEYMANAGER->isOnceKeyDown('W'))
	{
		_cursorSlot = _vSlot[_cursorNum].rc;
		_cursor->setSmallCursor();
		_cursor->getAni()->start();
	}

	//�Ʒ���
	if (!IntersectRect(&temp, &_cursorSlot, &_sellInfo[_cursorNum]) && KEYMANAGER->isOnceKeyDown('S'))
	{

		if (!_vTemp.empty()) //�������� ��������� �������ϴ� ��Ʈ�� �����ʵ��� ����ó��
		{
			int temp;
			temp = _cursorNum;
			_cursorNum += 2;
			if (_cursorNum >= 4)
			{
				_cursorNum = temp;
			}
			_cursorSlot = _vSlot[_cursorNum].rc;     //_slot - ������ �÷����� ��Ʈ
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


	//���� ���ϴ� ��Ʈ���� J�� ������ _selectNum�� true�� �Ǿ� ������ ���ϴ� �Լ��� �Ѿ
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
			//_cursorNum = ���� Ŀ���� ����Ű�� �ִ� ��Ʈ(0,1,2,3), _BoxChoiceNum = �ڸ���
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

		//_BoxChoiceNum�� �����ϸ� ������ �ڸ����� �����Ҽ��ֵ�
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

		//�������ϴ� ���Ʒ� ȭ��ǥ���� _BoxChoiceNum�� ���󰣴�
		_selectUpdownRc = RectMakeCenter(_sellInfo[_cursorNum].left + 10 + (_BoxChoiceNum * 20), _sellInfo[_cursorNum].top + 30, _selectUpdownImg->getWidth(), _selectUpdownImg->getHeight());

		//�� ������ ���ϱ� ���� 0���� �ʱ�ȭ. �ȱ׷��� ��� ������
		_playerPrice[_cursorNum][0] = 0;

		for (int k = 1; k < 8; k++)
		{
			//��� �ڸ����� ���ؼ� 0��ĭ�� �־��ش�. 0��ĭ�� �÷��̾ ���� ������ �ȴ�.
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
			//�� ������ 0�� �Ǹ� �ڵ����� �����ȴ�
			_vSlot[i].item = ITEMMANAGER->addItem("�������");
			_vSlot[i].item.setItemCnt_equal(1);
		}
		_vSlot[i].item.setRect(_tableRc.left + 30 + (i % 2 * 40), _tableRc.top + 20 + (i / 2 * 40)); //��������ġ ������Ʈ
	}
}

void sellTable::grab()
{
	for (int i = 0; i < _vSlot.size(); i++)
	{
		if (_vSlot[i].item.getItemInfo().itemName != "�������") //â�� ���� ������� �ʰ�
		{
			if ((_cursorNum == i) && KEYMANAGER->isOnceKeyDown('J'))// Ŀ���� �������� �浹�� ���¶��
			{
				_cursor->getAni()->start();

				//�ӽú��Ͱ� ��������� ���Ϳ� �߰�
				if (_vTemp.size() <= 0)
				{
					_vTemp.push_back(_vSlot[i]);
					_vTemp[0].item.setItemCnt_equal(1);
					_vSlot[i].item.setItemCnt(-1);
					break;
				}

				//�ӽú��Ϳ� �̹� ���� �̸��� �������� ������ ī��Ʈ�� �÷���
				if (_vTemp[0].item.getItemInfo().itemName == _vSlot[i].item.getItemInfo().itemName &&
					(_vSlot[i].item.getItemInfo().cnt + _vTemp[0].item.getItemInfo().cnt) <= _vTemp[0].item.getItemInfo().maxCnt)
				{
					_vTemp[0].item.setItemCnt();
					_vSlot[i].item.setItemCnt(-1);
					break;
				}
			}
		}

		if (_vTemp.size() > 0)   //������ ������� �ʴٸ�(�������� ��� �ִٸ�)
		{
			if (_vSlot[i].item.getItemInfo().itemName == "�������") //����ִ� ����
			{
				if ((_cursorNum == i) && KEYMANAGER->isOnceKeyDown('J'))//j�� ������ �������� �� �ڸ��� ����
				{
					_cursor->getAni()->start();
					_vSlot[i].item = _vTemp[0].item;
					_vSlot[i].item.setWave(true);
					_vTemp.pop_back();

					//�� ���� ������ ��ġ�� �ٽ� �����־� �ǸŴ뿡 �÷��� �������� ��ġ�� �����
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