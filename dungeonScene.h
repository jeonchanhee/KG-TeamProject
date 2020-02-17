#pragma once
#include"gameNode.h"
#include "storage.h"

class dungeonScene : public gameNode
{
private:
	storage* _storage;
public:
	dungeonScene();
	~dungeonScene();

	HRESULT init();
	void relaese();
	void update();
	void render();
};

