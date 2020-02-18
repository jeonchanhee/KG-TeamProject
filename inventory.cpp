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
	//=================================================������ �ִ� �̹�����=====================================================
	//bkrender()�� ���� �̹�����
	_bgimag = IMAGEMANAGER->findImage("���");								//�ڿ� ���

	//�κ��丮 ��
	_playerinventory._inventoryimg = IMAGEMANAGER->findImage("�κ��丮��");
	_playerinventory.x = WINSIZEX / 2;
	_playerinventory.y = WINSIZEY / 2;
	_playerinventory._inventoryrect = RectMakeCenter(_playerinventory.x, _playerinventory.y, _playerinventory._inventoryimg->getWidth(), _playerinventory._inventoryimg->getHeight());

	//�������� ������ ��ȯ�ϴ� �̹���
	_removeGlass._inventoryimg = IMAGEMANAGER->findImage("������");
	_removeGlass.x = 170;
	_removeGlass.y = 550;
	_removeGlass._inventoryrect = RectMakeCenter(_removeGlass.x, _removeGlass.y, _removeGlass._inventoryimg->getWidth(), _removeGlass._inventoryimg->getHeight());

	//�� �����ִ� ��
	_showitem._showitemimg = IMAGEMANAGER->findImage("�ۺ����ֱ�");					//������ Ŭ���ϸ� �ߴ� �� ������ ���� ����
	_showitem._showitemrc = RectMakeCenter(WINSIZEX - 70, 250, _showitem._showitemimg->getWidth(), _showitem._showitemimg->getHeight());

	_zbutton._inventoryimg = IMAGEMANAGER->findImage("Z��ư");

	_weaponiright._inventoryimg = IMAGEMANAGER->findImage("z��Ȱ��ȭ��");

	_weaponileft._inventoryimg = IMAGEMANAGER->findImage("z����Ȱ��ȭ��");

	//z����Ȱ��ȭ��,
	_weaponirighting._inventoryimg = IMAGEMANAGER->findImage("z����Ȱ��ȭ��");

	//Ȱ��ȭ��
	_weaponilefting._inventoryimg = IMAGEMANAGER->findImage("zȰ��ȭ��");

	_playerprofile._inventoryimg = IMAGEMANAGER->findImage("������");

	//bkrender()�� ���� �̹�����
	//============================================================================================================
	_inventorybg._inventoryimg = IMAGEMANAGER->findImage("�κ��丮����");
	_inventorybg.x = WINSIZEX / 2 - 410;
	_inventorybg.y = WINSIZEY / 2 - 215;

	//�κ��丮 ��ҵ�
	//�κ��丮(�÷��̾��&â���)	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			_inventoryelement._inventoryimg = IMAGEMANAGER->findImage("���");
			_inventoryelement.x = 190 + j * 55;
			_inventoryelement.y = 240 + i * 60;
			_inventoryelement._inventoryrect = RectMakeCenter(_inventoryelement.x, _inventoryelement.y, _inventoryelement._inventoryimg->getWidth(), _inventoryelement._inventoryimg->getHeight());
			_inventoryelement._item = ITEMMANAGER->addItem("�������");
			_inventoryelement._item.setRect(_inventoryelement._inventoryrect);
			_vInven.push_back(_inventoryelement);
		}
	}
	_vInven[0]._item = ITEMMANAGER->addItem("��������");
	
	//��������
	_inventoryelement._inventoryrect = RectMakeCenter((_removeGlass._inventoryrect.left + _removeGlass._inventoryrect.right) / 2 + 15, (_removeGlass._inventoryrect.top + _removeGlass._inventoryrect.bottom) / 2 - 30, 40, 40);
	_inventoryelement._item = ITEMMANAGER->addItem("�������");
	_inventoryelement._item.setRect(_inventoryelement._inventoryrect);
	_vInven.push_back(_inventoryelement);

	//�κ��丮(�÷��̾��)
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			_inventoryelement._inventoryrect = RectMakeCenter(612 + j * 132, 240, 40, 40);
			if (i >= 1)
			{
				_inventoryelement._inventoryrect = RectMakeCenter(555 + j * 50, 260 + i * 50, 40, 40);
			}
			_inventoryelement._item = ITEMMANAGER->addItem("�������");
			_inventoryelement._item.setRect(_inventoryelement._inventoryrect);
			_vInven.push_back(_inventoryelement);
		}
	}
	_vInven[21]._item = ITEMMANAGER->addItem("�Ʒÿ� �ܰ�");
	_vInven[22]._item = ITEMMANAGER->addItem("�÷��� ����");
	_vInven[26]._item = ITEMMANAGER->addItem("���� ����");

	//Ŀ�� Ŭ���� �̿��ϱ�
	_cursor = new cursor;
	_cursor->init();
	_cursorNumber = 0;
	_cursorrect = _vInven[_cursorNumber]._inventoryrect;
	_cursor->setRc(_cursorrect);

	_grab._grabimg = IMAGEMANAGER->addImage("Ŀ���׷�", "images/shop/grab.bmp", 50, 52, true, RGB(255, 0, 255));

	_storageusing = true;				//������ â�� �̿��ϱ� ���� �Ұ� bool test���� ��ó
	_storageOpen = false;				//â��� 
	_isweapon = false;					//���� ��ȯ�ϱ� ���� �Ұ�.. �̹����θ�
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
	// �κ��丮 ��Ȱ��ȭ
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
	//�κ��丮 Ȱ��ȭ
	else
	{
		if (KEYMANAGER->isOnceKeyDown('6'))
		{
			_openinventorywin = false;
		}
		cursormove();														//Ŀ�� �����̱�
		inventoryItem();
		grabitemremove();												 //J�� ������ �� �������� ����
		isweaponing();														//���� ü����
	}
}
// �κ��丮 �����ϴ� �� ������ �ٲٴ� ��
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

//Ŀ�� ������
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
		else						//�κ��丮(�÷��̾��)
		{
			if (_cursorNumber < 28);
		}

		_cursorrect = RectMake(_vInven[_cursorNumber]._inventoryrect.left, _vInven[_cursorNumber]._inventoryrect.top, 40, 40);
		_cursor->setRc(_cursorrect);
		_cursor->getAni()->start();
	}
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		if (_cursorNumber > 0) 	_cursorNumber -= 5;
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
	for (int i = 0; i < _vInven.size(); i++)			//���� ����� for������ ����  
	{
		if (_vInven[i]._item.getItemInfo().itemName != "�������")  // �������� ������� ���� ĭ�� Ȯ���Ѵ�.
		{
			if ((_cursorNumber == i) && KEYMANAGER->isOnceKeyDown('J'))   //Ŀ�� ��ȣ(_cursorNumber)�� ���� ��� i�� ��ġ��  J������
			{
				_cursor->getAni()->start();
				if (_vTemp.empty())
				{
					_vTemp.push_back(_vInven[i]); //�ӽ÷� ���� ���Ϳ� �κ��丮�� �ִ� ���� ��Ҹ� ��´�. 
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
		if (!_vTemp.empty())											//���� �ƴ϶��
		{
			if (i != 20)															//		i�� ���
			{
				if (_vInven[i]._item.getItemInfo().itemName == "�������")
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
			else // 20 ĭ�̸� ���� ó��
			{
				//��������
				if (_vInven[i]._item.getItemInfo().itemName == "�������")
				{
					if ((_cursorNumber == i) && KEYMANAGER->isOnceKeyDown('J'))
					{
						_cursor->getAni()->start();
						PLAYER->sellplayermoney((_vTemp[0]._item.getItemInfo().cnt*_vTemp[0]._item.getItemInfo().orignalPrice) / 5);
						_vInven[20]._item = ITEMMANAGER->addItem("�������");
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
			_vInven[i]._item = ITEMMANAGER->addItem("�������");
		}
	}
}

//����Ȱ ��ȭ or ���� ��Ȱ��ȭ
void inventory::isweaponing()
{
	if (!_isweapon)
	{
		if (KEYMANAGER->isOnceKeyDown('O'))					//�ӽ÷� 
		{
			_isweapon = true;
		}
	}
	else
	{
		if (KEYMANAGER->isOnceKeyDown('O'))					//�ӽ÷� 
		{
			_isweapon = false;
		}
	}
}

void inventory::resetelement()
{
	_inventoryelement._item = ITEMMANAGER->addItem("�������");
	_vInven.push_back(_inventoryelement);
}
//_vTemp[0].clear() �������
void inventory::tempRelass()
{
	_vTemp.clear();
}
//������ ���� �ִ��� ������ ��밡������?
void inventory::itempotion()
{
	if (0 < _vInven[26]._item.getItemInfo().cnt)					//������ 0���� ������
	{
		PLAYER->recoveryHp(_vInven[26]._item.getItemInfo().hp);				//�� ���� �÷��ش�
		_vInven[26]._item.setItemCnt(-1);
		if (_vInven[26]._item.getItemInfo().cnt == 0)
		{
			_vInven[26]._item = ITEMMANAGER->addItem("�������");
		}
	}
}


void inventory::swapItem(item swapItem)
{
	_inventoryelement._item = swapItem;
	_vTemp.push_back(_inventoryelement);
	_cursor->setRc(_vInven[0]._inventoryrect);
}

void inventory::render(HDC hdc)							// ���� ���� -> render>moverender()> bgrender()
{
	if (_openinventorywin)
	{
		bkrender(hdc);
		moverender(hdc);
		_cursor->render();				//Ŀ�� Ŭ���� ���� 
	}
	//storageopen �̶� ����� �κ��丮
	if (_storageOpen)
	{
		moverender(hdc);
	}
}

//���ȭ�� ����
void inventory::bkrender(HDC hdc)
{
	char str[128];
	char strspeed[128];				//���ǵ� �ؽ�Ʈ��
	char strshield[128];				//���� �ؽ�Ʈ��
	char strattack[128];				//���ÿ� �ؽ�Ʈ��			
	_bgimag->alphaRender(hdc, 1000);   // ���ķ��� ó���� ���ȭ��
	_playerinventory._inventoryimg->render(hdc, _playerinventory._inventoryrect.left, _playerinventory._inventoryrect.top);   //�÷��̾� �κ��丮

	IMAGEMANAGER->render("Z��ư", getMemDC(), 660, 225);
	IMAGEMANAGER->render("z������Ȱ��ȭ��", hdc, 637, 235);
	IMAGEMANAGER->render("z��Ȱ��ȭ��", hdc, 700, 235);
	if (!_isweapon)
	{
		IMAGEMANAGER->render("z����Ȱ��ȭ��", getMemDC(), 637, 235);
	}
	if (_isweapon)
	{
		IMAGEMANAGER->render("zȰ��ȭ��", getMemDC(), 700, 235);
	}
	_showitem._showitemimg->render(hdc, _showitem._showitemrc.left, _showitem._showitemrc.top, _showitem._showitemimg->getWidth(), _showitem._showitemimg->getHeight());					 //������ �������� �����ִ� �̹���.  
	for (int i = 0; i <= _vInven.size(); i++)									//��� �ִ� ��
	{
		if (21 <= i && i <= 28)
		{
			_vInven[i]._item.render();
			_vInven[i]._inventoryimg->render(hdc, _vInven[i]._inventoryrect.left, _vInven[i]._inventoryrect.top);
		}
	}
	IMAGEMANAGER->render("������", getMemDC(), WINSIZEX / 2 + 130, WINSIZEY / 2 - 97);
	PLAYER->invenRender(getMemDC());

	wsprintf(str, "%d", PLAYER->getHP());															//ü��
	SetTextColor(hdc, RGB(255, 255, 255));
	TextOut(hdc, WINSIZEX / 2 + 340, WINSIZEY / 2 - 65, str, strlen(str));

	wsprintf(strattack, "%d", PLAYER->getattskill());															//���ݷ�
	SetTextColor(hdc, RGB(255, 255, 255));
	TextOut(hdc, WINSIZEX / 2 + 340, WINSIZEY / 2 - 18, strattack, strlen(strattack));

	wsprintf(strshield, "%d", PLAYER->getshield());															//����
	SetTextColor(hdc, RGB(255, 255, 255));
	TextOut(hdc, WINSIZEX / 2 + 340, WINSIZEY / 2 + 30, strshield, strlen(strshield));

	wsprintf(strspeed, "%d", PLAYER->getspeed());															//���ǵ�
	SetTextColor(hdc, RGB(255, 255, 255));
	TextOut(hdc, WINSIZEX / 2 + 340, WINSIZEY / 2 + 75, strspeed, strlen(strspeed));

}

//(�κ��丮(�÷��̾��) & �κ��丮(â���))
void inventory::moverender(HDC hdc)
{
	if (_storageOpen || _openinventorywin)
	{
		char str[128];
		char moneystr[128];					//�÷��̾� �� 
		_inventorybg._inventoryimg->render(hdc, WINSIZEX / 2 - 410, WINSIZEY / 2 - 215);
		IMAGEMANAGER->render("������", hdc, _removeGlass._inventoryrect.left, _removeGlass._inventoryrect.top);

		wsprintf(moneystr, "%d", PLAYER->getMoney());					//���� ������ �ִ� �� 
		SetTextColor(hdc, RGB(41, 41, 41));					// �� ����
		TextOut(hdc, 285, 540, moneystr, strlen(moneystr));			// ��ġ ���� 
		itemrender(hdc);
		for (int i = 0; i < _vInven.size(); i++)						// �κ��丮 �ȿ� �������� �����ִ� for�� 
		{
			if (_vInven[i]._item.getItemInfo().itemName != "�������")
			{
				if (i < 21)
				{
					wsprintf(str, "%d", _vInven[i]._item.getItemInfo().cnt);
					SetTextColor(hdc, RGB(41, 41, 41));
					TextOut(hdc, _vInven[i]._item.getRECT().right, _vInven[i]._item.getRECT().bottom, str, strlen(str));
					SetBkMode(hdc, TRANSPARENT);				//���� �޹�� ó��
					if (IntersectRect(&_temp, &_cursorrect, &_vInven[i]._item.getRECT()))
					{
						_vInven[i]._item.getItemInfo().image->render(hdc, _showitem._showitemrc.left + 10, _showitem._showitemrc.top + 10);
					}
				}
			}
		}
		if (_openinventorywin)_cursor->render();					//�÷��̾ ������ �ִ� �κ��丮�ȿ� �ִ� Ŀ���� �� �� �ְԱ�
		if (_storageusing) _cursor->render();
	}
}

//�����۸� �����Ǵ� ���� 
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
	if (_vTemp.size() > 0)					//�ӽ� Ŀ�� �׷� �ߴ� ��
	{
		char str[128];
		_grab._grabimg->render(hdc, _cursorrect.left - 4, _cursorrect.top - 50);
		_vTemp[0]._item.getItemInfo().image->render(hdc, _cursorrect.left - 4, _cursorrect.top - 40);
		wsprintf(str, "%d", _vTemp[0]._item.getItemInfo().cnt);
		SetTextColor(hdc, RGB(41, 41, 41));
		TextOut(hdc, _cursorrect.right, _cursorrect.top - 40, str, strlen(str));
	}
}