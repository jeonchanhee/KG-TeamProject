#include "stdafx.h"
#include"mainGame.h"

void mainGame::imagesInit()
{
	//����
	IMAGEMANAGER->addFrameImage("��������", "images/��������.bmp", 522, 324, 12, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���ú�", "images/���ú�.bmp", 826, 528, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����ú�", "images/å��.bmp", 46, 136, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ݱ�", "images/�ݱ��ư.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ڷ�", "images/�ڷΰ����ư.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "images/�����ΰ����ư.bmp", 64, 64, true, RGB(255, 0, 255));

}