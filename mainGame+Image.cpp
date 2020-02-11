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
	IMAGEMANAGER->addImage("´øÀü", "images/dungeon.bmp", 215, 42, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¸¶À»", "images/village.bmp", 215, 42, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¼¼ÀÌºê", "images/save.bmp", 215, 42, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("·Îµå", "images/load.bmp", 215, 42, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÁöÇü", "images/terrain.bmp", 215, 42, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¿ÀºêÁ§Æ®", "images/object.bmp", 215, 42, true, RGB(255, 0, 255));


	//¸ó½ºÅÍ
	IMAGEMANAGER->addFrameImage("°ñ·½ÅÍ·¿", "images/monster/golemTurret.bmp", 0, 0, 546 * 2, 212 * 2, 12, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("°ñ·½ÅÍ·¿L", "°ñ·½ÅÍ·¿", 0, 11, 12, true, true);
	IMAGEMANAGER->addFrameImage("°ñ·½ÅÍ·¿", "images/monster/golemTurret.bmp", 0, 0, 551 * 2, 204 * 2, 12, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("°ñ·½ÅÍ·¿L", "°ñ·½ÅÍ·¿", 0, 11, 12, false, true);
	ANIMATIONMANAGER->addAnimation("°ñ·½ÅÍ·¿U", "°ñ·½ÅÍ·¿", 12, 24, 12, false, true);
	ANIMATIONMANAGER->addAnimation("°ñ·½ÅÍ·¿R", "°ñ·½ÅÍ·¿", 24, 36, 12, false, true);
	ANIMATIONMANAGER->addAnimation("°ñ·½ÅÍ·¿B", "°ñ·½ÅÍ·¿", 36, 47, 12, false, true);
	IMAGEMANAGER->addFrameImage("°ñ·½¼ÖÀú", "images/monster/golemSoldier.bmp", 0, 0, 1520, 760, 8, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("°ñ·½¼ÖÀúL", "°ñ·½¼ÖÀú", 0, 7, 8, false, true);
	ANIMATIONMANAGER->addAnimation("°ñ·½¼ÖÀúR", "°ñ·½¼ÖÀú", 8, 15, 8, false, true);
	ANIMATIONMANAGER->addAnimation("°ñ·½¼ÖÀúU", "°ñ·½¼ÖÀú", 16, 23, 8, false, true);
	ANIMATIONMANAGER->addAnimation("°ñ·½¼ÖÀúB", "°ñ·½¼ÖÀú", 24, 31, 8, false, true);
	IMAGEMANAGER->addFrameImage("°ñ·½¼ÖÀú°ø°Ý", "images/monster/golemSoldierAtk.bmp", 0, 0, 2460, 760, 13, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("°ñ·½¼ÖÀú°ø°ÝL", "°ñ·½¼ÖÀú°ø°Ý", 0, 12, 26, false, false);
	ANIMATIONMANAGER->addAnimation("°ñ·½¼ÖÀú°ø°ÝR", "°ñ·½¼ÖÀú°ø°Ý", 13, 25, 26, false, false);
	ANIMATIONMANAGER->addAnimation("°ñ·½¼ÖÀú°ø°ÝU", "°ñ·½¼ÖÀú°ø°Ý", 26, 38, 26, false, false);
	ANIMATIONMANAGER->addAnimation("°ñ·½¼ÖÀú°ø°ÝB", "°ñ·½¼ÖÀú°ø°Ý", 39, 51, 26, false, false);
	IMAGEMANAGER->addFrameImage("½½¶óÀÓ°ÇÆ²·¿", "images/monster/slimeGauntlet.bmp", 0, 0, 810 * 2, 356 * 2, 14, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("½½¶óÀÓ°ÇÆ²·¿L", "½½¶óÀÓ°ÇÆ²·¿", 0, 13, 14, false, true);
	ANIMATIONMANAGER->addAnimation("½½¶óÀÓ°ÇÆ²·¿U", "½½¶óÀÓ°ÇÆ²·¿", 14, 27, 14, false, true);
	ANIMATIONMANAGER->addAnimation("½½¶óÀÓ°ÇÆ²·¿R", "½½¶óÀÓ°ÇÆ²·¿", 28, 41, 14, false, true);
	ANIMATIONMANAGER->addAnimation("½½¶óÀÓ°ÇÆ²·¿B", "½½¶óÀÓ°ÇÆ²·¿", 42, 55, 14, false, true);
	IMAGEMANAGER->addFrameImage("½½¶óÀÓ°ÇÆ²·¿°ø°Ý", "images/monster/slimeGauntletAtk.bmp", 0, 0, 10420 * 2, 800 * 2, 52, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("½½¶óÀÓ°ÇÆ²·¿°ø°ÝB", "½½¶óÀÓ°ÇÆ²·¿°ø°Ý", 0, 51, 52, false, true);
	ANIMATIONMANAGER->addAnimation("½½¶óÀÓ°ÇÆ²·¿°ø°ÝL", "½½¶óÀÓ°ÇÆ²·¿°ø°Ý", 52, 103, 52, false, true);
	ANIMATIONMANAGER->addAnimation("½½¶óÀÓ°ÇÆ²·¿°ø°ÝR", "½½¶óÀÓ°ÇÆ²·¿°ø°Ý", 104, 155, 52, false, true);
	ANIMATIONMANAGER->addAnimation("½½¶óÀÓ°ÇÆ²·¿°ø°ÝU", "½½¶óÀÓ°ÇÆ²·¿°ø°Ý", 156, 207, 52, false, true);
	IMAGEMANAGER->addFrameImage("°ñ·½º¸½º", "images/monster/golemBoss.bmp", 0, 0, 778 * 2, 518 * 2, 8, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("°ñ·½º¸½ºL", "°ñ·½º¸½º", 0, 7, 8, false, true);
	ANIMATIONMANAGER->addAnimation("°ñ·½º¸½ºU", "°ñ·½º¸½º", 8, 15, 8, false, true);
	ANIMATIONMANAGER->addAnimation("°ñ·½º¸½ºR", "°ñ·½º¸½º", 16, 23, 8, false, true);
	ANIMATIONMANAGER->addAnimation("°ñ·½º¸½ºB", "°ñ·½º¸½º", 24, 31, 8, false, true);
	IMAGEMANAGER->addFrameImage("°ñ·½º¸½º°ø°Ý1", "images/monster/golemBossAtk12.bmp", 0, 0, 4502 * 2, 1152 * 2, 15, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("°ñ·½º¸½º°ø°Ý1B", "°ñ·½º¸½º°ø°Ý1", 0, 14, 15, false, true);
	ANIMATIONMANAGER->addAnimation("°ñ·½º¸½º°ø°Ý1L", "°ñ·½º¸½º°ø°Ý1", 15, 29, 15, false, true);
	ANIMATIONMANAGER->addAnimation("°ñ·½º¸½º°ø°Ý1R", "°ñ·½º¸½º°ø°Ý1", 30, 44, 15, false, true);
	ANIMATIONMANAGER->addAnimation("°ñ·½º¸½º°ø°Ý1U", "°ñ·½º¸½º°ø°Ý1", 45, 59, 15, false, true);
	IMAGEMANAGER->addFrameImage("°ñ·½º¸½º°ø°Ý2", "images/monster/golemBossAtk2.bmp", 0, 0, 3004 * 2, 1008 * 2, 15, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("°ñ·½º¸½º°ø°Ý2B", "°ñ·½º¸½º°ø°Ý2", 0, 14, 15, false, true);
	ANIMATIONMANAGER->addAnimation("°ñ·½º¸½º°ø°Ý2L", "°ñ·½º¸½º°ø°Ý2", 16, 29, 15, false, true);
	ANIMATIONMANAGER->addAnimation("°ñ·½º¸½º°ø°Ý2R", "°ñ·½º¸½º°ø°Ý2", 30, 44, 15, false, true);
	ANIMATIONMANAGER->addAnimation("°ñ·½º¸½º°ø°Ý2U", "°ñ·½º¸½º°ø°Ý2", 45, 59, 15, false, true);
	IMAGEMANAGER->addFrameImage("ÅÍ·¿¹Ì»çÀÏL", "images/monster/golemTurretMissileL.bmp", 0, 0, 35 * 4, 35 * 4, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ÅÍ·¿¹Ì»çÀÏR", "images/monster/golemTurretMissileR.bmp", 0, 0, 35 * 4, 35 * 4, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ÅÍ·¿¹Ì»çÀÏU", "images/monster/golemTurretMissileU.bmp", 0, 0, 35 * 4, 35 * 4, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ÅÍ·¿¹Ì»çÀÏB", "images/monster/golemTurretMissileB.bmp", 0, 0, 35 * 4, 35 * 4, 1, 1, true, RGB(255, 0, 255));

	//¾ÆÀÌÅÛ
	IMAGEMANAGER->addImage("ºñ¾îÀÖÀ½", "images/item/ºñ¾îÀÖÀ½.bmp", 36, 36, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("°­È­¼öÁ¤", "images/item/°­È­¼öÁ¤.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ãµ ¹Ý´Ù³ª", "images/item/Ãµ ¹Ý´Ù³ª.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ãµ Èä°©", "images/item/Ãµ Èä°©.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ãµ ºÎÃ÷", "images/item/Ãµ ºÎÃ÷.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ãµ", "images/item/Ãµ.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ã¶ ºÎÃ÷", "images/item/Ã¶ ºÎÃ÷.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ã¶ Çï¸ä", "images/item/Ã¶ Çï¸ä.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ã¶ Èä°©", "images/item/Ã¶ Èä°©.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¼è¸·´ë±â", "images/item/¼è¸·´ë±â.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¼öÁ¤È­ µÈ ¿¡³ÊÁö", "images/item/¼öÁ¤È­ µÈ ¿¡³ÊÁö.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¼ýµ¹", "images/item/¼ýµ¹.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÀÌ»¡¼®", "images/item/ÀÌ»¡¼®.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("µ¢Äð", "images/item/µ¢Äð.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("³ª¹µ°¡Áö", "images/item/³ª¹µ°¡Áö.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("°ñ·½ÄÚ¾î", "images/item/°ñ·½ÄÚ¾î.bmp", 36, 36, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("ÀÛÀº Æ÷¼Ç", "images/item/ÀÛÀºÆ÷¼Ç.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Áß°£ Æ÷¼Ç", "images/item/Áß°£Æ÷¼Ç.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Å« Æ÷¼Ç", "images/item/Å«Æ÷¼Ç.bmp", 36, 36, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("ÇÃ·¹ÀÓ º¸¿ì", "images/item/ÇÃ·¹ÀÓº¸¿ì.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ä³ÅÍÆÞÆ® º¸¿ì", "images/item/Ä³ÅÍÆÞÆ®º¸¿ì.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÈÆ·Ã¿ë ´Ü°Ë", "images/item/ÈÆ·Ã¿ë´Ü°Ë.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÈíÇ÷±ÍÀÇ ´Ü°Ë", "images/item/ÈíÇ÷±ÍÀÇ´Ü°Ë.bmp", 36, 36, true, RGB(255, 0, 255));

	//ÇÃ·¹ÀÌ¾î»óÁ¡
	IMAGEMANAGER->addFrameImage("Ä¿¼­", "images/shop/storageCursor2.bmp", 120, 60, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Ã¢°í1", "images/shop/storage1.bmp", 198 * 2, 134 * 2, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Ã¢°í2", "images/shop/storage2.bmp", 200 * 2, 102 * 2, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ã¢°í³»ºÎ", "images/shop/storageMain2.bmp", 554, 504, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÅÛº¸¿©ÁÖ±â", "images/shop/showItem.bmp", 60, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("½½·ÔÀÌ¹ÌÁö", "images/shop/slotImage.bmp", 40, 40,40,40,true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÆÇ¸Å½½·ÔÀÌ¹ÌÁö", "images/shop/sellSlot.bmp", 60, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¿­±â", "images/shop/¿­±â.bmp", 193 / 2, 87 / 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÆÇ¸ÅÃ¢", "images/shop/sellStand.bmp", 500, 500, true, RGB(255, 0, 255));

	//¹úÄÁÀÇ ´ëÀå°£(npc»óÁ¡)
	IMAGEMANAGER->addImage("¸ÁÄ¡ÀÌ¹ÌÁö", "images/blacksmith/¸ÁÄ¡ÀÌ¹ÌÁö.bmp", 204, 132, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¹úÄÁ", "images/blacksmith/¹úÄÁ.bmp", 186, 254, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¾ÆÀÌÅÛº¸¿©ÁÖ´ÂÃ¢", "images/blacksmith/imageSlot.bmp", 450, 250, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Å¸ÀÌÆ²", "images/blacksmith/Å¸ÀÌÆ².bmp", 201, 44, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¾÷±×·¹ÀÌµå·¹½ÃÇÇ", "images/blacksmith/¾÷±×·¹ÀÌµå·¹½ÃÇÇ.bmp", 170*2, 317*2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¾Æ¸Ó½½·Ô", "images/blacksmith/armorSlot.bmp", 57, 57, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("º¸¿ì½½·Ô", "images/blacksmith/bowSlot.bmp", 57, 57, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¼Òµå½½·Ô", "images/blacksmith/swordSlot.bmp", 57, 57, true, RGB(255, 0, 255));


	//ÀÎº¥Åä¸®
	IMAGEMANAGER->addImage("¹è°æ", "images/inventory/ÀÎº¥Åä¸®¹è°æÈ­¸é.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÀÎº¥Åä¸®ºÏ", "images/inventory/inventorytwo.bmp", 798, 410, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("µ·ÁÖ¸Ó´Ï", "images/inventory/µ·ÁÖ¸Ó´Ï.bmp", 64 * 1.7, 32 * 1.7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("µ¸º¸±â", "images/inventory/µ¸º¸±â.bmp", 128 * 1.7, 128 * 1.7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¿ä¼Ò", "images/inventory/¿ä¼Òµé.bmp", 45, 45, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("¿ä¼Ò", "images/inventory/¿ä¼Òµé.bmp", 59, 59, true, RGB(255, 0, 255));



}