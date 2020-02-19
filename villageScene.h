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

	NPCpotionShop* _potionShop;	//���ǻ���
	NPCblacksmith* _blacksmith;	//���尣

	image*   _npcImg_black;                  //������ NPC���
	animation* _npcAni_black;                 //npc�ִ�
	image*   _npcImg_witch;                  //������ NPC���
	animation* _npcAni_witch;                  //npc�ִ�

	playerShop* _playerSho;
public:
	villageScene();
	~villageScene();

	HRESULT init();
	void relaese();
	void update();
	void render();

};

