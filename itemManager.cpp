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
	IMAGEMANAGER->addImage("°­È­¼öÁ¤", "images/item/°­È­¼öÁ¤.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ºñ¾îÀÖÀ½", "images/item/ºñ¾îÀÖÀ½.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ãµ ¹Ý´Ù³ª", "images/item/Ãµ ¹Ý´Ù³ª.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ãµ Èä°©", "images/item/Ãµ Èä°©.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ãµ ºÎÃ÷", "images/item/Ãµ ºÎÃ÷.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ãµ", "images/item/Ãµ.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ã¶ ºÎÃ÷", "images/item/Ã¶ ºÎÃ÷.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ã¶ Çï¸ä", "images/item/Ã¶ Çï¸ä.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ã¶ Èä°©", "images/item/Ã¶ Èä°©.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¼è¸·´ë±â", "images/item/¼è¸·´ë±â.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¼öÁ¤È­ µÈ ¿¡³ÊÁö", "images/item/¼öÁ¤È­ µÈ ¿¡³ÊÁö.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¼ýµ¹", "images/item/¼ýµ¹.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÀÌ»¡¼®", "images/item/ÀÌ»¡¼®.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("µ¢Äð", "images/item/µ¢Äð.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("³ª¹µ°¡Áö", "images/item/³ª¹µ°¡Áö.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("°ñ·½ÄÚ¾î", "images/item/°ñ·½ÄÚ¾î.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Å« Æ÷¼Ç", "images/item/Å«Æ÷¼Ç.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÀÛÀº Æ÷¼Ç", "images/item/ÀÛÀºÆ÷¼Ç.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Áß°£ Æ÷¼Ç", "images/item/Áß°£Æ÷¼Ç.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÇÃ·¹ÀÓ º¸¿ì", "images/item/ÇÃ·¹ÀÓº¸¿ì.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ä³ÅÍÆÞÆ® º¸¿ì", "images/item/Ä³ÅÍÆÞÆ®º¸¿ì.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÈÆ·Ã¿ë ´Ü°Ë", "images/item/ÈÆ·Ã¿ë´Ü°Ë.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÈíÇ÷±ÍÀÇ ´Ü°Ë", "images/item/ÈíÇ÷±ÍÀÇ´Ü°Ë.bmp", 36, 36, true, RGB(255, 0, 255));


	//ÀÌ¸§,Å¸ÀÔ,¶³¾îÁ®ÀÖ´ÂÁö,¿ø°¡,ÆÇ¸Å°¡,°ø°Ý·Â,¹æ¾î·Â,¼Óµµ,Ã¼·Â,È¸º¹·®,°¹¼ö,ÃÖ´ë°¹¼ö
	_item.init("ºñ¾îÀÖÀ½",ITEM_EMPTY,false,0,0,0,0,0,0,0,0,0);
	_vItem.push_back(_item);
	
	//ÀâÅÛ ÃÊ±âÈ­
	_item.init("³ª¹µ°¡Áö", ITEM_ETC, false, 5, 0, 0, 0, 0, 0,0,0,10);
	_vItem.push_back(_item);
	_item.init("°­È­¼öÁ¤", ITEM_ETC, false, 50, 0, 0, 0, 0,0, 0,0,10);
	_vItem.push_back(_item);
	_item.init("°ñ·½ÄÚ¾î", ITEM_ETC, false, 100, 0, 0, 0, 0,0, 0,0,5);
	_vItem.push_back(_item);
	_item.init("µ¢Äð", ITEM_ETC, false, 7, 0, 0, 0, 0, 0,0, 0,10);
	_vItem.push_back(_item);
	_item.init("¼è¸·´ë±â", ITEM_ETC, false, 7, 0, 0, 0, 0, 0,0, 0,10);
	_vItem.push_back(_item);
	_item.init("¼öÁ¤È­ µÈ ¿¡³ÊÁö", ITEM_ETC, false, 0, 0, 0, 0, 0, 0,0, 0,10);
	_vItem.push_back(_item);
	_item.init("¼ýµ¹", ITEM_ETC, false, 10, 0, 0, 0, 0, 0,0, 0,10);
	_vItem.push_back(_item);
	_item.init("ÀÌ»¡¼®", ITEM_ETC, false, 5, 0, 0, 0, 0,0, 0, 0,10);
	_vItem.push_back(_item);
	_item.init("Ãµ", ITEM_ETC, false, 7, 0, 0, 0, 0, 0,0, 0,10);
	_vItem.push_back(_item);

	//Æ÷¼Ç ÃÊ±âÈ­
	_item.init("ÀÛÀº Æ÷¼Ç", ITEM_POTION, false, 150, 0, 0, 0, 0, 0,50,0,5);
	_vItem.push_back(_item);
	_item.init("Áß°£ Æ÷¼Ç", ITEM_POTION, false, 350, 0, 0, 0, 0, 0,100, 0,5);
	_vItem.push_back(_item);
	_item.init("Å« Æ÷¼Ç", ITEM_POTION, false, 550, 0, 0, 0, 0, 0,150, 0,5);
	_vItem.push_back(_item);
	
	//¹«±â ÃÊ±âÈ­
	_item.init("ÈÆ·Ã¿ë ´Ü°Ë", ITEM_SWORD, false, 1000, 0, 20, 0, 0, 0,0, 0,1);
	_vItem.push_back(_item);
	_item.init("ÈíÇ÷±ÍÀÇ ´Ü°Ë", ITEM_SWORD, false, 500000, 0, 300, 0, 0,0, 0, 0,1);
	_vItem.push_back(_item);
	_item.init("Ä³ÅÍÆÞÆ® º¸¿ì", ITEM_BOW, false, 2000, 0, 20, 0, 10,0, 0, 0,1);
	_vItem.push_back(_item);
	_item.init("ÇÃ·¹ÀÓ º¸¿ì", ITEM_BOW, false, 1000000, 0, 250, 0, 50, 0,0, 0,1);
	_vItem.push_back(_item);

	//¹æ¾î±¸ ÃÊ±âÈ­
	_item.init("Ãµ ¹Ý´Ù³ª", ITEM_HELMET, false, 2000, 0, 0, 0, 8, 30,0, 0,1);
	_vItem.push_back(_item);
	_item.init("Ãµ Èä°©", ITEM_ARMOR, false, 2000, 0, 0, 0, 8, 30, 0, 0,1);
	_vItem.push_back(_item);
	_item.init("Ãµ ºÎÃ÷", ITEM_BOOTS, false, 2000, 0, 250, 0, 4,14, 0, 0,1);
	_vItem.push_back(_item);

	_item.init("Ã¶ Çï¸ä", ITEM_HELMET, false, 2000, 0, 250, 0,0, 40, 0, 0,1);
	_vItem.push_back(_item);
	_item.init("Ã¶ Èä°©", ITEM_ARMOR, false, 2000, 0, 250, 0,0, 40, 0, 0,1);
	_vItem.push_back(_item);
	_item.init("Ã¶ ºÎÃ÷", ITEM_BOOTS, false, 2000, 0, 250, 0,-4,25, 0, 0,1);
	_vItem.push_back(_item);

	//ÀÌ¸§,Å¸ÀÔ,¶³¾îÁ®ÀÖ´ÂÁö,¿ø°¡,ÆÇ¸Å°¡,°ø°Ý·Â,¹æ¾î·Â,¼Óµµ,Ã¼·Â,È¸º¹·®,°¹¼ö,ÃÖ´ë°¹¼ö

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

item itemManager::addItem(string itemName)//ÀÌ¸§À¸·Î ¾ÆÀÌÅÛÀ» Ã£¾Æ¼­ º¸³»ÁÖ´Â ÇÔ¼ö
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
