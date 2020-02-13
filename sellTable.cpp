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
	_tableRc = RectMakeCenter(WINSIZEX / 2 - 350, WINSIZEY / 2 + 200, 100, 100);

	_slot[0] = RectMake(_sellMainImg->getWidth() + 83, _sellMainImg->getHeight() - 305, 40, 40);
	_slot[1] = RectMake(_sellMainImg->getWidth() + 312, _sellMainImg->getHeight() - 305, 40, 40);
	_slot[2] = RectMake(_sellMainImg->getWidth() + 83, _sellMainImg->getHeight() - 100, 40, 40);
	_slot[3] = RectMake(_sellMainImg->getWidth() + 312, _sellMainImg->getHeight() - 100, 40, 40);

	for (int i = 0; i < SLOTNUM; i++)
	{
		_slotImage[i] = IMAGEMANAGER->findImage("�ǸŽ����̹���");
		_sellInfo[i] = RectMakeCenter(_slot[i].left + (_slot[i].right - _slot[i].left) / 2, _slot[i].top + (_slot[i].bottom - _slot[i].top) / 2 + 80, 180, 90);
	}

	//Ŀ�� �ʱ�ȭ
	_cursorNum = 0;
	_cursorSlot = _slot[_cursorNum];
	_cursor = new cursor;
	_cursor->init();
	_grab = new image;
	_grab = IMAGEMANAGER->findImage("Ŀ���׷�");
	_BoxChoiceNum = 7;

	//����������� �ʱ�ȭ
	_vSellItem.push_back(ITEMMANAGER->addItem("��������"));
	_vSellItem.push_back(ITEMMANAGER->addItem("��������"));
	_vSellItem.push_back(ITEMMANAGER->addItem("�������"));
	_vSellItem.push_back(ITEMMANAGER->addItem("���ھ�"));
	_vSellItem[0].setItemCnt_equal(9);

	for (int i = 0; i < _vSellItem.size(); i++)
	{
		//�Ǹ����̺� �÷��� �������� ���Ʒ��� ���̺���
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
	playerCollision();
	cursorControl();
	selectPrice();
	removeItem();
}

void sellTable::render()
{
	//�������� �÷��δ� ���̺�� �� ���� ������ ������ ����
	IMAGEMANAGER->render("�Ǹ����̺�", getMemDC(), _tableRc.left, _tableRc.top);
	for (int i = 0; i < _vSellItem.size(); i++)
	{
		_vSellItem[i].render();
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
	if (_showWindow)
	{
		//_sellMainImg = �Ǹ����̺� ���� �ߴ� â
		_sellMainImg->render(getMemDC(), WINSIZEX / 2 - 70, 100, _sellMainImg->getWidth(), _sellMainImg->getHeight());

		//������ �̹����� �� ����,����,�Ѱ��� ���� 
		for (int i = 0; i < SLOTNUM; i++)
		{
			_slotImage[i]->render(getMemDC(), _slot[i].left, _slot[i].top);
			int k;
			k = i + 2;
			wsprintf(str, "%d", _playerPrice[i][0]);
			TextOut(getMemDC(), WINSIZEX / 2 + 100 + (k % 2 * 100), (k / 2 * 220) - 20, str, strlen(str));
			if (_vSellItem[i].getItemInfo().itemName != "�������")
			{
				wsprintf(str, "x%d", _vSellItem[i].getItemInfo().cnt);
				TextOut(getMemDC(), WINSIZEX / 2 + 100 + (k % 2 * 100), (k / 2 * 220) + 0, str, strlen(str));
			}
			wsprintf(str, "%d", _vSellItem[i].getItemInfo().cnt*_playerPrice[i][0]);
			TextOut(getMemDC(), WINSIZEX / 2 + 100 + (k % 2 * 100), (k / 2 * 220) + 20, str, strlen(str));
		}
		// �������ϴ� �κ��� ���Ʒ� ȭ��ǥ
		if (_selectNum)_selectUpdownImg->render(getMemDC(), _selectUpdownRc.left, _selectUpdownRc.top);

		//���� �ȿ� ���� ������ �̹���
		for (int i = 0; i < _vSellItem.size(); i++)
		{
			_vSellItem[i].getItemInfo().image->render(getMemDC(), _slot[i].left, _slot[i].top);
		}

		_cursor->render();
	}

	if (_vTemp.size() > 0)	//������ ������� �ʴٸ�(Ŀ���� ���� ��� �ִٸ�)
	{
		char str[128];
		IMAGEMANAGER->render("Ŀ���׷�", getMemDC(), _cursorSlot.left, _cursorSlot.top - 60);
		_vTemp[0].getItemInfo().image->render(getMemDC(), _cursorSlot.left, _cursorSlot.top - 50);
		wsprintf(str, "%d", _vTemp[0].getItemInfo().cnt);
		TextOut(getMemDC(), _cursorSlot.right, _cursorSlot.top - 40, str, strlen(str));
	}
}

void sellTable::cursorControl()
{
	if (_showWindow)
	{
		if (KEYMANAGER->isOnceKeyDown('A'))
		{
			//Ŀ���� ������ ��������
			_cursorNum--;
			if (_cursorNum < 0) _cursorNum = 0;

			//Ŀ���� �� ĭ���� �ű��
			_cursorSlot = RectMake(_slot[_cursorNum].left, _slot[_cursorNum].top, 40, 40);
			_cursor->setSmallCursor();		//Ŀ�� ũ�⸦ �۰��ϴ� �Լ�
			_cursor->getAni()->start();
		}
		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			//Ŀ���� ������ ��������
			_cursorNum++;
			if (_cursorNum >= SLOTNUM) _cursorNum = SLOTNUM - 1;

			_cursorSlot = RectMake(_slot[_cursorNum].left, _slot[_cursorNum].top, 40, 40);
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
				_cursorSlot = _slot[_cursorNum];	  //_slot�� ������ �÷����� ��Ʈ
			}
			else
			{
				_cursorSlot = _sellInfo[_cursorNum];  //_sellInfo�� �����۰��� ���ϴ� ��Ʈ
				_cursor->setBigCursor();			  //Ŀ�� ũ�⸦ ũ���ϴ��Լ�
			}

			_cursor->getAni()->start();
		}

		if (IntersectRect(&temp, &_cursorSlot, &_sellInfo[_cursorNum]) && KEYMANAGER->isOnceKeyDown('W'))
		{
			_cursorSlot = _slot[_cursorNum];
			_cursor->setSmallCursor();
			_cursor->getAni()->start();
		}

		//�Ʒ���
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

		//�׽� ������ ������Ʈ����.
		_vSellItem[_cursorNum].setPlayerPrice(_playerPrice[_cursorNum][0]);
		grab();
	}
}

void sellTable::playerCollision()
{
	if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &_tableRc)) //����ݱ�
	{
		if (!_showWindow)
		{
			if (KEYMANAGER->isOnceKeyDown('J'))_showWindow = true;
		}
		if (_showWindow)
		{
			if (KEYMANAGER->isOnceKeyDown('I'))_showWindow = false;
		}
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

		//�� ������ ���ϱ� ���� 0���� �ʱ�ȭ
		_playerPrice[_cursorNum][0] = 0;
		for (int k = 1; k < 8; k++)
		{
			//��� �ڸ����� ���ؼ� 0��ĭ�� �־��ش�. 0��ĭ�� �÷��̾ ���� ������ �ȴ�.
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
			//�� ������ 0�� �Ǹ� �����ȴ�
			_vSellItem.erase(_vSellItem.begin() + i);
			_vSellItem.insert(_vSellItem.begin() + i, ITEMMANAGER->addItem("�������"));
		}
	}
}

void sellTable::grab()
{
	for (int i = 0; i < _vSellItem.size(); i++)
	{
		if (_vSellItem[i].getItemInfo().itemName != "�������") //â�� ���� ������� �ʰ�
		{
			if ((_cursorNum == i) && KEYMANAGER->isOnceKeyDown('J'))// Ŀ���� �������� �浹�� ���¶��
			{
				_cursor->getAni()->start();

				//�ӽú��Ͱ� ��������� ���Ϳ� �߰�
				if (_vTemp.size() <= 0)
				{
					_vTemp.push_back(_vSellItem[i]);
					_vTemp[0].setItemCnt_equal(1);
					_vSellItem[i].setItemCnt(-1);
					break;
				}

				//�ӽú��Ϳ� �̹� ���� �̸��� �������� ������ ī��Ʈ�� �÷���
				if (_vTemp[0].getItemInfo().itemName == _vSellItem[i].getItemInfo().itemName &&
					(_vSellItem[i].getItemInfo().cnt + _vTemp[0].getItemInfo().cnt) <= _vTemp[0].getItemInfo().maxCnt)
				{
					_vTemp[0].setItemCnt();
					_vSellItem[i].setItemCnt(-1);
					break;
				}
			}
		}

		if (_vTemp.size() > 0)	//������ ������� �ʴٸ�(�������� ��� �ִٸ�)
		{
			if (_vSellItem[i].getItemInfo().itemName == "�������") //����ִ� ����
			{
				if ((_cursorNum == i) && KEYMANAGER->isOnceKeyDown('J'))//j�� ������ �������� �� �ڸ��� ����
				{
					_cursor->getAni()->start();

					_vSellItem.erase(_vSellItem.begin() + i);
					_vSellItem.insert(_vSellItem.begin() + i, _vTemp[0]);
					_vTemp.pop_back();

					//�� ���� ������ ��ġ�� �ٽ� �����־� �ǸŴ뿡 �÷��� �������� ��ġ�� �����
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
