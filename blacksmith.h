#pragma once
#include"gameNode.h"
#include"cursor.h"
#define SLOTNUM 9
class blacksmith :public gameNode
{
private:

	//image* 인게임이미지

	image*   _armorTabImg;					//방어구 보여주는탭
	image*   _swordTabImg;					//검 보여주는탭
	image*   _bowTabImg;					//활 보여주는탭
	image*   _showImg;						//각 아이템보여주는 창
	image*   _itemSlotImg[9];				//업그레이드템 보여주는 슬롯
	image*   _titleImg;						//벌컨의 대장간 타이틀
	image*   _npcImg;						//벌컨이미지
	image*   _recipeImg;					//업그레이드재료 및 아이템스탯보여주는창
	image*   _recipeSlotImg[3];				//업그레이드재료 슬롯의 이미지

	RECT	 _armorTab;
	RECT	 _swordTab;
	RECT	 _bowTab;
	int		 _currentTab;						//현재 탭을 가리키는 변수

	RECT	 _itemSlot[9];						//업그레이드템
	RECT	 _recipeSlot[3];					//재료템

	RECT	_npcRc;	//플레이어가 이녀석과 충돌하면 화면이 켜짐
	bool _showWindow;				//true가 되면 대장간 창이 뜸

	//커서
	RECT _choiceSlot;				//템선택하는렉트
	int _choiceNum;					//몇번슬롯이 선택되었는지
	image* _grab;
	cursor* _cursor;

	//아이템벡터
	vector<item> _vShowItem;	//업그레이드 아이템의 목록을 보여주기..
	vector<item> _vShowRecipe;	//업그레이드 아이템의 재료 보여주기
	item _temp;

	RECT temp;
	int a = 0;

	int OKcnt;
public:

	blacksmith();
	~blacksmith();

	HRESULT init();
	void release();
	void update();
	void render();

	void cursorControl();								//커서의 움직임WASD
	void tabControl();									//대장간에서 현재탭을 조절하는 함수. 방어구탭 검탭 활탭
	void setShow(bool show) { _showWindow = show; }		//true가 되면 대장간 창이 뜸

	RECT getRECT() { return _npcRc; }					//플레이어와 충돌할때씀

	void setRecipeItem();
	void buyItem(vector<item> &storage);
};