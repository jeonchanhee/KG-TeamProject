#include "stdafx.h"
#include "player.h"


void player::allplayerimage()
{
	//샵 이미지 
	_player._playerimg = IMAGEMANAGER->addFrameImage("샵캐릭터", "images/shop_player_motion.bmp", 1300 * 2, 1560 * 2, 10, 12, true, RGB(255, 0, 255));
	_player._playerimg = IMAGEMANAGER->addFrameImage("던전캐릭터", "images/will_dungeon.bmp", 1300 * 2, 1560 * 2, 10, 13, true, RGB(255, 0, 255));

}

void player::allplayerani()
{

	//샵 캐릭터 기본 모션
	ANIMATIONMANAGER->addAnimation("shop_right_walking", "샵캐릭터", 0, 7, 10, false, true);
	ANIMATIONMANAGER->addAnimation("shop_right_Idle", "샵캐릭터", 11, 19, 10, false, true);
	ANIMATIONMANAGER->addAnimation("shop_left_walking", "샵캐릭터", 20, 27, 10, false, true);
	ANIMATIONMANAGER->addAnimation("shop_left_Idle", "샵캐릭터", 31, 39, 10, false, true);
	ANIMATIONMANAGER->addAnimation("shop_up_walking", "샵캐릭터", 40, 47, 10, false, true);
	ANIMATIONMANAGER->addAnimation("shop_up_Idle", "샵캐릭터", 51, 59, 10, false, true);
	ANIMATIONMANAGER->addAnimation("shop_back_walking", "샵캐릭터", 60, 67, 10, false, true);
	ANIMATIONMANAGER->addAnimation("shop_back_Idle", "샵캐릭터", 71, 79, 10, false, true);

	//샵 캐릭터 구르기
	ANIMATIONMANAGER->addAnimation("shop_left_roll", "샵캐릭터", 80, 87, 11, false, true);
	ANIMATIONMANAGER->addAnimation("shop_right_roll", "샵캐릭터", 90, 97, 10, false, true);
	ANIMATIONMANAGER->addAnimation("shop_back_roll", "샵캐릭터", 100, 107, 10, false, true);
	ANIMATIONMANAGER->addAnimation("shop_up_roll", "샵캐릭터", 110, 117, 10, false, true);

	//던전 캐릭터 기본 모션
	//"던전캐릭터"
	ANIMATIONMANAGER->addAnimation("dungeon_up_walking", "던전캐릭터", 0, 7, 10, false, true);
	ANIMATIONMANAGER->addAnimation("dungeon_down_walking", "던전캐릭터", 10, 17, 10, false, true);
	ANIMATIONMANAGER->addAnimation("dungeon_right_walking", "던전캐릭터", 20, 27, 10, false, true);
	ANIMATIONMANAGER->addAnimation("dungeon_left_walking", "던전캐릭터", 30, 37, 10, false, true);
	//roll 모션
	ANIMATIONMANAGER->addAnimation("dungeon_righr_roll", "던전캐릭터", 40, 47, 10, false, true);
	ANIMATIONMANAGER->addAnimation("dungeon_left_roll", "던전캐릭터", 50, 57, 10, false, true);
	ANIMATIONMANAGER->addAnimation("dungeon_up_roll", "던전캐릭터", 60, 67, 10, false, true);
	ANIMATIONMANAGER->addAnimation("dungeon_down_roll", "던전캐릭터", 70, 77, 10, false, true);
	//idle 모션
	ANIMATIONMANAGER->addAnimation("dungeon_left_idle", "던전캐릭터", 80, 89, 10, false, true);
	ANIMATIONMANAGER->addAnimation("dungeon_right_idle", "던전캐릭터", 90, 99, 10, false, true);
	ANIMATIONMANAGER->addAnimation("dungeon_up_idle", "던전캐릭터", 100, 109, 10, false, true);
	ANIMATIONMANAGER->addAnimation("dungeon_down_idle", "던전캐릭터", 110, 119, 10, false, true);
	//죽는 모션
	ANIMATIONMANAGER->addAnimation("dungeon_die", "던전캐릭터", 120, 129, 10, false, true);



}

