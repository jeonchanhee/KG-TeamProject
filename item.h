#pragma once

#define MAGNETPOWER 2

enum itemType //아이템 종류
{
	ITEM_EMPTY,		 //비어있음
	ITEM_ARMOR,		 //방어구 
	ITEM_HELMET,	 //헬멧
	ITEM_BOOTS,		 //부츠
	ITEM_BOW,		 //활
	ITEM_SWORD,		 //검과 방패
	ITEM_POTION,	 //물약
	ITEM_ETC		 //잡템(재료템)
};
struct itemInfo
{
	image*		image;			//이미지
	string		itemName;		//이름
	itemType	type;			//아이템의 종류
	RECT		rc;				//렉트
	RECT		magnetRc;		//바닥에 떨어진 상태에서 주변의 플레이어를 감지하는 렉트

	bool		move;			//바닥에 떨어진 아이템인지 아닌지

	int			orignalPrice;	//원가
	int			playerPrice;	//플레이어가 정한 가격

	int			atk;			//공격력
	int			def;			//방어력
	int			speed;			//속도 
	int			hp;				//체력

	int			heal;			//포션의 회복양

	int			cnt;			//현재소지갯수
	int			maxCnt;			//인벤토리 1칸당 최대소지갯수
	bool		maxItem;		//소지갯수가 최대에 도달하면 true
};

class item
{
private:
	itemInfo _item;

	bool updown;			 //바닥에 떨어진 템이 위아래로 흔들릴떄 쓰는 변수
	int waveCnt;			 //바닥에 떨어진 템이 위아래로 흔들릴떄 쓰는 변수
	RECT test;
public:
	item();
	~item();

	HRESULT init(const char* name, itemType type, int orignalPrice, int playerPrice,
				 int atk, int def, int speed, int hp, int heal, int maxCnt);
	void release();
	void update();
	void render();

	void magnet(RECT playerRc);						//바닥에 떨어진 템이 플레이어게 끌려가는 기능
	void wave();									//바닥에 떨어진 아이템이 약간 흔들리는 기능
	itemInfo getItemInfo() {return _item;}			//아이템 정보를 가져옴
	RECT getRECT() { return _item.rc; }				//아이템의 렉트를 가져옴
	void setItemCnt() { _item.cnt++; }				//갯수1증가
	void setItemCnt(int num) { _item.cnt+= num; }	//갯수를 num만큼 증가
	void setMaxItem() { _item.maxItem = true; }		

	// 렉트의 위치를 설정
	void setRect(int x, int y) { _item.rc = RectMakeCenter(x, y, _item.image->getWidth(), _item.image->getHeight()); } 
	void setRect(RECT rc) { _item.rc = rc; } 
	
	//아이템의 상태를 바꿔줌(인벤에 있을때 false, 바닥에 떨어져있을때 true)
	void setMove(bool move) { _item.move = move; } 

	//플레이어가 아이템가격을 정할때 쓰는 함수
	void setPlayerPrice(int price) { _item.playerPrice = price; } 

																													  
	//string getType() { return _type; } // 이름을 가져옴
	//RECT getRect() { return _rc; } //rc를 가져옴



};

