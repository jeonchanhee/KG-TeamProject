#include "stdafx.h"
#include "player.h"


void player::allplayerimage()
{
	_player._playerimg = IMAGEMANAGER->addFrameImage("��ĳ����", "images/player/shop_player_motion.bmp", 2600, 3120, 10, 12, true, RGB(255, 0, 255));	//�� �̹��� 
	_player._playerimg = IMAGEMANAGER->addFrameImage("����ĳ����", "images/player/will_dungeon.bmp", 1200, 1580, 10, 13, true, RGB(255, 0, 255)); //����ĳ����
	_player._playerimg = IMAGEMANAGER->addFrameImage("���� ��� �ִ� ����ĳ����", "images/player/dungeon_player_sword.bmp", 1320, 480, 11, 4, true, RGB(255, 0, 255)); // ���� ĳ���� Į�� 
	_player._playerimg = IMAGEMANAGER->addFrameImage("ȭ���� ��� �ִ� ����ĳ����", "images/player/will_bow.bmp", 1080, 480, 9, 4, true, RGB(255, 0, 255)); //����ĳ���� Ȱ��
}


