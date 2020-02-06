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
	
	//이름,타입,떨어져있는지,원가,판매가,공격력,방어력,속도,체력,회복량,갯수,최대갯수
	_item.init("비어있음",ITEM_EMPTY,false,0,0,0,0,0,0,0,0,0);
	_vItem.push_back(_item);
	
	//잡템 초기화
	_item.init("나뭇가지", ITEM_ETC, false, 5, 0, 0, 0, 0, 0,0,0,10);
	_vItem.push_back(_item);
	_item.init("강화수정", ITEM_ETC, false, 50, 0, 0, 0, 0,0, 0,0,10);
	_vItem.push_back(_item);
	_item.init("골렘코어", ITEM_ETC, false, 100, 0, 0, 0, 0,0, 0,0,5);
	_vItem.push_back(_item);
	_item.init("덩쿨", ITEM_ETC, false, 7, 0, 0, 0, 0, 0,0, 0,10);
	_vItem.push_back(_item);
	_item.init("쇠막대기", ITEM_ETC, false, 7, 0, 0, 0, 0, 0,0, 0,10);
	_vItem.push_back(_item);
	_item.init("수정화 된 에너지", ITEM_ETC, false, 0, 0, 0, 0, 0, 0,0, 0,10);
	_vItem.push_back(_item);
	_item.init("숫돌", ITEM_ETC, false, 10, 0, 0, 0, 0, 0,0, 0,10);
	_vItem.push_back(_item);
	_item.init("이빨석", ITEM_ETC, false, 5, 0, 0, 0, 0,0, 0, 0,10);
	_vItem.push_back(_item);
	_item.init("천", ITEM_ETC, false, 7, 0, 0, 0, 0, 0,0, 0,10);
	_vItem.push_back(_item);

	//포션 초기화
	_item.init("작은 포션", ITEM_POTION, false, 150, 0, 0, 0, 0, 0,50,0,5);
	_vItem.push_back(_item);
	_item.init("중간 포션", ITEM_POTION, false, 350, 0, 0, 0, 0, 0,100, 0,5);
	_vItem.push_back(_item);
	_item.init("큰 포션", ITEM_POTION, false, 550, 0, 0, 0, 0, 0,150, 0,5);
	_vItem.push_back(_item);
	
	//무기 초기화
	_item.init("훈련용 단검", ITEM_SWORD, false, 1000, 0, 20, 0, 0, 0,0, 0,1);
	_vItem.push_back(_item);
	_item.init("흡혈귀의 단검", ITEM_SWORD, false, 500000, 0, 300, 0, 0,0, 0, 0,1);
	_vItem.push_back(_item);
	_item.init("캐터펄트 보우", ITEM_BOW, false, 2000, 0, 20, 0, 10,0, 0, 0,1);
	_vItem.push_back(_item);
	_item.init("플레임 보우", ITEM_BOW, false, 1000000, 0, 250, 0, 50, 0,0, 0,1);
	_vItem.push_back(_item);

	//방어구 초기화
	_item.init("천 반다나", ITEM_HELMET, false, 2000, 0, 0, 0, 8, 30,0, 0,1);
	_vItem.push_back(_item);
	_item.init("천 흉갑", ITEM_ARMOR, false, 2000, 0, 0, 0, 8, 30, 0, 0,1);
	_vItem.push_back(_item);
	_item.init("천 부츠", ITEM_BOOTS, false, 2000, 0, 250, 0, 4,14, 0, 0,1);
	_vItem.push_back(_item);

	_item.init("철 헬멧", ITEM_HELMET, false, 2000, 0, 250, 0,0, 40, 0, 0,1);
	_vItem.push_back(_item);
	_item.init("철 흉갑", ITEM_ARMOR, false, 2000, 0, 250, 0,0, 40, 0, 0,1);
	_vItem.push_back(_item);
	_item.init("철 부츠", ITEM_BOOTS, false, 2000, 0, 250, 0,-4,25, 0, 0,1);
	_vItem.push_back(_item);

	//이름,타입,떨어져있는지,원가,판매가,공격력,방어력,속도,체력,회복량,갯수,최대갯수

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
