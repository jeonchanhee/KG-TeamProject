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
	IMAGEMANAGER->addFrameImage("golemTurret", "images/monster/golemTurret.bmp", 0, 0, 546 * 2, 212 * 2, 12, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("golemTurretL", "golemTurret", 0, 11, 12, true, true);
	ANIMATIONMANAGER->addAnimation("golemTurretU", "golemTurret", 12, 24, 12, false, true);
	ANIMATIONMANAGER->addAnimation("golemTurretR", "golemTurret", 24, 36, 12, false, true);
	ANIMATIONMANAGER->addAnimation("golemTurretB", "golemTurret", 36, 47, 12, false, true);
	IMAGEMANAGER->addFrameImage("golemSoldier", "images/monster/golemSoldier.bmp", 0, 0, 1520 * 2, 760 * 2, 8, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("golemSoldierL", "golemSoldier", 0, 7, 8, false, true);
	ANIMATIONMANAGER->addAnimation("golemSoldierR", "golemSoldier", 8, 15, 8, false, true);
	ANIMATIONMANAGER->addAnimation("golemSoldierU", "golemSoldier", 16, 23, 8, false, true);
	ANIMATIONMANAGER->addAnimation("golemSoldierB", "golemSoldier", 24, 31, 8, false, true);
	IMAGEMANAGER->addFrameImage("golemSoldierAtk", "images/monster/golemSoldierAtk.bmp", 0, 0, 2460 * 2, 760 * 2, 13, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("golemSoldierAtkL", "golemSoldierAtk", 0, 12, 13, false, true);
	ANIMATIONMANAGER->addAnimation("golemSoldierAtkR", "golemSoldierAtk", 13, 25, 13, false, true);
	ANIMATIONMANAGER->addAnimation("golemSoldierAtkU", "golemSoldierAtk", 26, 38, 13, false, true);
	ANIMATIONMANAGER->addAnimation("golemSoldierAtkB", "golemSoldierAtk", 39, 52, 13, false, true);
	IMAGEMANAGER->addFrameImage("slimeGauntlet", "images/monster/slimeGauntlet.bmp", 0, 0, 810 * 2, 356 * 2, 14, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("slimeGauntletL", "slimeGauntlet", 0, 13, 14, false, true);
	ANIMATIONMANAGER->addAnimation("slimeGauntletU", "slimeGauntlet", 14, 27, 14, false, true);
	ANIMATIONMANAGER->addAnimation("slimeGauntletR", "slimeGauntlet", 28, 41, 14, false, true);
	ANIMATIONMANAGER->addAnimation("slimeGauntletB", "slimeGauntlet", 42, 55, 14, false, true);
	IMAGEMANAGER->addFrameImage("golemBoss", "images/monster/golemBoss.bmp", 0, 0, 778 * 2, 518 * 2, 8, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("golemBossL", "golemBoss", 0, 7, 8, false, true);
	ANIMATIONMANAGER->addAnimation("golemBossU", "golemBoss", 8, 15, 8, false, true);
	ANIMATIONMANAGER->addAnimation("golemBossR", "golemBoss", 16, 23, 8, false, true);
	ANIMATIONMANAGER->addAnimation("golemBossB", "golemBoss", 24, 31, 8, false, true);






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
	IMAGEMANAGER->addImage("�ǸŽ����̹���", "images/shop/sellSlot.bmp", 60, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "images/shop/����.bmp", 193 / 2, 87 / 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ǹ�â", "images/shop/sellStand.bmp", 500, 500, true, RGB(255, 0, 255));

	//������ ���尣(npc����)
	IMAGEMANAGER->addImage("��ġ�̹���", "images/blacksmith/��ġ�̹���.bmp", 204, 132, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "images/blacksmith/����.bmp", 186, 254, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����ۺ����ִ�â", "images/blacksmith/imageSlot.bmp", 450, 250, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ÿ��Ʋ", "images/blacksmith/Ÿ��Ʋ.bmp", 201, 44, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���׷��̵巹����", "images/blacksmith/���׷��̵巹����.bmp", 170, 317, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ƹӽ���", "images/blacksmith/armorSlot.bmp", 57, 57, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���콽��", "images/blacksmith/bowSlot.bmp", 57, 57, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ҵ彽��", "images/blacksmith/swordSlot.bmp", 57, 57, true, RGB(255, 0, 255));

}