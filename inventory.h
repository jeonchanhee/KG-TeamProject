#pragma once
#include "gameNode.h"
#include "cursor.h"

//아이템 구역
enum ITEMKIND
{
	ITEM_STORGE,												 	//인벤토리(저장용)만 보이는 곳 
	ITEM_EQUOMENT,										 	//인벤토리 장비(무기, 물약)
	ITEM_GARBAGE											 	//쓰레기 통
};
//인벤토리 정보 					
struct  tagplayerinven
{
	ITEMKIND _itemkind;									 	//아이템 종류 
	image*_inventoryimg;
	RECT _inventoryrect;
	item _item;
	float x, y;
	//bool _isleft;													//-->인벤토리(플레이어용) 또는 창고용만 보이는지 나타내는 상태
};

//아이템 이미지 
struct taginvenimg
{
	image* _invenimg;
	RECT _inventoryrc;
	float x, y;

};
//그랩 정보
struct taggrab
{
	image* _grabimg;
	RECT _temp;														//비어있는 인벤토리 요소들을 모아보기
	bool _isopen;													//J를 눌른 상태에서 눌렀을 때 
};
//보여주기용 정보
struct tagshowitem
{
	image* _showitemimg;
	RECT _showitemrc;
};

class inventory :public gameNode
{
private:
	image* _bgimag;												 // 알파랜더 처리할 배경화면
	tagplayerinven _playerinventory;					//플레이어 인벤토리
	tagplayerinven _removeGlass;						// 아이템을 돈으로 반환하는 이미지
	tagplayerinven  _inventorybg;						//인벤토리(플레이용) & 인벤토리(창고용)
	tagplayerinven _inventoryelement;				//인벤토리 칸
	tagplayerinven _zbutton;								// z버튼
	tagplayerinven _playerprofile;						//플레이어프로필
	tagplayerinven _weaponiright;						//오른쪽 비활 성화 z
	tagplayerinven _weaponirighting;				// 오른쪽 활 성화 z
	tagplayerinven _weaponileft;						//왼쪽 비활 성화 z
	tagplayerinven _weaponilefting;					//쪽 비활 성화 z



	taggrab _grab;													// 그랩(임시벡터 이미지)
	tagshowitem   _showitem;								//우측에 떠있는 이미지

	//커서
	cursor* _cursor;												// 인벤토리 마우스
	RECT _cursorrect;
	int _cursorNumber;


	//아이템 담을 벡터 
	vector< tagplayerinven> _vInven;
	vector< tagplayerinven>::iterator _viInven;


	RECT _temp;
	vector<tagplayerinven> _vTemp;					//임시로 닮을 벡터



	bool _openinventorywin;								//인벤토리 창을 열기 위한 것
	bool test;															//아이템 창고 이용하기 위한 불값
	bool _storageOpen;											//아이템 창고 이용하기 위한 불값
	bool _storageusing;											//아이템 창고 이용하기 위한 불값
	bool _isweapon;												//무기 전환하기 위한 불값.. 이미지로만


public:
	inventory();
	~inventory();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void moverender(HDC hdc);								//저장소에서 보여줄 랜더
	void itemrender(HDC hdc);
	void bkrender(HDC hdc);

	bool getOpen() { return _openinventorywin; }

	void inventoryItem();					//인벤토리 요소 안에 상태를 알리기 위한 함수
	void cursormove();						//커서 이동 아이템 
	void grabmove();							//J로 아이템 잡기
	void grabitemremove();				//J로 아이템 
	void isweaponing();					//z버튼으로 무기 아이템 전환
	void resetelement();											//리셋해주는 함수
	void getitem(string _stritem);						   //아이템 먹기 등, 상점이나 던전에서 사용해주시길 바람 (일단 예비로 만들어 놓은 것...)

	vector<tagplayerinven> getvInven() { return _vInven; }											//현재  가지고 있는 아이템 
	vector<tagplayerinven>::iterator getviterInven() { return _viInven; }
	vector<tagplayerinven> getvTemp() { return _vTemp; }

	int getcusornumber() { return _cursorNumber; }

	bool getstorgeuding() { return _storageusing; }											//인벤토리(창고용)
	void setstorgeuding(bool _using) { _storageusing = _using; }					//인벤토리(창고용) 넘어가기 위한 함수

	bool getStorageOpen() { return _storageOpen; }
	void setStprageOpen(bool storageOpen) { _storageOpen = storageOpen; }

	//한번 시범용으로 
	RECT geteRect() { return _cursorrect; }
	void setRect(RECT _rect) { _cursorrect = _rect; }

	void setOpen(bool open) { _openinventorywin = open; }

	//추가한거
  void swapItem(item swapItem);
	void tempClear() {
		_vTemp.clear();
		test = false;
		_cursorNumber = 0;
	}
};
