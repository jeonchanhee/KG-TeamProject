#pragma once
#include"gameNode.h"
#include"storage.h"
#include"sellTable.h"
#include"buyNPC.h"
class playerShop : public gameNode
{
private:
	storage* _storage1;//창고
	storage* _storage2;

	sellTable* _sellStand;//플레이어 상점

	RECT temp;

	RECT villageRc;

	buyNPC* _girlNPC;

public:

	playerShop();
	~playerShop();

	HRESULT init();
	void release();
	void update();
	void render();

};

