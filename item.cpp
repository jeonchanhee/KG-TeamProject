#include "stdafx.h"
#include "item.h"


item::item()
{
}


item::~item()
{
}

HRESULT item::init()
{
	m_initItem.name = "�������";
	m_initItem.image = IMAGEMANAGER->addImage("�������", "images/�������.bmp", 36, 36, true, RGB(255, 0, 255));
	m_initItem.description = "";
	m_initItem.type = ITEM_EMPTY;
	m_initItem.move = false;
	m_initItem.orignalPrice = 0;
	m_initItem.playerPrice = 0;
	m_initItem.rc = RectMakeCenter(0, 0, m_initItem.image->getWidth(), m_initItem.image->getHeight());
	m_initItem.magnetRc = RectMakeCenter(m_initItem.rc.left, m_initItem.rc.top, m_initItem.image->getWidth() * 5, m_initItem.image->getHeight()*5);
	m_initItem.atk = 0;
	m_initItem.def = 0;
	m_initItem.speed = 0;
	m_vItem.push_back(m_initItem);

	m_initItem.name = "��������";
	m_initItem.image = IMAGEMANAGER->addImage("��������", "images/��������.bmp", 36, 36, true, RGB(255, 0, 255));
	m_initItem.description = "";
	m_initItem.type = ITEM_ETC;
	m_initItem.move = false;
	m_initItem.orignalPrice = 5;
	m_initItem.playerPrice = 0;
	m_initItem.rc = RectMakeCenter(0, 0, m_initItem.image->getWidth(), m_initItem.image->getHeight());
	m_initItem.magnetRc = RectMakeCenter(m_initItem.rc.left, m_initItem.rc.top, m_initItem.image->getWidth() * 5, m_initItem.image->getHeight() * 5);
	m_initItem.atk = 0;
	m_initItem.def = 0;
	m_initItem.speed = 0;
	m_vItem.push_back(m_initItem);

	m_initItem.name = "���ھ�";
	m_initItem.image = IMAGEMANAGER->addImage("���ھ�", "images/���ھ�.bmp", 36, 36, true, RGB(255, 0, 255));
	m_initItem.description = "";
	m_initItem.type = ITEM_ETC;
	m_initItem.move = false;
	m_initItem.orignalPrice = 50;
	m_initItem.playerPrice = 0;
	m_initItem.rc = RectMakeCenter(0, 0, m_initItem.image->getWidth(), m_initItem.image->getHeight());
	m_initItem.magnetRc = RectMakeCenter(m_initItem.rc.left, m_initItem.rc.top, m_initItem.image->getWidth() * 5, m_initItem.image->getHeight() * 5);
	m_initItem.atk = 0;
	m_initItem.def = 0;
	m_initItem.speed = 0;
	m_vItem.push_back(m_initItem);

	m_initItem.name = "��ȭ����";
	m_initItem.image = IMAGEMANAGER->addImage("��ȭ����", "images/��ȭ����.bmp", 36, 36, true, RGB(255, 0, 255));
	m_initItem.description = "";
	m_initItem.type = ITEM_ETC;
	m_initItem.move = false;
	m_initItem.orignalPrice = 50;
	m_initItem.playerPrice = 0;
	m_initItem.rc = RectMakeCenter(0, 0, m_initItem.image->getWidth(), m_initItem.image->getHeight());
	m_initItem.magnetRc = RectMakeCenter(m_initItem.rc.left, m_initItem.rc.top, m_initItem.image->getWidth() * 5, m_initItem.image->getHeight() * 5);
	m_initItem.atk = 0;
	m_initItem.def = 0;
	m_initItem.speed = 0;
	m_vItem.push_back(m_initItem);

	return S_OK;
}

void item::release()
{
}

void item::update()
{
	test = RectMakeCenter(m_ptMouse.x, m_ptMouse.y, 30, 30);
	magnet(test);
}

void item::render()
{
	Rectangle(getMemDC(), test.left, test.top, test.right, test.bottom);

	m_viItem = m_vItem.begin();
	for (m_viItem; m_viItem != m_vItem.end(); ++m_viItem)
	{
		(*m_viItem).image->render(getMemDC(), (*m_viItem).rc.left, (*m_viItem).rc.top); 
	}
}

void item::magnet(RECT playerRc) //�ٴڿ� ������ �������ΰ�� �÷��̾�� �������� �Լ�
{
	RECT temp;

	m_viItem = m_vItem.begin();
	for (m_viItem; m_viItem != m_vItem.end(); ++m_viItem)
	{
		//���°� �����϶�, �׸��� �÷��̾ �����ϴ� ��Ʈ�� �÷��̾��� ��Ʈ�� �浹������
		if (m_viItem->move == true &&(IntersectRect(&temp,&m_viItem->magnetRc,&playerRc)))
		{
			//���׳ݷ�Ʈ�� x,y
			int magetX = m_viItem->magnetRc.left + (m_viItem->magnetRc.right - m_viItem->magnetRc.left) / 2;
			int magetY = m_viItem->magnetRc.top + (m_viItem->magnetRc.bottom - m_viItem->magnetRc.top) / 2;
			//�÷��̾��� x,y
			int playerX = playerRc.left + (playerRc.right - playerRc.left) / 2;
			int playerY = playerRc.top + (playerRc.bottom - playerRc.top) / 2;

			if (magetX <= playerX && magetY >= playerY) //����
			{
				m_viItem->rc.left += MAGNETPOWER;
				m_viItem->rc.right += MAGNETPOWER;
				m_viItem->rc.top -= MAGNETPOWER;
				m_viItem->rc.bottom -= MAGNETPOWER;
			}
			if (magetX <= playerX && magetY <= playerY) //���ϴ�
			{
				m_viItem->rc.left += MAGNETPOWER;
				m_viItem->rc.right += MAGNETPOWER;
				m_viItem->rc.top += MAGNETPOWER;
				m_viItem->rc.bottom += MAGNETPOWER;
			}
			if(magetX >= playerX && magetY>= playerY) //�»��
			{
				m_viItem->rc.left -= MAGNETPOWER;
				m_viItem->rc.right -= MAGNETPOWER;
				m_viItem->rc.top -= MAGNETPOWER;
				m_viItem->rc.bottom -= MAGNETPOWER;
			}
			if(magetX >= playerX && magetY<= playerY) //���ϴ�
			{
				m_viItem->rc.left -= MAGNETPOWER;
				m_viItem->rc.right -= MAGNETPOWER;
				m_viItem->rc.top += MAGNETPOWER;
				m_viItem->rc.bottom += MAGNETPOWER;
			}
		}
	}
}

itemInfo item::addItem(string itemName)//�̸����� �������� ã�Ƽ� �����ִ� �Լ�
{
	m_viItem = m_vItem.begin();
	for (m_viItem; m_viItem != m_vItem.end(); ++m_viItem)
	{
		if (m_viItem->name == itemName)
		{
			return (*m_viItem);
		}
	}
}

void item::removeItem(int arrNum)
{
	m_vItem.erase(m_vItem.begin() + arrNum);
}
