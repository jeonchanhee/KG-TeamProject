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
	_boxImg = IMAGEMANAGER->findImage(storageName);
	_boxRc = RectMakeCenter(xy.x,xy.y , _boxImg->getFrameWidth(), _boxImg->getFrameHeight());

	if(storageName=="â��1")_storageAni = ANIMATIONMANAGER->findAnimation("â��1����");
	if(storageName=="â��2")_storageAni = ANIMATIONMANAGER->findAnimation("â��2����");

	_mainImage = IMAGEMANAGER->findImage("â����");

	_showItem = IMAGEMANAGER->findImage("�ۺ����ֱ�");
	_showItemRc = RectMakeCenter(WINSIZEX - 70, 250, _showItem->getWidth(), _showItem->getHeight());

	//â���κ��丮 ���� �ʱ�ȭ
	for (int i = 0; i < SLOTNUM; i++)
	{
		int k, j;
		k = i % 7;
		j = i / 7;
		_slot[i] = RectMakeCenter(WINSIZEX / 2 + 20 + (k * 60), WINSIZEY / 2 - 60 + (j * 60), 40, 40);
		_slotImage[i] = IMAGEMANAGER->findImage("�����̹���");
	}

	//Ŀ�� �ʱ�ȭ
	_choiceNum = 0;
	_choiceSlot = _slot[_choiceNum];
	_cursor = new cursor;
	_cursor->init();
	_grab = new image;
	_grab = IMAGEMANAGER->addImage("Ŀ���׷�", "images/shop/grab.bmp", 50, 52, true, RGB(255, 0, 255));


	//�ӽ÷� �־��
	_vStorage.push_back(ITEMMANAGER->addItem("��������"));
	_vStorage.push_back(ITEMMANAGER->addItem("��������"));
	_vStorage.push_back(ITEMMANAGER->addItem("��������"));
	_vStorage.push_back(ITEMMANAGER->addItem("��������"));
	_vStorage.push_back(ITEMMANAGER->addItem("��������"));
	_vStorage.push_back(ITEMMANAGER->addItem("��������"));
	_vStorage.push_back(ITEMMANAGER->addItem("��������"));
	_vStorage.push_back(ITEMMANAGER->addItem("��������"));
	_vStorage.push_back(ITEMMANAGER->addItem("��������"));
	_vStorage.push_back(ITEMMANAGER->addItem("��������"));
	_vStorage.push_back(ITEMMANAGER->addItem("��������"));
	_vStorage.push_back(ITEMMANAGER->addItem("��������"));
	_vStorage.push_back(ITEMMANAGER->addItem("õ"));
	_vStorage.push_back(ITEMMANAGER->addItem("õ"));
	_vStorage.push_back(ITEMMANAGER->addItem("õ"));
	_vStorage.push_back(ITEMMANAGER->addItem("õ"));




	return S_OK;
}

void storage::release()
{
}

void storage::update()
{
	itemArrange();	   //Z��ư�� ������ â�� ����ִ� �͵��� �ڵ����� �������ִ� �Լ�...�̿ϼ�
	cursorControl();   //Ŀ����Ʈ�� WASD��ư
	setStorageItem();  // â����� ������ ��ġ�� ������Ʈ
	removeItem();
}

void storage::render()
{
	storageRender();
	//Rectangle(getMemDC(), _choiceSlot.left, _choiceSlot.top, _choiceSlot.right, _choiceSlot.bottom);
	if (_vTemp.size() > 0)
	{
		char str[128];
		IMAGEMANAGER->render("Ŀ���׷�", getMemDC(), _choiceSlot.left, _choiceSlot.top - 60);
		_vTemp[0].getItemInfo().image->render(getMemDC(), _choiceSlot.left, _choiceSlot.top - 50);
		wsprintf(str, "%d", _vTemp[0].getItemInfo().cnt);
		TextOut(getMemDC(), _choiceSlot.right, _choiceSlot.top - 40, str, strlen(str));
	}
}


void storage::setStorageItem()
{

	if (_showWindow)
	{
		for (int i = 0; i < SLOTNUM; i++)
		{
			//â�� ������ �������� ��Ʈ�� ���Կ� �°� �ʱ�ȭ
			if (i < _vStorage.size())
			{
				_vStorage[i].setRect(_slot[i]);
			}

		}
	}
}

void storage::storageRender()
{
	_boxImg->aniRender(getMemDC(), _boxRc.left, _boxRc.top, _storageAni);

	if (_showWindow)
	{
		//â���ο� ���� �������̹��� ����ִ�â
		char str[128];
		_mainImage->render(getMemDC(), WINSIZEX / 2 - 70, 100, _mainImage->getWidth(), _mainImage->getHeight());
		_showItem->render(getMemDC(), _showItemRc.left, _showItemRc.top, _showItem->getWidth(), _showItem->getHeight());

		//������ĭ ����. [] <<�̷��Ի����
		for (int i = 0; i < SLOTNUM; i++)
		{
			_slotImage[i]->render(getMemDC(), _slot[i].left, _slot[i].top);
		}

		//���� â�� �ȿ� �������� ������ ���Կ� �������� ������.
		for (int i = 0; i < _vStorage.size(); i++)
		{
			if (_vStorage[i].getItemInfo().itemName != "�������") //�������� ������ ����
			{
				_vStorage[i].render();

				wsprintf(str, "%d", _vStorage[i].getItemInfo().cnt);
				TextOut(getMemDC(), _vStorage[i].getRECT().right, _vStorage[i].getRECT().bottom, str, strlen(str));
				if (IntersectRect(&temp, &_choiceSlot, &_vStorage[i].getRECT()))// Ŀ���� �������� �浹�� ���¶�� 
				{
					_vStorage[i].getItemInfo().image->render(getMemDC(), _showItemRc.left+10, _showItemRc.top+10);
				}
			}
		}

		_cursor->render();

		if (KEYMANAGER->isToggleKey('T'))//�����
		{
			Rectangle(getMemDC(), _choiceSlot.left, _choiceSlot.top, _choiceSlot.right, _choiceSlot.bottom);
		}
	}
}

void storage::cursorControl()
{
	if (_showWindow)
	{
		_cursor->update(_choiceSlot);
		if (KEYMANAGER->isOnceKeyDown('A'))
		{
			//Ŀ���� ������ ��������
			_choiceNum--;
			if (_choiceNum < 0) _choiceNum = 0;

			_choiceSlot = RectMake(_slot[_choiceNum].left, _slot[_choiceNum].top, 40, 40);
			_cursor->setRc(_choiceSlot);
			_cursor->getAni()->start();
		}
		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			//Ŀ���� ������ ��������
			_choiceNum++;
			if (_choiceNum > SLOTNUM) _choiceNum = SLOTNUM;

			_choiceSlot = RectMake(_slot[_choiceNum].left, _slot[_choiceNum].top, 40, 40);
			_cursor->setRc(_choiceSlot);
			_cursor->getAni()->start();
		}
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			//Ŀ���� ���θ�������
			int temp;
			temp = _choiceNum;
			_choiceNum-=7;
			if (_choiceNum < 0)_choiceNum = temp;

			_choiceSlot = RectMake(_slot[_choiceNum].left, _slot[_choiceNum].top, 40, 40);
			_cursor->setRc(_choiceSlot);
			_cursor->getAni()->start();
		}
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			//Ŀ���� �Ʒ��� ��������
			int temp;
			temp = _choiceNum;
			_choiceNum+=7;
			if (_choiceNum > SLOTNUM)_choiceNum = temp;

			_choiceSlot = RectMake(_slot[_choiceNum].left, _slot[_choiceNum].top, 40, 40);
			_cursor->setRc(_choiceSlot);
			_cursor->getAni()->start();
		}

		if (KEYMANAGER->isOnceKeyDown('I'))
		{
			_cursor->getAni()->start();
		}
		grab();
	}
}

void storage::itemArrange() //�̿ϼ�
{
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		for (int k = 0; k < _vStorage.size(); k++)//������ ������ ������ ���Ƽ�
		{
			if (_vStorage[k].maxItem() == false) // ���� �������� �ִ밹���� �ƴ϶�� 
			{
				for (int j = k + 1; j < _vStorage.size(); j++) //�� �����ۺ��� �����ؼ� ������ ���Ƽ� 
				{
					if (_vStorage[k].getItemInfo().itemName == _vStorage[j].getItemInfo().itemName)
					{
						//���� �������� ������ ��������
						_vStorage[k].setItemCnt();
						_vStorage.erase(_vStorage.begin() + j);
						if (_vStorage[k].getItemInfo().cnt >= _vStorage[k].getItemInfo().maxCnt)
						{
							//�׷��� �ִ밹���� �����ϸ� �ִ밹���� �ٲ��־� ��������
							_vStorage[k].maxItem();
						}
						//break;
					}
				}
			}
		}
	}
}

void storage::resetChoiceNum()
{
	//â�� â�� ���������� Ŀ����ġ �ʱ�ȭ
	_choiceNum = 0; 
	_choiceSlot = _slot[_choiceNum];
}

void storage::removeItem()
{
	for (int i = 0; i < _vStorage.size(); i++)
	{
		if(_vStorage[i].getItemInfo().cnt == 0)
		{
			_vStorage.erase(_vStorage.begin() + i);
		}
	}
}

void storage::grab()
{

	for (int i = 0; i < _vStorage.size(); i++)
	{
		if (_vStorage[i].getItemInfo().itemName != "�������") //â�� ���� ������� �ʰ�
		{
			if ((_choiceNum == i )&& KEYMANAGER->isOnceKeyDown('J'))// Ŀ���� �������� �浹�� ���¶��
			{
					_cursor->getAni()->start();
		
					//�ӽú��Ͱ� ��������� ���Ϳ� �߰�
					if (_vTemp.size() <= 0) 
					{
						_vTemp.push_back(_vStorage[i]);
						_vStorage.erase(_vStorage.begin() + i);
						_vStorage.insert(_vStorage.begin() + i, ITEMMANAGER->addItem("�������"));
						break;
					}

					//�ӽú��Ϳ� �̹� ���� �̸��� �������� ������ ī��Ʈ�� �÷���
					if (_vTemp[0].getItemInfo().itemName == _vStorage[i].getItemInfo().itemName &&
						(_vStorage[i].getItemInfo().cnt+_vTemp[0].getItemInfo().cnt)<= _vTemp[0].getItemInfo().maxCnt) 
					{
						_vTemp[0].setItemCnt(_vStorage[i].getItemInfo().cnt);
						_vStorage.erase(_vStorage.begin() + i);
						_vStorage.insert(_vStorage.begin() + i, ITEMMANAGER->addItem("�������"));
						break;
					}
			}
		}

		if (_vTemp.size() > 0)
		{
			if (_vStorage[i].getItemInfo().itemName == "�������") //����ִ� ����
			{
				if ((_choiceNum == i) && KEYMANAGER->isOnceKeyDown('J'))//j�� ������ �������� �� �ڸ��� ����
				{
					_cursor->getAni()->start();

					_vStorage.erase(_vStorage.begin() + i);
					_vStorage.insert(_vStorage.begin() + i, _vTemp[0]);
					_vTemp.pop_back();
					break;
				}
			}
		}

	}
}
