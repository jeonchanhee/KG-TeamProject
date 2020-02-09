#pragma once
#include"gameNode.h"
#include"storage.h"
#include"sellStand.h"
#include"blacksmith.h"


class playerShop : public gameNode
{
private:
	bool _showWindow;
	storage* _storage1;
	storage* _storage2;
	sellStand* _sellStand;
	blacksmith* _blacksmith;
	image* _open; //"J버튼 열기" 보여주는 이미지

	RECT temp;

public:

	playerShop();
	~playerShop();

	HRESULT init();
	void release();
	void update();
	void render();


};

