#pragma once
#include"gameNode.h"
<<<<<<< HEAD
=======
#include"mapTool.h"
#include "player.h" //�÷��̾� Ŭ���� 
>>>>>>> 5001e4eff0c23d1813e7a24b65d9e226632545b8
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



};

