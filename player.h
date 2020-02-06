#pragma once
//#include"gameNode.h"
#include"singletonBase.h"

enum PLAYERLOCATION  //플레이어 위치 
{
	SHOP_PLAYER_VERSION,			  // shop 플레이어 버전
	DUNGEON_PLAYER_VERSION	  // dungeon 플레이어 버전
};

enum PLAYERMOVING		//플레이어 동작 상태
{
	PLAYER_DOWN_IDLE,
	PLAYER_DOWN,
	PLAYER_UP_IDLE,
	PLAYER_UP,
	PLAYER_LEFT_IDLE,
	PLAYER_LEFT,
	PLAYER_RIGHT_IDLE,
	PLAYER_RIGHT,
	PLAYER_RIGHT_ROLL,
	PLAYER_LEFT_ROLL,
	PLAYER_UP_ROLL,
	PLAYER_BACK_ROLL,
	PLAYER_DIE
};


struct tagplayer		//플레이어 구조체
{
	PLAYERLOCATION  _playerLocation;			//플레이어 위치 상태 shop이면 샵 플레이어 던전 또는 마을이면 던전, 마을 상태를 표시함
	PLAYERMOVING  _playermove;				//플레이어 움직이는 이넘 값
	image* _playerimg;						//플레이어 이미지
	animation* _playerani;					//플래이어 애니메이션
	RECT _playerrect;						//플레이어 기본 rect
	RECT _collisionplayer;				//플레이어 충돌 rect 충돌하고 싶은 부분 있으면 이 rect로 이용할 것
	int _playercount;						//플레이어 이미지 카운터
	int _playerindex;						//플레이어 이미지 인덱스 
	float x, y;									//플레이어 x, y
	int HP;
};

class player : public singletonBase<player>//public gameNode //public singletonBase<player>
{
private:
	tagplayer _player;  //shop player 정보 

	bool _isanimation;	 //애니메이션 상태 구를것인가? 아니면 상하좌우 모션인가?

	float time;



public:
	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void shopPlayermove();				//샵플레이어 이동 함수
	void dungeonPlayermove();		// 던전 플레이어 이동 함수
	void playermoveversion();		  //플레이어 무브 버전
	void allplayerimage();				// 플레이어 이미지 모음

	int getHP() { return _player.HP; }
	void setHP(int hp) { _player.HP = hp; }

	RECT getPlayercollision() { return _player._collisionplayer; }		 //플레이어 함수
};

