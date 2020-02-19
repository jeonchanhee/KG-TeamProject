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

	//_recipeImg = IMAGEMANAGER->findImage("���׷��̵巹����_����");

	NPCshopBase::init();
	_vItemSlot[0].item = ITEMMANAGER->addItem("���� ����");
	_vItemSlot[1].item = ITEMMANAGER->addItem("�߰� ����");
	_vItemSlot[2].item = ITEMMANAGER->addItem("ū ����");
	for (int i = 3; i < _vItemSlot.size(); i++)
	{
		_vItemSlot[i].item = ITEMMANAGER->addItem("�������");
	}

	_npcRc = RectMakeCenter(npcXY.x, npcXY.y, _npcImg->getFrameWidth(), _npcImg->getFrameHeight()+70);


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
	if (_showWindow) //������������ �긦 ���� ����
	{
		IMAGEMANAGER->render("���׷��̵巹����_����", getMemDC(), WINSIZEX - 350, 60);
	}

	NPCshopBase::render();

	if (_showWindow)
	{
		TextOut(getMemDC(), WINSIZEX / 2 - 70, 20, "��������", strlen("��������"));
		TextOut(getMemDC(), WINSIZEX / 2 - 180, 110, "����", strlen("����"));
		IMAGEMANAGER->render("��ġū�̹���", getMemDC(), 10, 100);
		for (int i = 0; i < _vItemSlot.size(); i++)
		{
			_vItemSlot[i].item.getItemInfo().image->render(getMemDC(), _vItemSlot[i].rc.left, _vItemSlot[i].rc.top);
		}
		if (_temp.getItemInfo().type != ITEM_EMPTY)  // <- �̺κ��� _temp���� ����� �ȵ��°Ͱ���
		{
			//����=���� Ŀ���� ����Ű�� �ִ� ������.
			_temp.getItemInfo().image->render(getMemDC(), WINSIZEX - 120, 80);

			//������ �κп� ���� Ŀ���� ����Ű�� �ִ� ���׷��̵� �������� ����,��� ����� ����
			TextOut(getMemDC(), WINSIZEX - 220, 30, _temp.getItemInfo().itemName.c_str(), _temp.getItemInfo().itemName.length());
			wsprintf(str, "%d", _temp.getItemInfo().orignalPrice / 2);
			TextOut(getMemDC(), WINSIZEX - 130, 370, str, strlen(str));
			for (int i = 0; i < _vRecipeSlot.size(); i++)
			{
				wsprintf(str, "�ʿ� : %d", _vRecipeSlot[i].item.getItemInfo().cnt);
				TextOut(getMemDC(), WINSIZEX - 250, WINSIZEY / 2 + 70 + (i * 60), str, strlen(str));
			}
			for (int i = 0; i < _vItemSlot.size(); i++)
			{
				if (i == _cursorNum)
				{
					wsprintf(str, "ü�� ȸ����: %d", _vItemSlot[i].item.getItemInfo().heal);
					TextOut(getMemDC(), WINSIZEX - 300,150, str, strlen(str));
				}
			}
		}
		_cursor->render();
	}
}

void NPCpotionShop::tabControl()
{
	//_vItemSlot[0].item = ITEMMANAGER->addItem("���� ����");
	//_vItemSlot[1].item = ITEMMANAGER->addItem("�߰� ����");
	//_vItemSlot[2].item = ITEMMANAGER->addItem("ū ����");
	//for (int i = 3; i < _vItemSlot.size(); i++)
	//{
	//	_vItemSlot[i].item = ITEMMANAGER->addItem("�������");
	//}
}

void NPCpotionShop::cursorControl()
{

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		//Ŀ���� ������ ��������
		_cursorNum--;
		if (_cursorNum < 0) _cursorNum = 0;
		if (_currentTab == 0 && _cursorNum <= 0)_cursorNum = 0;

		_cursorSlot = _vItemSlot[_cursorNum].rc;
		_cursor->getAni()->start();
	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		//Ŀ���� ������ ��������
		int temp;
		temp = _cursorNum;
		_cursorNum++;
		if (_cursorNum >= SLOTNUM) _cursorNum = temp;

		_cursorSlot = _vItemSlot[_cursorNum].rc;
		_cursor->getAni()->start();
	}
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		//Ŀ���� ���θ�������
		int temp;
		temp = _cursorNum;
		_cursorNum -= 4;
		if (_cursorNum < 0)_cursorNum = temp;

		_cursorSlot = _vItemSlot[_cursorNum].rc;
		_cursor->getAni()->start();
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		//Ŀ���� �Ʒ��� ��������
		int temp;
		temp = _cursorNum;
		_cursorNum += 4;
		if (_cursorNum >= SLOTNUM)_cursorNum = temp;

		_cursorSlot = _vItemSlot[_cursorNum].rc;
		_cursor->getAni()->start();
	}
	_cursor->setRc(_cursorSlot);
}
