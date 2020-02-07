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
	
	//����
	IMAGEMANAGER->addFrameImage("golemTurret", "images/monster/golemTurret.bmp", 460, 460, 546 * 2, 212 * 2, 12, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("golemTurretL", "golemTurret", 0, 11, 12, true, true);
	ANIMATIONMANAGER->addAnimation("golemTurretU", "golemTurret", 12, 24, 12, false, true);
	ANIMATIONMANAGER->addAnimation("golemTurretR", "golemTurret", 24, 36, 12, false, true);
	ANIMATIONMANAGER->addAnimation("golemTurretB", "golemTurret", 36, 48, 12, false, true);






	//������
	IMAGEMANAGER->addImage("�������", "images/item/�������.bmp", 36, 36, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("��ȭ����", "images/item/��ȭ����.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("õ �ݴٳ�", "images/item/õ �ݴٳ�.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("õ �䰩", "images/item/õ �䰩.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("õ ����", "images/item/õ ����.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("õ", "images/item/õ.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ö ����", "images/item/ö ����.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ö ���", "images/item/ö ���.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ö �䰩", "images/item/ö �䰩.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�踷���", "images/item/�踷���.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����ȭ �� ������", "images/item/����ȭ �� ������.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "images/item/����.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�̻���", "images/item/�̻���.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "images/item/����.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��������", "images/item/��������.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���ھ�", "images/item/���ھ�.bmp", 36, 36, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("���� ����", "images/item/��������.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�߰� ����", "images/item/�߰�����.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ū ����", "images/item/ū����.bmp", 36, 36, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�÷��� ����", "images/item/�÷��Ӻ���.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ĳ����Ʈ ����", "images/item/ĳ����Ʈ����.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ʒÿ� �ܰ�", "images/item/�Ʒÿ�ܰ�.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�������� �ܰ�", "images/item/�������Ǵܰ�.bmp", 36, 36, true, RGB(255, 0, 255));

	//�÷��̾����
	IMAGEMANAGER->addFrameImage("Ŀ��", "images/shop/storageCursor2.bmp", 120, 60, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("â��1", "images/shop/storage1.bmp", 198 * 2, 134 * 2, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("â��2", "images/shop/storage2.bmp", 200 * 2, 102 * 2, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("â����", "images/shop/storageMain2.bmp", 554, 504, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ۺ����ֱ�", "images/shop/showItem.bmp", 60, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����̹���", "images/shop/slotImage.bmp", 40, 40, true, RGB(255, 0, 255));

}