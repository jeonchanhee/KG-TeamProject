#pragma once
#include"gameNode.h"
#include"tileNode.h"
#include"monsterManager.h"
class dungeonScene5 : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY];
	tagTile _temp[TILEX * TILEY];
	monsterManager* _monster;
	vector<item> dungeonItem;
	RECT door[3];

public:
	dungeonScene5();
	~dungeonScene5();

	HRESULT init();
	void relaese();
	void update();
	void render();
};
