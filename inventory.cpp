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

	_bgimag = IMAGEMANAGER->findImage("���");								//�ڿ� ���

	//�κ��丮 ��
	_playerinventory._inventoryimg = IMAGEMANAGER->findImage("�κ��丮��");
	_playerinventory.x = WINSIZEX / 2;
	_playerinventory.y = WINSIZEY / 2;
	_playerinventory._inventoryrect = RectMakeCenter(_playerinventory.x, _playerinventory.y, _playerinventory._inventoryimg->getWidth(), _playerinventory._inventoryimg->getHeight());

	//���ָӴ� ��ġ �̹���
	_moneyicon._inventoryimg = IMAGEMANAGER->findImage("���ָӴ�");
	_moneyicon.x = 270;
	_moneyicon.y = 480;

	//�������� ������ ��ȯ�ϴ� �̹���
	_removeGlass._inventoryimg = IMAGEMANAGER->findImage("������");
	_removeGlass.x = 170;
	_removeGlass.y = 550;
	_removeGlass._inventoryrect = RectMakeCenter(_removeGlass.x, _removeGlass.y, _removeGlass._inventoryimg->getWidth(), _removeGlass._inventoryimg->getHeight());


	//�κ��丮 ��ҵ�
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			_invenotryelement[0].x = 210;
			_invenotryelement[0].y = 250;
			_invenotryelement[i + 5 * j]._inventoryrect = RectMakeCenter(_invenotryelement[0].x + i * 55, _invenotryelement[0].y + j * 60, 40, 40);	 // ����� ������ 1~2��° �� �κ��丮 ��Ҵ�
			if (j >= 2)   // ����� �� 3~4��° �� �κ��丮 ��Ҵ�
			{
				_invenotryelement[i + 5 * j]._inventoryimg = IMAGEMANAGER->findImage("���");										// �κ��丮 ��� �ҷ����� �̹���  
				_invenotryelement[i + 5 * j]._inventoryrect = RectMakeCenter(_invenotryelement[0].x + i * 55, _invenotryelement[0].y + j * 60, 40, 40);				//�κ��丮 ��ġ ����
			}
		}
	}
	_invenotryelement[20]._inventoryrect = RectMakeCenter((_removeGlass._inventoryrect.left + _removeGlass._inventoryrect.right) / 2 + 15, (_removeGlass._inventoryrect.top + _removeGlass._inventoryrect.bottom) / 2 - 22, 40, 40);			// �������� ������ ��ȯ�ϴ� �κ��丮 ��� ��������ġ

	//Ŀ�� Ŭ���� �̿��ϱ�
	_cursor = new cursor;
	_cursor->init();
	_cursorNumber = 0;
	_cursorrect = _invenotryelement[_cursorNumber]._inventoryrect;


	//Ŀ�� �׷�
	_grab._grabimg = IMAGEMANAGER->addImage("Ŀ���׷�", "images/shop/grab.bmp", 50, 52, true, RGB(255, 0, 255));
	_grab._isopen = false;

	_openinventorywin = false;
	_itemcount = 0;

	//for (int i = 0; i < 20; i++) // ������ �ʱ�ȭ �ӽ÷� ����
	//{
	//	_vInven.push_back(ITEMMANAGER->addItem("����"));						//���� ����

	//}

	return S_OK;
}
void inventory::release()
{

}

void inventory::update()
{
	inventoryItem();

	for (_viInven = _vInven.begin(); _viInven != _vInven.end(); ++_viInven)  //�ӽ÷� �߰��س���
	{
		_vInven[0].setRect(_invenotryelement[0]._inventoryrect.left + 22, _invenotryelement[0]._inventoryrect.top + 22);
	}

		//_cursor->update();
	if (!_openinventorywin)   // �κ��丮 ��Ȱ��ȭ
	{
		if (KEYMANAGER->isOnceKeyDown('I'))				//I �κ��丮 ������
		{
			_openinventorywin = true; // �κ��丮Ȱ��ȭ
	  cursormove();
		}
	}
	else  // �κ��丮Ȱ��ȭ
	{
		if (KEYMANAGER->isOnceKeyDown('I'))
		{
			_openinventorywin = false;    // �κ��丮 ��Ȱ��ȭ
		}
	}
	ANIMATIONMANAGER->update();
	cursormove();  //Ŀ�� �̵� 

}

void inventory::cursormove()   //Ŀ�� �̵�  �Լ�
{
	_cursor->update(_cursorrect);						//���� �ʱ�ȭ
	if (KEYMANAGER->isOnceKeyDown('A'))		//����
	{
		_cursorNumber--;
		if (_cursorNumber < 0)_cursorNumber = 0;
		_cursorrect = RectMake(_invenotryelement[_cursorNumber]._inventoryrect.left, _invenotryelement[_cursorNumber]._inventoryrect.top, 40, 40);
		_cursor->setRc(_cursorrect);
		_cursor->getAni()->start();
	}
	if (KEYMANAGER->isOnceKeyDown('D'))			//������
	{
		_cursorNumber++;
		if (_cursorNumber > 20) _cursorNumber = 20;
		_cursorrect = RectMake(_invenotryelement[_cursorNumber]._inventoryrect.left, _invenotryelement[_cursorNumber]._inventoryrect.top, 40, 40);
		_cursor->setRc(_cursorrect);
		_cursor->getAni()->start();
	}
	if (KEYMANAGER->isOnceKeyDown('W'))			//��
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

		if()//��ġ�Ѵ�
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

void inventory::inventoryItem()				//�κ��丮 ���ĭ(_invenotryelement[i])�� ���� (_vInven[i])ĭ�� ��ġ�� ���Ͻ�Ű�� ���� �Լ�
{
	if (_openinventorywin)
	{
		for (int i = 0; i < 20; i++)
		{
			if (i < _vInven.size())		//���� �κ��丮 ĭ ��ü ũ�� ���� 
				_vInven[i].setRect(_invenotryelement[i]._inventoryrect); // �κ��丮 ĭ ��� ��ġ = ���� �κ��丮 ĭ ��ġ�� ���� ��Ŵ

			for (int j = _vInven.size(); j < 21; j++)
			{
				_vInven.push_back(ITEMMANAGER->addItem("�������"));   // 22ĭ�� ��� ����ִ� ��Ҹ� ���� ����������� ó���Ѵ�.
			}
		}
	}

}
void inventory::render()
{
	if (_openinventorywin)
	{
	char str[128];
	char moneystr[128];					//�÷��̾� �� 
	_bgimag->alphaRender(getMemDC(), 1000);   // ���ķ��� ó���� ���ȭ��
	_playerinventory._inventoryimg->render(getMemDC(), _playerinventory._inventoryrect.left, _playerinventory._inventoryrect.top);   //�÷��̾� �κ��丮

	IMAGEMANAGER->render("���ָӴ�", getMemDC(), _moneyicon.x, _moneyicon.y);

	IMAGEMANAGER->render("������", getMemDC(), _removeGlass._inventoryrect.left, _removeGlass._inventoryrect.top);

	for (int i = 0; i < 21; i++)
	{
		IMAGEMANAGER->render("���", getMemDC(), _invenotryelement[i]._inventoryrect.left, _invenotryelement[i]._inventoryrect.top);
	}

	for (int i = 0; i < _vInven.size(); i++) // �κ��丮 �ȿ� �������� �����ִ� for�� 
	{
		if (_vInven[i].getItemInfo().itemName != "�������")     // �������� ������
		{
			wsprintf(str, "%d", _vInven[i].getItemInfo().cnt);
			TextOut(getMemDC(), _vInven[i].getRECT().right, _vInven[i].getRECT().bottom, str, strlen(str));
			SetBkMode(getMemDC(), TRANSPARENT);				//���� �޹�� ó��
			//�浹ó��

		}
	}
	_cursor->render();


	//Rectangle(getMemDC(), _cursorrect.left, _cursorrect.top, _cursorrect.right, _cursorrect.bottom);
	if (KEYMANAGER->isToggleKey('1'))
	{
		Rectangle(getMemDC(), _cursorrect.left, _cursorrect.top, _cursorrect.right, _cursorrect.bottom);
		//Rectangle(getMemDC(), _invenotryelement[i]._inventoryrect.left, _invenotryelement[i]._inventoryrect.top, _invenotryelement[i]._inventoryrect.right, _invenotryelement[i]._inventoryrect.bottom);
	}


	if (_grab._isopen) //Ŀ���׷� ���� ���� bool  true��  ��� �����
	{
		_grab._grabimg->render(getMemDC(), _invenotryelement[_cursorNumber]._inventoryrect.left - 4, _invenotryelement[_cursorNumber]._inventoryrect.top - 50);

	}

	wsprintf(moneystr, "%d", PLAYER->getMoney());
	SetTextColor(CAMERAMANAGER->getCameraDC(), RGB(41, 41, 41));
	TextOut(CAMERAMANAGER->getCameraDC(), 304, 540, moneystr, strlen(moneystr));

	}
	itemrender();
}

void inventory::itemrender()  //item���͸� ���� ������
{
	for (_viInven = _vInven.begin(); _viInven != _vInven.end(); ++_viInven)
	{
		(*_viInven).render();
	}


}


/*
  �κ��丮 ����
 ���� 10 �������� 2�� �踷��� 2 õ 1 �踷��� 1

*/