#pragma once
#include "gameNode.h"
#include "cursor.h"


struct  tagplayerinven
{
	image*_inventoryimg;
	RECT _inventoryrect;
	float x, y;
	bool _isleft;
};

struct taggrab
{
	image* _grabimg;
	RECT _temp;			//비어있는 인벤토리 요소들을 모아보기
	bool _isopen;		//J를 눌른 상태에서 눌렀을 때 
};

struct tagshowitem
{
	image* _showitemimg;
	RECT _showitemrc;
};

class inventory :public gameNode
{
private:
	tagplayerinven _playerinventory; //플레이어 인벤토리
	tagplayerinven _removeGlass;		// 아이템을 돈으로 반환하는 이미지
	tagplayerinven  _inventorybg;
	tagplayerinven _invenotryelement[29];				//인벤토리 칸
	tagplayerinven _zbutton;					// z버튼
	tagplayerinven _playerprofile;		//플레이어프로필
	tagplayerinven _weaponiright;			//오른쪽 비활 성화 z
	tagplayerinven _weaponirighting;	// 오른쪽 활 성화 z
	tagplayerinven _weaponileft;			//왼쪽 비활 성화 z
	tagplayerinven _weaponilefting;		//쪽 비활 성화 z


	//tagplayerinven _sworleft;

	taggrab _grab;			// 그랩

	tagshowitem   _showitem;

	//커서
	cursor* _cursor;		// 인벤토리 마우스
	RECT _cursorrect;
	int _cursorNumber;

	image* _bgimag;	 // 알파랜더 처리할 배경화면

	//아이템 담을 벡터 
	vector<item> _vInven;
	vector<item>::iterator _viInven;

	item _item;			//아이템	

	RECT _temp;
	vector<item> _vTemp;				//임시로 닮을 벡터

	bool _openinventorywin;  //인벤토리 창을 열기 위한 것
	bool test;				//아이템 창고 이용하기 위한 불값
	bool _storageOpen;		//아이템 창고 이용하기 위한 불값
	bool _isweapon;			//무기 전환하기 위한 불값.. 이미지로만


public:
	inventory();
	~inventory();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void moverender(HDC hdc);			//저장소에서 보여줄 랜더
	void itemrender(HDC hdc);
	void bkrender(HDC hdc);

	void setOpen(bool open) { _openinventorywin = open; }

	void inventoryItem();					//인벤토리 요소 안에 상태를 알리기 위한 함수
	void cursormove();						//커서 이동 아이템 
	void grabmove();							//J로 아이템 잡기
	void grabitemremove();				//J로 아이템 
	void isweaponing();					//z버튼으로 무기 아이템 전환


	vector<item> getvInven() { return _vInven; }			//현재  가지고 있는 아이템 
	vector<item>::iterator getviterInven() { return _viInven; }
	vector<item> getvTemp() { return _vTemp; }


	int getcusornumber() { return _cursorNumber; }

	bool getTest() { return test; }
	void setTest(bool t) { test = t; }

	bool getStorageOpen() { return _storageOpen; }
	void setStprageOpen(bool storageOpen) { _storageOpen = storageOpen; }

	//한번 시범용으로 
	RECT geteRect() { return _cursorrect; }
	void setRect(RECT _rect) { _cursorrect = _rect; }


	//추가한거
	void swapItem(item swapItem);
	void tempClear() {

		_vTemp.clear();
		test = false;
		_cursorNumber = 0;

	}
};
