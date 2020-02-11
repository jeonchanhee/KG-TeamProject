#include "stdafx.h"
#include "blacksmith.h"

blacksmith::blacksmith()
{
}

blacksmith::~blacksmith()
{
}

HRESULT blacksmith::init()
{
	//�̹��� �ʱ�ȭ
	_armorTabImg = IMAGEMANAGER->findImage("�Ƹӽ���");
	_bowTabImg = IMAGEMANAGER->findImage("���콽��");
	_swordTabImg = IMAGEMANAGER->findImage("�ҵ彽��");
	_titleImg = IMAGEMANAGER->findImage("Ÿ��Ʋ");
	_showImg = IMAGEMANAGER->findImage("�����ۺ����ִ�â");
	_npcImg = IMAGEMANAGER->findImage("����");
	_recipeImg = IMAGEMANAGER->findImage("���׷��̵巹����");
	OKcnt = 0;
	for (int i = 0; i < 9; i++)
	{
		_itemSlotImg[i] = IMAGEMANAGER->findImage("�����̹���");
	}
	for (int i = 0; i < 3; i++)
	{
		_recipeSlotImg[i] = IMAGEMANAGER->findImage("�����̹���");
	}

	//��Ʈ�ʱ�ȭ
	_armorTab = RectMakeCenter(WINSIZEX / 2 - 160, WINSIZEY / 2 - 280, _armorTabImg->getWidth(), _armorTabImg->getWidth());
	_swordTab = RectMakeCenter(WINSIZEX / 2 - 100, WINSIZEY / 2 - 280, _swordTabImg->getWidth(), _swordTabImg->getHeight());
	_bowTab = RectMakeCenter(WINSIZEX / 2 - 40, WINSIZEY / 2 - 280, _bowTabImg->getWidth(), _bowTabImg->getHeight());

	_itemSlot[0]= RectMakeCenter(WINSIZEX / 2 - 160, WINSIZEY / 2 - 170, _itemSlotImg[0]->getWidth(), _itemSlotImg[0]->getHeight());

	//���׷��̵� �� �����ִ� ������ ��Ʈ
	for (int i = 1; i < 9; i++)
	{
		if (i < 5)
		{
			_itemSlot[i] = RectMakeCenter(_itemSlot[0].right-20 + (i * 60), _itemSlot[0].top - 10, _itemSlotImg[i]->getWidth(), _itemSlotImg[i]->getWidth());
		}
		if (i >= 5)
		{
			_itemSlot[i] = RectMakeCenter(_itemSlot[0].right-20 + ((i%5+1)* 60), _itemSlot[0].bottom +10, _itemSlotImg[i]->getWidth(), _itemSlotImg[i]->getWidth());
		}
	}


	_npcRc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 - 200, 100, 100);

	_currentTab = 0;  //������

	//Ŀ���ʱ�ȭ
	_choiceNum = 1;
	_choiceSlot = _itemSlot[_choiceNum];
	_cursor = new cursor;
	_cursor->init();
	_grab = new image;
	_grab = IMAGEMANAGER->addImage("Ŀ���׷�", "images/shop/grab.bmp", 50, 52, true, RGB(255, 0, 255));

	//�����ʱ�ȭ
	_vShowItem.push_back(ITEMMANAGER->addItem("�Ʒÿ� �ܰ�"));
	_vShowItem.push_back(ITEMMANAGER->addItem("�������� �ܰ�"));
	_vShowItem.push_back(ITEMMANAGER->addItem("ĳ����Ʈ ����"));
	_vShowItem.push_back(ITEMMANAGER->addItem("�÷��� ����"));
	_vShowItem.push_back(ITEMMANAGER->addItem("õ �ݴٳ�"));
	_vShowItem.push_back(ITEMMANAGER->addItem("õ �䰩"));

	return S_OK;
}

void blacksmith::release()
{
}

void blacksmith::update()
{
	tabControl();		
	cursorControl();
	//setRecipeItem();

	//���׷��̵� ������ ��Ʈ �ʱ�ȭ
	switch (_currentTab)
	{
	case 0:
		a = 1;
		for (int i = 0; i < _vShowItem.size(); i++)
		{
			if (_vShowItem[i].getItemInfo().type == ITEM_ARMOR)
			{
				_vShowItem[i].setRect(_itemSlot[a]);
				a += 4;
			}
			if (_vShowItem[i].getItemInfo().type == ITEM_HELMET)
			{
				_vShowItem[i].setRect(_itemSlot[a]);
				a += 4;
			}
			else _vShowItem[i].setRect(_itemSlot[99]);
		}
		break;
	case 1:
		a = 0;
		for (int i = 0; i < _vShowItem.size(); i++)
		{
			if (_vShowItem[i].getItemInfo().type == ITEM_SWORD)
			{
				_vShowItem[i].setRect(_itemSlot[a]);
				a++;
			}
			else _vShowItem[i].setRect(_itemSlot[99]);
		}
		break;
	case 2:
		a = 0;
		for (int i = 0; i < _vShowItem.size(); i++)
		{
			if (_vShowItem[i].getItemInfo().type == ITEM_BOW)
			{
				_vShowItem[i].setRect(_itemSlot[a]);
				a++;
			}
			else _vShowItem[i].setRect(_itemSlot[99]);
		}
		break;
	}
	setRecipeItem();
}

void blacksmith::render()
{
	Rectangle(getMemDC(), _npcRc.left, _npcRc.top, _npcRc.right, _npcRc.bottom);

	if (_showWindow)
	{
		_armorTabImg->render(getMemDC(), _armorTab.left, _armorTab.top);
		_swordTabImg->render(getMemDC(), _swordTab.left, _swordTab.top);
		_bowTabImg->render(getMemDC(), _bowTab.left, _bowTab.top);
		_showImg->render(getMemDC(), WINSIZEX / 2-250, WINSIZEY / 2-300);
		_recipeImg->render(getMemDC(), WINSIZEX - 350, 60);

		for (int i = 0 ; i < 3; i++)
		{
			_recipeSlotImg[i]->render(getMemDC(), WINSIZEX/2 + 200, WINSIZEY/2+ 50+(i* 70));
			if (_vShowRecipe.size()-1 >= i && _vShowRecipe.size()>0)
			{
				_vShowRecipe[i].getItemInfo().image->render(getMemDC(), WINSIZEX / 2 + 200, WINSIZEY / 2 + 50 + (i * 70));
			}
		}
		//���׷��̵� �������� ������
		switch (_currentTab)
		{
		case 0:
			for (int i = 1; i < 9; i++)
			{
				_itemSlotImg[i]->render(getMemDC(), _itemSlot[i].left, _itemSlot[i].top);
			}
			for (int i = 0; i < _vShowItem.size(); i++)
			{
				if (_vShowItem[i].getItemInfo().type == ITEM_ARMOR)
				{
					_vShowItem[i].render();
				}
				if (_vShowItem[i].getItemInfo().type == ITEM_HELMET)
				{
					_vShowItem[i].render();
				}
			}
			break;
		case 1:
			for (int i = 0; i < 9; i++)
			{
				_itemSlotImg[i]->render(getMemDC(), _itemSlot[i].left, _itemSlot[i].top);
			}
			for (int i = 0; i < _vShowItem.size(); i++)
			{
				if (_vShowItem[i].getItemInfo().type == ITEM_SWORD)
				{
					_vShowItem[i].render();
				}
			}
			break;
		case 2:
			for (int i = 0; i < 9; i++)
			{
				_itemSlotImg[i]->render(getMemDC(), _itemSlot[i].left, _itemSlot[i].top);
			}
			for (int i = 0; i < _vShowItem.size(); i++)
			{
				if (_vShowItem[i].getItemInfo().type == ITEM_BOW)
				{
					_vShowItem[i].render();
				}
			}
			break;
		}

		_cursor->render();
	}

}

void blacksmith::cursorControl()
{
	if (_showWindow)
	{
		_cursor->update(_choiceSlot);
		if (KEYMANAGER->isOnceKeyDown('A'))
		{
			//Ŀ���� ������ ��������
			_choiceNum--;
			if (_choiceNum < 0) _choiceNum = 0;

			_choiceSlot = RectMake(_itemSlot[_choiceNum].left, _itemSlot[_choiceNum].top, 40, 40);
			_cursor->setRc(_choiceSlot);
			_cursor->getAni()->start();
		}
		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			//Ŀ���� ������ ��������
			_choiceNum++;
			if (_choiceNum > SLOTNUM) _choiceNum = SLOTNUM;

			_choiceSlot = RectMake(_itemSlot[_choiceNum].left, _itemSlot[_choiceNum].top, 40, 40);
			_cursor->setRc(_choiceSlot);
			_cursor->getAni()->start();
		}
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			//Ŀ���� ���θ�������
			int temp;
			temp = _choiceNum;
			_choiceNum -= 4;
			if (_choiceNum <= 0)_choiceNum = temp;

			_choiceSlot = RectMake(_itemSlot[_choiceNum].left, _itemSlot[_choiceNum].top, 40, 40);
			_cursor->setRc(_choiceSlot);
			_cursor->getAni()->start();
		}
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			//Ŀ���� �Ʒ��� ��������
			int temp;
			temp = _choiceNum;
			_choiceNum += 4;
			if (_choiceNum >= SLOTNUM)_choiceNum = temp;

			_choiceSlot = RectMake(_itemSlot[_choiceNum].left, _itemSlot[_choiceNum].top, 40, 40);
			_cursor->setRc(_choiceSlot);
			_cursor->getAni()->start();
		}

		if (KEYMANAGER->isOnceKeyDown('I'))
		{
			_cursor->getAni()->start();
		}
		
	}
}

void blacksmith::tabControl()
{
	if (_showWindow)
	{
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			_currentTab--;

			if (_currentTab <= 0)
			{
				_currentTab = 0;
				_choiceNum = 1;
				_choiceSlot = _itemSlot[_choiceNum];
			}
		}
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			_currentTab++;
			if (_currentTab >= 1) 
			{
				_choiceNum = 0;
				_choiceSlot = _itemSlot[_choiceNum];
			}
			if (_currentTab >= 2)_currentTab = 2;
		}
	}
	_armorTab = RectMakeCenter(WINSIZEX / 2 - 160, WINSIZEY / 2 - 280, _armorTabImg->getWidth(), _armorTabImg->getWidth());
	_swordTab = RectMakeCenter(WINSIZEX / 2 - 100, WINSIZEY / 2 - 280, _swordTabImg->getWidth(), _swordTabImg->getHeight());
	_bowTab = RectMakeCenter(WINSIZEX / 2 -40, WINSIZEY / 2 - 280, _bowTabImg->getWidth(), _bowTabImg->getHeight());

	switch (_currentTab)
	{
	case 0:
		_armorTab = RectMakeCenter(WINSIZEX / 2 - 160, WINSIZEY / 2 - 300, _armorTabImg->getWidth(), _armorTabImg->getWidth());
		break;
	case 1:
		_swordTab = RectMakeCenter(WINSIZEX / 2 - 100, WINSIZEY / 2 - 300, _swordTabImg->getWidth(), _swordTabImg->getHeight());
		break;
	case 2:
		_bowTab = RectMakeCenter(WINSIZEX / 2 - 40, WINSIZEY / 2 - 300, _bowTabImg->getWidth(), _bowTabImg->getHeight());
		break;
	}
}

void blacksmith::setRecipeItem()
{
	for (int i = 0; i < _vShowItem.size(); i++)
	{
		//Ŀ���� ���׷��̵�������� ������ ���������� �����ȴ�
		if (IntersectRect(&temp, &_choiceSlot, &_vShowItem[i].getRECT()))
		{
			//������ ���õ� �������� ����
			if (_vShowItem[i].getItemInfo().itemName == "�Ʒÿ� �ܰ�")
			{
				/*_vTemp.clear();
				_vTemp.push_back(_vShowItem[i]);*/
				_temp = _vShowItem[i];
				_vShowRecipe.clear();
				_vShowRecipe.push_back(ITEMMANAGER->addItem("��������"));
				_vShowRecipe[0].setItemCnt(3);
				OKcnt = _vShowRecipe[0].getItemInfo().cnt; //����۰���. = 4
				break;
			}
			if (_vShowItem[i].getItemInfo().itemName == "ĳ����Ʈ ����")
			{
				/*_vTemp.clear();
				_vTemp.push_back(_vShowItem[i]);*/
				_temp = _vShowItem[i];

				_vShowRecipe.clear();
				_vShowRecipe.push_back(ITEMMANAGER->addItem("���ھ�"));
				_vShowRecipe[0].setItemCnt(3);
				OKcnt = _vShowRecipe[0].getItemInfo().cnt; //����۰���. = 4
				break;
			}
			if (_vShowItem[i].getItemInfo().itemName == "õ �ݴٳ�")
			{
				/*_vTemp.clear();
				_vTemp.push_back(_vShowItem[i]);*/
				_temp = _vShowItem[i];

				_vShowRecipe.clear();
				_vShowRecipe.push_back(ITEMMANAGER->addItem("õ"));
				_vShowRecipe[0].setItemCnt(1);
				OKcnt = _vShowRecipe[0].getItemInfo().cnt; //����۰���. = 4
				break;
			}
		}
	}
}

void blacksmith::buyItem(vector<item> &storage)
{
	if (_showWindow)
	{
		if (KEYMANAGER->isOnceKeyDown('0'))
		{
			for (int j = 0; j < _vShowRecipe.size(); j++)
			{
				for (int k = 0; k < storage.size(); k++)
				{
					if (_vShowRecipe[j].getItemInfo().itemName == storage[k].getItemInfo().itemName)
					{
						if (OKcnt > 0)
						{
							OKcnt -= storage[k].getItemInfo().cnt;
							storage[k].setItemCnt(-storage[k].getItemInfo().cnt);
						}

						if (OKcnt == 0)
						{
							storage.push_back(_temp);
							break;
						}

						if (OKcnt < 0)
						{
							storage[k].setItemCnt(abs(0 - OKcnt));
							storage.push_back(_temp);
							break;
						}
					}
				}//����۰� â����� ���� ������
			}
		}

	}
}
