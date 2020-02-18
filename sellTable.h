#pragma once
#include "gameNode.h"
#include "cursor.h"
#define SLOTNUM 4

struct sellSlot
{
	image*		img;		//슬롯 이미지
	RECT		rc;			//판매창의 아이템 슬롯
	item		item;
	float  x, y;
};
class sellTable : public gameNode
{
private:
	RECT		 _tableRc;					//판매대 렉트

	image*		 _sellMainImg;				//판매창 이미지
	RECT		 _sellInfo[SLOTNUM];		//판매아이템 가격 정하는 부분의 렉트

	sellSlot _sellSlot;
	vector<sellSlot>	_vSlot;
	vector<sellSlot>	_vTemp;;


	int  _playerPrice[SLOTNUM][8];			//가격을 정할 배열
	int  _BoxChoiceNum;						//이 변수를 사용해서 _playerPrice 배열을 이동하며 키보드로 가격을 정함


	bool   _selectNum;						//_sellInfo렉트에서 j를 누르면 true가 되어 아이템을 정하는 모드가 됨
	image* _selectUpdownImg;				//가격정할때 위아래 화살표뜨는 이미지
	RECT   _selectUpdownRc;					//가격정할때 위아래 화살표뜨는 이미지의 렉트

	//커서
	cursor* _cursor;
	RECT _cursorSlot;						//템선택하는렉트(커서)
	int _cursorNum;							//몇번슬롯이 선택되었는지
	image* _grab;							//커서가 잡은 아이템의 배경
	bool _test;

	bool _showWindow;						//트루면 창이 띄워짐
	RECT temp;								//렉트충돌용
	char str[128];							//텍스트아웃 출력용

public:
	sellTable();
	~sellTable();

	HRESULT init();
	void release();
	void update();
	void render();

	void cursorControl();									//커서 움직임 제어
	void selectPrice();										//가격을 정할떄
	void removeItem();										//창고에 아이템 지우기
	void grab();											//커서가 아이템을 잡았을떄

	RECT getTableRc() { return _tableRc; }
	item& getSellItem(int arrNum) { return _vSlot[arrNum].item; }

};

