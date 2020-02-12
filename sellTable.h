#pragma once
#include "gameNode.h"
#include "cursor.h"
#define SLOTNUM 4
class sellTable : public gameNode
{
private:
	RECT		_tableRc;				 //판매대 렉트

	image*		_sellMainImg;		 //판매창 이미지

	image*		_slotImage[SLOTNUM];
	RECT		_slot[SLOTNUM];			 //판매창의 아이템 슬롯
	RECT		_sellInfo[SLOTNUM];		 //판매아이템 가격 정하는 부분의 렉트
	RECT temp;
	vector<item> _vSellItem;  //판매 아이템을 담을 벡터

	int playerPrice;



	//커서
	cursor* _cursor;
	RECT _cursorSlot;				//템선택하는렉트(커서)
	int _cursorNum;					//몇번슬롯이 선택되었는지
	item _itemTemp;			//아이템을 임시로 담을 벡터
	image* _grab;					//커서가 잡은 아이템의 배경

	bool _showWindow;
	bool _choiceItem;				//아이템을 선택했는지
public:
	sellTable();
	~sellTable();

	HRESULT init();
	void release();
	void update();
	void render();

	void cursorControl();
	void playerCollision();
};

