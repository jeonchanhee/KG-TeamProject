#include "stdafx.h"
#include"mainGame.h"

void mainGame::imagesInit()
{
	//¸ÊÅø
	IMAGEMANAGER->addFrameImage("¸ÊÅø", "images/¸ÊÅø.bmp", 600 * 2, 550 * 2, 12, 11, true, RGB(255, 0, 255));
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

	IMAGEMANAGER->addFrameImage("ÀÎÆ®·Î¹è°æ", "images/ÀÎÆ®·Î¹è°æ.bmp", 16384, WINSIZEY, 16, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("·Î°í", "images/·Î°í.bmp", 172 * 2, 140 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÀÎÆ®·Î½ÃÀÛ", "images/ÀÎÆ®·Î½ÃÀÛ.bmp", 544 / 2, 133 / 2 , true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÀÎÆ®·Î¸ÊÅø", "images/ÀÎÆ®·Î¸ÊÅø.bmp", 544 / 2, 133 / 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÀÎÆ®·Î¿É¼Ç", "images/ÀÎÆ®·Î¿É¼Ç.bmp", 544 / 2, 133 / 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÀÎÆ®·Î³ª°¡±â", "images/ÀÎÆ®·Î³ª°¡±â.bmp", 544 / 2, 133 / 2, true, RGB(255, 0, 255));

	//Ã¼·Â¹Ù
	IMAGEMANAGER->addImage("Ã¼·Â¹Ù¾Õ", "images/monster/progressBarFront.bmp", 0, 0, 50, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ã¼·Â¹ÙµÚ", "images/monster/progressBarBack.bmp", 0, 0, 50, 10, true, RGB(255, 0, 255));
	//¸ó½ºÅÍ
	IMAGEMANAGER->addFrameImage("°ñ·½ÅÍ·¿", "images/monster/golemTurret.bmp", 551 * 2, 204 * 2, 12, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("°ñ·½ÅÍ·¿L", "°ñ·½ÅÍ·¿", 0, 11, 12, false, true);
	ANIMATIONMANAGER->addAnimation("°ñ·½ÅÍ·¿U", "°ñ·½ÅÍ·¿", 12, 24, 12, false, true);
	ANIMATIONMANAGER->addAnimation("°ñ·½ÅÍ·¿R", "°ñ·½ÅÍ·¿", 24, 36, 12, false, true);
	ANIMATIONMANAGER->addAnimation("°ñ·½ÅÍ·¿B", "°ñ·½ÅÍ·¿", 36, 47, 12, false, true);
	IMAGEMANAGER->addFrameImage("°ñ·½¼ÖÀú", "images/monster/golemSoldier.bmp", 1520, 760, 8, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("°ñ·½¼ÖÀúL", "°ñ·½¼ÖÀú", 0, 7, 8, false, true);
	ANIMATIONMANAGER->addAnimation("°ñ·½¼ÖÀúR", "°ñ·½¼ÖÀú", 8, 15, 8, false, true);
	ANIMATIONMANAGER->addAnimation("°ñ·½¼ÖÀúU", "°ñ·½¼ÖÀú", 16, 23, 8, false, true);
	ANIMATIONMANAGER->addAnimation("°ñ·½¼ÖÀúB", "°ñ·½¼ÖÀú", 24, 31, 8, false, true);
	IMAGEMANAGER->addFrameImage("°ñ·½¼ÖÀú°ø°Ý", "images/monster/golemSoldierAtk.bmp", 2460, 760, 13, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("°ñ·½¼ÖÀú°ø°ÝL", "°ñ·½¼ÖÀú°ø°Ý", 0, 12, 26, false, false);
	ANIMATIONMANAGER->addAnimation("°ñ·½¼ÖÀú°ø°ÝR", "°ñ·½¼ÖÀú°ø°Ý", 13, 25, 26, false, false);
	ANIMATIONMANAGER->addAnimation("°ñ·½¼ÖÀú°ø°ÝU", "°ñ·½¼ÖÀú°ø°Ý", 26, 38, 26, false, false);
	ANIMATIONMANAGER->addAnimation("°ñ·½¼ÖÀú°ø°ÝB", "°ñ·½¼ÖÀú°ø°Ý", 39, 51, 26, false, false);
	IMAGEMANAGER->addFrameImage("½½¶óÀÓ", "images/monster/slime.bmp", 1804 * 2, 402 * 2, 18, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("½½¶óÀÓÀÌµ¿", "½½¶óÀÓ", 0, 8, 9, false, true);
	ANIMATIONMANAGER->addAnimation("½½¶óÀÓ°ø°Ý", "½½¶óÀÓ", 19, 34, 5, false, false);
	IMAGEMANAGER->addFrameImage("ÇÃ¶óÀ×°ñ·½", "images/monster/flyingGolem.bmp", 1102 * 2, 143 * 2, 22, 2, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("ÇÃ¶óÀ×°ñ·½ÀÌµ¿", "ÇÃ¶óÀ×°ñ·½", 0, 5, 6, false, true);
	ANIMATIONMANAGER->addAnimation("ÇÃ¶óÀ×°ñ·½°ø°Ý", "ÇÃ¶óÀ×°ñ·½", 22, 43, 11, false, true);
	IMAGEMANAGER->addFrameImage("½½¶óÀÓ°ÇÆ²·¿", "images/monster/slimeGauntletAtk.bmp", 10408 * 2, 1608 * 2, 52, 8, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("½½¶óÀÓ°ÇÆ²·¿°ø°ÝB", "½½¶óÀÓ°ÇÆ²·¿", 0, 51, 13, false, false);
	ANIMATIONMANAGER->addAnimation("½½¶óÀÓ°ÇÆ²·¿°ø°ÝL", "½½¶óÀÓ°ÇÆ²·¿", 52, 103, 13, false, false);
	ANIMATIONMANAGER->addAnimation("½½¶óÀÓ°ÇÆ²·¿°ø°ÝR", "½½¶óÀÓ°ÇÆ²·¿", 104, 155, 13, false, false);
	ANIMATIONMANAGER->addAnimation("½½¶óÀÓ°ÇÆ²·¿°ø°ÝU", "½½¶óÀÓ°ÇÆ²·¿", 156, 207, 13, false, false);
	ANIMATIONMANAGER->addAnimation("½½¶óÀÓ°ÇÆ²·¿B", "½½¶óÀÓ°ÇÆ²·¿", 208, 221, 14, false, true);
	ANIMATIONMANAGER->addAnimation("½½¶óÀÓ°ÇÆ²·¿L", "½½¶óÀÓ°ÇÆ²·¿", 260, 273, 14, false, true);
	ANIMATIONMANAGER->addAnimation("½½¶óÀÓ°ÇÆ²·¿R", "½½¶óÀÓ°ÇÆ²·¿", 312, 325, 14, false, true);
	ANIMATIONMANAGER->addAnimation("½½¶óÀÓ°ÇÆ²·¿U", "½½¶óÀÓ°ÇÆ²·¿", 364, 377, 14, false, true);
	IMAGEMANAGER->addFrameImage("°ñ·½º¸½º", "images/monster/golemBossAtk14.bmp", 4516 * 2, 3512 * 2, 15, 12, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("°ñ·½º¸½ºB", "°ñ·½º¸½º", 60, 67, 8, false, true);
	ANIMATIONMANAGER->addAnimation("°ñ·½º¸½ºL", "°ñ·½º¸½º", 75, 82, 8, false, true);
	ANIMATIONMANAGER->addAnimation("°ñ·½º¸½ºR", "°ñ·½º¸½º", 90, 97, 8, false, true);
	ANIMATIONMANAGER->addAnimation("°ñ·½º¸½ºU", "°ñ·½º¸½º", 105, 112, 8, false, true);
	ANIMATIONMANAGER->addAnimation("°ñ·½º¸½º°ø°Ý1B", "°ñ·½º¸½º", 0, 14, 8, false, false);
	ANIMATIONMANAGER->addAnimation("°ñ·½º¸½º°ø°Ý1L", "°ñ·½º¸½º", 15, 29, 8, false, false);
	ANIMATIONMANAGER->addAnimation("°ñ·½º¸½º°ø°Ý1R", "°ñ·½º¸½º", 30, 44, 8, false, false);
	ANIMATIONMANAGER->addAnimation("°ñ·½º¸½º°ø°Ý1U", "°ñ·½º¸½º", 45, 59, 8, false, false);
	ANIMATIONMANAGER->addAnimation("°ñ·½º¸½º°ø°Ý2B", "°ñ·½º¸½º", 120, 134, 8, false, false);
	ANIMATIONMANAGER->addAnimation("°ñ·½º¸½º°ø°Ý2L", "°ñ·½º¸½º", 135, 149, 8, false, false);
	ANIMATIONMANAGER->addAnimation("°ñ·½º¸½º°ø°Ý2R", "°ñ·½º¸½º", 150, 165, 8, false, false);
	ANIMATIONMANAGER->addAnimation("°ñ·½º¸½º°ø°Ý2U", "°ñ·½º¸½º", 165, 179, 8, false, false);
	IMAGEMANAGER->addFrameImage("ÅÍ·¿¹Ì»çÀÏL", "images/monster/bulletL.bmp", 35, 35, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ÅÍ·¿¹Ì»çÀÏU", "images/monster/bulletU.bmp", 35, 35, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ÅÍ·¿¹Ì»çÀÏR", "images/monster/bulletR.bmp", 35, 35, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ÅÍ·¿¹Ì»çÀÏD", "images/monster/bulletD.bmp", 35, 35, 1, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("¸ó½ºÅÍÁ×À½", "images/monster/fx_boom.bmp", 1150 * 2, 110 * 2, 10, 1, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("¸ó½ºÅÍÁÖ±Ý", "¸ó½ºÅÍÁ×À½", 0, 9, 10, false, false);

	//NPC
	IMAGEMANAGER->addFrameImage("¿©ÀÚ", "images/NPC/girl.bmp", 810, 360, 9, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("¿©ÀÚD", "¿©ÀÚ", 0, 8, 9, false, true);
	ANIMATIONMANAGER->addAnimation("¿©ÀÚU", "¿©ÀÚ", 9, 17, 9, false, true);
	ANIMATIONMANAGER->addAnimation("¿©ÀÚL", "¿©ÀÚ", 18, 26, 9, false, true);
	ANIMATIONMANAGER->addAnimation("¿©ÀÚR", "¿©ÀÚ", 27, 35, 9, false, true);
	int stopImgD[] = { 0 };
	int stopImgU[] = { 9 };
	int stopImgL[] = { 18 };
	int stopImgR[] = { 27 };
	ANIMATIONMANAGER->addAnimation("¿©ÀÚÁ¤ÁöD", "¿©ÀÚ", stopImgD, 1, 1, true);
	ANIMATIONMANAGER->addAnimation("¿©ÀÚÁ¤ÁöU", "¿©ÀÚ", stopImgU, 1, 1, true);
	ANIMATIONMANAGER->addAnimation("¿©ÀÚÁ¤ÁöL", "¿©ÀÚ", stopImgL, 1, 1, true);
	ANIMATIONMANAGER->addAnimation("¿©ÀÚÁ¤ÁöR", "¿©ÀÚ", stopImgR, 1, 1, true);
	IMAGEMANAGER->addFrameImage("³²ÀÚ", "images/NPC/Guy.bmp", 810, 360, 9, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("³²ÀÚD", "³²ÀÚ", 0, 8, 9, false, false);
	ANIMATIONMANAGER->addAnimation("³²ÀÚU", "³²ÀÚ", 9, 17, 9, false, false);
	ANIMATIONMANAGER->addAnimation("³²ÀÚL", "³²ÀÚ", 18, 26, 9, false, false);
	ANIMATIONMANAGER->addAnimation("³²ÀÚR", "³²ÀÚ", 27, 35, 9, false, false);
	ANIMATIONMANAGER->addAnimation("³²ÀÚÁ¤ÁöD", "³²ÀÚ", stopImgD, 1, 1, true);
	ANIMATIONMANAGER->addAnimation("³²ÀÚÁ¤ÁöU", "³²ÀÚ", stopImgU, 1, 1, true);
	ANIMATIONMANAGER->addAnimation("³²ÀÚÁ¤ÁöL", "³²ÀÚ", stopImgL, 1, 1, true);
	ANIMATIONMANAGER->addAnimation("³²ÀÚÁ¤ÁöR", "³²ÀÚ", stopImgR, 1, 1, true);
	IMAGEMANAGER->addFrameImage("¾ÆÀÌ", "images/NPC/Kids.bmp", 600, 400, 6, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("¾ÆÀÌD", "¾ÆÀÌ", 0, 5, 6, false, false);
	ANIMATIONMANAGER->addAnimation("¾ÆÀÌU", "¾ÆÀÌ", 6, 11, 6, false, false);
	ANIMATIONMANAGER->addAnimation("¾ÆÀÌL", "¾ÆÀÌ", 12, 17, 6, false, false);
	ANIMATIONMANAGER->addAnimation("¾ÆÀÌR", "¾ÆÀÌ", 18, 23, 6, false, false);
	IMAGEMANAGER->addFrameImage("Ã»³â", "images/NPC/Lunk.bmp", 810, 360, 9, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("Ã»³âD", "Ã»³â", 0, 8, 9, false, false);
	ANIMATIONMANAGER->addAnimation("Ã»³âU", "Ã»³â", 9, 17, 9, false, false);
	ANIMATIONMANAGER->addAnimation("Ã»³âL", "Ã»³â", 18, 26, 9, false, false);
	ANIMATIONMANAGER->addAnimation("Ã»³âR", "Ã»³â", 27, 35, 9, false, false);
	ANIMATIONMANAGER->addAnimation("Ã»³âÁ¤ÁöD", "Ã»³â", stopImgD, 1, 1, true);
	ANIMATIONMANAGER->addAnimation("Ã»³âÁ¤ÁöU", "Ã»³â", stopImgU, 1, 1, true);
	ANIMATIONMANAGER->addAnimation("Ã»³âÁ¤ÁöL", "Ã»³â", stopImgL, 1, 1, true);
	ANIMATIONMANAGER->addAnimation("Ã»³âÁ¤ÁöR", "Ã»³â", stopImgR, 1, 1, true);
	IMAGEMANAGER->addFrameImage("Ç¥Á¤", "images/NPC/visitorTalk1.bmp", 330 * 2, 210 * 2, 11, 7, true, RGB(255, 0, 255));
	int think[] = { 0,0,0,1,1,1,2,2,2,3,3,3 };
	int cheap[] = { 11,11,11,11,11,11,12,12,12,12,12,12 };
	int veryCheap[] = { 33,34,35,36,37,38,39,40,41,42,43,43 };
	int expensive[] = { 22,22,22,22,23,23,23,23,24,24,24,24 };
	int veryExpensive[] = { 44,45,46,47,48,48,48,49,49,50,50,50 };
	int soso[] = { 55,55,56,56,57,57,57,57,57,57,57,57 };
	int wait[] = { 66,66,67,67,66,66,67,67,66,66,67,67 };
	ANIMATIONMANAGER->addAnimation("°¨Á¤Áß", "Ç¥Á¤", think, 12, 3, false);
	ANIMATIONMANAGER->addAnimation("½Ó", "Ç¥Á¤", cheap, 12, 6, false);
	ANIMATIONMANAGER->addAnimation("ºñ½Ó", "Ç¥Á¤", expensive, 12, 6, false);
	ANIMATIONMANAGER->addAnimation("¸Å¿ì½Ó", "Ç¥Á¤", veryCheap, 12, 6, false);
	ANIMATIONMANAGER->addAnimation("¸Å¿ìºñ½Ó", "Ç¥Á¤", veryExpensive, 12, 6, false);
	ANIMATIONMANAGER->addAnimation("º¸Åë", "Ç¥Á¤", soso, 12, 6, false);
	ANIMATIONMANAGER->addAnimation("±â´Ù¸²", "Ç¥Á¤", wait, 12, 60, true);


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
	IMAGEMANAGER->addImage("ÈÆ·Ã¿ë Ã¢", "images/item/ÈÆ·Ã¿ë Ã¢.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("°ñ·½ µå¸± Ã¢", "images/item/°ñ·½ µå¸± Ã¢.bmp", 36, 36, true, RGB(255, 0, 255));

	//ÇÃ·¹ÀÌ¾î»óÁ¡
	IMAGEMANAGER->addFrameImage("Ä¿¼­", "images/shop/storageCursor2.bmp", 120, 60, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ºòÄ¿¼­", "images/shop/storageCursor2.bmp", 480, 120, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Ã¢°í1", "images/shop/storage1.bmp", 198 * 2, 134 * 2, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Ã¢°í2", "images/shop/storage2.bmp", 200 * 2, 102 * 2, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ã¢°í³»ºÎ", "images/shop/storageMain2.bmp", 554, 504, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÅÛº¸¿©ÁÖ±â", "images/shop/showItem.bmp", 60, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("½½·ÔÀÌ¹ÌÁö", "images/shop/slotImage.bmp", 40, 40, 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÆÇ¸Å½½·ÔÀÌ¹ÌÁö", "images/shop/sellSlot.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¿­±â", "images/shop/¿­±â.bmp", 193 / 2, 87 / 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÆÇ¸ÅÃ¢", "images/shop/sellStand.bmp", 450, 450, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÆÇ¸ÅÅ×ÀÌºí", "images/shop/table items.bmp", 48 * 2, 56 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ä¿¼­±×·¦", "images/shop/grab.bmp", 50, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("À§¾Æ·¡È­»ìÇ¥", "images/shop/updown.bmp", 20, 50, true, RGB(255, 0, 255));

	int arrlen1[] = { 0,1,2 };
	int arrlen2[] = { 3,4,5 };
	ANIMATIONMANAGER->addAnimation("Ã¢°í1¿ÀÇÂ", "Ã¢°í1", arrlen1, 3, 10, false);
	ANIMATIONMANAGER->addAnimation("Ã¢°í1Å¬·ÎÁî", "Ã¢°í1", arrlen2, 3, 10, false);
	int arrlen3[] = { 0,1,2,3 };
	int arrlen4[] = { 4,5,6,7 };
	ANIMATIONMANAGER->addAnimation("Ã¢°í2¿ÀÇÂ", "Ã¢°í2", arrlen3, 4, 10, false);
	ANIMATIONMANAGER->addAnimation("Ã¢°í2Å¬·ÎÁî", "Ã¢°í2", arrlen4, 4, 10, false);

	//NPC»óÁ¡(´ëÀå°£+Æ÷¼Ç»óÁ¡)
	IMAGEMANAGER->addImage("¸ÁÄ¡ÀÌ¹ÌÁö", "images/blacksmith/¸ÁÄ¡ÀÌ¹ÌÁö.bmp", 204, 132, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("¹úÄÁ", "images/blacksmith/¹úÄÁÀÎ°ÔÀÓidle.bmp", 210 * 2, 49 * 2, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("À§Ä¡", "images/blacksmith/À§Ä¡ÀÎ°ÔÀÓidle.bmp", 132 * 2, 44 * 2, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¾ÆÀÌÅÛº¸¿©ÁÖ´ÂÃ¢", "images/blacksmith/imageSlot.bmp", 450, 250, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Å¸ÀÌÆ²", "images/blacksmith/Å¸ÀÌÆ².bmp", 201 * 2, 44, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¾÷±×·¹ÀÌµå·¹½ÃÇÇ", "images/blacksmith/¾÷±×·¹ÀÌµå·¹½ÃÇÇ.bmp", 170 * 2, 317 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¾÷±×·¹ÀÌµå·¹½ÃÇÇ_Æ÷¼Ç", "images/blacksmith/¾÷±×·¹ÀÌµå·¹½ÃÇÇ_Æ÷¼Ç.bmp", 170 * 2, 317 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¾Æ¸Ó½½·Ô", "images/blacksmith/armorSlot.bmp", 57, 57, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("º¸¿ì½½·Ô", "images/blacksmith/bowSlot.bmp", 57, 57, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¼Òµå½½·Ô", "images/blacksmith/swordSlot.bmp", 57, 57, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("½ºÇÇ¾î½½·Ô", "images/blacksmith/spearSlot.bmp", 57, 57, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÀÌ¸§Ä­", "images/blacksmith/ÀÌ¸§Ä­.bmp", 464 / 2, 30, true, RGB(255, 0, 255));

	ANIMATIONMANAGER->addDefAnimation("¹úÄÁ±âº»¸ð¼Ç", "¹úÄÁ", 3, false, false);
	ANIMATIONMANAGER->addDefAnimation("À§Ä¡±âº»¸ð¼Ç", "À§Ä¡", 3, false, false);

	//ÀÎº¥Åä¸®
	IMAGEMANAGER->addImage("¹è°æ", "images/inventory/ÀÎº¥Åä¸®¹è°æÈ­¸é.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÀÎº¥Åä¸®ºÏ", "images/inventory/inventorytwo.bmp", 798, 410, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÀÎº¥Åä¸®Á¾ÀÌ", "images/inventory/inventoryelementbg.bmp", 365, 410, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("µ·ÁÖ¸Ó´Ï", "images/inventory/µ·ÁÖ¸Ó´Ï.bmp", 64 * 1.7, 32 * 1.7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("µ¸º¸±â", "images/inventory/µ¸º¸±â.bmp", 128 * 1.7, 128 * 1.7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¿ä¼Ò", "images/inventory/¿ä¼Òµé.bmp", 45, 45, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Z¹öÆ°", "images/inventory/Z.bmp", 19 * 2, 18 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("zÈ°¼ºÈ­¿À", "images/inventory/z¹öÀüÈ°¼ºÈ­(¿À).bmp", 23, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("zºñÈ°¼ºÈ­¿À", "images/inventory/z¹öÀüºñÈ°¼ºÈ­(¿À).bmp", 23, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("z¹öÀüÈ°¼ºÈ­¿Þ", "images/inventory/z¹öÀüÈ°¼ºÈ­(¿Þ).bmp", 23, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("z¹öÀüºñÈ°¼ºÈ­¿Þ", "images/inventory/z¹öÀüºñÈ°¼ºÈ­(¿Þ).bmp", 23, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÇÁ·ÎÇÊ", "images/inventory/profile.bmp", 134, 170, true, RGB(255, 0, 255));
}