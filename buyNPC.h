#pragma once
#include"gameNode.h"
#define PLAYERSPEED 1
#define CAMERASPEED 1

class buyNPC : public gameNode
{
private:
	image * _img;		//이미지
	animation * _ani;	//애니
	animation * _talkAni;	//토크애니
	int _x, _y;			//중심좌표
	RECT _rc;			//이미지 사각형
	POINT point;		//아이템 구매할 위치
	bool isLeft;
	bool isRight;
	bool isUp;
	bool isDown;
	int itemRndNum;
	bool _move;
	bool isTalk;
	bool isTalking;
	bool isCheap;
	bool isExpensive;
	bool isVeryCheap;
	bool isVeryExpensive;
	image * itemImg;	//아이템이미지
	image * talkImg;	//토크이미지
	int playerPrice;	//플레이어가격
	int oriPrice;		//정가
	RECT itemRc;		//아이템렉트
	RECT talkRc;		//토크이미지렉트
	int talkCount;		//토크 카운트
	int waitCount;		//기다림 카운트
	int exit;			//시간되면 사라짐
	bool motionChange;	//모션이미지바꿈
	bool talkChange;	//토크이미지바꿈
	int step;			//0일때 상품으로 걸어감. 1일때 정지. 2일때 플레이어로 걸어감. 3일때 정지. 4일때 밖으로 간다
	bool isWait;
public:
	RECT _tableRc;
	int num;
	buyNPC();
	~buyNPC();

	HRESULT init(RECT _tableRect);
	void release();
	void update(item& item1, item& item2, item& item3, item& item4);
	void render();
	void aniChange();	//아이템 구매할 위치를 찾아 이동
	void talk(item& item1, item& item2, item& item3, item& item4);	//감정
	void talking();		//감정모션
	void soso();
	void cheap();
	void expensive();
	void veryCheap();
	void veryExpensive();
	void wait();
	bool sell();	//판매및 금액수령
	int reduceItemNum;
	//get
	int getReduceItemNum() { return reduceItemNum; }
	//set
};

