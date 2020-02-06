#pragma once
//#include"gameNode.h"
#include"singletonBase.h"

enum PLAYERLOCATION  //�÷��̾� ��ġ 
{
	SHOP_PLAYER_VERSION,			  // shop �÷��̾� ����
	DUNGEON_PLAYER_VERSION	  // dungeon �÷��̾� ����
};

enum PLAYERMOVING		//�÷��̾� ���� ����
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


struct tagplayer		//�÷��̾� ����ü
{
	PLAYERLOCATION  _playerLocation;			//�÷��̾� ��ġ ���� shop�̸� �� �÷��̾� ���� �Ǵ� �����̸� ����, ���� ���¸� ǥ����
	PLAYERMOVING  _playermove;				//�÷��̾� �����̴� �̳� ��
	image* _playerimg;						//�÷��̾� �̹���
	animation* _playerani;					//�÷��̾� �ִϸ��̼�
	RECT _playerrect;						//�÷��̾� �⺻ rect
	RECT _collisionplayer;				//�÷��̾� �浹 rect �浹�ϰ� ���� �κ� ������ �� rect�� �̿��� ��
	int _playercount;						//�÷��̾� �̹��� ī����
	int _playerindex;						//�÷��̾� �̹��� �ε��� 
	float x, y;									//�÷��̾� x, y
	int HP;
};

class player : public singletonBase<player>//public gameNode //public singletonBase<player>
{
private:
	tagplayer _player;  //shop player ���� 

	bool _isanimation;	 //�ִϸ��̼� ���� �������ΰ�? �ƴϸ� �����¿� ����ΰ�?

	float time;



public:
	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void shopPlayermove();				//���÷��̾� �̵� �Լ�
	void dungeonPlayermove();		// ���� �÷��̾� �̵� �Լ�
	void playermoveversion();		  //�÷��̾� ���� ����
	void allplayerimage();				// �÷��̾� �̹��� ����

	int getHP() { return _player.HP; }
	void setHP(int hp) { _player.HP = hp; }

	RECT getPlayercollision() { return _player._collisionplayer; }		 //�÷��̾� �Լ�
};

