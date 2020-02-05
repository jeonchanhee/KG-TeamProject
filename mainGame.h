#pragma once
#include"gameNode.h"
#include"mapTool.h"
#include "player.h"


class mainGame : public gameNode
{
private:
	mapTool* _mapTool;
	player* _player;

public:
	mainGame();
	~mainGame();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);

	void imagesInit();
};

