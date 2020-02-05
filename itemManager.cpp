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
	IMAGEMANAGER->addImage("��ȭ����", "images/item/��ȭ����.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�������", "images/item/�������.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("õ �ݴٳ�", "images/item/õ �ݴٳ�.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("õ �䰩", "images/item/õ �䰩.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("õ ����", "images/item/õ ����.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("õ", "images/item/õ.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ö ����", "images/item/ö ����.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ö ���", "images/item/ö ���.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ö �䰩", "images/item/ö �䰩.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�踷���", "images/item/�踷���.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����ȭ �� ������", "images/item/����ȭ �� ������.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "images/item/����.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�̻���", "images/item/�̻���.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "images/item/����.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��������", "images/item/��������.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���ھ�", "images/item/���ھ�.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ū ����", "images/item/ū����.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���� ����", "images/item/��������.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�߰� ����", "images/item/�߰�����.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�÷��� ����", "images/item/�÷��Ӻ���.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ĳ����Ʈ ����", "images/item/ĳ����Ʈ����.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ʒÿ� �ܰ�", "images/item/�Ʒÿ�ܰ�.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�������� �ܰ�", "images/item/�������Ǵܰ�.bmp", 36, 36, true, RGB(255, 0, 255));


	//�̸�,Ÿ��,�������ִ���,����,�ǸŰ�,���ݷ�,����,�ӵ�,ü��,ȸ����,����,�ִ밹��
	_item.init("�������",ITEM_EMPTY,false,0,0,0,0,0,0,0,0,0);
	_vItem.push_back(_item);
	
	//���� �ʱ�ȭ
	_item.init("��������", ITEM_ETC, false, 5, 0, 0, 0, 0, 0,0,0,10);
	_vItem.push_back(_item);
	_item.init("��ȭ����", ITEM_ETC, false, 50, 0, 0, 0, 0,0, 0,0,10);
	_vItem.push_back(_item);
	_item.init("���ھ�", ITEM_ETC, false, 100, 0, 0, 0, 0,0, 0,0,5);
	_vItem.push_back(_item);
	_item.init("����", ITEM_ETC, false, 7, 0, 0, 0, 0, 0,0, 0,10);
	_vItem.push_back(_item);
	_item.init("�踷���", ITEM_ETC, false, 7, 0, 0, 0, 0, 0,0, 0,10);
	_vItem.push_back(_item);
	_item.init("����ȭ �� ������", ITEM_ETC, false, 0, 0, 0, 0, 0, 0,0, 0,10);
	_vItem.push_back(_item);
	_item.init("����", ITEM_ETC, false, 10, 0, 0, 0, 0, 0,0, 0,10);
	_vItem.push_back(_item);
	_item.init("�̻���", ITEM_ETC, false, 5, 0, 0, 0, 0,0, 0, 0,10);
	_vItem.push_back(_item);
	_item.init("õ", ITEM_ETC, false, 7, 0, 0, 0, 0, 0,0, 0,10);
	_vItem.push_back(_item);

	//���� �ʱ�ȭ
	_item.init("���� ����", ITEM_POTION, false, 150, 0, 0, 0, 0, 0,50,0,5);
	_vItem.push_back(_item);
	_item.init("�߰� ����", ITEM_POTION, false, 350, 0, 0, 0, 0, 0,100, 0,5);
	_vItem.push_back(_item);
	_item.init("ū ����", ITEM_POTION, false, 550, 0, 0, 0, 0, 0,150, 0,5);
	_vItem.push_back(_item);
	
	//���� �ʱ�ȭ
	_item.init("�Ʒÿ� �ܰ�", ITEM_SWORD, false, 1000, 0, 20, 0, 0, 0,0, 0,1);
	_vItem.push_back(_item);
	_item.init("�������� �ܰ�", ITEM_SWORD, false, 500000, 0, 300, 0, 0,0, 0, 0,1);
	_vItem.push_back(_item);
	_item.init("ĳ����Ʈ ����", ITEM_BOW, false, 2000, 0, 20, 0, 10,0, 0, 0,1);
	_vItem.push_back(_item);
	_item.init("�÷��� ����", ITEM_BOW, false, 1000000, 0, 250, 0, 50, 0,0, 0,1);
	_vItem.push_back(_item);

	//�� �ʱ�ȭ
	_item.init("õ �ݴٳ�", ITEM_HELMET, false, 2000, 0, 0, 0, 8, 30,0, 0,1);
	_vItem.push_back(_item);
	_item.init("õ �䰩", ITEM_ARMOR, false, 2000, 0, 0, 0, 8, 30, 0, 0,1);
	_vItem.push_back(_item);
	_item.init("õ ����", ITEM_BOOTS, false, 2000, 0, 250, 0, 4,14, 0, 0,1);
	_vItem.push_back(_item);

	_item.init("ö ���", ITEM_HELMET, false, 2000, 0, 250, 0,0, 40, 0, 0,1);
	_vItem.push_back(_item);
	_item.init("ö �䰩", ITEM_ARMOR, false, 2000, 0, 250, 0,0, 40, 0, 0,1);
	_vItem.push_back(_item);
	_item.init("ö ����", ITEM_BOOTS, false, 2000, 0, 250, 0,-4,25, 0, 0,1);
	_vItem.push_back(_item);

	//�̸�,Ÿ��,�������ִ���,����,�ǸŰ�,���ݷ�,����,�ӵ�,ü��,ȸ����,����,�ִ밹��

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
