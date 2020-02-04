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
	m_initItem.name = "비어있음";
	m_initItem.image = IMAGEMANAGER->addImage("비어있음", "images/비어있음.bmp", 36, 36, true, RGB(255, 0, 255));
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

	m_initItem.name = "나뭇가지";
	m_initItem.image = IMAGEMANAGER->addImage("나뭇가지", "images/나뭇가지.bmp", 36, 36, true, RGB(255, 0, 255));
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

	m_initItem.name = "골렘코어";
	m_initItem.image = IMAGEMANAGER->addImage("골렘코어", "images/골렘코어.bmp", 36, 36, true, RGB(255, 0, 255));
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

	m_initItem.name = "강화수정";
	m_initItem.image = IMAGEMANAGER->addImage("강화수정", "images/강화수정.bmp", 36, 36, true, RGB(255, 0, 255));
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

void item::magnet(RECT playerRc) //바닥에 떨어진 아이템인경우 플레이어에게 끌려가는 함수
{
	RECT temp;

	m_viItem = m_vItem.begin();
	for (m_viItem; m_viItem != m_vItem.end(); ++m_viItem)
	{
		//상태가 무브일때, 그리고 플레이어를 감지하는 렉트와 플레이어의 렉트가 충돌했을때
		if (m_viItem->move == true &&(IntersectRect(&temp,&m_viItem->magnetRc,&playerRc)))
		{
			//마그넷렉트의 x,y
			int magetX = m_viItem->magnetRc.left + (m_viItem->magnetRc.right - m_viItem->magnetRc.left) / 2;
			int magetY = m_viItem->magnetRc.top + (m_viItem->magnetRc.bottom - m_viItem->magnetRc.top) / 2;
			//플레이어의 x,y
			int playerX = playerRc.left + (playerRc.right - playerRc.left) / 2;
			int playerY = playerRc.top + (playerRc.bottom - playerRc.top) / 2;

			if (magetX <= playerX && magetY >= playerY) //우상단
			{
				m_viItem->rc.left += MAGNETPOWER;
				m_viItem->rc.right += MAGNETPOWER;
				m_viItem->rc.top -= MAGNETPOWER;
				m_viItem->rc.bottom -= MAGNETPOWER;
			}
			if (magetX <= playerX && magetY <= playerY) //우하단
			{
				m_viItem->rc.left += MAGNETPOWER;
				m_viItem->rc.right += MAGNETPOWER;
				m_viItem->rc.top += MAGNETPOWER;
				m_viItem->rc.bottom += MAGNETPOWER;
			}
			if(magetX >= playerX && magetY>= playerY) //좌상단
			{
				m_viItem->rc.left -= MAGNETPOWER;
				m_viItem->rc.right -= MAGNETPOWER;
				m_viItem->rc.top -= MAGNETPOWER;
				m_viItem->rc.bottom -= MAGNETPOWER;
			}
			if(magetX >= playerX && magetY<= playerY) //좌하단
			{
				m_viItem->rc.left -= MAGNETPOWER;
				m_viItem->rc.right -= MAGNETPOWER;
				m_viItem->rc.top += MAGNETPOWER;
				m_viItem->rc.bottom += MAGNETPOWER;
			}
		}
	}
}

itemInfo item::addItem(string itemName)//이름으로 아이템을 찾아서 보내주는 함수
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
