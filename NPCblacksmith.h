#pragma once
#include "NPCshopBase.h"
class NPCblacksmith : public NPCshopBase
{
private:
	image*   _armorTabImg;					//방어구 보여주는탭
	RECT	 _armorTab;

	image*   _swordTabImg;					//검 보여주는탭
	RECT	 _swordTab;

	image*   _bowTabImg;					//활 보여주는탭
	RECT	 _bowTab;

	image*   _spearTabImg;					//창 보여주는탭
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

