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

	_golemTurret = IMAGEMANAGER->findImage("golemTurret");

	//몬스터 타입 0(골렘터렛)
	switch (monType)
	{
	case 0:
		//이미지방향
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

		//해당 몬스터의 벡터 값 넣기
		_monType = monType;			//몬스터 종류
		_monState = monState;		//몬스터 상태
		_monDirect = monDirect;		//몬스터 방향
		count = 0;					//카운트
		rc = RectMakeCenter(x, y,
			_golemTurret->getFrameWidth(), _golemTurret->getFrameHeight());
		//몬스터 피격범위
		atk = 10;					//공격력
		hp = 50;					//체력
		speed = 5;					//이동속도
		_x = x;						//초기좌표
		_y = y;
		dropItemNum1 = 0;			//드랍가능한 아이템 번호
		dropItemNum2 = 1;			//드랍가능한 아이템 번호
		dropItemNum3 = 2;			//드랍가능한 아이템 번호
		break;

	}
	return S_OK;
}

void monster::release()
{
}

void monster::update()
{

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
	_golemTurret->aniRender(getMemDC(), rc.left, rc.top, _ani);

	//몬스터 피격범위
	//RectangleMake(getMemDC(), rc.left, rc.top, _golemTurret->getFrameWidth(), _golemTurret->getFrameHeight());
}

void monster::animation()
{
}

bool monster::attack()
{

	count++;

	if (count == 30)
	{
		//_rndFireCount = RND->getFromIntTo(1, 1000);
		count = 0;
		return true;
	}


	return false;
}