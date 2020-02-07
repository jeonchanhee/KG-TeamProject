#include "stdafx.h"
#include "monster.h"

monster::monster()
{
}

monster::~monster()
{
}

HRESULT monster::init()
{
	return S_OK;
}

HRESULT monster::init(
	MONSTER_TYPE monType,	//타입
	MONSTER_STATE monState,	//상태
	MONSTER_DIRECTION monDirect,//방향
	int x,
	int y		//초기좌표
)
{

	
	
	
	//몬스터 타입에 따른 벡터값 넣기
	switch (monType)
	{
	case MONSTER_TYPE_GOLEMTURRET://골렘터렛
		_monsterImg = IMAGEMANAGER->findImage("golemTurret");
		//방향값으로 맞는 방향 이미지 찾기
		golemTurretDirectImg(monDirect);//이미지방향
		
		//몬스터 피격범위
		rc = RectMakeCenter(x, y,
			_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
		atk = 10;					//공격력
		maxHp = 100;				//체력
		currentHp = 100;			//현재체력
		speed = 0;					//이동속도
		_x = x;						//초기좌표
		_y = y;
		dropItemNum1 = 0;			//드랍가능한 아이템 번호
		dropItemNum2 = 1;			//드랍가능한 아이템 번호
		dropItemNum3 = 2;			//드랍가능한 아이템 번호
		break;
	case MONSTER_TYPE_GOLEMSOLDIER://골렘솔져
		_monsterImg = IMAGEMANAGER->findImage("golemSoldier");
		//방향값으로 맞는 방향 이미지 찾기
		golemSoldierDirectImg(monDirect);//이미지방향
		//몬스터 피격범위
		rc = RectMakeCenter(x, y,
			_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
		atk = 15;					//공격력
		maxHp = 100;				//체력
		currentHp = 100;				//현재체력
		speed = 5;					//이동속도
		_x = x;						//초기좌표
		_y = y;
		dropItemNum1 = 1;			//드랍가능한 아이템 번호
		dropItemNum2 = 3;			//드랍가능한 아이템 번호
		dropItemNum3 = 2;			//드랍가능한 아이템 번호
		break;
	case MONSTER_TYPE_SLIMEGAUNTLET:
		_monsterImg = IMAGEMANAGER->findImage("slimeGauntlet");
		//방향값으로 맞는 방향 이미지 찾기
		slimeGauntletDirectImg(monDirect);//이미지방향
		//몬스터 피격범위
		rc = RectMakeCenter(x, y,
			_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
		atk = 15;					//공격력
		maxHp = 100;				//체력
		currentHp = 100;				//현재체력
		speed = 0;					//이동속도
		_x = x;						//초기좌표
		_y = y;
		dropItemNum1 = 1;			//드랍가능한 아이템 번호
		dropItemNum2 = 3;			//드랍가능한 아이템 번호
		dropItemNum3 = 2;			//드랍가능한 아이템 번호
		break;
	case MONSTER_TYPE_GOLEMBOSS:
		_monsterImg = IMAGEMANAGER->findImage("golemBoss");
		//방향값으로 맞는 방향 이미지 찾기
		golemBossDirectImg(monDirect);//이미지방향
		//몬스터 피격범위
		rc = RectMakeCenter(x, y,
			_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
		atk = 15;					//공격력
		maxHp = 100;				//체력
		currentHp = 100;				//현재체력
		speed = 0;					//이동속도
		_x = x;						//초기좌표
		_y = y;
		dropItemNum1 = 1;			//드랍가능한 아이템 번호
		dropItemNum2 = 3;			//드랍가능한 아이템 번호
		dropItemNum3 = 2;			//드랍가능한 아이템 번호
		break;
	}
	
	//해당 몬스터의 벡터 값 넣기
	_monType = monType;			//몬스터 종류
	_monState = monState;		//몬스터 상태
	_monDirect = monDirect;		//몬스터 방향
	count = 0;					//카운트
	_hpBar = new monsterProgressBar;
	_hpBar->init("images/monster/progressBarFront.bmp", "images/monster/progressBarBack.bmp", 0, 0, 50, 10);
	_hpBar->setGauge(currentHp, maxHp);
	_hpBar->setX(x - 25);
	_hpBar->setY(y - 70);
	return S_OK;
}

void monster::release()
{
}

void monster::update()
{
	viewProgressBar();
	//animation();
}

void monster::render()
{
	draw();
}
//프레임이미지 그려줌
void monster::draw()
{
	//골렘터렛 렌더
	_monsterImg->aniRender(getMemDC(), rc.left, rc.top, _ani);
	_hpBar->render();
	//몬스터 피격범위
	//RectangleMake(getMemDC(), rc.left, rc.top, _monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
}

void monster::animation()
{
}
//공격
bool monster::attack(MONSTER_TYPE monType)
{
	switch (monType) {
	case MONSTER_TYPE_GOLEMTURRET:
		golemTurretAtk();
		break;
	case MONSTER_TYPE_GOLEMSOLDIER:
		
		break;
	}

	//골렘터렛을 제외한 몬스터는 범위에 플레이어가 있을때 카운트가 올라간다.
	return false;
}

void monster::golemTurretDirectImg(MONSTER_DIRECTION monDirect)
{
	_monsterImg = IMAGEMANAGER->findImage("golemTurret");
	//방향값으로 맞는 방향 이미지 찾기
	switch (monDirect)
	{
	case 0:
		_ani = ANIMATIONMANAGER->findAnimation("golemTurretL");
		ANIMATIONMANAGER->start("golemTurretL");
		break;
	case 1:
		_ani = ANIMATIONMANAGER->findAnimation("golemTurretU");
		ANIMATIONMANAGER->start("golemTurretU");
		break;
	case 2:
		_ani = ANIMATIONMANAGER->findAnimation("golemTurretR");
		ANIMATIONMANAGER->start("golemTurretR");
		break;
	case 3:
		_ani = ANIMATIONMANAGER->findAnimation("golemTurretB");
		ANIMATIONMANAGER->start("golemTurretB");
		break;
	}
}

void monster::golemSoldierDirectImg(MONSTER_DIRECTION monDirect)
{
	_monsterImg = IMAGEMANAGER->findImage("golemSoldier");
	//방향값으로 맞는 방향 이미지 찾기
	switch (monDirect)
	{
	case 0:
		_ani = ANIMATIONMANAGER->findAnimation("golemSoldierL");
		ANIMATIONMANAGER->start("golemSoldierL");
		break;
	case 1:
		_ani = ANIMATIONMANAGER->findAnimation("golemSoldierU");
		ANIMATIONMANAGER->start("golemSoldierU");
		break;
	case 2:
		_ani = ANIMATIONMANAGER->findAnimation("golemSoldierR");
		ANIMATIONMANAGER->start("golemSoldierR");
		break;
	case 3:
		_ani = ANIMATIONMANAGER->findAnimation("golemSoldierB");
		ANIMATIONMANAGER->start("golemSoldierB");
		break;
	}
}

void monster::slimeGauntletDirectImg(MONSTER_DIRECTION monDirect)
{
	_monsterImg = IMAGEMANAGER->findImage("slimeGauntlet");
	//방향값으로 맞는 방향 이미지 찾기
	switch (monDirect)
	{
	case 0:
		_ani = ANIMATIONMANAGER->findAnimation("slimeGauntletL");
		ANIMATIONMANAGER->start("slimeGauntletL");
		break;
	case 1:
		_ani = ANIMATIONMANAGER->findAnimation("slimeGauntletU");
		ANIMATIONMANAGER->start("slimeGauntletU");
		break;
	case 2:
		_ani = ANIMATIONMANAGER->findAnimation("slimeGauntletR");
		ANIMATIONMANAGER->start("slimeGauntletR");
		break;
	case 3:
		_ani = ANIMATIONMANAGER->findAnimation("slimeGauntletB");
		ANIMATIONMANAGER->start("slimeGauntletB");
		break;
	}
}

void monster::golemBossDirectImg(MONSTER_DIRECTION monDirect)
{
	_monsterImg = IMAGEMANAGER->findImage("golemBoss");
	//방향값으로 맞는 방향 이미지 찾기
	switch (monDirect)
	{
	case 0:
		_ani = ANIMATIONMANAGER->findAnimation("golemBossL");
		ANIMATIONMANAGER->start("golemBossL");
		break;
	case 1:
		_ani = ANIMATIONMANAGER->findAnimation("golemBossU");
		ANIMATIONMANAGER->start("golemBossU");
		break;
	case 2:
		_ani = ANIMATIONMANAGER->findAnimation("golemBossR");
		ANIMATIONMANAGER->start("golemBossR");
		break;
	case 3:
		_ani = ANIMATIONMANAGER->findAnimation("golemBossB");
		ANIMATIONMANAGER->start("golemBossB");
		break;
	}
}


//골렘터렛공격
bool monster::golemTurretAtk()
{
	//if (monType == 0) {
		count++;
		//카운트가 30일때 공격
		if (count == 30)
		{
			//_rndFireCount = RND->getFromIntTo(1, 1000);
			count = 0;
			return true;
		}
	//}
	return false;
}

//골렘솔져공격
bool monster::golemSoldierAtk()
{
	//if (monType == 0) {
	count++;
	//카운트가 30일때 공격
	if (count == 30)
	{
		_monState = MONSTER_STATE_ATK;
		
		//_rndFireCount = RND->getFromIntTo(1, 1000);
		count = 0;
		return true;
	}
	//}
	return false;
}

bool monster::slimeGauntletAtk()
{
	//if (monType == 0) {
	count++;
	//카운트가 30일때 공격
	if (count == 30)
	{
		_monState = MONSTER_STATE_ATK;
		//_rndFireCount = RND->getFromIntTo(1, 1000);
		count = 0;
		return true;
	}
	//}
	return false;
}

bool monster::golemBossAtk()
{
	//if (monType == 0) {
	count++;
	//카운트가 30일때 공격
	if (count == 30)
	{
		_monState = MONSTER_STATE_ATK;
		//_rndFireCount = RND->getFromIntTo(1, 1000);
		count = 0;
		return true;
	}
	//}
	return false;
}

//체력 보여주는 함수
void monster::viewProgressBar()
{
	_hpBar->setGauge(currentHp, maxHp);
	_hpBar->update();
}