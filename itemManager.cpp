#include "stdafx.h"
#include "itemManager.h"


itemManager::itemManager()
{
}


itemManager::~itemManager()
{
}

HRESULT itemManager::init()
{
	
	//�̸�,Ÿ��,����,�ǸŰ�,���ݷ�,����,�ӵ�,ü��,ȸ����,����,�ִ밹��

	_item.init("�������",ITEM_EMPTY,0,0,0,0,0,0,0,0);
	_vItem.push_back(_item);
	
	//���� �ʱ�ȭ
	_item.init("��������", ITEM_ETC, 5, 0, 0, 0, 0, 0,0,10);
	_vItem.push_back(_item);
	_item.init("��ȭ����", ITEM_ETC, 50, 0, 0, 0, 0,0, 0,10);
	_vItem.push_back(_item);
	_item.init("���ھ�", ITEM_ETC, 100, 0, 0, 0, 0,0,0,5);
	_vItem.push_back(_item);
	_item.init("����", ITEM_ETC, 7, 0, 0, 0, 0, 0,0,10);
	_vItem.push_back(_item);
	_item.init("�踷���", ITEM_ETC, 7, 0, 0, 0, 0, 0,0, 10);
	_vItem.push_back(_item);
	_item.init("����ȭ �� ������", ITEM_ETC, 0, 0, 0, 0, 0, 0,0, 10);
	_vItem.push_back(_item);
	_item.init("����", ITEM_ETC, 10, 0, 0, 0, 0, 0,0, 10);
	_vItem.push_back(_item);
	_item.init("�̻���", ITEM_ETC, 5, 0, 0, 0, 0,0, 0, 10);
	_vItem.push_back(_item);
	_item.init("õ", ITEM_ETC, 7, 0, 0, 0, 0, 0,0, 10);
	_vItem.push_back(_item);

	//���� �ʱ�ȭ
	_item.init("���� ����", ITEM_POTION, 150, 0, 0, 0, 0, 0,50,5);
	_vItem.push_back(_item);
	_item.init("�߰� ����", ITEM_POTION, 350, 0, 0, 0, 0, 0,100, 5);
	_vItem.push_back(_item);
	_item.init("ū ����", ITEM_POTION, 550, 0, 0, 0, 0, 0,150, 5);
	_vItem.push_back(_item);
	
	//���� �ʱ�ȭ
	_item.init("�Ʒÿ� �ܰ�", ITEM_SWORD, 1000, 0, 20, 0, 0, 0,0, 1);
	_vItem.push_back(_item);
	_item.init("�������� �ܰ�", ITEM_SWORD, 50000, 0, 300, 0, 0,0, 0, 1);
	_vItem.push_back(_item);
	_item.init("ĳ����Ʈ ����", ITEM_BOW, 2000, 0, 20, 0, 10,0, 0, 1);
	_vItem.push_back(_item);
	_item.init("�÷��� ����", ITEM_BOW, 100000, 0, 250, 0, 50, 0,0, 1);
	_vItem.push_back(_item);
	_item.init("�Ʒÿ� â", ITEM_SPEAR, 2000, 0, 30, 0, 5, 0, 0, 1);
	_vItem.push_back(_item);
	_item.init("�� �帱 â", ITEM_SPEAR, 100000, 0, 300, 0, 25, 0, 0, 1);
	_vItem.push_back(_item);
	//�� �ʱ�ȭ
	_item.init("õ �ݴٳ�", ITEM_HELMET, 2000, 0, 0, 0, 8, 30,0, 1);
	_vItem.push_back(_item);
	_item.init("õ �䰩", ITEM_ARMOR, 2000, 0, 0, 0, 8, 30, 0, 1);
	_vItem.push_back(_item);
	_item.init("õ ����", ITEM_BOOTS, 2000, 0, 250, 0, 4,14, 0, 1);
	_vItem.push_back(_item);

	_item.init("ö ���", ITEM_HELMET, 2000, 0, 250, 0,0, 40, 0, 1);
	_vItem.push_back(_item);
	_item.init("ö �䰩", ITEM_ARMOR, 2000, 0, 250, 0,0, 40, 0, 1);
	_vItem.push_back(_item);
	_item.init("ö ����", ITEM_BOOTS, 2000, 0, 250, 0,-4,25, 0, 1);
	_vItem.push_back(_item);

	//�̸�,Ÿ��,����,�ǸŰ�,���ݷ�,����,�ӵ�,ü��,ȸ����,����,�ִ밹��

	return S_OK;
}

void itemManager::release()
{
}

void itemManager::update()
{
	_viItem = _vItem.begin();
	for (_viItem; _viItem != _vItem.end(); ++_viItem)
	{
		(*_viItem).update();
	}
}

void itemManager::render()
{
	_viItem = _vItem.begin();
	for (_viItem; _viItem != _vItem.end(); ++_viItem)
	{
		(*_viItem).render();
	}
}

item itemManager::addItem(string itemName)//�̸����� �������� ã�Ƽ� �����ִ� �Լ�
{
	_viItem = _vItem.begin();
	for (_viItem; _viItem != _vItem.end(); ++_viItem)
	{
		if (_viItem->getItemInfo().itemName == itemName)
		{
			return (*_viItem);
		}
	}
	//for (int i = 0; i < _vItem.size(); i++)
	//{
	//	if (_vItem[i].getName() == itemName)
	//	{
	//		return _vItem[i];
	//	}
	//}
}

item itemManager::addItem(string itemName, int cntNum)
{
	_viItem = _vItem.begin();
	for (_viItem; _viItem != _vItem.end(); ++_viItem)
	{
		if (_viItem->getItemInfo().itemName == itemName)
		{
			return (*_viItem);
			break;
		}
	}
}
