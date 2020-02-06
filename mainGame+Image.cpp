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
	
	//몬스터
	IMAGEMANAGER->addFrameImage("golemTurret", "images/monster/golemTurret.bmp", 460, 460, 546 * 2, 212 * 2, 12, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("golemTurretL", "golemTurret", 0, 11, 12, true, true);
	ANIMATIONMANAGER->addAnimation("golemTurretU", "golemTurret", 12, 24, 12, false, true);
	ANIMATIONMANAGER->addAnimation("golemTurretR", "golemTurret", 24, 36, 12, false, true);
	ANIMATIONMANAGER->addAnimation("golemTurretB", "golemTurret", 36, 48, 12, false, true);






	//아이템
	IMAGEMANAGER->addImage("비어있음", "images/item/비어있음.bmp", 36, 36, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("강화수정", "images/item/강화수정.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("천 반다나", "images/item/천 반다나.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("천 흉갑", "images/item/천 흉갑.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("천 부츠", "images/item/천 부츠.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("천", "images/item/천.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("철 부츠", "images/item/철 부츠.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("철 헬멧", "images/item/철 헬멧.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("철 흉갑", "images/item/철 흉갑.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("쇠막대기", "images/item/쇠막대기.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("수정화 된 에너지", "images/item/수정화 된 에너지.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("숫돌", "images/item/숫돌.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("이빨석", "images/item/이빨석.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("덩쿨", "images/item/덩쿨.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("나뭇가지", "images/item/나뭇가지.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("골렘코어", "images/item/골렘코어.bmp", 36, 36, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("작은 포션", "images/item/작은포션.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("중간 포션", "images/item/중간포션.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("큰 포션", "images/item/큰포션.bmp", 36, 36, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("플레임 보우", "images/item/플레임보우.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("캐터펄트 보우", "images/item/캐터펄트보우.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("훈련용 단검", "images/item/훈련용단검.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("흡혈귀의 단검", "images/item/흡혈귀의단검.bmp", 36, 36, true, RGB(255, 0, 255));

	//플레이어상점
	IMAGEMANAGER->addFrameImage("커서", "images/shop/storageCursor2.bmp", 120, 60, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("창고1", "images/shop/storage1.bmp", 198 * 2, 134 * 2, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("창고2", "images/shop/storage2.bmp", 200 * 2, 102 * 2, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("창고내부", "images/shop/storageMain2.bmp", 554, 504, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("템보여주기", "images/shop/showItem.bmp", 60, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("슬롯이미지", "images/shop/slotImage.bmp", 40, 40, true, RGB(255, 0, 255));

}