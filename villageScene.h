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

	image*   _npcImg_black;                  //마을내 NPC모습
	animation* _npcAni_black;                 //npc애니
	image*   _npcImg_witch;                  //마을내 NPC모습
	animation* _npcAni_witch;                  //npc애니

	playerShop* _playerSho;
public:
	villageScene();
	~villageScene();

	HRESULT init();
	void relaese();
	void update();
	void render();

};

