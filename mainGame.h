#pragma once
#include"gameNode.h"
#include"mapTool.h"
#include"playerShop.h"
//#include"player.h"

#define DC gameNode::getMemDC()

class mainGame : public gameNode
{
private:
	mapTool* _mapTool;
	playerShop* _playerShop;
	//player* _player;
public:
	mainGame();
	~mainGame();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);

	void imagesInit();
};

