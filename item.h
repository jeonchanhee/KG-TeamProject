#pragma once
#include"gameNode.h"
#include "singletonBase.h"

#define MAGNETPOWER 5
enum itemType //아이템 종류
{
	ITEM_EMPTY,		 //비어있음
	ITEM_ARMOR,		 //방어구 
	ITEM_ARROW,		 //활
	ITEM_SWORD,		 //검과 방패
	ITEM_ETC,		 //잡템(재료템)
	ITEM_END
};

struct itemInfo //아이템의 속성
{
	image*		image;			//이미지
	string		name;			//이름
	string		description;	//설명
	itemType	type;			//아이템의 종류
	RECT		rc;				//렉트
	RECT		magnetRc;		//바닥에 떨어진 상태에서 주변의 플레이어를 감지하는 렉트
	bool		move;			//바닥에 떨어진 아이템인지 아닌지

	int			orignalPrice;	//원가
	int			playerPrice;	//플레이어가 정한 가격

	int			atk;			//공격력
	int			def;			//방어력
	int			speed;			//속도 
};

class item : public gameNode, public singletonBase<item>
{
private:
	itemInfo m_initItem;		//아이템 벡터에 넣을 용도의 변수

	vector<itemInfo> m_vItem;  //아이템을 담을 벡터
	vector<itemInfo>::iterator m_viItem;

	
	RECT test;
public:
	item();
	~item();

	HRESULT init();
	void release();
	void update();
	void render();

	void magnet(RECT playerRc); //바닥에 떨어진 아이템인경우 플레이어에게 끌려가는 함수

	itemInfo addItem(string itemName);  //이름으로 아이템을 찾아서 보내주는 함수
	void removeItem(int arrNum);		//아이템을 벡터에서 지우는 함수
	vector<itemInfo> getItemList() { return m_vItem; } //아이템 벡터 자체를 보내는 함수
};

