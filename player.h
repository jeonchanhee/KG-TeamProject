#pragma once
#include "gameNode.h"

enum PLAYERVERSION
{
	SHOP_PLAYER_VERSION, //shop�� ���¿��� �ߴ� ������
	DUNGEON_PLAYER_VERSION
};
struct tagplaeyr
{
	PLAYERVERSION _playerversion; // �÷��̾� ������ �̿��� ����� ��
	image* _playerimg; // �÷��̾� �̹���
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
�÷��̾� ���� 


*/