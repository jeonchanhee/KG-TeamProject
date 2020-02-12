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
	tagplayerinven _moneyicon;		//돈아이콘
	tagplayerinven _removeGlass;		// 아이템을 돈으로 반환하는 이미지
	tagplayerinven  _inventorybg;
	tagplayerinven _invenotryelement[21];				//인벤토리 칸
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

	int _itemcount;					// 'J'를 누른만큼 아이템을 옮기는 것 
	int money;

	bool _openinventorywin;  //인벤토리 창을 열기 위한 것
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

	void moneyitem();						// 아이템을 돈을 바꾸는 함수
	void inventoryItem();					//인벤토리 요소 안에 상태를 알리기 위한 함수
	void cursormove();						//커서 이동 아이템 
	void grabmove();							//J로 아이템 잡기
	void grabitemremove();				//J로 아이템 


		//눌렀을 때 잡기
};

