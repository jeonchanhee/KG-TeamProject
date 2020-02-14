#pragma once
#include"gameNode.h"

class dungeonScene : public gameNode
{

public:
	dungeonScene();
	~dungeonScene();


	HRESULT init();
	void relaese();
	void update();
	void render();

	

};

