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
	if (SOUNDMANAGER->getCurrentSong() != "������")
	{
		SOUNDMANAGER->stop(SOUNDMANAGER->getCurrentSong());
		SOUNDMANAGER->setCurrentNum(5);
		SOUNDMANAGER->play("��������", 1);
	}
	return E_NOTIMPL;
}

void dungeonScene5::relaese()
{
}

void dungeonScene5::update()
{
}

void dungeonScene5::render()
{
}
