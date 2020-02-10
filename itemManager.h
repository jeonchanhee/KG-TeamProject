#pragma once
#include"item.h"
#include "singletonBase.h"

class itemManager : public item, public singletonBase<itemManager>
{
private:
	item _item;						 //아이템을 초기화할 변수

	vector<item> _vItem;			 //아이템을 담을 벡터
	vector<item>::iterator _viItem;


public:
	itemManager();
	~itemManager();

	HRESULT init();
	void release();
	void update();
	void render();



	item addItem(string itemName);				  //이름으로 아이템을 찾아서 보내주는 함수
	item addItem(string itemName , int cntNum);	  //이름으로 아이템을 찾아서 보내주는 함수, 숫자로 갯수도 세팅가능
	vector<item> getItemList() { return _vItem; } //아이템 벡터 자체를 보내는 함수

};

