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

	//_recipeImg = IMAGEMANAGER->findImage("���׷��̵巹����");

	NPCshopBase::init();

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
	if (_showWindow) //������������ �곻����
	{
		_armorTabImg->render(getMemDC(), _armorTab.left, _armorTab.top);
		_swordTabImg->render(getMemDC(), _swordTab.left, _swordTab.top);
		_bowTabImg->render(getMemDC(), _bowTab.left, _bowTab.top);
		_spearTabImg->render(getMemDC(), _spearTab.left, _spearTab.top);
		IMAGEMANAGER->render("���׷��̵巹����", getMemDC(), WINSIZEX - 350, 60);
	}
	NPCshopBase::render();

	if (_showWindow)
	{
		TextOut(getMemDC(), WINSIZEX / 2 - 70, 20, "������ ���尣", strlen("������ ���尣"));
		for (int i = 0; i < 8; i++)
		{
			_vItemSlot[i].img->render(getMemDC(), _vItemSlot[i].rc.left, _vItemSlot[i].rc.top);
			if (_vItemSlot[i].item.getItemInfo().type != ITEM_EMPTY)
			{
				_vItemSlot[i].item.getItemInfo().image->render(getMemDC(), _vItemSlot[i].rc.left, _vItemSlot[i].rc.top);
			}
		}
		switch (_currentTab)
		{
		case 0:
			TextOut(getMemDC(), WINSIZEX / 2 - 180, 110, "��", strlen("��"));
			break;
		case 1:
			TextOut(getMemDC(), WINSIZEX / 2 - 180, 110, "�˰� ����", strlen("�˰� ����"));
			break;
		case 2:
			TextOut(getMemDC(), WINSIZEX / 2 - 180, 110, "Ȱ", strlen("Ȱ"));
			break;
		case 3:
			TextOut(getMemDC(), WINSIZEX / 2 - 180, 110, "â", strlen("â"));
			break;
		}

		if (_temp.getItemInfo().type != ITEM_EMPTY) //���� ������ ����
		{
			//����=���� Ŀ���� ����Ű�� �ִ� ������.
			_temp.getItemInfo().image->render(getMemDC(), WINSIZEX - 120, 80);

			//������ �κп� ���� Ŀ���� ����Ű�� �ִ� ���׷��̵� �������� ����,��� ����� ����
			TextOut(getMemDC(), WINSIZEX - 220, 30, _temp.getItemInfo().itemName.c_str(), _temp.getItemInfo().itemName.length());
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
			for (int i = 0; i < _vRecipeSlot.size(); i++)
			{
				wsprintf(str, "�ʿ� : %d", _vRecipeSlot[i].item.getItemInfo().cnt);
				TextOut(getMemDC(), WINSIZEX - 250, WINSIZEY / 2 + 70 + (i * 60), str, strlen(str));
			}
		}
		_cursor->render();
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
				_cursorNum = 0;
				_cursorSlot = _vItemSlot[_cursorNum].rc;
				//�� ���� Ŀ���� 0�� ĭ���Ͱ� �ƴ� 1��ĭ���� ������..
			}
		}
		if (KEYMANAGER->isOnceKeyDown('V'))//���� �ű�� Ŀ�� ��ġ �ʱ�ȭ
		{
			_currentTab++;
			if (_currentTab >= 1)
			{
				_cursorNum = 0;
				_cursorSlot = _vItemSlot[_cursorNum].rc;
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

		_vItemSlot[0].item = ITEMMANAGER->addItem("õ �䰩");
		_vItemSlot[1].item = ITEMMANAGER->addItem("õ ����");
		_vItemSlot[2].item = ITEMMANAGER->addItem("õ �ݴٳ�");
		for (int i = 3; i < _vItemSlot.size(); i++)
		{
			_vItemSlot[i].item = ITEMMANAGER->addItem("�������");
		}
		break;
	case 1:
		_swordTab = RectMakeCenter(WINSIZEX / 2 - 100, WINSIZEY / 2 - 300, _swordTabImg->getWidth(), _swordTabImg->getHeight());
		_vItemSlot[0].item = ITEMMANAGER->addItem("�Ʒÿ� �ܰ�");
		_vItemSlot[1].item = ITEMMANAGER->addItem("�������� �ܰ�");
		for (int i = 2; i < _vItemSlot.size(); i++)
		{
			_vItemSlot[i].item = ITEMMANAGER->addItem("�������");
		}

		break;
	case 2:
		_bowTab = RectMakeCenter(WINSIZEX / 2 - 40, WINSIZEY / 2 - 300, _bowTabImg->getWidth(), _bowTabImg->getHeight());
		_vItemSlot[0].item = ITEMMANAGER->addItem("ĳ����Ʈ ����");
		_vItemSlot[1].item = ITEMMANAGER->addItem("�÷��� ����");
		for (int i = 2; i < _vItemSlot.size(); i++)
		{
			_vItemSlot[i].item = ITEMMANAGER->addItem("�������");
		}
		break;
	case 3:
		_spearTab = RectMakeCenter(WINSIZEX / 2 + 20, WINSIZEY / 2 - 300, _spearTabImg->getWidth(), _spearTabImg->getHeight());
		_vItemSlot[0].item = ITEMMANAGER->addItem("�Ʒÿ� â");
		_vItemSlot[1].item = ITEMMANAGER->addItem("�� �帱 â");
		for (int i = 2; i < _vItemSlot.size(); i++)
		{
			_vItemSlot[i].item = ITEMMANAGER->addItem("�������");
		}
		break;
	}
}

void NPCblacksmith::cursorControl()
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