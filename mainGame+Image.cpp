#include "stdafx.h"
#include"mainGame.h"

void mainGame::imagesInit()
{
	//����
	IMAGEMANAGER->addFrameImage("����", "images/����.bmp", 600 * 2, 550 * 2, 12, 11, true, RGB(255, 0, 255));
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

	IMAGEMANAGER->addFrameImage("��Ʈ�ι��", "images/��Ʈ�ι��.bmp", 16384, WINSIZEY, 16, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ΰ�", "images/�ΰ�.bmp", 172 * 2, 140 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��Ʈ�ν���", "images/��Ʈ�ν���.bmp", 544 / 2, 133 / 2 , true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��Ʈ�θ���", "images/��Ʈ�θ���.bmp", 544 / 2, 133 / 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��Ʈ�οɼ�", "images/��Ʈ�οɼ�.bmp", 544 / 2, 133 / 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��Ʈ�γ�����", "images/��Ʈ�γ�����.bmp", 544 / 2, 133 / 2, true, RGB(255, 0, 255));

	//ü�¹�
	IMAGEMANAGER->addImage("ü�¹پ�", "images/monster/progressBarFront.bmp", 0, 0, 50, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ü�¹ٵ�", "images/monster/progressBarBack.bmp", 0, 0, 50, 10, true, RGB(255, 0, 255));
	//����
	IMAGEMANAGER->addFrameImage("���ͷ�", "images/monster/golemTurret.bmp", 551 * 2, 204 * 2, 12, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("���ͷ�L", "���ͷ�", 0, 11, 12, false, true);
	ANIMATIONMANAGER->addAnimation("���ͷ�U", "���ͷ�", 12, 24, 12, false, true);
	ANIMATIONMANAGER->addAnimation("���ͷ�R", "���ͷ�", 24, 36, 12, false, true);
	ANIMATIONMANAGER->addAnimation("���ͷ�B", "���ͷ�", 36, 47, 12, false, true);
	IMAGEMANAGER->addFrameImage("�񷽼���", "images/monster/golemSoldier.bmp", 1520, 760, 8, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("�񷽼���L", "�񷽼���", 0, 7, 8, false, true);
	ANIMATIONMANAGER->addAnimation("�񷽼���R", "�񷽼���", 8, 15, 8, false, true);
	ANIMATIONMANAGER->addAnimation("�񷽼���U", "�񷽼���", 16, 23, 8, false, true);
	ANIMATIONMANAGER->addAnimation("�񷽼���B", "�񷽼���", 24, 31, 8, false, true);
	IMAGEMANAGER->addFrameImage("�񷽼�������", "images/monster/golemSoldierAtk.bmp", 2460, 760, 13, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("�񷽼�������L", "�񷽼�������", 0, 12, 26, false, false);
	ANIMATIONMANAGER->addAnimation("�񷽼�������R", "�񷽼�������", 13, 25, 26, false, false);
	ANIMATIONMANAGER->addAnimation("�񷽼�������U", "�񷽼�������", 26, 38, 26, false, false);
	ANIMATIONMANAGER->addAnimation("�񷽼�������B", "�񷽼�������", 39, 51, 26, false, false);
	IMAGEMANAGER->addFrameImage("������", "images/monster/slime.bmp", 1804 * 2, 402 * 2, 18, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("�������̵�", "������", 0, 8, 9, false, true);
	ANIMATIONMANAGER->addAnimation("�����Ӱ���", "������", 19, 34, 5, false, false);
	IMAGEMANAGER->addFrameImage("�ö��װ�", "images/monster/flyingGolem.bmp", 1102 * 2, 143 * 2, 22, 2, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("�ö��װ��̵�", "�ö��װ�", 0, 5, 6, false, true);
	ANIMATIONMANAGER->addAnimation("�ö��װ񷽰���", "�ö��װ�", 22, 43, 11, false, true);
	IMAGEMANAGER->addFrameImage("�����Ӱ�Ʋ��", "images/monster/slimeGauntletAtk.bmp", 10408 * 2, 1608 * 2, 52, 8, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("�����Ӱ�Ʋ������B", "�����Ӱ�Ʋ��", 0, 51, 13, false, false);
	ANIMATIONMANAGER->addAnimation("�����Ӱ�Ʋ������L", "�����Ӱ�Ʋ��", 52, 103, 13, false, false);
	ANIMATIONMANAGER->addAnimation("�����Ӱ�Ʋ������R", "�����Ӱ�Ʋ��", 104, 155, 13, false, false);
	ANIMATIONMANAGER->addAnimation("�����Ӱ�Ʋ������U", "�����Ӱ�Ʋ��", 156, 207, 13, false, false);
	ANIMATIONMANAGER->addAnimation("�����Ӱ�Ʋ��B", "�����Ӱ�Ʋ��", 208, 221, 14, false, true);
	ANIMATIONMANAGER->addAnimation("�����Ӱ�Ʋ��L", "�����Ӱ�Ʋ��", 260, 273, 14, false, true);
	ANIMATIONMANAGER->addAnimation("�����Ӱ�Ʋ��R", "�����Ӱ�Ʋ��", 312, 325, 14, false, true);
	ANIMATIONMANAGER->addAnimation("�����Ӱ�Ʋ��U", "�����Ӱ�Ʋ��", 364, 377, 14, false, true);
	IMAGEMANAGER->addFrameImage("�񷽺���", "images/monster/golemBossAtk14.bmp", 4516 * 2, 3512 * 2, 15, 12, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("�񷽺���B", "�񷽺���", 60, 67, 8, false, true);
	ANIMATIONMANAGER->addAnimation("�񷽺���L", "�񷽺���", 75, 82, 8, false, true);
	ANIMATIONMANAGER->addAnimation("�񷽺���R", "�񷽺���", 90, 97, 8, false, true);
	ANIMATIONMANAGER->addAnimation("�񷽺���U", "�񷽺���", 105, 112, 8, false, true);
	ANIMATIONMANAGER->addAnimation("�񷽺�������1B", "�񷽺���", 0, 14, 8, false, false);
	ANIMATIONMANAGER->addAnimation("�񷽺�������1L", "�񷽺���", 15, 29, 8, false, false);
	ANIMATIONMANAGER->addAnimation("�񷽺�������1R", "�񷽺���", 30, 44, 8, false, false);
	ANIMATIONMANAGER->addAnimation("�񷽺�������1U", "�񷽺���", 45, 59, 8, false, false);
	ANIMATIONMANAGER->addAnimation("�񷽺�������2B", "�񷽺���", 120, 134, 8, false, false);
	ANIMATIONMANAGER->addAnimation("�񷽺�������2L", "�񷽺���", 135, 149, 8, false, false);
	ANIMATIONMANAGER->addAnimation("�񷽺�������2R", "�񷽺���", 150, 165, 8, false, false);
	ANIMATIONMANAGER->addAnimation("�񷽺�������2U", "�񷽺���", 165, 179, 8, false, false);
	IMAGEMANAGER->addFrameImage("�ͷ��̻���L", "images/monster/bulletL.bmp", 35, 35, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ͷ��̻���U", "images/monster/bulletU.bmp", 35, 35, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ͷ��̻���R", "images/monster/bulletR.bmp", 35, 35, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ͷ��̻���D", "images/monster/bulletD.bmp", 35, 35, 1, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("��������", "images/monster/fx_boom.bmp", 1150 * 2, 110 * 2, 10, 1, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("�����ֱ�", "��������", 0, 9, 10, false, false);

	//NPC
	IMAGEMANAGER->addFrameImage("����", "images/NPC/girl.bmp", 810, 360, 9, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("����D", "����", 0, 8, 9, false, true);
	ANIMATIONMANAGER->addAnimation("����U", "����", 9, 17, 9, false, true);
	ANIMATIONMANAGER->addAnimation("����L", "����", 18, 26, 9, false, true);
	ANIMATIONMANAGER->addAnimation("����R", "����", 27, 35, 9, false, true);
	int stopImgD[] = { 0 };
	int stopImgU[] = { 9 };
	int stopImgL[] = { 18 };
	int stopImgR[] = { 27 };
	ANIMATIONMANAGER->addAnimation("��������D", "����", stopImgD, 1, 1, true);
	ANIMATIONMANAGER->addAnimation("��������U", "����", stopImgU, 1, 1, true);
	ANIMATIONMANAGER->addAnimation("��������L", "����", stopImgL, 1, 1, true);
	ANIMATIONMANAGER->addAnimation("��������R", "����", stopImgR, 1, 1, true);
	IMAGEMANAGER->addFrameImage("����", "images/NPC/Guy.bmp", 810, 360, 9, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("����D", "����", 0, 8, 9, false, false);
	ANIMATIONMANAGER->addAnimation("����U", "����", 9, 17, 9, false, false);
	ANIMATIONMANAGER->addAnimation("����L", "����", 18, 26, 9, false, false);
	ANIMATIONMANAGER->addAnimation("����R", "����", 27, 35, 9, false, false);
	ANIMATIONMANAGER->addAnimation("��������D", "����", stopImgD, 1, 1, true);
	ANIMATIONMANAGER->addAnimation("��������U", "����", stopImgU, 1, 1, true);
	ANIMATIONMANAGER->addAnimation("��������L", "����", stopImgL, 1, 1, true);
	ANIMATIONMANAGER->addAnimation("��������R", "����", stopImgR, 1, 1, true);
	IMAGEMANAGER->addFrameImage("����", "images/NPC/Kids.bmp", 600, 400, 6, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("����D", "����", 0, 5, 6, false, false);
	ANIMATIONMANAGER->addAnimation("����U", "����", 6, 11, 6, false, false);
	ANIMATIONMANAGER->addAnimation("����L", "����", 12, 17, 6, false, false);
	ANIMATIONMANAGER->addAnimation("����R", "����", 18, 23, 6, false, false);
	IMAGEMANAGER->addFrameImage("û��", "images/NPC/Lunk.bmp", 810, 360, 9, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("û��D", "û��", 0, 8, 9, false, false);
	ANIMATIONMANAGER->addAnimation("û��U", "û��", 9, 17, 9, false, false);
	ANIMATIONMANAGER->addAnimation("û��L", "û��", 18, 26, 9, false, false);
	ANIMATIONMANAGER->addAnimation("û��R", "û��", 27, 35, 9, false, false);
	ANIMATIONMANAGER->addAnimation("û������D", "û��", stopImgD, 1, 1, true);
	ANIMATIONMANAGER->addAnimation("û������U", "û��", stopImgU, 1, 1, true);
	ANIMATIONMANAGER->addAnimation("û������L", "û��", stopImgL, 1, 1, true);
	ANIMATIONMANAGER->addAnimation("û������R", "û��", stopImgR, 1, 1, true);
	IMAGEMANAGER->addFrameImage("ǥ��", "images/NPC/visitorTalk1.bmp", 330 * 2, 210 * 2, 11, 7, true, RGB(255, 0, 255));
	int think[] = { 0,0,0,1,1,1,2,2,2,3,3,3 };
	int cheap[] = { 11,11,11,11,11,11,12,12,12,12,12,12 };
	int veryCheap[] = { 33,34,35,36,37,38,39,40,41,42,43,43 };
	int expensive[] = { 22,22,22,22,23,23,23,23,24,24,24,24 };
	int veryExpensive[] = { 44,45,46,47,48,48,48,49,49,50,50,50 };
	int soso[] = { 55,55,56,56,57,57,57,57,57,57,57,57 };
	int wait[] = { 66,66,67,67,66,66,67,67,66,66,67,67 };
	ANIMATIONMANAGER->addAnimation("������", "ǥ��", think, 12, 3, false);
	ANIMATIONMANAGER->addAnimation("��", "ǥ��", cheap, 12, 6, false);
	ANIMATIONMANAGER->addAnimation("���", "ǥ��", expensive, 12, 6, false);
	ANIMATIONMANAGER->addAnimation("�ſ��", "ǥ��", veryCheap, 12, 6, false);
	ANIMATIONMANAGER->addAnimation("�ſ���", "ǥ��", veryExpensive, 12, 6, false);
	ANIMATIONMANAGER->addAnimation("����", "ǥ��", soso, 12, 6, false);
	ANIMATIONMANAGER->addAnimation("��ٸ�", "ǥ��", wait, 12, 60, true);


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
	IMAGEMANAGER->addImage("�Ʒÿ� â", "images/item/�Ʒÿ� â.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�� �帱 â", "images/item/�� �帱 â.bmp", 36, 36, true, RGB(255, 0, 255));

	//�÷��̾����
	IMAGEMANAGER->addFrameImage("Ŀ��", "images/shop/storageCursor2.bmp", 120, 60, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ŀ��", "images/shop/storageCursor2.bmp", 480, 120, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("â��1", "images/shop/storage1.bmp", 198 * 2, 134 * 2, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("â��2", "images/shop/storage2.bmp", 200 * 2, 102 * 2, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("â����", "images/shop/storageMain2.bmp", 554, 504, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ۺ����ֱ�", "images/shop/showItem.bmp", 60, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����̹���", "images/shop/slotImage.bmp", 40, 40, 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ǸŽ����̹���", "images/shop/sellSlot.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "images/shop/����.bmp", 193 / 2, 87 / 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ǹ�â", "images/shop/sellStand.bmp", 450, 450, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ǹ����̺�", "images/shop/table items.bmp", 48 * 2, 56 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ŀ���׷�", "images/shop/grab.bmp", 50, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���Ʒ�ȭ��ǥ", "images/shop/updown.bmp", 20, 50, true, RGB(255, 0, 255));

	int arrlen1[] = { 0,1,2 };
	int arrlen2[] = { 3,4,5 };
	ANIMATIONMANAGER->addAnimation("â��1����", "â��1", arrlen1, 3, 10, false);
	ANIMATIONMANAGER->addAnimation("â��1Ŭ����", "â��1", arrlen2, 3, 10, false);
	int arrlen3[] = { 0,1,2,3 };
	int arrlen4[] = { 4,5,6,7 };
	ANIMATIONMANAGER->addAnimation("â��2����", "â��2", arrlen3, 4, 10, false);
	ANIMATIONMANAGER->addAnimation("â��2Ŭ����", "â��2", arrlen4, 4, 10, false);

	//NPC����(���尣+���ǻ���)
	IMAGEMANAGER->addImage("��ġ�̹���", "images/blacksmith/��ġ�̹���.bmp", 204, 132, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����", "images/blacksmith/�����ΰ���idle.bmp", 210 * 2, 49 * 2, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��ġ", "images/blacksmith/��ġ�ΰ���idle.bmp", 132 * 2, 44 * 2, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����ۺ����ִ�â", "images/blacksmith/imageSlot.bmp", 450, 250, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ÿ��Ʋ", "images/blacksmith/Ÿ��Ʋ.bmp", 201 * 2, 44, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���׷��̵巹����", "images/blacksmith/���׷��̵巹����.bmp", 170 * 2, 317 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���׷��̵巹����_����", "images/blacksmith/���׷��̵巹����_����.bmp", 170 * 2, 317 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ƹӽ���", "images/blacksmith/armorSlot.bmp", 57, 57, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���콽��", "images/blacksmith/bowSlot.bmp", 57, 57, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ҵ彽��", "images/blacksmith/swordSlot.bmp", 57, 57, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���Ǿ��", "images/blacksmith/spearSlot.bmp", 57, 57, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�̸�ĭ", "images/blacksmith/�̸�ĭ.bmp", 464 / 2, 30, true, RGB(255, 0, 255));

	ANIMATIONMANAGER->addDefAnimation("�����⺻���", "����", 3, false, false);
	ANIMATIONMANAGER->addDefAnimation("��ġ�⺻���", "��ġ", 3, false, false);

	//�κ��丮
	IMAGEMANAGER->addImage("���", "images/inventory/�κ��丮���ȭ��.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�κ��丮��", "images/inventory/inventorytwo.bmp", 798, 410, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�κ��丮����", "images/inventory/inventoryelementbg.bmp", 365, 410, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���ָӴ�", "images/inventory/���ָӴ�.bmp", 64 * 1.7, 32 * 1.7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "images/inventory/������.bmp", 128 * 1.7, 128 * 1.7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���", "images/inventory/��ҵ�.bmp", 45, 45, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Z��ư", "images/inventory/Z.bmp", 19 * 2, 18 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("zȰ��ȭ��", "images/inventory/z����Ȱ��ȭ(��).bmp", 23, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("z��Ȱ��ȭ��", "images/inventory/z������Ȱ��ȭ(��).bmp", 23, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("z����Ȱ��ȭ��", "images/inventory/z����Ȱ��ȭ(��).bmp", 23, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("z������Ȱ��ȭ��", "images/inventory/z������Ȱ��ȭ(��).bmp", 23, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "images/inventory/profile.bmp", 134, 170, true, RGB(255, 0, 255));
}