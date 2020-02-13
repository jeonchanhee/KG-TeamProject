#include "stdafx.h"
#include "NPCpotionShop.h"

NPCpotionShop::NPCpotionShop()
{
}

NPCpotionShop::~NPCpotionShop()
{
}


HRESULT NPCpotionShop::init(POINT npcXY)
{
	_npcImg = IMAGEMANAGER->findImage("��ġ");
	_npcAni = ANIMATIONMANAGER->findAnimation("��ġ�⺻���");

	_recipeImg = IMAGEMANAGER->findImage("���׷��̵巹����_����");
	_vShowItem.push_back(ITEMMANAGER->addItem("���� ����"));
	_vShowItem.push_back(ITEMMANAGER->addItem("�߰� ����"));
	_vShowItem.push_back(ITEMMANAGER->addItem("ū ����"));
	_npcRc = RectMakeCenter(npcXY.x, npcXY.y, _npcImg->getFrameWidth(), _npcImg->getFrameHeight());

	NPCshopBase::init();

	return S_OK;
}

void NPCpotionShop::release()
{
}

void NPCpotionShop::update()
{
	NPCshopBase::update();
}

void NPCpotionShop::render()
{
	NPCshopBase::render();

	if (_showWindow)
	{
		//����=���� Ŀ���� ����Ű�� �ִ� ������.
		_temp.getItemInfo().image->render(getMemDC(), WINSIZEX - 120, 80);

		//������ �κп� ���� Ŀ���� ����Ű�� �ִ� ���׷��̵� �������� ����,��� ����� ����
		TextOut(getMemDC(), WINSIZEX / 2 - 180, 110, "����", strlen("����"));
		wsprintf(str, "%d", _temp.getItemInfo().orignalPrice / 2);
		TextOut(getMemDC(), WINSIZEX - 130, 370, str, strlen(str));
		for (int i = 0; i < _vShowRecipe.size(); i++)
		{
			wsprintf(str, "�ʿ� : %d", _vShowRecipe[i].getItemInfo().cnt);
			TextOut(getMemDC(), WINSIZEX - 250, WINSIZEY / 2 + 70 + (i * 60), str, strlen(str));
		}
		for (int i = 0; i < _vShowItem.size(); i++)
		{
			_vShowItem[i].render();
			if (i + 1 == _cursorNum)
			{
				wsprintf(str, "ü�� ȸ����: %d", _vShowItem[i].getItemInfo().heal);
				TextOut(getMemDC(), WINSIZEX - 250, WINSIZEY / 2 - 100, str, strlen(str));
			}
		}
	}
}

void NPCpotionShop::tabControl()
{
	for (int i = 0; i < _vShowItem.size(); i++) //�̺κ� �߸���.. �̿ϼ�
	{
		_vShowItem[i].setRect(_itemSlot[i + 1]);
	}
}

void NPCpotionShop::cursorControl()
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
