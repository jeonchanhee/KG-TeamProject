#pragma once
#include"gameNode.h"
#include"storage.h"
#include"sellTable.h"
#include"NPCpotionShop.h"
#include"NPCblacksmith.h"

class playerShop : public gameNode
{
private:
	storage* _storage1;//â��
	storage* _storage2;

	sellTable* _sellStand;//�÷��̾� ����

	NPCpotionShop* _potionShop;	//���ǻ���
	NPCblacksmith* _blacksmith;	//���尣

	RECT temp;

public:

	playerShop();
	~playerShop();

	HRESULT init();
	void release();
	void update();
	void render();

};

