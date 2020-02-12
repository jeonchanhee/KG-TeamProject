#pragma once
#include "NPCshopBase.h"

class NPCpotionShop : public NPCshopBase
{
private:

public:
	NPCpotionShop();
	~NPCpotionShop();

	virtual HRESULT init(POINT npcXY);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void tabControl();
	virtual void cursorControl();
};

