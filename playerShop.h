#pragma once
#include"gameNode.h"
#include"storage.h"
#include"sellTable.h"

class playerShop : public gameNode
{
private:
	storage* _storage1;//â��
	storage* _storage2;

	sellTable* _sellStand;//�÷��̾� ����

	RECT temp;

	RECT villageRc;

public:

	playerShop();
	~playerShop();

	HRESULT init();
	void release();
	void update();
	void render();

};

