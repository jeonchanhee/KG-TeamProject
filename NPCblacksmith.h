#pragma once
#include "NPCshopBase.h"
class NPCblacksmith : public NPCshopBase
{
private:
	image*   _armorTabImg;					//�� �����ִ���
	RECT	 _armorTab;

	image*   _swordTabImg;					//�� �����ִ���
	RECT	 _swordTab;

	image*   _bowTabImg;					//Ȱ �����ִ���
	RECT	 _bowTab;

	image*   _spearTabImg;					//â �����ִ���
	RECT	 _spearTab;

public:
	NPCblacksmith();
	~NPCblacksmith();

	virtual HRESULT init(POINT npcXY);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void tabControl();
	virtual void cursorControl();
};

