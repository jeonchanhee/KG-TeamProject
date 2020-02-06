#include "stdafx.h"
#include"mainGame.h"

void mainGame::imagesInit()
{
	//맵툴
	IMAGEMANAGER->addFrameImage("맵툴던전", "images/맵툴던전.bmp", 522, 324, 12, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("셈플북", "images/셈플북.bmp", 826, 528, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("옆셈플북", "images/책옆.bmp", 46, 136, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("닫기", "images/닫기버튼.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("뒤로", "images/뒤로가기버튼.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("앞으로", "images/앞으로가기버튼.bmp", 64, 64, true, RGB(255, 0, 255));

}