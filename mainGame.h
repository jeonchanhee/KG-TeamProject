#pragma once
#include"gameNode.h"
#include"mapTool.h"
#include"introScene.h"
#include"dungeonScene.h"
#include"dungeonScene2.h"
#include"dungeonScene3.h"
#include"dungeonScene4.h"
#include"dungeonScene5.h"
#include"villageScene.h"
#include"playerShop.h"

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

