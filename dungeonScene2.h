#pragma once
#include"gameNode.h"
#include"tileNode.h"
#include"monsterManager.h"
class dungeonScene2 : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY];
	tagTile _temp[TILEX * TILEY];
	monsterManager* _monster;
	vector<item> dungeonItem;
	RECT door;

public:
	dungeonScene2();
	~dungeonScene2();

	HRESULT init();
	void relaese();
	void update();
	void render();
};
