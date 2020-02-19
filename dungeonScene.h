#pragma once
#include"gameNode.h"
#include"tileNode.h"
#include"monsterManager.h"
class dungeonScene : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY];
	tagTile _temp[TILEX * TILEY];
	monsterManager* _monster;

	RECT door[3];

public:
	dungeonScene();
	~dungeonScene();

	HRESULT init();
	void relaese();
	void update();
	void render();
};

