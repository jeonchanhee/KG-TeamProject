#include "stdafx.h"
#include"mainGame.h"

void mainGame::imagesInit()
{
	//¸ÊÅø
	IMAGEMANAGER->addFrameImage("¸ÊÅø´øÀü", "images/¸ÊÅø´øÀü.bmp", 522, 324, 12, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¼ÀÇÃºÏ", "images/¼ÀÇÃºÏ.bmp", 826, 528, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¿·¼ÀÇÃºÏ", "images/Ã¥¿·.bmp", 46, 136, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("´Ý±â", "images/´Ý±â¹öÆ°.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("µÚ·Î", "images/µÚ·Î°¡±â¹öÆ°.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¾ÕÀ¸·Î", "images/¾ÕÀ¸·Î°¡±â¹öÆ°.bmp", 64, 64, true, RGB(255, 0, 255));
	
	//¸ó½ºÅÍ
	IMAGEMANAGER->addFrameImage("golemTurret", "images/monster/golemTurret.bmp", 460, 460, 546 * 2, 212 * 2, 12, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("golemTurretL", "golemTurret", 0, 11, 12, true, true);
	ANIMATIONMANAGER->addAnimation("golemTurretU", "golemTurret", 12, 24, 12, false, true);
	ANIMATIONMANAGER->addAnimation("golemTurretR", "golemTurret", 24, 36, 12, false, true);
	ANIMATIONMANAGER->addAnimation("golemTurretB", "golemTurret", 36, 48, 12, false, true);





}