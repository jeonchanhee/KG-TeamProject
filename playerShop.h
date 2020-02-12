#pragma once
#include"gameNode.h"
#include"storage.h"
#include"sellTable.h"
#include"NPCpotionShop.h"
#include"NPCblacksmith.h"

class playerShop : public gameNode
{
private:
	storage* _storage1;//창고
	storage* _storage2;

	sellTable* _sellStand;//플레이어 상점

	NPCpotionShop* _potionShop;	//포션상점
	NPCblacksmith* _blacksmith;	//대장간

	RECT temp;

public:

	playerShop();
	~playerShop();

	HRESULT init();
	void release();
	void update();
	void render();

};

