#pragma once
#include "gameNode.h"

enum PLAYERVERSION
{
	SHOP_PLAYER_VERSION, //shop인 상태에서 뜨는 열거형
	DUNGEON_PLAYER_VERSION
};
struct tagplaeyr
{
	PLAYERVERSION _playerversion; // 플레이어 버전을 이용할 사용할 것
	image* _playerimg; // 플레이어 이미지
	animation _playerani;
};
class player : public gameNode
{
private:


public:
	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render();
};

/*
플레이어 공간 


*/