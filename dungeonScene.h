#pragma once
#include"gameNode.h"
#include "storage.h"
#include"sellTable.h"
#include"NPCblacksmith.h"
#include"NPCpotionShop.h"
class dungeonScene : public gameNode
{
private:
	storage* _storage;
	sellTable* _sell;
	NPCblacksmith* _black;
	NPCpotionShop* _potion;

public:
	dungeonScene();
	~dungeonScene();

	HRESULT init();
	void relaese();
	void update();
	void render();
};

