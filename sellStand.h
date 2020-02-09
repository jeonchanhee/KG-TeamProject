#pragma once
#include "gameNode.h"
#define SLOTNUM 4
class sellStand : public gameNode
{
private:
	image*		_img;				 //판매대 이미지
	RECT		_rc;				 //판매대 렉트

	image*		_sellImag;		 //판매창 이미지

	image*		_slotImage[SLOTNUM];
	RECT		_slot[SLOTNUM];			 //판매창의 아이템 슬롯
	RECT		_sellInfo[SLOTNUM];		 //판매아이템 가격 정하는 부분의 렉트
	
	vector<item> _vSellItem;  //판매 아이템을 담을 벡터

	bool _showWindow;
public:
	sellStand();
	~sellStand();

	HRESULT init();
	void release();
	void update();
	void render();

	RECT getRECT() { return _rc; }

	void setShow(bool show) { _showWindow = show; }
};

