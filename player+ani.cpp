#include "stdafx.h"
#include "player.h"


void player::allplayerimage()
{
	_player._playerimg = IMAGEMANAGER->addFrameImage("샵캐릭터", "images/player/shop_player_motion.bmp", 2600, 3120, 10, 12, true, RGB(255, 0, 255));	//샵 이미지 
	_player._playerimg = IMAGEMANAGER->addFrameImage("던전캐릭터", "images/player/will_dungeon.bmp", 1200, 1580, 10, 13, true, RGB(255, 0, 255)); //던전캐릭턱
	_player._playerimg = IMAGEMANAGER->addFrameImage("검을 들고 있는 던전캐릭터", "images/player/dungeon_player_sword.bmp", 1320, 480, 11, 4, true, RGB(255, 0, 255)); // 던전 캐릭터 칼용 
	_player._playerimg = IMAGEMANAGER->addFrameImage("화살을 들고 있는 던전캐릭터", "images/player/will_bow.bmp", 1080, 480, 9, 4, true, RGB(255, 0, 255)); //던전캐릭터 활용
}


