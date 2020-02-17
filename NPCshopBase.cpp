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
	_titleImg = IMAGEMANAGER->findImage("Ÿ��Ʋ");
	_showImg = IMAGEMANAGER->findImage("�����ۺ����ִ�â");
	for (int i = 0; i < 9; i++)
	{
		_itemSlotImg[i] = IMAGEMANAGER->findImage("�����̹���");
		if (i < 3) _recipeSlotImg[i] = IMAGEMANAGER->findImage("�����̹���");
	}

	//���׷��̵� �� �����ִ� ������ ��Ʈ�ʱ�ȭ
	_itemSetSlot = 0;
	_itemSlot[0] = RectMakeCenter(WINSIZEX / 2 - 160, WINSIZEY / 2 - 170, _itemSlotImg[0]->getWidth(), _itemSlotImg[0]->getHeight());
	for (int i = 1; i < 9; i++)
	{
		if (i < 5)
		{
			_itemSlot[i] = RectMakeCenter(_itemSlot[0].right - 20 + (i * 60), _itemSlot[0].top - 10, _itemSlotImg[i]->getWidth(), _itemSlotImg[i]->getHeight());
		}
		if (i >= 5)
		{
			_itemSlot[i] = RectMakeCenter(_itemSlot[0].right - 20 + ((i % 5 + 1) * 60), _itemSlot[0].bottom + 10, _itemSlotImg[i]->getWidth(), _itemSlotImg[i]->getHeight());
		}
	}

	//Ŀ���ʱ�ȭ
	_cursorNum = 1;
	_cursorSlot = _itemSlot[_cursorNum];
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

	playerCollision();
	cursorControl();
	setRecipeItem();
	tabControl();
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

	if (_showWindow)
	{
		baseRender();
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
	_vShowRecipe.clear();   //�����ǿ� Ȥ�� ���� ����� ���� ���� �� �𸣴� �ѹ� ������
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
			makeRecipe("õ ����", "����", "õ", "�������", i, 2, 2, 0);
			makeRecipe("�Ʒÿ� â", "����", "�������", "�������", i, 7, 0, 0);
			makeRecipe("�� �帱 â", "����", "��ȭ����", "�������", i, 7, 5, 0);
			makeRecipe("���� ����", "��������", "�������", "�������", i, 7, 0, 0);
			makeRecipe("�߰� ����", "�̻���", "�������", "�������", i, 8, 0, 0);
			makeRecipe("ū ����", "���ھ�", "�������", "�������", i, 9, 0, 0);
			makeRecipe("�������", "�������", "�������", "�������", i, 0, 0, 0);
		}
	}
}

void NPCshopBase::makeRecipe(string makeItemName, string RecipeItemName1, string RecipeItemName2, string RecipeItemName3, int forNum, int itemCnt1, int itemCnt2, int itemCnt3)
{
	if (_vShowItem[forNum].getItemInfo().itemName == makeItemName)
	{
		_temp = _vShowItem[forNum];         //���� = Ŀ���� ����Ű�� �ִ� ������
		_vShowRecipe.push_back(ITEMMANAGER->addItem(RecipeItemName1)); //���Ϳ� ��Ḧ ����
		_vShowRecipe.push_back(ITEMMANAGER->addItem(RecipeItemName2));
		_vShowRecipe.push_back(ITEMMANAGER->addItem(RecipeItemName3));
		_vShowRecipe[0].setItemCnt_equal(itemCnt1);                  //������ ������ ������
		_vShowRecipe[1].setItemCnt_equal(itemCnt2);
		_vShowRecipe[2].setItemCnt_equal(itemCnt3);

		//������� ����(���ۿ� �ʿ��� ����)�� _OKcnt�� ����־� ���Ÿ� ó���ϵ��� ���غ�
		for (int i = 0; i < _vShowRecipe.size(); i++)
		{
			if (_vShowRecipe[i].getItemInfo().type != ITEM_EMPTY)
			{
				_OKcnt[i] = _vShowRecipe[i].getItemInfo().cnt;
			}
			else if (_vShowRecipe[i].getItemInfo().type == ITEM_EMPTY)
			{
				_OKcnt[i] = 0;
			}
		}
	}
}

void NPCshopBase::buy()   //���°� ���� ������ �Լ�
{
	//if (_showWindow)
	//{
	//	if (KEYMANAGER->isOnceKeyDown('0'))
	//	{
	//		//test�� �κ��丮 ���� ���ۿ� �ʿ��� ����� ������ ���� ���� ����
	//		int test[3] = { 0,0,0 };

	//		//���� ���� �ִ��� ���������� Ȯ��.   ������ ������ ������ ���۽� �ʿ��� ���� ������ ������ �����̱⶧��
	//		if (PLAYER->getMoney() >= _temp.getItemInfo().orignalPrice / 2)
	//		{
	//			for (int j = 0; j < _vShowRecipe.size(); j++)
	//			{
	//				for (int k = 0; k < PLAYER->getinventory()->getvInven().size(); k++)
	//				{
	//					//�κ��丮�� ���� ���� ������� Ȯ���Ѵ�.
	//					if (_vShowRecipe[j].getItemInfo().itemName == PLAYER->getinventory()->getvInven()[k].getItemInfo().itemName)
	//					{
	//						//_OKcnt = ������� ����. test = �κ��丮 ���� ������� ����.
	//						if (_OKcnt[j] >= test[j])
	//						{
	//							test[j] += PLAYER->getinventory()->getvInven()[k].getItemInfo().cnt;
	//						}
	//						//���� �κ��丮 ���� ������� �����ȴٸ� ���� ������� ã���� ������.
	//						if (_OKcnt[j] <= test[j])
	//						{
	//							break;
	//						}
	//					}
	//				}
	//			}   //for��
	//		}

	//		//������� ���� �����Ǹ�(��� OKcnt <= test�� ���) + �׸��� �������� �����Ǹ� �����۱��Ű� ����ȴ�.
	//		if (_OKcnt[0] <= test[0] && _OKcnt[1] <= test[1] && _OKcnt[2] <= test[2] && PLAYER->getMoney() >= _temp.getItemInfo().orignalPrice / 2)
	//		{
	//			buyItem();
	//		}
	//		//�ƴϸ� ���Ű� �ȵ�
	//		else
	//		{
	//			TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, "���̳� ���� �����ؿ�", strlen("���̳� ���� �����ؿ�"));
	//		}
	//	}
	//}
}

void NPCshopBase::buyItem()
{
	//for (int j = 0; j < _vShowRecipe.size(); j++)
	//{
	//	for (int k = 0; k < PLAYER->getinventory()->getvInven().size(); k++)
	//	{
	//		if (_vShowRecipe[j].getItemInfo().itemName == PLAYER->getinventory()->getvInven()[k].getItemInfo().itemName)
	//		{
	//			//_OKcnt = ������� ����. ������ 0�� �ɶ����� �κ��丮 ������ �պ��� ��� �˻��ؼ� ��� ����
	//			if (_OKcnt[j] > 0)
	//			{
	//				// PLAYER->getinventory()->setItemCnt�� _vInven[forNum].setItemCnt(itemCnt) �� ����
	//				_OKcnt[j] -= PLAYER->getinventory()->getvInven()[k].getItemInfo().cnt;
	//				PLAYER->getinventory()->setItemCnt(k, -PLAYER->getinventory()->getvInven()[k].getItemInfo().cnt);
	//			}

	//			//���� _OKcnt�� 0���ϰ� �Ǹ� ���� _OKcnt�� �Ѿ��.(�ִ� 3������)
	//			//Ȥ�� ��� �������� ��ġ���� �������� ������ ��ġ�� ��ģ��ŭ �ٽ� �����ش�
	//			if (_OKcnt[j] <= 0)
	//			{
	//				PLAYER->getinventory()->setItemCnt(k, abs(0 - _OKcnt[j]));
	//				break;
	//			}
	//		}
	//	}
	//}//for��

	////������� ���� �����Ǹ�(_OKcnt�� ��� 0���ϸ�) �κ��丮 ���Ϳ� �������� �߰��Ѵ�.
	//if (_OKcnt[0] <= 0 && _OKcnt[1] <= 0 && _OKcnt[2] <= 0)
	//{
	//	for (int k = 0; k < PLAYER->getinventory()->getvInven().size(); k++)
	//	{
	//		if (PLAYER->getinventory()->getvInven()[k].getItemInfo().itemName == "�������" || PLAYER->getinventory()->getvInven()[k].getItemInfo().cnt <= 0)
	//		{
	//			PLAYER->setMoney(PLAYER->getMoney() - _temp.getItemInfo().orignalPrice / 2);

	//			PLAYER->getinventory()->addItem(k, _temp);
	//			break;
	//		}
	//	}
	//}
}

void NPCshopBase::baseRender()
{
	//�⺻���� ����
	_showImg->render(getMemDC(), WINSIZEX / 2 - 250, WINSIZEY / 2 - 300);
	_recipeImg->render(getMemDC(), WINSIZEX - 350, 60);

	for (int i = 1; i < 9; i++)
	{
		//�����۽���
		_itemSlotImg[i]->render(getMemDC(), _itemSlot[i].left, _itemSlot[i].top);
	}
	for (int i = 0; i < 3; i++)
	{
		//������ ������ �̹����� ������ �۵��� �̹���
		_recipeSlotImg[i]->render(getMemDC(), WINSIZEX / 2 + 200, WINSIZEY / 2 + 50 + (i * 70));
		if (_vShowRecipe.size() - 1 >= i && _vShowRecipe.size() > 0)
		{
			_vShowRecipe[i].getItemInfo().image->render(getMemDC(), WINSIZEX / 2 + 200, WINSIZEY / 2 + 50 + (i * 70));
		}
	}
	_cursor->render();
}

void NPCshopBase::playerCollision()   //����ݱ�
{
	if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &_npcRc))
	{
		if (!_showWindow)
		{
			if (KEYMANAGER->isOnceKeyDown('J'))
			{
				_showWindow = true;

				//â�� ���������� Ŀ����ġ �ʱ�ȭ
				_cursorNum = 1;
				_cursorSlot = _itemSlot[_cursorNum];
			}
		}
		if (_showWindow)
		{
			if (KEYMANAGER->isOnceKeyDown('I'))_showWindow = false;
		}
	}
}