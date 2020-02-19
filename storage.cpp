#include "stdafx.h"
#include "storage.h"

storage::storage()
{
}

storage::~storage()
{
}

HRESULT storage::init(string storageName, POINT xy)
{
	//â�� �ʱ�ȭ
	_name = storageName;
	_boxImg = IMAGEMANAGER->findImage(storageName);
	_boxRc = RectMakeCenter(xy.x, xy.y, _boxImg->getFrameWidth(), _boxImg->getFrameHeight());

	if (storageName == "â��1")_storageAni = ANIMATIONMANAGER->findAnimation("â��1����");
	if (storageName == "â��2")_storageAni = ANIMATIONMANAGER->findAnimation("â��2����");

	_mainImage = IMAGEMANAGER->findImage("â����");

	_showItem = IMAGEMANAGER->findImage("�ۺ����ֱ�");
	_showItemRc = RectMakeCenter(WINSIZEX - 70, 250, _showItem->getWidth(), _showItem->getHeight());

	//���Ժ��� �ʱ�ȭ
	for (int i = 0; i < SLOTNUM; i++)
	{
		int x, y;
		x = i % 7;
		y = i / 7;
		_slotInfo.img = IMAGEMANAGER->findImage("�����̹���");
		_slotInfo.x = WINSIZEX / 2 + (x * 60) + 20;
		_slotInfo.y = WINSIZEY / 2 - 80 + (y * 60) + 20;
		_slotInfo.rc = RectMakeCenter(_slotInfo.x, _slotInfo.y, _slotInfo.img->getWidth(), _slotInfo.img->getHeight());
		_slotInfo.item = ITEMMANAGER->addItem("õ");
		_slotInfo.item.setItemCnt(8);
		_slotInfo.item.setRect(_slotInfo.rc);
		_vSlot.push_back(_slotInfo);
	}
	//Ŀ�� �ʱ�ȭ
	_cursor = new cursor;
	_cursor->init();
	_cursorNum = 0;
	_cursorSlot = _vSlot[_cursorNum].rc;
	_cursor->setRc(_cursorSlot);
	_grab = new image;
	_grab = IMAGEMANAGER->findImage("Ŀ���׷�");


	return S_OK;
}

void storage::release()
{
	SAFE_DELETE(_cursor);
}

void storage::update()
{

	if (!_showWindow)
	{
		if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &_boxRc))
		{
			if (KEYMANAGER->isOnceKeyDown('J')) //����
			{
				if (_name == "â��1")_storageAni = ANIMATIONMANAGER->findAnimation("â��1����");
				if (_name == "â��2")_storageAni = ANIMATIONMANAGER->findAnimation("â��2����");
				_storageAni->start();

				_showWindow = true;
				_cursor->update(_cursorSlot);
				_cursorNum = 0;
				_cursorSlot = _vSlot[_cursorNum].rc;
				_cursor->setRc(_cursorSlot);
				PLAYER->getinventory()->setStprageOpen(true);  //--->������ â(�κ�) ���� 
			}
		}
	}
	else
	{
		if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &_boxRc))
		{
			if (KEYMANAGER->isOnceKeyDown('6')) //�ݱ�
			{
				if (_name == "â��1")_storageAni = ANIMATIONMANAGER->findAnimation("â��1Ŭ����");
				if (_name == "â��2")_storageAni = ANIMATIONMANAGER->findAnimation("â��2Ŭ����");

				_storageAni->start();
				PLAYER->getinventory()->setStprageOpen(false);			//--> ������â(�κ�) �ݱ�
				_showWindow = false;
			}
		}
		//playerCollision(); //����ݱ�
		//itemArrange();	   //Z��ư�� ������ â�� ����ִ� �͵��� �ڵ����� �������ִ� �Լ�...�̿ϼ�
		if (!PLAYER->getinventory()->getstorgeuding()) cursorControl();   //-->Ŀ����Ʈ�� WASD��ư
		else PLAYER->getinventory()->cursormove();				//-->Ŀ����Ʈ�� WASD��ư


		if (!PLAYER->getinventory()->getstorgeuding() && !PLAYER->getinventory()->getvTemp().empty())
		{
			slot temp;

			temp.img = PLAYER->getinventory()->getvTemp()[0]._inventoryimg;
			temp.item = PLAYER->getinventory()->getvTemp()[0]._item;

			_vTemp.push_back(temp);

			PLAYER->getinventory()->tempClear();
		}

		cursorControl();   //Ŀ����Ʈ�� WASD��ư
		grab();
		removeItem();	   //ī��Ʈ�� 0���� ������ �����۵��� ��� �����ش�. ������ �������� �ٽ� '�������'�� �־���
		setStorageItem();  //â����� ������ ��ġ�� ������Ʈ

		PLAYER->getinventory()->inventoryItem();						//			---> â���� �κ��丮�� ���¸� ��������ϸ� 
		PLAYER->getinventory()->grabitemremove();					//			--->  â���� (â���)�κ��丮 �������� ������ ���¸� �˾ƾ��Ѵ�. 

	}
}

void storage::render()
{
	PLAYER->getinventory()->moverender(getMemDC());
	_boxImg->aniRender(getMemDC(), _boxRc.left, _boxRc.top, _storageAni);
	//Rectangle(getMemDC(), _cursorSlot.left, _cursorSlot.top, _cursorSlot.right, _cursorSlot.bottom);

	if (!_showWindow)
	{
		if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &_boxRc))
		{
			IMAGEMANAGER->render("����", getMemDC(), _boxRc.right, _boxRc.top - 20);
		}
	}
	else
	{
		storageRender();
		if (_vTemp.size() > 0)	//������ ������� �ʴٸ�(Ŀ���� ���� ��� �ִٸ�)
		{
			char str[128];
			IMAGEMANAGER->render("Ŀ���׷�", getMemDC(), _cursorSlot.left, _cursorSlot.top - 60);
			_vTemp[0].item.getItemInfo().image->render(getMemDC(), _cursorSlot.left, _cursorSlot.top - 50);
			wsprintf(str, "%d", _vTemp[0].item.getItemInfo().cnt);
			TextOut(getMemDC(), _cursorSlot.right, _cursorSlot.top - 40, str, strlen(str));
		}
	}
}


void storage::setStorageItem()
{
	for (int i = 0; i < SLOTNUM; i++)
	{
		//â�� ������ �������� ��Ʈ�� ���Կ� �°� �ʱ�ȭ
		if (i < _vSlot.size())
		{
			_vSlot[i].item.setRect(_vSlot[i].rc);
		}
	}
}

void storage::storageRender()
{
	char str[128];

	//â����
	_mainImage->render(getMemDC(), WINSIZEX / 2 - 70, 100, _mainImage->getWidth(), _mainImage->getHeight());
	_showItem->render(getMemDC(), _showItemRc.left, _showItemRc.top, _showItem->getWidth(), _showItem->getHeight());

	//������ĭ ����. [] <<�̷��Ի����
	for (int i = 0; i < SLOTNUM; i++)
	{
		_vSlot[i].img->render(getMemDC(), _vSlot[i].rc.left, _vSlot[i].rc.top);
	}

	//���� â�� �ȿ� �������� ������ ���Կ� �������� ������.
	for (int i = 0; i < _vSlot.size(); i++)
	{
		if (_vSlot[i].item.getItemInfo().itemName != "�������") //�������� ������ ����
		{
			_vSlot[i].item.render();

			wsprintf(str, "%d", _vSlot[i].item.getItemInfo().cnt);
			TextOut(getMemDC(), _vSlot[i].rc.right, _vSlot[i].rc.bottom, str, strlen(str));

			// Ŀ���� �������� �浹�� ���¶�� �߰��� ��ĭ�� �̹����� �����
			if (IntersectRect(&temp, &_cursorSlot, &_vSlot[i].rc))
			{
				_vSlot[i].item.getItemInfo().image->render(getMemDC(), _showItemRc.left + 10, _showItemRc.top + 10);
			}
		}
	}

	if (!PLAYER->getinventory()->getstorgeuding()) _cursor->render();

}

void storage::cursorControl()
{
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		//Ŀ���� ������ ��������
		_cursorNum--;
		if (_cursorNum < 0)
		{
			_cursorNum = 0;
			PLAYER->getinventory()->setstorgeuding(true); //������ �κ��丮�� �ű��
			if (_vTemp.size() != 0) PLAYER->getinventory()->swapItem(_vTemp[0].item);
			_vTemp.clear();
		}
		_cursorSlot = _vSlot[_cursorNum].rc;
		_cursor->getAni()->start();
	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		//Ŀ���� ������ ��������
		_cursorNum++;
		if (_cursorNum > SLOTNUM) _cursorNum = SLOTNUM;
		_cursorSlot = _vSlot[_cursorNum].rc;
		_cursor->getAni()->start();
	}
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		//Ŀ���� ���θ�������
		int temp;
		temp = _cursorNum;
		_cursorNum -= 7;
		if (_cursorNum < 0)_cursorNum = temp;
		_cursorSlot = _vSlot[_cursorNum].rc;
		_cursor->getAni()->start();
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		//Ŀ���� �Ʒ��� ��������
		int temp;
		temp = _cursorNum;
		_cursorNum += 7;
		if (_cursorNum > SLOTNUM)_cursorNum = temp;

		_cursorSlot = _vSlot[_cursorNum].rc;
		_cursor->getAni()->start();
	}
	_cursor->setRc(_cursorSlot);

	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		_cursor->getAni()->start();
	}
}

void storage::itemArrange() //�̿ϼ�
{
	//if (KEYMANAGER->isOnceKeyDown('1'))
	//{
	//	for (int k = 0; k < _vStorage.size(); k++)//������ ������ ������ ���Ƽ�
	//	{
	//		if (_vStorage[k].maxItem() == false) // ���� �������� �ִ밹���� �ƴ϶�� 
	//		{
	//			for (int j = k + 1; j < _vStorage.size(); j++) //�� �����ۺ��� �����ؼ� ������ ���Ƽ� 
	//			{
	//				if (_vStorage[k].getItemInfo().itemName == _vStorage[j].getItemInfo().itemName)
	//				{
	//					//���� �������� ������ ��������
	//					_vStorage[k].setItemCnt();
	//					_vStorage.erase(_vStorage.begin() + j);
	//					if (_vStorage[k].getItemInfo().cnt >= _vStorage[k].getItemInfo().maxCnt)
	//					{
	//						//�׷��� �ִ밹���� �����ϸ� �ִ밹���� �ٲ��־� ��������
	//						_vStorage[k].maxItem();
	//					}
	//					//break;
	//				}
	//			}
	//		}
	//	}
	//}
}

void storage::removeItem()
{
	for (int i = 0; i < _vSlot.size(); i++)
	{
		if (_vSlot[i].item.getItemInfo().cnt <= 0)
		{
			_vSlot[i].item = ITEMMANAGER->addItem("�������");
			_vSlot[i].item.setItemCnt_equal(1);
		}
	}
}

void storage::grab()
{
	for (int i = 0; i < _vSlot.size(); i++)
	{
		if (_vSlot[i].item.getItemInfo().itemName != "�������") //â�� ���� ������� �ʰ�
		{
			if ((_cursorNum == i) && KEYMANAGER->isOnceKeyDown('J'))// Ŀ���� �������� �浹�� ���¶��
			{
				_cursor->getAni()->start();

				//�ӽú��Ͱ� ��������� ���Ϳ� �߰�
				if (_vTemp.empty())
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

		if (!_vTemp.empty())	//������ ������� �ʴٸ�(�������� ��� �ִٸ�)
		{
			if (_vSlot[i].item.getItemInfo().itemName == "�������") //����ִ� ����
			{
				if ((_cursorNum == i) && KEYMANAGER->isOnceKeyDown('J'))//j�� ������ �������� �� �ڸ��� ����
				{
					_cursor->getAni()->start();
					_vSlot[i].item = _vTemp[0].item;

					_vTemp.pop_back();
					break;
				}
			}
		}

	}
}

