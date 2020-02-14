#pragma once
#include"singletonBase.h"
#include "bullet.h"				// 무기(공격) 클래스 
#include "progressBar.h"
#include "inventory.h"

/*
	인벤토리
	피격
	스텟

	시간이 남으면 UI룰 하세요
	더 남으면 다이얼로그하세요
	코드를 줄테니 보고 공부하고 해보세요

	메이플스토리 폰트

	플레이어 공간입니다.
*/

enum PLAYERLOCATION  //플레이어 위치 
{
	SHOP_PLAYER_VERSION,			  // shop 플레이어 버전
	DUNGEON_PLAYER_VERSION	  // dungeon 플레이어 버전
};

enum PLAYERMOVING		//플레이어 동작 상태
{
	PLAYER_STOP_IDLE,
	PLAYER_DOWN_IDLE,
	PLAYER_DOWN,
	PAYER_LEFT_DOWN,
	PAYER_RIGHT_DOWN,
	PLAYER_UP_IDLE,
	PLAYER_UP,
	PAYER_LEFT_UP,
	PAYER_RIGHT_UP,
	PLAYER_LEFT_IDLE,
	PLAYER_LEFT,
	PLAYER_RIGHT_IDLE,
	PLAYER_RIGHT,
	PLAYER_RIGHT_ROLL,
	PLAYER_LEFT_ROLL,
	PLAYER_UP_ROLL,
	PAYER_LEFT_UP_ROLL,
	PAYER_RIGHT_UP_ROLL,
	PLAYER_BACK_ROLL,
	PAYER_LEFT_DOWN_ROLL,
	PAYER_RIGHT_DOWN_ROOL,
	PLAYER_DIE
};

enum TAGATTACKPLAYER			//던전 플레이어에게만 사용할 수 있는 것  
{
	PLAYER_SWORD,				//검
	PLAYER_ARROW,				// 화살
	PLAYER_SPEAR
};

enum TAGATTACKMOTION
{
	PLAYER_ATK_STOP,
	PLAYER_ATK_LEFT,							//왼쪽
	PLAYER_ATK_RIGHT,							//오른쪽
	PLAYER_ATK_UP,								//위
	PLAYER_ATK_DOWN						//아래
};

struct tagplayer		//플레이어 구조체
{
	PLAYERLOCATION  _playerLocation;			//플레이어 위치 상태 shop이면 샵 플레이어 던전 또는 마을이면 던전, 마을 상태를 표시함
	PLAYERMOVING  _playermove;					//플레이어 움직이는 이넘 값
	TAGATTACKPLAYER _attackplayer;				//플레이어 무기 
	TAGATTACKMOTION _attacmove;				 //플레이어 공격 동작 

	image* _playerimg;							//플레이어 이미지

	RECT _playerrect;						//플레이어 기본 rect
	RECT _collisionplayer;				//플레이어 충돌 rect 충돌하고 싶은 부분 있으면 이 rect로 이용할 것


	int _playercount;						//플레이어 이미지 카운터
	int _playerindex;						//플레이어 이미지 인덱스 
	int _pmoney;				// 플레이어 돈 
	int attCount;

	float x, y;									//플레이어 x, y

	bool _isattackmove;					//캐릭터의 공격동작을 알려주는 bool값
	bool  _isFire;									//활을 쐈냐?

};

struct taghpbar // 프로그래스바
{
	PlayerHpbar* _hpbar;				// 프로그래스바
	int  _HP;										//현재 HP
	int _maxhp;								//
};


class player : public singletonBase<player>//public gameNode //public singletonBase<player>
{
private:
	tagplayer _player;  //shop player 정보 
	taghpbar _playerhp;				//player의 hp 

	bool _isanimation;	 //애니메이션 상태 구를것인가? 아니면 상하좌우 모션인가?

	float time;					//TIMEMANAGER를 이용하여 조건 값 준것(앞구르기 참고)

	float attacktime;			//TIMEMANAGER를 이용하여 조건 값 준 것(KEYMANAGER->isOnceKeyDown('K')) 참고

	weapons* _arrowfirst;   // 화살 
	inventory* _inventory;

	RECT _swordrect[4];

	bool _ishwing;			// 칼을 휘둘렀냐 안휘둘렀냐?(안휘두름)
public:
	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);


	void playerKeyControl();				// 플레이어 키
	void playerAtt();							//플레이어 공격 
	void playermoveversion();		  //플레이어 이동 모션
	void attackmove();						// 던전 플레이어 공격 함수 
	void allplayerimage();							//플레이어 이미지 모음
	void arrowFIre(WEAPONMOVE weponMove);
	void monsterbattle();			 //몬스터 배틀
	void playerhitDameage(int _damage); //피깍는 함수
	void buyplayermoney(int _money);				//물건을 살때
	void sellplayermoney(int _money);					//물건을 팔때



	int getX() { return _player.x; }
	int getY() { return _player.y; }

	int getHP() { return _playerhp._HP; }
	void setHP(int hp) { _playerhp._HP = hp; }

	RECT getPlayercollision() { return _player._collisionplayer; }		 //플레이어 rect 함수(아이템과 창고용?)
	RECT getplayerandMonster() { return _player._playerrect; }		//플레이어랑  몬스터 공격하기 위한 rect 함수

	float getPlayerX() { return _player.x; }					// 몬스터가 플레이어를 따라오기 위한 x
	float getPlayerY() { return _player.y; }					// 몬스터가 플레이어를 따라오기 위한 y

	int getMoney() { return _player._pmoney; }													//상점이나 인벤토리 용
	void setMoney(int money) { _player._pmoney = money; }							//상점이나 인벤토리용

	RECT getattacksword() { return _swordrect[4]; }

	inventory* getinventory() { return _inventory; }

	
	PLAYERLOCATION getPlayerLocation() { return _player._playerLocation; }
	void setPlayerLocation(PLAYERLOCATION location) { _player._playerLocation = location; }
};