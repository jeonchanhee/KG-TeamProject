#pragma once
#include"gameNode.h"
#include"mapTool.h"
#include"introScene.h"
#include"dungeonScene.h"

//#include"player.h"

#define DC gameNode::getMemDC()

class mainGame : public gameNode
{
private:

public:
	mainGame();
	~mainGame();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);

	void imagesInit();
};

