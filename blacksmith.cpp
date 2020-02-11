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

	//���׷��̵� �� �����ִ� ������ ��Ʈ�ʱ�ȭ
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
	_itemSetSlot = 0;
	_currentTab = 0;  //������

	//Ŀ���ʱ�ȭ
	_cursorNum = 1;
	_cursorSlot = _itemSlot[_cursorNum];
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
	cursorControl();
	tabControl();
	setRecipeItem();
}

void blacksmith::render()
{
	Rectangle(getMemDC(), _npcRc.left, _npcRc.top, _npcRc.right, _npcRc.bottom);

	if (_showWindow)
	{
		//�⺻���� ����
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

		//���� �����ִ� �ǿ� ���� ����.(0�� 1�� 2Ȱ)
		switch (_currentTab)
		{
		case 0:
			for (int i = 1; i < 9; i++)
			{
				_itemSlotImg[i]->render(getMemDC(), _itemSlot[i].left, _itemSlot[i].top);
			}
			TextOut(getMemDC(), WINSIZEX / 2- 180, 110, "��", strlen("��"));
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
			TextOut(getMemDC(), WINSIZEX / 2- 180, 110, "�˰� ����", strlen("�˰� ����"));
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
			TextOut(getMemDC(), WINSIZEX/2-180, 110, "Ȱ", strlen("Ȱ"));
			for (int i = 0; i < _vShowItem.size(); i++)
			{
				if (_vShowItem[i].getItemInfo().type == ITEM_BOW)
				{
					_vShowItem[i].render();
				}
			}
			break;
		}

		//����=���� Ŀ���� ����Ű�� �ִ� ������.
		_temp.getItemInfo().image->render(getMemDC(), WINSIZEX - 120, 80);

		//������ �κп� ���� Ŀ���� ����Ű�� �ִ� ���׷��̵� �������� ����,��� ����� ����
		wsprintf(str, "%d", _temp.getItemInfo().hp);
		TextOut(getMemDC(), WINSIZEX - 250 ,150, str, strlen(str));
		wsprintf(str, "%d", _temp.getItemInfo().atk);
		TextOut(getMemDC(), WINSIZEX - 250, 190, str, strlen(str));
		wsprintf(str, "%d", _temp.getItemInfo().def);
		TextOut(getMemDC(), WINSIZEX - 250, 230, str, strlen(str));
		wsprintf(str, "%d", _temp.getItemInfo().speed);
		TextOut(getMemDC(), WINSIZEX - 250, 270, str, strlen(str));
		wsprintf(str, "%d", _temp.getItemInfo().orignalPrice/2);
		TextOut(getMemDC(), WINSIZEX - 130, 370, str, strlen(str));
		for (int i = 0; i < _vShowRecipe.size(); i++)
		{
			wsprintf(str, "�ʿ� : %d", _vShowRecipe[i].getItemInfo().cnt);
			TextOut(getMemDC(), WINSIZEX - 250, WINSIZEY/2 +70 + (i*60), str, strlen(str));
		}

		_cursor->render();
	}
}

void blacksmith::cursorControl()
{
	if (_showWindow)
	{
		if (KEYMANAGER->isOnceKeyDown('A'))
		{
			//Ŀ���� ������ ��������
			_cursorNum--;
			if (_cursorNum < 0) _cursorNum = 0;
			if (_currentTab == 0 && _cursorNum <= 1)_cursorNum = 1;

			_cursorSlot = RectMake(_itemSlot[_cursorNum].left, _itemSlot[_cursorNum].top, 40, 40);
			_cursor->getAni()->start();
		}
		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			//Ŀ���� ������ ��������
			int temp;
			temp = _cursorNum;
			_cursorNum++;
			if (_cursorNum >= SLOTNUM) _cursorNum = temp;

			_cursorSlot = RectMake(_itemSlot[_cursorNum].left, _itemSlot[_cursorNum].top, 40, 40);
			_cursor->getAni()->start();
		}
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			//Ŀ���� ���θ�������
			int temp;
			temp = _cursorNum;
			_cursorNum -= 4;
			if (_cursorNum <= 0)_cursorNum = temp;

			_cursorSlot = RectMake(_itemSlot[_cursorNum].left, _itemSlot[_cursorNum].top, 40, 40);
			_cursor->getAni()->start();
		}
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			//Ŀ���� �Ʒ��� ��������
			int temp;
			temp = _cursorNum;
			_cursorNum += 4;
			if (_cursorNum >= SLOTNUM)_cursorNum = temp;

			_cursorSlot = RectMake(_itemSlot[_cursorNum].left, _itemSlot[_cursorNum].top, 40, 40);
			_cursor->getAni()->start();
		}
		_cursor->setRc(_cursorSlot);
	}
}

void blacksmith::tabControl()
{
	if (_showWindow)
	{
		if (KEYMANAGER->isOnceKeyDown('X')) //���� �ű�� Ŀ�� ��ġ �ʱ�ȭ
		{
			_currentTab--;

			if (_currentTab <= 0)
			{
				_currentTab = 0;
				_cursorNum = 1;
				_cursorSlot = _itemSlot[_cursorNum];
				//�� ���� Ŀ���� 0�� ĭ���Ͱ� �ƴ� 1��ĭ���� ������..
			}
		}
		if (KEYMANAGER->isOnceKeyDown('C'))//���� �ű�� Ŀ�� ��ġ �ʱ�ȭ
		{
			_currentTab++;
			if (_currentTab >= 1) 
			{
				_cursorNum = 0;
				_cursorSlot = _itemSlot[_cursorNum];
			}
			if (_currentTab >= 2)_currentTab = 2;
		}
	}
	_armorTab = RectMakeCenter(WINSIZEX / 2 - 160, WINSIZEY / 2 - 280, _armorTabImg->getWidth(), _armorTabImg->getWidth());
	_swordTab = RectMakeCenter(WINSIZEX / 2 - 100, WINSIZEY / 2 - 280, _swordTabImg->getWidth(), _swordTabImg->getHeight());
	_bowTab = RectMakeCenter(WINSIZEX / 2 -40, WINSIZEY / 2 - 280, _bowTabImg->getWidth(), _bowTabImg->getHeight());

	switch (_currentTab)  //�̺κ� �߸���... �̿ϼ�
	{
	case 0:
		_armorTab = RectMakeCenter(WINSIZEX / 2 - 160, WINSIZEY / 2 - 300, _armorTabImg->getWidth(), _armorTabImg->getWidth());
		_itemSetSlot = 1;
		for (int i = 0; i < _vShowItem.size(); i++)
		{
			if (_vShowItem[i].getItemInfo().type == ITEM_ARMOR)
			{
				_vShowItem[i].setRect(_itemSlot[_itemSetSlot]);

				_itemSetSlot += 4;
			}
			if (_vShowItem[i].getItemInfo().type == ITEM_HELMET)
			{
				_vShowItem[i].setRect(_itemSlot[_itemSetSlot]);
				_itemSetSlot += 4;
			}
			if (_vShowItem[i].getItemInfo().type == ITEM_BOOTS)
			{
				_vShowItem[i].setRect(_itemSlot[_itemSetSlot]);
				_itemSetSlot += 4;
			}
			else if(_vShowItem[i].getItemInfo().type != ITEM_BOOTS && _vShowItem[i].getItemInfo().type != ITEM_HELMET && _vShowItem[i].getItemInfo().type != ITEM_ARMOR)
				_vShowItem[i].setRect(_itemSlot[99]);
		}
		break;
	case 1:
		_swordTab = RectMakeCenter(WINSIZEX / 2 - 100, WINSIZEY / 2 - 300, _swordTabImg->getWidth(), _swordTabImg->getHeight());
		_itemSetSlot = 0;
		for (int i = 0; i < _vShowItem.size(); i++)
		{
			if (_vShowItem[i].getItemInfo().type == ITEM_SWORD)
			{
				_vShowItem[i].setRect(_itemSlot[_itemSetSlot]);
				_itemSetSlot++;
			}
			else _vShowItem[i].setRect(_itemSlot[99]);
		}
		break;
	case 2:
		_bowTab = RectMakeCenter(WINSIZEX / 2 - 40, WINSIZEY / 2 - 300, _bowTabImg->getWidth(), _bowTabImg->getHeight());
		_itemSetSlot = 0;
		for (int i = 0; i < _vShowItem.size(); i++)
		{
			if (_vShowItem[i].getItemInfo().type == ITEM_BOW)
			{
				_vShowItem[i].setRect(_itemSlot[_itemSetSlot]);
				_itemSetSlot++;
			}
			else _vShowItem[i].setRect(_itemSlot[99]);
		}
		break;
	}
}

void blacksmith::setRecipeItem()
{
	for (int i = 0; i < _vShowItem.size(); i++)
	{
		//Ŀ���� ���׷��̵� �������� �����ϸ�(������) ���������� �����ȴ�
		if (IntersectRect(&temp, &_cursorSlot, &_vShowItem[i].getRECT()))
		{
			makeRecipe("�Ʒÿ� �ܰ�", "��������", "�������", "�������", i, 3, 0, 0);
			makeRecipe("�������� �ܰ�", "��������", "����ȭ �� ������", "�������", i, 10, 3, 0);
			makeRecipe("ĳ����Ʈ ����", "���ھ�", "�������", "�������", i, 5, 0, 0);
			makeRecipe("�÷��� ����", "���ھ�", "�̻���", "�������", i, 10, 5, 0);
			makeRecipe("õ �ݴٳ�", "õ", "�������", "�������", i, 10, 0, 0);
			makeRecipe("õ �䰩", "����", "�������", "�������", i, 7, 0, 0);
		}
	}
}

void blacksmith::makeRecipe(string makeItemName, string RecipeItemName1, string RecipeItemName2, string RecipeItemName3, int forNum, int itemCnt1, int itemCnt2, int itemCnt3)
{
	if (_vShowItem[forNum].getItemInfo().itemName == makeItemName)
	{
		_temp = _vShowItem[forNum];			//���� = Ŀ���� ����Ű�� �ִ� ������
		_vShowRecipe.clear();				//Ȥ�� ���� ����� ���� ���� �� �𸣴� �ѹ� ������
		_vShowRecipe.push_back(ITEMMANAGER->addItem(RecipeItemName1)); //���Ϳ� ��Ḧ ����
		_vShowRecipe.push_back(ITEMMANAGER->addItem(RecipeItemName2));
		_vShowRecipe.push_back(ITEMMANAGER->addItem(RecipeItemName3));
		_vShowRecipe[0].setItemCnt_equal(itemCnt1);					   //������ ������ ������
		_vShowRecipe[1].setItemCnt_equal(itemCnt2);
		_vShowRecipe[2].setItemCnt_equal(itemCnt3);

		//����� ����(���ۿ� �ʿ��� ����)�� OKcnt�� ����־� ���Ÿ� ó���ϵ��� ���غ�
		for (int i = 0; i < _vShowRecipe.size(); i++) 
		{
			if (_vShowRecipe[i].getItemInfo().type != ITEM_EMPTY)
			{
				OKcnt[i] = _vShowRecipe[i].getItemInfo().cnt;
			}
			else if (_vShowRecipe[i].getItemInfo().type == ITEM_EMPTY)
			{
				OKcnt[i] = 0;
			}
		}
	}
}

void blacksmith::buy(vector<item> &storage)
{
	if (_showWindow)
	{
		if (KEYMANAGER->isOnceKeyDown('0')  )
		{
			int test[3] = {0,0,0};
			if (PLAYER->getMoney() >= _temp.getItemInfo().orignalPrice / 2)
			{
				for (int j = 0; j < _vShowRecipe.size(); j++)
				{
					for (int k = 0; k < storage.size(); k++)
					{
						if (_vShowRecipe[j].getItemInfo().itemName == storage[k].getItemInfo().itemName)
						{
							//OKcnt = ������� ����. �ϴ� â�� ���� �������� �����ϴ��� Ȯ���Ѵ�.
							if (OKcnt[j] >= test[j])
							{
								test[j] += storage[k].getItemInfo().cnt;
							}
							//���� OKcnt�� 0���ϰ� �Ǹ� ���� OKcnt�� �Ѿ��.
							if (OKcnt[j] <= test[j])
							{
								break;
							}
						}
					}
				}//for��
			}

			//������� ���� �����Ǹ�(OKcnt�� ��� 0���ϸ�) �����۱��Ű� ����ȴ�.
			if (OKcnt[0] <= test[0]&& OKcnt[1] <= test[1]&& OKcnt[2] <= test[2] && PLAYER->getMoney() >= _temp.getItemInfo().orignalPrice / 2)
			{
				buyItem(storage);
			}
			//�ƴϸ� ���Ű� �ȵ�
			else
			{
				TextOut(getMemDC(), WINSIZEX/2, WINSIZEY/2, "���̳� ���� �����ؿ�", strlen("���̳� ���� �����ؿ�"));
			}
		}
	}
}

void blacksmith::buyItem(vector<item>& storage)
{
	for (int j = 0; j < _vShowRecipe.size(); j++)
	{
		for (int k = 0; k < storage.size(); k++)
		{
			if (_vShowRecipe[j].getItemInfo().itemName == storage[k].getItemInfo().itemName)
			{
				//OKcnt = ������� ����. ������ 0�� �ɶ����� ���� �պ��� ��� �˻��ؼ� ��� ����
				if (OKcnt[j] > 0)
				{
					OKcnt[j] -= storage[k].getItemInfo().cnt;
					storage[k].setItemCnt(-storage[k].getItemInfo().cnt);
				}
				//���� OKcnt�� 0���ϰ� �Ǹ� ���� OKcnt�� �Ѿ��.
				//Ȥ�� ������� ��ġ���� �������� ������ ��ġ�� ��ģ��ŭ �ٽ� �����ش�
				if (OKcnt[j] <= 0)
				{
					storage[k].setItemCnt(abs(0 - OKcnt[j]));
					break;
				}
			}
		}
	}//for��

	//������� ���� �����Ǹ�(OKcnt�� ��� 0���ϸ�) ���Ϳ� �������� �߰��Ѵ�.
	if (OKcnt[0] <= 0 && OKcnt[1] <= 0 && OKcnt[2] <= 0)
	{
		for (int k = 0; k < storage.size(); k++)
		{
			if (storage[k].getItemInfo().itemName == "�������" || storage[k].getItemInfo().cnt <= 0)
			{
				PLAYER->setMoney(PLAYER->getMoney() - _temp.getItemInfo().orignalPrice / 2);
				storage.erase(storage.begin() + k);
				storage.insert(storage.begin() + k, _temp);
				break;
			}
		}
	}

}
