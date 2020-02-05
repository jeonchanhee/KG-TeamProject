#include "stdafx.h"
#include "player.h"


void player::allplayerimage()
{
	//�� �̹��� 
	_player._playerimg = IMAGEMANAGER->addFrameImage("��ĳ����", "images/shop_player_motion.bmp", 1300 * 2, 1560 * 2, 10, 12, true, RGB(255, 0, 255));
	_player._playerimg = IMAGEMANAGER->addFrameImage("����ĳ����", "images/will_dungeon.bmp", 1300 * 2, 1560 * 2, 10, 13, true, RGB(255, 0, 255));

}

void player::allplayerani()
{

	//�� ĳ���� �⺻ ���
	ANIMATIONMANAGER->addAnimation("shop_right_walking", "��ĳ����", 0, 7, 10, false, true);
	ANIMATIONMANAGER->addAnimation("shop_right_Idle", "��ĳ����", 11, 19, 10, false, true);
	ANIMATIONMANAGER->addAnimation("shop_left_walking", "��ĳ����", 20, 27, 10, false, true);
	ANIMATIONMANAGER->addAnimation("shop_left_Idle", "��ĳ����", 31, 39, 10, false, true);
	ANIMATIONMANAGER->addAnimation("shop_up_walking", "��ĳ����", 40, 47, 10, false, true);
	ANIMATIONMANAGER->addAnimation("shop_up_Idle", "��ĳ����", 51, 59, 10, false, true);
	ANIMATIONMANAGER->addAnimation("shop_back_walking", "��ĳ����", 60, 67, 10, false, true);
	ANIMATIONMANAGER->addAnimation("shop_back_Idle", "��ĳ����", 71, 79, 10, false, true);

	//�� ĳ���� ������
	ANIMATIONMANAGER->addAnimation("shop_left_roll", "��ĳ����", 80, 87, 11, false, true);
	ANIMATIONMANAGER->addAnimation("shop_right_roll", "��ĳ����", 90, 97, 10, false, true);
	ANIMATIONMANAGER->addAnimation("shop_back_roll", "��ĳ����", 100, 107, 10, false, true);
	ANIMATIONMANAGER->addAnimation("shop_up_roll", "��ĳ����", 110, 117, 10, false, true);

	//���� ĳ���� �⺻ ���
	//"����ĳ����"
	ANIMATIONMANAGER->addAnimation("dungeon_up_walking", "����ĳ����", 0, 7, 10, false, true);
	ANIMATIONMANAGER->addAnimation("dungeon_down_walking", "����ĳ����", 10, 17, 10, false, true);
	ANIMATIONMANAGER->addAnimation("dungeon_right_walking", "����ĳ����", 20, 27, 10, false, true);
	ANIMATIONMANAGER->addAnimation("dungeon_left_walking", "����ĳ����", 30, 37, 10, false, true);
	//roll ���
	ANIMATIONMANAGER->addAnimation("dungeon_righr_roll", "����ĳ����", 40, 47, 10, false, true);
	ANIMATIONMANAGER->addAnimation("dungeon_left_roll", "����ĳ����", 50, 57, 10, false, true);
	ANIMATIONMANAGER->addAnimation("dungeon_up_roll", "����ĳ����", 60, 67, 10, false, true);
	ANIMATIONMANAGER->addAnimation("dungeon_down_roll", "����ĳ����", 70, 77, 10, false, true);
	//idle ���
	ANIMATIONMANAGER->addAnimation("dungeon_left_idle", "����ĳ����", 80, 89, 10, false, true);
	ANIMATIONMANAGER->addAnimation("dungeon_right_idle", "����ĳ����", 90, 99, 10, false, true);
	ANIMATIONMANAGER->addAnimation("dungeon_up_idle", "����ĳ����", 100, 109, 10, false, true);
	ANIMATIONMANAGER->addAnimation("dungeon_down_idle", "����ĳ����", 110, 119, 10, false, true);
	//�״� ���
	ANIMATIONMANAGER->addAnimation("dungeon_die", "����ĳ����", 120, 129, 10, false, true);



}

