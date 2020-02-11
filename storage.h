#pragma once
#include"gameNode.h"
#include "cursor.h"

#define SLOTNUM 28

class storage : public gameNode
{
private:


	image* _boxImg;			 //상자이미지
	RECT _boxRc;			 //상자가 위치할 곳
	animation* _storageAni;	 //창고 애니메이션
	vector<item> _vStorage;	 //아이템을 담을 벡터

	image* _mainImage;				//상자를열면 나오는 창고인벤토리 이미지
	image* _slotImage[SLOTNUM];		//창고가 열렸을때 아이템슬롯 (총 28칸)
	RECT _slot[SLOTNUM];

	image* _showItem;				//인벤 옆에서 아이템보여주는창
	RECT _showItemRc;

	bool _showWindow;				//플레이어가 j버튼을 누르면 true가 돼서 창고 창을 띄움


	//커서
	RECT _cursorSlot;				//템선택하는렉트(커서)
	int _cursorNum;					//몇번슬롯이 선택되었는지
	image* _grab;					//커서가 잡은 아이템의 배경
	vector<item> _vTemp;			//아이템을 임시로 담을 벡터

	cursor* _cursor;

	RECT temp;	int a, b;
public:

	storage();
	~storage();

	HRESULT init(string storageName, POINT xy);
	void release();
	void update();
	void render();

	void setAni(string name){_storageAni = ANIMATIONMANAGER->findAnimation(name);} 
	void setShow(bool show) { _showWindow = show; } // true가 되면 창고창을띄움
	void setStorageItem();		// 창고 아이템의 위치를 업데이트해줌
	void storageRender();		//창고의 애니메이션 담당
	void cursorControl();

	RECT getRECT() { return _boxRc; }
	RECT getSlot(int arrNum) { return _slot[arrNum]; }
	vector<item> getStorage() {return _vStorage;}
	vector<item>& getStorage1() {return _vStorage;}
	animation* getAni() { return _storageAni; }
	
	void itemArrange();			//아이템을 정리정돈 해주는 담당
	void resetChoiceNum();		//템창껏다켰을때 커서위치 초기화
	void addItem(item item) { _vStorage.push_back(item); }
	void removeItem();

	void grab(); //커서가 아이템을 잡았을떄
};



