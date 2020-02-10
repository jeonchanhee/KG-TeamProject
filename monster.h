#pragma once
#include"gameNode.h"
#include"monsterProgressBar.h"
//몬스터 종류
enum MONSTER_TYPE
{
	MONSTER_TYPE_GOLEMTURRET,		//골렘터렛
	MONSTER_TYPE_GOLEMSOLDIER,		//골렘솔져
	MONSTER_TYPE_FLYINGGOLEM,		//플라잉골렘
	MONSTER_TYPE_SLIME,				//슬라임
	MONSTER_TYPE_SLIMEGAUNTLET,		//슬라임건틀렛
	MONSTER_TYPE_GOLEMBOSS			//골렘보스
};
//몬스터 상태
enum MONSTER_STATE
{
	MONSTER_STATE_IDLE,		//대기
	MONSTER_STATE_MOVE,		//이동
	MONSTER_STATE_ATK,		//공격
	MONSTER_STATE_HIT,		//피격
	MONSTER_STATE_DEAD		//제거
};
//몬스터 방향
enum MONSTER_DIRECTION
{
	MONSTER_DIRECTION_LEFT,		//왼쪽
	MONSTER_DIRECTION_UP,	//오른쪽
	MONSTER_DIRECTION_RIGHT,		//위
	MONSTER_DIRECTION_DOWN		//아래
};

class monster : public gameNode
{
private:
	MONSTER_TYPE _monType;	//타입
	MONSTER_STATE _monState;	//상태
	MONSTER_DIRECTION _monDirect;//방향
	image * _monsterImg;	//이미지
	animation* _ani;			//애니메이션
	animation* _aniAtk;			//애니메이션
	monsterProgressBar* _hpBar;	//체력바
	RECT rc;				//피격범위
	int atk;				//공격력
	int maxHp;				//체력
	int currentHp;			//현재체력
	int speed;				//이동속도
	int _x, _y;				//초기 좌표
	int currentX, currentY;	//이동 좌표
	int count;				//카운트
	int dropItemNum1;		//드랍가능한 아이템 번호
	int dropItemNum2;		//드랍가능한 아이템 번호
	int dropItemNum3;		//드랍가능한 아이템 번호
	int fireCount;			//발사딜레이		

public:
	monster();
	~monster();

	HRESULT init();
	HRESULT init(
		MONSTER_TYPE monType,		//타입
		MONSTER_STATE monState,		//상태
		MONSTER_DIRECTION monDirect,//방향
		int x,
		int y						//초기 좌표
	);
	void release();
	void update();
	void render();

	//그려주는 
	virtual void draw();
	//애니메이션 함수
	virtual void animation();



	bool attack(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect);	//공격
	bool hit();		//피격
	bool move();	//이동
	bool die();		//사망, 아이템드롭
	//get
	RECT getRect() { return rc; }
	MONSTER_DIRECTION getDirection() { return _monDirect; }
	MONSTER_TYPE getType() { return _monType; }

	//set
	void setMonDirect(MONSTER_DIRECTION MonDirect) { _monDirect = MonDirect; }

	//이미지불러오기
	void golemTurretDirectImg(MONSTER_DIRECTION monDirect);
	void golemSoldierDirectImg(MONSTER_DIRECTION monDirect);
	void slimeGauntletDirectImg(MONSTER_DIRECTION monDirect);
	void golemBossDirectImg(MONSTER_DIRECTION monDirect);

	bool golemTurretAtk();//골렘터렛공격
	bool golemSoldierAtk(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect);//골렘솔져공격
	bool slimeGauntletAtk(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect);//슬라임건틀릿공격
	bool golemBossAtk(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect);//골렘보스공격

	//몬스터 HP바
	void viewProgressBar();

};

