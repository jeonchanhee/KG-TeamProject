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
	IMAGEMANAGER->addImage("����", "images/dungeon.bmp", 215, 42, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "images/village.bmp", 215, 42, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���̺�", "images/save.bmp", 215, 42, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ε�", "images/load.bmp", 215, 42, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "images/terrain.bmp", 215, 42, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������Ʈ", "images/object.bmp", 215, 42, true, RGB(255, 0, 255));


	//����
	IMAGEMANAGER->addFrameImage("���ͷ�", "images/monster/golemTurret.bmp", 0, 0, 546 * 2, 212 * 2, 12, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("���ͷ�L", "���ͷ�", 0, 11, 12, true, true);
	IMAGEMANAGER->addFrameImage("���ͷ�", "images/monster/golemTurret.bmp", 0, 0, 551 * 2, 204 * 2, 12, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("���ͷ�L", "���ͷ�", 0, 11, 12, false, true);
	ANIMATIONMANAGER->addAnimation("���ͷ�U", "���ͷ�", 12, 24, 12, false, true);
	ANIMATIONMANAGER->addAnimation("���ͷ�R", "���ͷ�", 24, 36, 12, false, true);
	ANIMATIONMANAGER->addAnimation("���ͷ�B", "���ͷ�", 36, 47, 12, false, true);
	IMAGEMANAGER->addFrameImage("�񷽼���", "images/monster/golemSoldier.bmp", 0, 0, 1520, 760, 8, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("�񷽼���L", "�񷽼���", 0, 7, 8, false, true);
	ANIMATIONMANAGER->addAnimation("�񷽼���R", "�񷽼���", 8, 15, 8, false, true);
	ANIMATIONMANAGER->addAnimation("�񷽼���U", "�񷽼���", 16, 23, 8, false, true);
	ANIMATIONMANAGER->addAnimation("�񷽼���B", "�񷽼���", 24, 31, 8, false, true);
	IMAGEMANAGER->addFrameImage("�񷽼�������", "images/monster/golemSoldierAtk.bmp", 0, 0, 2460, 760, 13, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("�񷽼�������L", "�񷽼�������", 0, 12, 26, false, false);
	ANIMATIONMANAGER->addAnimation("�񷽼�������R", "�񷽼�������", 13, 25, 26, false, false);
	ANIMATIONMANAGER->addAnimation("�񷽼�������U", "�񷽼�������", 26, 38, 26, false, false);
	ANIMATIONMANAGER->addAnimation("�񷽼�������B", "�񷽼�������", 39, 51, 26, false, false);
	IMAGEMANAGER->addFrameImage("�����Ӱ�Ʋ��", "images/monster/slimeGauntlet.bmp", 0, 0, 810 * 2, 356 * 2, 14, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("�����Ӱ�Ʋ��L", "�����Ӱ�Ʋ��", 0, 13, 14, false, true);
	ANIMATIONMANAGER->addAnimation("�����Ӱ�Ʋ��U", "�����Ӱ�Ʋ��", 14, 27, 14, false, true);
	ANIMATIONMANAGER->addAnimation("�����Ӱ�Ʋ��R", "�����Ӱ�Ʋ��", 28, 41, 14, false, true);
	ANIMATIONMANAGER->addAnimation("�����Ӱ�Ʋ��B", "�����Ӱ�Ʋ��", 42, 55, 14, false, true);
	IMAGEMANAGER->addFrameImage("�����Ӱ�Ʋ������", "images/monster/slimeGauntletAtk.bmp", 0, 0, 10420 * 2, 800 * 2, 52, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("�����Ӱ�Ʋ������B", "�����Ӱ�Ʋ������", 0, 51, 52, false, true);
	ANIMATIONMANAGER->addAnimation("�����Ӱ�Ʋ������L", "�����Ӱ�Ʋ������", 52, 103, 52, false, true);
	ANIMATIONMANAGER->addAnimation("�����Ӱ�Ʋ������R", "�����Ӱ�Ʋ������", 104, 155, 52, false, true);
	ANIMATIONMANAGER->addAnimation("�����Ӱ�Ʋ������U", "�����Ӱ�Ʋ������", 156, 207, 52, false, true);
	IMAGEMANAGER->addFrameImage("�񷽺���", "images/monster/golemBoss.bmp", 0, 0, 778 * 2, 518 * 2, 8, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("�񷽺���L", "�񷽺���", 0, 7, 8, false, true);
	ANIMATIONMANAGER->addAnimation("�񷽺���U", "�񷽺���", 8, 15, 8, false, true);
	ANIMATIONMANAGER->addAnimation("�񷽺���R", "�񷽺���", 16, 23, 8, false, true);
	ANIMATIONMANAGER->addAnimation("�񷽺���B", "�񷽺���", 24, 31, 8, false, true);
	IMAGEMANAGER->addFrameImage("�񷽺�������1", "images/monster/golemBossAtk12.bmp", 0, 0, 4502 * 2, 1152 * 2, 15, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("�񷽺�������1B", "�񷽺�������1", 0, 14, 15, false, true);
	ANIMATIONMANAGER->addAnimation("�񷽺�������1L", "�񷽺�������1", 15, 29, 15, false, true);
	ANIMATIONMANAGER->addAnimation("�񷽺�������1R", "�񷽺�������1", 30, 44, 15, false, true);
	ANIMATIONMANAGER->addAnimation("�񷽺�������1U", "�񷽺�������1", 45, 59, 15, false, true);
	IMAGEMANAGER->addFrameImage("�񷽺�������2", "images/monster/golemBossAtk2.bmp", 0, 0, 3004 * 2, 1008 * 2, 15, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("�񷽺�������2B", "�񷽺�������2", 0, 14, 15, false, true);
	ANIMATIONMANAGER->addAnimation("�񷽺�������2L", "�񷽺�������2", 16, 29, 15, false, true);
	ANIMATIONMANAGER->addAnimation("�񷽺�������2R", "�񷽺�������2", 30, 44, 15, false, true);
	ANIMATIONMANAGER->addAnimation("�񷽺�������2U", "�񷽺�������2", 45, 59, 15, false, true);
	IMAGEMANAGER->addFrameImage("�ͷ��̻���L", "images/monster/golemTurretMissileL.bmp", 0, 0, 35 * 4, 35 * 4, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ͷ��̻���R", "images/monster/golemTurretMissileR.bmp", 0, 0, 35 * 4, 35 * 4, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ͷ��̻���U", "images/monster/golemTurretMissileU.bmp", 0, 0, 35 * 4, 35 * 4, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ͷ��̻���B", "images/monster/golemTurretMissileB.bmp", 0, 0, 35 * 4, 35 * 4, 1, 1, true, RGB(255, 0, 255));

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
	IMAGEMANAGER->addImage("�����̹���", "images/shop/slotImage.bmp", 40, 40,40,40,true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ǸŽ����̹���", "images/shop/sellSlot.bmp", 60, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "images/shop/����.bmp", 193 / 2, 87 / 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ǹ�â", "images/shop/sellStand.bmp", 500, 500, true, RGB(255, 0, 255));

	//������ ���尣(npc����)
	IMAGEMANAGER->addImage("��ġ�̹���", "images/blacksmith/��ġ�̹���.bmp", 204, 132, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "images/blacksmith/����.bmp", 186, 254, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����ۺ����ִ�â", "images/blacksmith/imageSlot.bmp", 450, 250, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ÿ��Ʋ", "images/blacksmith/Ÿ��Ʋ.bmp", 201, 44, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���׷��̵巹����", "images/blacksmith/���׷��̵巹����.bmp", 170*2, 317*2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ƹӽ���", "images/blacksmith/armorSlot.bmp", 57, 57, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���콽��", "images/blacksmith/bowSlot.bmp", 57, 57, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ҵ彽��", "images/blacksmith/swordSlot.bmp", 57, 57, true, RGB(255, 0, 255));


	//�κ��丮
	IMAGEMANAGER->addImage("���", "images/inventory/�κ��丮���ȭ��.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�κ��丮��", "images/inventory/inventorytwo.bmp", 798, 410, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���ָӴ�", "images/inventory/���ָӴ�.bmp", 64 * 1.7, 32 * 1.7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "images/inventory/������.bmp", 128 * 1.7, 128 * 1.7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���", "images/inventory/��ҵ�.bmp", 45, 45, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("���", "images/inventory/��ҵ�.bmp", 59, 59, true, RGB(255, 0, 255));



}