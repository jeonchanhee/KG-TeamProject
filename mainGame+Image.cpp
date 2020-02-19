#include "stdafx.h"
#include"mainGame.h"

void mainGame::imagesInit()
{
	//맵툴
	IMAGEMANAGER->addFrameImage("맵툴", "images/맵툴.bmp", 600 * 2, 550 * 2, 12, 11, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("맵툴던전", "images/맵툴던전.bmp", 522, 324, 12, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("셈플북", "images/셈플북.bmp", 826, 528, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("옆셈플북", "images/책옆.bmp", 46, 136, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("닫기", "images/닫기버튼.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("뒤로", "images/뒤로가기버튼.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("앞으로", "images/앞으로가기버튼.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("던전", "images/dungeon.bmp", 215, 42, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("마을", "images/village.bmp", 215, 42, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("세이브", "images/save.bmp", 215, 42, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("로드", "images/load.bmp", 215, 42, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("지형", "images/terrain.bmp", 215, 42, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("오브젝트", "images/object.bmp", 215, 42, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("인트로배경", "images/인트로배경.bmp", 16384, WINSIZEY, 16, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("로고", "images/로고.bmp", 172 * 2, 140 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("인트로시작", "images/인트로시작.bmp", 544 / 2, 133 / 2 , true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("인트로맵툴", "images/인트로맵툴.bmp", 544 / 2, 133 / 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("인트로옵션", "images/인트로옵션.bmp", 544 / 2, 133 / 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("인트로나가기", "images/인트로나가기.bmp", 544 / 2, 133 / 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("던전저장버튼", "images/맵툴로드버튼1.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("마을저장버튼", "images/맵툴로드버튼2.bmp", 100, 100, true, RGB(255, 0, 255));

	//체력바
	IMAGEMANAGER->addImage("체력바앞", "images/monster/progressBarFront.bmp", 0, 0, 50, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("체력바뒤", "images/monster/progressBarBack.bmp", 0, 0, 50, 10, true, RGB(255, 0, 255));
	//몬스터
	IMAGEMANAGER->addFrameImage("골렘터렛", "images/monster/golemTurret.bmp", 551 * 2, 204 * 2, 12, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("골렘터렛L", "골렘터렛", 0, 11, 12, false, true);
	ANIMATIONMANAGER->addAnimation("골렘터렛U", "골렘터렛", 12, 24, 12, false, true);
	ANIMATIONMANAGER->addAnimation("골렘터렛R", "골렘터렛", 24, 36, 12, false, true);
	ANIMATIONMANAGER->addAnimation("골렘터렛B", "골렘터렛", 36, 47, 12, false, true);
	IMAGEMANAGER->addFrameImage("골렘솔저", "images/monster/golemSoldier.bmp", 1520, 760, 8, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("골렘솔저L", "골렘솔저", 0, 7, 8, false, true);
	ANIMATIONMANAGER->addAnimation("골렘솔저R", "골렘솔저", 8, 15, 8, false, true);
	ANIMATIONMANAGER->addAnimation("골렘솔저U", "골렘솔저", 16, 23, 8, false, true);
	ANIMATIONMANAGER->addAnimation("골렘솔저B", "골렘솔저", 24, 31, 8, false, true);
	IMAGEMANAGER->addFrameImage("골렘솔저공격", "images/monster/golemSoldierAtk.bmp", 2460, 760, 13, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("골렘솔저공격L", "골렘솔저공격", 0, 12, 26, false, false);
	ANIMATIONMANAGER->addAnimation("골렘솔저공격R", "골렘솔저공격", 13, 25, 26, false, false);
	ANIMATIONMANAGER->addAnimation("골렘솔저공격U", "골렘솔저공격", 26, 38, 26, false, false);
	ANIMATIONMANAGER->addAnimation("골렘솔저공격B", "골렘솔저공격", 39, 51, 26, false, false);
	IMAGEMANAGER->addFrameImage("슬라임", "images/monster/slime.bmp", 1804 * 2, 402 * 2, 18, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("슬라임이동", "슬라임", 0, 8, 9, false, true);
	ANIMATIONMANAGER->addAnimation("슬라임공격", "슬라임", 19, 34, 10, false, false);
	IMAGEMANAGER->addFrameImage("플라잉골렘", "images/monster/flyingGolem.bmp", 1102 * 2, 143 * 2, 22, 2, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("플라잉골렘이동", "플라잉골렘", 0, 5, 6, false, true);
	ANIMATIONMANAGER->addAnimation("플라잉골렘공격", "플라잉골렘", 22, 43, 11, false, true);
	IMAGEMANAGER->addFrameImage("슬라임건틀렛", "images/monster/slimeGauntletAtk.bmp", 10408 * 2, 1608 * 2, 52, 8, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("슬라임건틀렛공격B", "슬라임건틀렛", 0, 51, 13, false, false);
	ANIMATIONMANAGER->addAnimation("슬라임건틀렛공격L", "슬라임건틀렛", 52, 103, 13, false, false);
	ANIMATIONMANAGER->addAnimation("슬라임건틀렛공격R", "슬라임건틀렛", 104, 155, 13, false, false);
	ANIMATIONMANAGER->addAnimation("슬라임건틀렛공격U", "슬라임건틀렛", 156, 207, 13, false, false);
	ANIMATIONMANAGER->addAnimation("슬라임건틀렛B", "슬라임건틀렛", 208, 221, 14, false, true);
	ANIMATIONMANAGER->addAnimation("슬라임건틀렛L", "슬라임건틀렛", 260, 273, 14, false, true);
	ANIMATIONMANAGER->addAnimation("슬라임건틀렛R", "슬라임건틀렛", 312, 325, 14, false, true);
	ANIMATIONMANAGER->addAnimation("슬라임건틀렛U", "슬라임건틀렛", 364, 377, 14, false, true);
	IMAGEMANAGER->addFrameImage("골렘보스", "images/monster/golemBossAtk14.bmp", 4516 * 2, 3512 * 2, 15, 12, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("골렘보스B", "골렘보스", 60, 67, 8, false, true);
	ANIMATIONMANAGER->addAnimation("골렘보스L", "골렘보스", 75, 82, 8, false, true);
	ANIMATIONMANAGER->addAnimation("골렘보스R", "골렘보스", 90, 97, 8, false, true);
	ANIMATIONMANAGER->addAnimation("골렘보스U", "골렘보스", 105, 112, 8, false, true);
	ANIMATIONMANAGER->addAnimation("골렘보스공격1B", "골렘보스", 0, 14, 12, false, false);
	ANIMATIONMANAGER->addAnimation("골렘보스공격1L", "골렘보스", 15, 29, 12, false, false);
	ANIMATIONMANAGER->addAnimation("골렘보스공격1R", "골렘보스", 30, 44, 12, false, false);
	ANIMATIONMANAGER->addAnimation("골렘보스공격1U", "골렘보스", 45, 59, 12, false, false);
	ANIMATIONMANAGER->addAnimation("골렘보스공격2B", "골렘보스", 120, 134, 12, false, false);
	ANIMATIONMANAGER->addAnimation("골렘보스공격2L", "골렘보스", 135, 149, 12, false, false);
	ANIMATIONMANAGER->addAnimation("골렘보스공격2R", "골렘보스", 150, 165, 12, false, false);
	ANIMATIONMANAGER->addAnimation("골렘보스공격2U", "골렘보스", 165, 179, 12, false, false);
	IMAGEMANAGER->addFrameImage("터렛미사일L", "images/monster/bulletL.bmp", 35, 35, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("터렛미사일U", "images/monster/bulletU.bmp", 35, 35, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("터렛미사일R", "images/monster/bulletR.bmp", 35, 35, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("터렛미사일D", "images/monster/bulletD.bmp", 35, 35, 1, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("몬스터죽음", "images/monster/fx_boom.bmp", 1150 * 2, 110 * 2, 10, 1, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("몬스터주금", "몬스터죽음", 0, 9, 10, false, false);

	//NPC
	IMAGEMANAGER->addFrameImage("여자", "images/NPC/girl.bmp", 810, 360, 9, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("여자D", "여자", 0, 8, 9, false, true);
	ANIMATIONMANAGER->addAnimation("여자U", "여자", 9, 17, 9, false, true);
	ANIMATIONMANAGER->addAnimation("여자L", "여자", 18, 26, 9, false, true);
	ANIMATIONMANAGER->addAnimation("여자R", "여자", 27, 35, 9, false, true);
	int stopImgD[] = { 0 };
	int stopImgU[] = { 9 };
	int stopImgL[] = { 18 };
	int stopImgR[] = { 27 };
	ANIMATIONMANAGER->addAnimation("여자정지D", "여자", stopImgD, 1, 1, true);
	ANIMATIONMANAGER->addAnimation("여자정지U", "여자", stopImgU, 1, 1, true);
	ANIMATIONMANAGER->addAnimation("여자정지L", "여자", stopImgL, 1, 1, true);
	ANIMATIONMANAGER->addAnimation("여자정지R", "여자", stopImgR, 1, 1, true);
	IMAGEMANAGER->addFrameImage("남자", "images/NPC/Guy.bmp", 810, 360, 9, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("남자D", "남자", 0, 8, 9, false, false);
	ANIMATIONMANAGER->addAnimation("남자U", "남자", 9, 17, 9, false, false);
	ANIMATIONMANAGER->addAnimation("남자L", "남자", 18, 26, 9, false, false);
	ANIMATIONMANAGER->addAnimation("남자R", "남자", 27, 35, 9, false, false);
	ANIMATIONMANAGER->addAnimation("남자정지D", "남자", stopImgD, 1, 1, true);
	ANIMATIONMANAGER->addAnimation("남자정지U", "남자", stopImgU, 1, 1, true);
	ANIMATIONMANAGER->addAnimation("남자정지L", "남자", stopImgL, 1, 1, true);
	ANIMATIONMANAGER->addAnimation("남자정지R", "남자", stopImgR, 1, 1, true);
	IMAGEMANAGER->addFrameImage("아이", "images/NPC/Kids.bmp", 600, 400, 6, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("아이D", "아이", 0, 5, 6, false, false);
	ANIMATIONMANAGER->addAnimation("아이U", "아이", 6, 11, 6, false, false);
	ANIMATIONMANAGER->addAnimation("아이L", "아이", 12, 17, 6, false, false);
	ANIMATIONMANAGER->addAnimation("아이R", "아이", 18, 23, 6, false, false);
	IMAGEMANAGER->addFrameImage("청년", "images/NPC/Lunk.bmp", 810, 360, 9, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("청년D", "청년", 0, 8, 9, false, false);
	ANIMATIONMANAGER->addAnimation("청년U", "청년", 9, 17, 9, false, false);
	ANIMATIONMANAGER->addAnimation("청년L", "청년", 18, 26, 9, false, false);
	ANIMATIONMANAGER->addAnimation("청년R", "청년", 27, 35, 9, false, false);
	ANIMATIONMANAGER->addAnimation("청년정지D", "청년", stopImgD, 1, 1, true);
	ANIMATIONMANAGER->addAnimation("청년정지U", "청년", stopImgU, 1, 1, true);
	ANIMATIONMANAGER->addAnimation("청년정지L", "청년", stopImgL, 1, 1, true);
	ANIMATIONMANAGER->addAnimation("청년정지R", "청년", stopImgR, 1, 1, true);
	IMAGEMANAGER->addFrameImage("표정", "images/NPC/visitorTalk1.bmp", 330 * 2, 210 * 2, 11, 7, true, RGB(255, 0, 255));
	int think[] = { 0,0,0,1,1,1,2,2,2,3,3,3 };
	int cheap[] = { 11,11,11,11,11,11,12,12,12,12,12,12 };
	int veryCheap[] = { 33,34,35,36,37,38,39,40,41,42,43,43 };
	int expensive[] = { 22,22,22,22,23,23,23,23,24,24,24,24 };
	int veryExpensive[] = { 44,45,46,47,48,48,48,49,49,50,50,50 };
	int soso[] = { 55,55,56,56,57,57,57,57,57,57,57,57 };
	int wait[] = { 66,66,67,67,66,66,67,67,66,66,67,67 };
	ANIMATIONMANAGER->addAnimation("감정중", "표정", think, 12, 3, false);
	ANIMATIONMANAGER->addAnimation("쌈", "표정", cheap, 12, 6, false);
	ANIMATIONMANAGER->addAnimation("비쌈", "표정", expensive, 12, 6, false);
	ANIMATIONMANAGER->addAnimation("매우쌈", "표정", veryCheap, 12, 6, false);
	ANIMATIONMANAGER->addAnimation("매우비쌈", "표정", veryExpensive, 12, 6, false);
	ANIMATIONMANAGER->addAnimation("보통", "표정", soso, 12, 6, false);
	ANIMATIONMANAGER->addAnimation("기다림", "표정", wait, 12, 60, true);


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
	IMAGEMANAGER->addImage("훈련용 창", "images/item/훈련용 창.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("골렘 드릴 창", "images/item/골렘 드릴 창.bmp", 36, 36, true, RGB(255, 0, 255));

	//플레이어상점
	IMAGEMANAGER->addFrameImage("커서", "images/shop/storageCursor2.bmp", 120, 60, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("빅커서", "images/shop/storageCursor2.bmp", 480, 120, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("창고1", "images/shop/storage1.bmp", 198 * 2, 134 * 2, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("창고2", "images/shop/storage2.bmp", 200 * 2, 102 * 2, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("창고내부", "images/shop/storageMain2.bmp", 554, 504, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("템보여주기", "images/shop/showItem.bmp", 60, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("슬롯이미지", "images/shop/slotImage.bmp", 40, 40, 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("판매슬롯이미지", "images/shop/sellSlot.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("열기", "images/shop/열기.bmp", 193 / 2, 87 / 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("판매창", "images/shop/sellStand.bmp", 450, 450, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("판매테이블", "images/shop/table items.bmp", 48 * 2, 56 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("커서그랩", "images/shop/grab.bmp", 50, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("위아래화살표", "images/shop/updown.bmp", 20, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("플레이어상점이미지", "images/shop/build_Shop.bmp", 528/2, 436/2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("상점씬", "images/shop/shopScene.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("플레이어상점마젠타이미지", "images/shop/shop마젠타.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));

	int arrlen1[] = { 0,1,2 };
	int arrlen2[] = { 3,4,5 };
	ANIMATIONMANAGER->addAnimation("창고1오픈", "창고1", arrlen1, 3, 10, false);
	ANIMATIONMANAGER->addAnimation("창고1클로즈", "창고1", arrlen2, 3, 10, false);
	int arrlen3[] = { 0,1,2,3 };
	int arrlen4[] = { 4,5,6,7 };
	ANIMATIONMANAGER->addAnimation("창고2오픈", "창고2", arrlen3, 4, 10, false);
	ANIMATIONMANAGER->addAnimation("창고2클로즈", "창고2", arrlen4, 4, 10, false);

	//NPC상점(대장간+포션상점)
	IMAGEMANAGER->addImage("망치이미지", "images/blacksmith/망치이미지.bmp", 204, 132, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("벌컨큰이미지", "images/blacksmith/벌컨.bmp", 186 * 2, 254 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("위치큰이미지", "images/blacksmith/위치.bmp", 186 * 2, 254 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("벌컨", "images/blacksmith/벌컨인게임idle.bmp", 210 * 2, 49 * 2, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("위치", "images/blacksmith/위치인게임idle.bmp", 132 * 2, 44 * 2, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("아이템보여주는창", "images/blacksmith/imageSlot.bmp", 450, 250, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("타이틀", "images/blacksmith/타이틀.bmp", 201 * 2, 44, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("업그레이드레시피", "images/blacksmith/업그레이드레시피.bmp", 170 * 2, 317 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("업그레이드레시피_포션", "images/blacksmith/업그레이드레시피_포션.bmp", 170 * 2, 317 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("아머슬롯", "images/blacksmith/armorSlot.bmp", 57, 57, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("보우슬롯", "images/blacksmith/bowSlot.bmp", 57, 57, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("소드슬롯", "images/blacksmith/swordSlot.bmp", 57, 57, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스피어슬롯", "images/blacksmith/spearSlot.bmp", 57, 57, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("이름칸", "images/blacksmith/이름칸.bmp", 464 / 2, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("마을대장간이미지", "images/blacksmith/Village_Blacksmith.bmp", 118*2, 52*2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("마을포션상점이미지", "images/blacksmith/Village_Witch.bmp", 256*2, 256*2, true, RGB(255, 0, 255));

	ANIMATIONMANAGER->addDefAnimation("벌컨기본모션", "벌컨", 3, false, false);
	ANIMATIONMANAGER->addDefAnimation("위치기본모션", "위치", 3, false, false);

	//인벤토리
	IMAGEMANAGER->addImage("배경", "images/inventory/인벤토리배경화면.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("인벤토리북", "images/inventory/inventorytwo.bmp", 798, 410, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("인벤토리종이", "images/inventory/inventoryelementbg.bmp", 365, 410, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("돈주머니", "images/inventory/돈주머니.bmp", 64 * 1.7, 32 * 1.7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("돋보기", "images/inventory/돋보기.bmp", 128 * 1.7, 128 * 1.7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("요소", "images/inventory/요소들.bmp", 45, 45, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Z버튼", "images/inventory/Z.bmp", 19 * 2, 18 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("z활성화오", "images/inventory/z버전활성화(오).bmp", 23, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("z비활성화오", "images/inventory/z버전비활성화(오).bmp", 23, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("z버전활성화왼", "images/inventory/z버전활성화(왼).bmp", 23, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("z버전비활성화왼", "images/inventory/z버전비활성화(왼).bmp", 23, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("프로필", "images/inventory/profile.bmp", 134, 170, true, RGB(255, 0, 255));


	//던전씬
	//IMAGEMANAGER->addImage("던전문", "images/dungeon/dunDoor.bmp", 128, 128, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("움직이는던전문", "images/dungeon/dunDoorAni.bmp", 990*2, 68*2, 9, 1, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addDefAnimation("문애니", "움직이는던전문", 3, false, false);
}