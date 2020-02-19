#include "stdafx.h"
#include "NPCshopBase.h"

NPCshopBase::NPCshopBase()
{
}

NPCshopBase::~NPCshopBase()
{
}

HRESULT NPCshopBase::init()
{
	//_showImg = IMAGEMANAGER->findImage("�����ۺ����ִ�â");


	//������ �����ִ� ���� �ʱ�ȭ
	//_vItemSlot 0��ĭ�� ��ġ�� �޶� ���� �ʱ�ȭ

	for (int i = 0; i < 2; i++)
	{
		for (int k = 0; k < 4; k++)
		{

			_itemInfo.img = IMAGEMANAGER->findImage("���");

			_itemInfo.x = WINSIZEX / 2 - 130 + (k * 70);
			_itemInfo.y = WINSIZEY / 2 - 180 + (i * 50);
			_itemInfo.rc = RectMakeCenter(_itemInfo.x, _itemInfo.y, _itemInfo.img->getWidth(), _itemInfo.img->getHeight());

			_itemInfo.item = ITEMMANAGER->addItem("�������");
			_vItemSlot.push_back(_itemInfo);
		}
	}

	//������ ���� �ʱ�ȭ
	for (int i = 0; i < 3; i++)
	{
		_itemInfo.img = IMAGEMANAGER->findImage("���");
		_itemInfo.x = WINSIZEX / 2 + (i * 30);
		_itemInfo.y = WINSIZEY / 2 + (i * 30);
		_itemInfo.rc = RectMakeCenter(_itemInfo.x, _itemInfo.y, _itemInfo.img->getWidth(), _itemInfo.img->getHeight());
		_itemInfo.item = ITEMMANAGER->addItem("�������");
		_vRecipeSlot.push_back(_itemInfo);

	}
	//���׷��̵� �� �����ִ� ������ ��Ʈ�ʱ�ȭ
	_itemSetSlot = 0;

	//Ŀ���ʱ�ȭ
	_cursorNum = 1;
	_cursorSlot = _vItemSlot[_cursorNum].rc;
	_cursor = new cursor;
	_cursor->init();
	_grab = new image;
	_grab = IMAGEMANAGER->addImage("Ŀ���׷�", "images/shop/grab.bmp", 50, 52, true, RGB(255, 0, 255));

	return S_OK;
}

void NPCshopBase::release()
{
	SAFE_DELETE(_cursor);
}

void NPCshopBase::update()
{
	_index++;
	if (_index % 200 == 0) _npcAni->start();

	if (!_showWindow)
	{
		if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &_npcRc) && KEYMANAGER->isOnceKeyDown('J'))
		{
			_showWindow = true;

			//â�� ���������� Ŀ����ġ �ʱ�ȭ
			_cursorNum = 0;
			_cursorSlot = _vItemSlot[_cursorNum].rc;
		}
	}
	else
	{
		if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &_npcRc) && KEYMANAGER->isOnceKeyDown('6'))
		{
			_showWindow = false;
		}
		cursorControl();
		tabControl();
		setRecipeItem();
	}
}

void NPCshopBase::render()
{
	_npcImg->aniRender(getMemDC(), _npcRc.left, _npcRc.top, _npcAni);

	if (!_showWindow)
	{
		if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &_npcRc))
		{
			IMAGEMANAGER->render("����", getMemDC(), _npcRc.right, _npcRc.top - 20);
		}
	}
	else
	{
		//�⺻���� ����

		//_showImg->render(getMemDC(), WINSIZEX / 2 - 250, WINSIZEY / 2 - 300);
		//_recipeImg->render(getMemDC(), WINSIZEX - 350, 60);
		IMAGEMANAGER->render("Ÿ��Ʋ", getMemDC(), WINSIZEX / 2 - 200, 0);
		IMAGEMANAGER->render("�̸�ĭ", getMemDC(), WINSIZEX - 300, 20);
		IMAGEMANAGER->render("�����ۺ����ִ�â", getMemDC(), WINSIZEX / 2 - 250, WINSIZEY / 2 - 300);

		for (int i = 0; i < 8; i++)
		{
			_vItemSlot[i].img->render(getMemDC(), _vItemSlot[i].rc.left, _vItemSlot[i].rc.top);
		}
		for (int i = 0; i < 3; i++)
		{
			//������ ������ �̹����� ������ �۵��� �̹���
			_vRecipeSlot[i].img->render(getMemDC(), WINSIZEX / 2 + 200, WINSIZEY / 2 + 50 + (i * 70));
			if (!_vRecipeSlot.empty())
			{
				_vRecipeSlot[i].item.getItemInfo().image->render(getMemDC(), WINSIZEX / 2 + 200, WINSIZEY / 2 + 50 + (i * 70));
			}
		}
	}
}

void NPCshopBase::tabControl()
{
}

void NPCshopBase::cursorControl()
{
}

void NPCshopBase::setRecipeItem()
{
	//�����ǿ� Ȥ�� ���� ����� ���� ���� �� �𸣴� �ѹ� ������
	_temp = ITEMMANAGER->addItem("�������");
	for (int i = 0; i < 3; i++)
	{
		_vRecipeSlot[i].item = ITEMMANAGER->addItem("�������");
	}

	for (int i = 0; i < _vItemSlot.size(); i++)
	{
		//Ŀ���� ���׷��̵� �������� �����ϸ�(������) ���������� �����ȴ�
		if (_cursorNum == i)
		{
			makeRecipe("�Ʒÿ� �ܰ�", "��������", "�������", "�������", i, 3, 0, 0);
			makeRecipe("�������� �ܰ�", "��������", "����ȭ �� ������", "�������", i, 10, 3, 0);
			makeRecipe("ĳ����Ʈ ����", "���ھ�", "�������", "�������", i, 5, 0, 0);
			makeRecipe("�÷��� ����", "���ھ�", "�̻���", "�������", i, 10, 5, 0);
			makeRecipe("õ �ݴٳ�", "õ", "�������", "�������", i, 10, 0, 0);
			makeRecipe("õ �䰩", "����", "�������", "�������", i, 7, 0, 0);
			makeRecipe("õ ����", "����", "õ", "�������", i, 2, 2, 0);
			makeRecipe("�Ʒÿ� â", "����", "�������", "�������", i, 7, 0, 0);
			makeRecipe("�� �帱 â", "����", "��ȭ����", "�������", i, 7, 5, 0);
			makeRecipe("���� ����", "��������", "�������", "�������", i, 7, 0, 0);
			makeRecipe("�߰� ����", "�̻���", "�������", "�������", i, 8, 0, 0);
			makeRecipe("ū ����", "���ھ�", "�������", "�������", i, 9, 0, 0);
		}
	}
}

void NPCshopBase::makeRecipe(string makeItemName, string RecipeItemName1, string RecipeItemName2, string RecipeItemName3, int forNum, int itemCnt1, int itemCnt2, int itemCnt3)
{
	if (_vItemSlot[forNum].item.getItemInfo().itemName == makeItemName)
	{
		_temp = _vItemSlot[forNum].item;         //���� = Ŀ���� ����Ű�� �ִ� ������

		_vRecipeSlot[0].item = ITEMMANAGER->addItem(RecipeItemName1);
		_vRecipeSlot[0].item.setItemCnt_equal(itemCnt1);

		_vRecipeSlot[1].item = ITEMMANAGER->addItem(RecipeItemName2);
		_vRecipeSlot[1].item.setItemCnt_equal(itemCnt2);

		_vRecipeSlot[2].item = ITEMMANAGER->addItem(RecipeItemName3);
		_vRecipeSlot[2].item.setItemCnt_equal(itemCnt3);

		//������� ����(���ۿ� �ʿ��� ����)�� _OKcnt�� ����־� ���Ÿ� ó���ϵ��� ���غ�
		for (int i = 0; i < _vRecipeSlot.size(); i++)
		{
			if (_vRecipeSlot[i].item.getItemInfo().type != ITEM_EMPTY)
			{
				_OKcnt[i] = _vRecipeSlot[i].item.getItemInfo().cnt;
			}
			else if (_vRecipeSlot[i].item.getItemInfo().type == ITEM_EMPTY)
			{
				_OKcnt[i] = 0;
			}
		}
	}
}

void NPCshopBase::buy()   //���°� ���� ������ �Լ�
{
	if (KEYMANAGER->isOnceKeyDown('0'))
	{
		//test�� �κ��丮 ���� ���ۿ� �ʿ��� ����� ������ ���� ���� ����
		int test[3] = { 0,0,0 };

		//���� ���� �ִ��� ���������� Ȯ��.   ������ ������ ������ ���۽� �ʿ��� ���� ������ ������ �����̱⶧��
		if (PLAYER->getMoney() >= _temp.getItemInfo().orignalPrice / 2)
		{
			for (int j = 0; j < _vRecipeSlot.size(); j++)
			{
				for (int k = 0; k < PLAYER->getinventory()->getvInven().size(); k++)
				{
					//�κ��丮�� ���� ���� ������� Ȯ���Ѵ�.
					if (_vRecipeSlot[j].item.getItemInfo().itemName == PLAYER->getinventory()->getvInven()[k]._item.getItemInfo().itemName)
					{
						//_OKcnt = ������� ����. test = �κ��丮 ���� ������� ����.
						if (_OKcnt[j] >= test[j])
						{
							test[j] += PLAYER->getinventory()->getvInven()[k]._item.getItemInfo().cnt;
						}
						//���� �κ��丮 ���� ������� �����ȴٸ� ���� ������� ã���� ������.
						if (_OKcnt[j] <= test[j])
						{
							break;
						}
					}
				}
			}   //for��
		}

		//������� ���� �����Ǹ�(��� OKcnt <= test�� ���) + �׸��� �������� �����Ǹ� �����۱��Ű� ����ȴ�.
		if (_OKcnt[0] <= test[0] && _OKcnt[1] <= test[1] && _OKcnt[2] <= test[2] && PLAYER->getMoney() >= _temp.getItemInfo().orignalPrice / 2)
		{
			buyItem();
		}
		//�ƴϸ� ���Ű� �ȵ�
		else
		{
			TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, "���̳� ���� �����ؿ�", strlen("���̳� ���� �����ؿ�"));
		}
	}
}

void NPCshopBase::buyItem()
{
	for (int j = 0; j < _vRecipeSlot.size(); j++)
	{
		for (int k = 0; k < PLAYER->getinventory()->getvInven().size(); k++)
		{
			if (_vRecipeSlot[j].item.getItemInfo().itemName == PLAYER->getinventory()->getvInven()[k]._item.getItemInfo().itemName)
			{
				//_OKcnt = ������� ����. ������ 0�� �ɶ����� �κ��丮 ������ �պ��� ��� �˻��ؼ� ��� ����
				if (_OKcnt[j] > 0)
				{
					// PLAYER->getinventory()->setItemCnt�� _vInven[forNum].setItemCnt(itemCnt) �� ����
					_OKcnt[j] -= PLAYER->getinventory()->getvInven()[k]._item.getItemInfo().cnt;
					PLAYER->getinventory()->setItemCnt(k, -PLAYER->getinventory()->getvInven()[k]._item.getItemInfo().cnt);
				}

				//���� _OKcnt�� 0���ϰ� �Ǹ� ���� _OKcnt�� �Ѿ��.(�ִ� 3������)
				//Ȥ�� ��� �������� ��ġ���� �������� ������ ��ġ�� ��ģ��ŭ �ٽ� �����ش�
				if (_OKcnt[j] <= 0)
				{
					PLAYER->getinventory()->setItemCnt(k, abs(0 - _OKcnt[j]));
					break;
				}
			}
		}
	}//for��

	//������� ���� �����Ǹ�(_OKcnt�� ��� 0���ϸ�) �κ��丮 ���Ϳ� �������� �߰��Ѵ�.
	if (_OKcnt[0] <= 0 && _OKcnt[1] <= 0 && _OKcnt[2] <= 0)
	{
		for (int k = 0; k < PLAYER->getinventory()->getvInven().size(); k++)
		{
			if (PLAYER->getinventory()->getvInven()[k]._item.getItemInfo().itemName == "�������" || PLAYER->getinventory()->getvInven()[k]._item.getItemInfo().cnt <= 0)
			{
				PLAYER->setMoney(PLAYER->getMoney() - _temp.getItemInfo().orignalPrice / 2);

				PLAYER->getinventory()->addItem(k, _temp);
				break;
			}
		}
	}
}
