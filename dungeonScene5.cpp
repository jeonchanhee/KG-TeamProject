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
	if (SOUNDMANAGER->getCurrentSong() != "보스방")
	{
		SOUNDMANAGER->stop(SOUNDMANAGER->getCurrentSong());
		SOUNDMANAGER->setCurrentNum(5);
		SOUNDMANAGER->play("보스방브금", 1);
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
