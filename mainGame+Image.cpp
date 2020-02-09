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
	IMAGEMANAGER->addImage("½½·ÔÀÌ¹ÌÁö", "images/shop/slotImage.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÆÇ¸Å½½·ÔÀÌ¹ÌÁö", "images/shop/sellSlot.bmp", 60, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¿­±â", "images/shop/¿­±â.bmp", 193 / 2, 87 / 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÆÇ¸ÅÃ¢", "images/shop/sellStand.bmp", 500, 500, true, RGB(255, 0, 255));

	//¹úÄÁÀÇ ´ëÀå°£(npc»óÁ¡)
	IMAGEMANAGER->addImage("¸ÁÄ¡ÀÌ¹ÌÁö", "images/blacksmith/¸ÁÄ¡ÀÌ¹ÌÁö.bmp", 204, 132, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¹úÄÁ", "images/blacksmith/¹úÄÁ.bmp", 186, 254, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¾ÆÀÌÅÛº¸¿©ÁÖ´ÂÃ¢", "images/blacksmith/imageSlot.bmp", 450, 250, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Å¸ÀÌÆ²", "images/blacksmith/Å¸ÀÌÆ².bmp", 201, 44, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¾÷±×·¹ÀÌµå·¹½ÃÇÇ", "images/blacksmith/¾÷±×·¹ÀÌµå·¹½ÃÇÇ.bmp", 170, 317, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¾Æ¸Ó½½·Ô", "images/blacksmith/armorSlot.bmp", 57, 57, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("º¸¿ì½½·Ô", "images/blacksmith/bowSlot.bmp", 57, 57, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¼Òµå½½·Ô", "images/blacksmith/swordSlot.bmp", 57, 57, true, RGB(255, 0, 255));

}