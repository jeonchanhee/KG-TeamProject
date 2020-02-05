#pragma once
#include "gameNode.h"

enum PLAYERVERSION  //플레이어 버전 
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
};



struct tagplayer		//플레이어 구조체
{
	PLAYERVERSION  _playerversions;			//플레이어 위치 상태 shop이면 샵 플레이어 던전 또는 마을이면 던전, 마을 상태를 표시함
	PLAYERMOVING  _playermove;				//플레이어 움직이는 이넘 값
	image* _playerimg;						//플레이어 이미지
	animation* _playerani;					//플래이어 애니메이션
	RECT _playerrect;						//플레이어 rect
};

class player : public gameNode
{
private:
	tagplayer _player;  //shop player 정보 
	bool _isanimation;	 //애니메이션 상태 구를것인가? 아니면 상하좌우 모션인가?

	int time;
public:
	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render();

	void shopPlayermove();			//샵플레이어 이동 함수
	void allplayerani();            //애니메이션 모음집
	void playermoveversion();       //플레이어 무브 버전
	void allplayerimage();			// 플레이어 이미지 모음
};

