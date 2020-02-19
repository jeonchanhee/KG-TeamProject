#pragma once
#include"gameNode.h"
#include "cursor.h"

#define SLOTNUM 28
struct slot
{
	image* img;
	RECT   rc;
	item   item;
	float  x, y;
};

class storage : public gameNode
{
private:

	string _name;
	image* _boxImg;					//상자이미지
	RECT _boxRc;					//상자가 위치할 곳
	animation* _storageAni;			//창고 애니메이션
	image* _mainImage;				//상자를열면 나오는 창고인벤토리 이미지

	slot _slotInfo;
	vector<slot> _vSlot;			//슬롯을 담을 벡터
	vector<slot> _vTemp;			//슬롯을 담을 벡터

	//인벤 옆에 아이템보여주는창
	image* _showItem;
	RECT _showItemRc;

	bool _showWindow;				//플레이어가 j버튼을 누르면 true가 돼서 창고 창을 띄움

	//커서
	cursor* _cursor;
	RECT _cursorSlot;				//템선택하는렉트(커서)
	int _cursorNum;					//몇번슬롯이 선택되었는지
	image* _grab;					//커서가 잡은 아이템의 배경

	RECT temp;
	image* _bgimag;
public:

	storage();
	~storage();

	HRESULT init(string storageName, POINT xy);
	void release();
	void update();
	void render();


	RECT getRECT() { return _boxRc; }

	void setStorageItem();						// 창고 아이템의 위치를 업데이트해줌
	void storageRender();						//창고의 애니메이션 담당
	void cursorControl();						//커서 조정

	void itemArrange();							//아이템을 정리정돈 해주는 담당 ..미완성

	void removeItem();										//창고에 아이템 지우기

	void grab();											//커서가 아이템을 잡았을떄

};