#pragma once
#include "gameNode.h"

enum PLAYERVERSION
{
	SHOP_PLAYER_VERSION,
	//�÷��̾�
};

struct tagplaeyr
{

};
class player : public gameNode
{
private:
	RECT _plauer;

public:
	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render();
};

/*
�÷��̾� ���� 


*/