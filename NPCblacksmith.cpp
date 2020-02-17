#include "stdafx.h"
#include "NPCblacksmith.h"

NPCblacksmith::NPCblacksmith()
{
}

NPCblacksmith::~NPCblacksmith()
{
}

HRESULT NPCblacksmith::init(POINT npcXY)
{
	_npcImg = IMAGEMANAGER->findImage("����");
	_npcAni = ANIMATIONMANAGER->findAnimation("�����⺻���");

	_recipeImg = IMAGEMANAGER->findImage("���׷��̵巹����");

	_vShowItem.push_back(ITEMMANAGER->addItem("�Ʒÿ� �ܰ�"));
	_vShowItem.push_back(ITEMMANAGER->addItem("�������� �ܰ�"));
	_vShowItem.push_back(ITEMMANAGER->addItem("ĳ����Ʈ ����"));
	_vShowItem.push_back(ITEMMANAGER->addItem("�÷��� ����"));
	_vShowItem.push_back(ITEMMANAGER->addItem("õ �ݴٳ�"));
	_vShowItem.push_back(ITEMMANAGER->addItem("õ �䰩"));
	_vShowItem.push_back(ITEMMANAGER->addItem("õ ����"));
	_vShowItem.push_back(ITEMMANAGER->addItem("�Ʒÿ� â"));
	_vShowItem.push_back(ITEMMANAGER->addItem("�� �帱 â"));

	_armorTabImg = IMAGEMANAGER->findImage("�Ƹӽ���");
	_armorTab = RectMakeCenter(WINSIZEX / 2 - 160, WINSIZEY / 2 - 280, _armorTabImg->getWidth(), _armorTabImg->getWidth());
	_bowTabImg = IMAGEMANAGER->findImage("���콽��");
	_bowTab = RectMakeCenter(WINSIZEX / 2 - 40, WINSIZEY / 2 - 280, _bowTabImg->getWidth(), _bowTabImg->getHeight());
	_swordTabImg = IMAGEMANAGER->findImage("�ҵ彽��");
	_swordTab = RectMakeCenter(WINSIZEX / 2 - 100, WINSIZEY / 2 - 280, _swordTabImg->getWidth(), _swordTabImg->getHeight());
	_spearTabImg = IMAGEMANAGER->findImage("���Ǿ��");
	_spearTab = RectMakeCenter(WINSIZEX / 2 + 20, WINSIZEY / 2 - 280, _spearTabImg->getWidth(), _spearTabImg->getHeight());

	_currentTab = 0;  //������

	_npcRc = RectMakeCenter(npcXY.x, npcXY.y, _npcImg->getFrameWidth(), _npcImg->getFrameHeight());

	NPCshopBase::init();

	return S_OK;
}

void NPCblacksmith::release()
{
}

void NPCblacksmith::update()
{
	NPCshopBase::update();
}

void NPCblacksmith::render()
{
	_npcImg->aniRender(getMemDC(), _npcRc.left, _npcRc.top, _npcAni);
	NPCshopBase::render();

	if (_showWindow)
	{
		_armorTabImg->render(getMemDC(), _armorTab.left, _armorTab.top);
		_swordTabImg->render(getMemDC(), _swordTab.left, _swordTab.top);
		_bowTabImg->render(getMemDC(), _bowTab.left, _bowTab.top);
		_spearTabImg->render(getMemDC(), _spearTab.left, _spearTab.top);

		switch (_currentTab)
		{
		case 0:
			for (int i = 1; i < 9; i++)
			{
				_itemSlotImg[i]->render(getMemDC(), _itemSlot[i].left, _itemSlot[i].top);
			}
			TextOut(getMemDC(), WINSIZEX / 2 - 180, 110, "��", strlen("��"));
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
				if (_vShowItem[i].getItemInfo().type == ITEM_BOOTS)
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
			TextOut(getMemDC(), WINSIZEX / 2 - 180, 110, "�˰� ����", strlen("�˰� ����"));
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
			TextOut(getMemDC(), WINSIZEX / 2 - 180, 110, "Ȱ", strlen("Ȱ"));
			for (int i = 0; i < _vShowItem.size(); i++)
			{
				if (_vShowItem[i].getItemInfo().type == ITEM_BOW)
				{
					_vShowItem[i].render();
				}
			}
			break;
		case 3:
			for (int i = 0; i < 9; i++)
			{
				_itemSlotImg[i]->render(getMemDC(), _itemSlot[i].left, _itemSlot[i].top);
			}
			TextOut(getMemDC(), WINSIZEX / 2 - 180, 110, "â", strlen("â"));
			for (int i = 0; i < _vShowItem.size(); i++)
			{
				if (_vShowItem[i].getItemInfo().type == ITEM_SPEAR)
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
		TextOut(getMemDC(), WINSIZEX - 250, 150, str, strlen(str));
		wsprintf(str, "%d", _temp.getItemInfo().atk);
		TextOut(getMemDC(), WINSIZEX - 250, 190, str, strlen(str));
		wsprintf(str, "%d", _temp.getItemInfo().def);
		TextOut(getMemDC(), WINSIZEX - 250, 230, str, strlen(str));
		wsprintf(str, "%d", _temp.getItemInfo().speed);
		TextOut(getMemDC(), WINSIZEX - 250, 270, str, strlen(str));
		wsprintf(str, "%d", _temp.getItemInfo().orignalPrice / 2);
		TextOut(getMemDC(), WINSIZEX - 130, 370, str, strlen(str));
		for (int i = 0; i < _vShowRecipe.size(); i++)
		{
			wsprintf(str, "�ʿ� : %d", _vShowRecipe[i].getItemInfo().cnt);
			TextOut(getMemDC(), WINSIZEX - 250, WINSIZEY / 2 + 70 + (i * 60), str, strlen(str));
		}
	}
}

void NPCblacksmith::tabControl()
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
		if (KEYMANAGER->isOnceKeyDown('V'))//���� �ű�� Ŀ�� ��ġ �ʱ�ȭ
		{
			_currentTab++;
			if (_currentTab >= 1)
			{
				_cursorNum = 0;
				_cursorSlot = _itemSlot[_cursorNum];
			}
			if (_currentTab >= 3)_currentTab = 3;
		}
	}
	_armorTab = RectMakeCenter(WINSIZEX / 2 - 160, WINSIZEY / 2 - 280, _armorTabImg->getWidth(), _armorTabImg->getWidth());
	_swordTab = RectMakeCenter(WINSIZEX / 2 - 100, WINSIZEY / 2 - 280, _swordTabImg->getWidth(), _swordTabImg->getHeight());
	_bowTab = RectMakeCenter(WINSIZEX / 2 - 40, WINSIZEY / 2 - 280, _bowTabImg->getWidth(), _bowTabImg->getHeight());
	_spearTab = RectMakeCenter(WINSIZEX / 2 + 20, WINSIZEY / 2 - 280, _spearTabImg->getWidth(), _spearTabImg->getHeight());

	switch (_currentTab)  //�̺κ� �߸���... �̿ϼ�
	{
	case 0:
		_armorTab = RectMakeCenter(WINSIZEX / 2 - 160, WINSIZEY / 2 - 300, _armorTabImg->getWidth(), _armorTabImg->getWidth());
		_itemSetSlot = 1;
		for (int i = 0; i < _vShowItem.size(); i++)
		{
			if (_vShowItem[i].getItemInfo().type == ITEM_ARMOR)
			{
				_vShowItem[i].setRect(_itemSlot[1]);
			}
			if (_vShowItem[i].getItemInfo().type == ITEM_HELMET)
			{
				_vShowItem[i].setRect(_itemSlot[3]);
			}
			if (_vShowItem[i].getItemInfo().type == ITEM_BOOTS)
			{
				_vShowItem[i].setRect(_itemSlot[5]);
			}
			else if (_vShowItem[i].getItemInfo().type != ITEM_BOOTS && _vShowItem[i].getItemInfo().type != ITEM_HELMET && _vShowItem[i].getItemInfo().type != ITEM_ARMOR)
				_vShowItem[i].setRect(WINSIZEX, WINSIZEY * 2);
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
			else _vShowItem[i].setRect(WINSIZEX, WINSIZEY * 2);
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
			else _vShowItem[i].setRect(WINSIZEX, WINSIZEY * 2);
		}
		break;
	case 3:
		_spearTab = RectMakeCenter(WINSIZEX / 2 + 20, WINSIZEY / 2 - 300, _spearTabImg->getWidth(), _spearTabImg->getHeight());
		_itemSetSlot = 0;
		for (int i = 0; i < _vShowItem.size(); i++)
		{
			if (_vShowItem[i].getItemInfo().type == ITEM_SPEAR)
			{
				_vShowItem[i].setRect(_itemSlot[_itemSetSlot]);
				_itemSetSlot++;
			}
			else _vShowItem[i].setRect(WINSIZEX, WINSIZEY * 2);
		}
		break;
	}
}

void NPCblacksmith::cursorControl()
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