#pragma once
#include"gameNode.h"
#include"mapTool.h"
#include"monsterManager.h"
#include"playerShop.h"
#include"inventory.h"

//#include"player.h"

#define DC gameNode::getMemDC()

class mainGame : public gameNode
{
private:
	mapTool* _mapTool;
	monsterManager* _monsterManager;
	playerShop* _playerShop;
	//player* _player;
	inventory* _invenotry;
public:
	mainGame();
	~mainGame();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);

	void imagesInit();
};

