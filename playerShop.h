#pragma once
#include"gameNode.h"

enum STORAGE_STATE
{
	STORAGE_OPEN,
	STORAGE_CLOSE
};
enum CURSOR_STATE
{
	CURSOR_IDLE,
	CURSOR_MOVE,
	CURSOR_GRAB
};
struct strorage
{
	image* inGameImage; //상자이미지
	RECT rc;	//상자가 위치할 곳
	animation* storageAni; //창고 애니메이션
	vector<item> vStorstorage; //아이템을 담을 벡터
	STORAGE_STATE storageState; //창고의 상태. 오픈or클로즈
};
struct storageCursor
{
	image* image; //커서의 이미지
	CURSOR_STATE cursorState; //커서상태
	RECT rc; //커서의 위치
	animation* ani; //커서의 애니메이션
	int cursorMove; //커서의 움직임을 담당할 변수. 창고슬롯 배열을돌아다녀서 커서를 움직임.
};

class playerShop : public gameNode
{
private:
	image* _mainImage; //상자를열면 나오는 창고인벤토리
	image* _slotImage[28];
	RECT _slot[28];		//창고가 열렸을때 아이템슬롯
	strorage _storage1;
	strorage _storage2;
	strorage _storage[2];

	image* _showItem;	//인벤 옆에서 아이템보여주는창
	RECT _showItemRc;

	storageCursor _cursor;
	image* _open;//열기 이미지
	RECT _openRc;//열기 렉트
	RECT temp;

public:

	playerShop();
	~playerShop();

	HRESULT init();
	void release();
	void update();
	void render();

	void setStorage(); // 창고 초기화 담당
	void controlStorage();// 창고 담당
	void storageRender(); //창고의 애니메이션 담당


	void controlCursor(); //커서움직임담당
	void cursorRender();//커서 애니메이션담당
};

