#include "stdafx.h"
#include "dungeonScene5.h"

dungeonScene5::dungeonScene5()
{
}

dungeonScene5::~dungeonScene5()
{
}

HRESULT dungeonScene5::init()
{
	_monster = new monsterManager;
	_monster->init4();
	return S_OK;
}

void dungeonScene5::relaese()
{
}

void dungeonScene5::update()
{
	ANIMATIONMANAGER->update();
	_monster->update(dungeonItem);
	PLAYER->update();
	for (int i = 0; i < dungeonItem.size(); i++)
	{
		dungeonItem[i].update();
	}
}

void dungeonScene5::render()
{
	_monster->render();
	if (!dungeonItem.empty()) {
		for (int i = 0; i < dungeonItem.size(); i++)
		{
			dungeonItem[i].getItemInfo().image->render(getMemDC(), dungeonItem[i].getItemInfo().rc.left, dungeonItem[i].getItemInfo().rc.top);
		}
	}

	PLAYER->render(getMemDC());
}
