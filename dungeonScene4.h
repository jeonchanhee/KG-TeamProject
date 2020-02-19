#pragma once
#include"gameNode.h"
#include"tileNode.h"
#include"monsterManager.h"
class dungeonScene4 : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY];
	tagTile _temp[TILEX * TILEY];

	monsterManager* _monster;
	RECT door[2];

	RECT healSpa;

public:
	dungeonScene4();
	~dungeonScene4();

	HRESULT init();
	void relaese();
	void update();
	void render();
};

