#pragma once
#include"gameNode.h"

class introScene : public gameNode
{
private:
	image* backGround;
	image* logo;
	image* buttonImg[4];

	RECT buttonRc[4];
	RECT logoRc;

	int index;
	int count;

public:
	introScene();
	~introScene();

	HRESULT init();
	void relaese();
	void update();
	void render();

	void butoonInit();
	void buttonSelect();

};

