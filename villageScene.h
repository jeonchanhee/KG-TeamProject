#pragma once
#include"gameNode.h"


class villageScene : public gameNode
{
private:

public:
	villageScene();
	~villageScene();

	HRESULT init();
	void relaese();
	void update();
	void render();

};

