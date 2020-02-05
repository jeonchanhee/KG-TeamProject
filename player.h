#pragma once
#include "gameNode.h"

enum PLAYERVERSION  //�÷��̾� ���� 
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
};



struct tagplayer		//�÷��̾� ����ü
{
	PLAYERVERSION  _playerversions;			//�÷��̾� ��ġ ���� shop�̸� �� �÷��̾� ���� �Ǵ� �����̸� ����, ���� ���¸� ǥ����
	PLAYERMOVING  _playermove;				//�÷��̾� �����̴� �̳� ��
	image* _playerimg;						//�÷��̾� �̹���
	animation* _playerani;					//�÷��̾� �ִϸ��̼�
	RECT _playerrect;						//�÷��̾� rect
};

class player : public gameNode
{
private:
	tagplayer _player;  //shop player ���� 
	bool _isanimation;	 //�ִϸ��̼� ���� �������ΰ�? �ƴϸ� �����¿� ����ΰ�?

	int time;
public:
	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render();

	void shopPlayermove();			//���÷��̾� �̵� �Լ�
	void allplayerani();            //�ִϸ��̼� ������
	void playermoveversion();       //�÷��̾� ���� ����
	void allplayerimage();			// �÷��̾� �̹��� ����
};

