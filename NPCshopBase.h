#pragma once
#include"gameNode.h"
#include"cursor.h"
#define SLOTNUM 8

struct itemSlot
{
	image*		img;		//슬롯 이미지
	RECT		rc;			//판매창의 아이템 슬롯
	item		item;
	float  x, y;
};

class NPCshopBase :public gameNode
{
private:

protected:
	string _name;
	image*   _npcImg;                  //마을내 NPC모습
	animation* _npcAni;                  //npc애니
	image*   _titleImg;                  //창이 뜨면 중앙 상단에 나오는 타이틀

	image*   _showImg;                  //아이템 슬롯을 보여주는 창
	//image*   _recipeImg;               //업그레이드재료 및 아이템스탯 보여주는창

	int      _OKcnt[3];                  //재료템을 갖고있는지 확인하는 용도. OKcnt가 전부 0이되면 구매실행   
	int       _currentTab;               //현재 탭을 가리키는 변수

	RECT   _npcRc;                     //플레이어가 이녀석과 충돌하면 화면이 켜짐
	bool   _showWindow;               //true가 되면 대장간 창이 뜸
	int _index;                        //애니메이션 재생용 변수

	//커서
	RECT _cursorSlot;                  //템선택하는렉트
	int _cursorNum;                     //몇번슬롯이 선택되었는지
	image* _grab;
	cursor* _cursor;

	//아이템벡터
	itemSlot _itemInfo;
	vector<itemSlot> _vItemSlot;
	vector<itemSlot> _vRecipeSlot;
	vector<itemSlot> _vTemp;

	item _temp;                        //커서가 가리키고 있는 아이템.
	int _itemSetSlot;


	RECT temp;                        //렉트충돌용      
	char str[128];                     //텍스트아웃 출력용
public:

	NPCshopBase();
	~NPCshopBase();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void tabControl();
	virtual void cursorControl();               //커서의 움직임WASD

	void setRecipeItem();                     //커서가 가리키는 템의 레시피를 결정하는 함수
	void makeRecipe(string makeItemName, string RecipeItemName1, string RecipeItemName2, string RecipeItemName3,
		int forNum, int itemCnt1, int itemCnt2, int itemCnt3); //레시피를 세팅하는 함수

	void buy();                              //구매가 가능한지 확인하는 함수
	void buyItem();                           //구매가 실행되는 함수
	bool getOpen() { return _showWindow; }

	RECT getNpcRc() { return _npcRc; }
};