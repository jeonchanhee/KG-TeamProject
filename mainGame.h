#pragma once
#include"gameNode.h"
#include"mapTool.h"
<<<<<<< HEAD
#include "player.h" //플레이어 클래스 
>>>>>>> 5001e4eff0c23d1813e7a24b65d9e226632545b8
=======

>>>>>>> 0e80ddae0a3757d2c371d7e2ebb66f8ee3e82212
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

