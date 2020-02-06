#include "stdafx.h"
#include "player.h"


void player::allplayerimage()
{

	_player._playerimg = IMAGEMANAGER->addFrameImage("샵캐릭터", "images/shop_player_motion.bmp", 2600, 3120, 10, 12, true, RGB(255, 0, 255));	//샵 이미지 
	_player._playerimg = IMAGEMANAGER->addFrameImage("던전캐릭터", "images/will_dungeon.bmp", 1200, 1580, 10, 13, true, RGB(255, 0, 255)); //던전캐릭턱

}


