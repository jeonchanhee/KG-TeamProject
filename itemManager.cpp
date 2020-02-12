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
	
	//이름,타입,원가,판매가,공격력,방어력,속도,체력,회복량,갯수,최대갯수

	_item.init("비어있음",ITEM_EMPTY,0,0,0,0,0,0,0,0);
	_vItem.push_back(_item);
	
	//잡템 초기화
	_item.init("나뭇가지", ITEM_ETC, 5, 0, 0, 0, 0, 0,0,10);
	_vItem.push_back(_item);
	_item.init("강화수정", ITEM_ETC, 50, 0, 0, 0, 0,0, 0,10);
	_vItem.push_back(_item);
	_item.init("골렘코어", ITEM_ETC, 100, 0, 0, 0, 0,0,0,5);
	_vItem.push_back(_item);
	_item.init("덩쿨", ITEM_ETC, 7, 0, 0, 0, 0, 0,0,10);
	_vItem.push_back(_item);
	_item.init("쇠막대기", ITEM_ETC, 7, 0, 0, 0, 0, 0,0, 10);
	_vItem.push_back(_item);
	_item.init("수정화 된 에너지", ITEM_ETC, 0, 0, 0, 0, 0, 0,0, 10);
	_vItem.push_back(_item);
	_item.init("숫돌", ITEM_ETC, 10, 0, 0, 0, 0, 0,0, 10);
	_vItem.push_back(_item);
	_item.init("이빨석", ITEM_ETC, 5, 0, 0, 0, 0,0, 0, 10);
	_vItem.push_back(_item);
	_item.init("천", ITEM_ETC, 7, 0, 0, 0, 0, 0,0, 10);
	_vItem.push_back(_item);

	//포션 초기화
	_item.init("작은 포션", ITEM_POTION, 150, 0, 0, 0, 0, 0,50,5);
	_vItem.push_back(_item);
	_item.init("중간 포션", ITEM_POTION, 350, 0, 0, 0, 0, 0,100, 5);
	_vItem.push_back(_item);
	_item.init("큰 포션", ITEM_POTION, 550, 0, 0, 0, 0, 0,150, 5);
	_vItem.push_back(_item);
	
	//무기 초기화
	_item.init("훈련용 단검", ITEM_SWORD, 1000, 0, 20, 0, 0, 0,0, 1);
	_vItem.push_back(_item);
	_item.init("흡혈귀의 단검", ITEM_SWORD, 50000, 0, 300, 0, 0,0, 0, 1);
	_vItem.push_back(_item);
	_item.init("캐터펄트 보우", ITEM_BOW, 2000, 0, 20, 0, 10,0, 0, 1);
	_vItem.push_back(_item);
	_item.init("플레임 보우", ITEM_BOW, 100000, 0, 250, 0, 50, 0,0, 1);
	_vItem.push_back(_item);
	_item.init("훈련용 창", ITEM_SPEAR, 2000, 0, 30, 0, 5, 0, 0, 1);
	_vItem.push_back(_item);
	_item.init("골렘 드릴 창", ITEM_SPEAR, 100000, 0, 300, 0, 25, 0, 0, 1);
	_vItem.push_back(_item);
	//방어구 초기화
	_item.init("천 반다나", ITEM_HELMET, 2000, 0, 0, 0, 8, 30,0, 1);
	_vItem.push_back(_item);
	_item.init("천 흉갑", ITEM_ARMOR, 2000, 0, 0, 0, 8, 30, 0, 1);
	_vItem.push_back(_item);
	_item.init("천 부츠", ITEM_BOOTS, 2000, 0, 250, 0, 4,14, 0, 1);
	_vItem.push_back(_item);

	_item.init("철 헬멧", ITEM_HELMET, 2000, 0, 250, 0,0, 40, 0, 1);
	_vItem.push_back(_item);
	_item.init("철 흉갑", ITEM_ARMOR, 2000, 0, 250, 0,0, 40, 0, 1);
	_vItem.push_back(_item);
	_item.init("철 부츠", ITEM_BOOTS, 2000, 0, 250, 0,-4,25, 0, 1);
	_vItem.push_back(_item);

	//이름,타입,원가,판매가,공격력,방어력,속도,체력,회복량,갯수,최대갯수

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

item itemManager::addItem(string itemName)//이름으로 아이템을 찾아서 보내주는 함수
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
