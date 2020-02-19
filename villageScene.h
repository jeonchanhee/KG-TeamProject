#pragma once
#include"gameNode.h"
#include"tileNode.h"
#include"playerShop.h"
#include"NPCblacksmith.h"
#include"NPCpotionShop.h"
class villageScene : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY];
	tagTile _temp[TILEX * TILEY];
	RECT _dungeon;
	RECT _shop;

	NPCpotionShop* _potionShop;	//포션상점
	NPCblacksmith* _blacksmith;	//대장간

	playerShop* _playerSho;
public:
	villageScene();
	~villageScene();

	HRESULT init();
	void relaese();
	void update();
	void render();

};

