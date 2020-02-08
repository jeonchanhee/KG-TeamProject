#pragma once
//#include"gameNode.h"
#include"singletonBase.h"
//#include "weapons.h"				// ����(����) Ŭ����  ���� �̿ϼ� �ϼ��Ǹ� bulletŬ���� ���� ��
//#include "bullet.h"					// ȭ���� ���� �� �ֵ��� 

/*
	�κ��丮
	�ǰ�
	����

	�ð��� ������ UI�� �ϼ���
	�� ������ ���̾�α��ϼ���
	�ڵ带 ���״� ���� �����ϰ� �غ�����

	�����ý��丮 ��Ʈ

	���� �Ѵ� ������ �������� �ұ�

*/

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

enum TAGATTACKPLAYER			//���� �÷��̾�Ը� ����� �� �ִ� ��  
{
	PLAYER_SWORD,				//��
	PLAYER_ARROW,				// ȭ��
	PLAYER_SPEAR
};

enum TAGATTACKMOTION
{
	PLAYER_ATK_STOP,
	PLAYER_ATK_LEFT,							//����
	PLAYER_ATK_RIGHT,							//������
	PLAYER_ATK_UP,								//��
	PLAYER_ATK_DOWN						//�Ʒ�
};

struct tagplayer		//�÷��̾� ����ü
{
	PLAYERLOCATION  _playerLocation;			//�÷��̾� ��ġ ���� shop�̸� �� �÷��̾� ���� �Ǵ� �����̸� ����, ���� ���¸� ǥ����
	PLAYERMOVING  _playermove;					//�÷��̾� �����̴� �̳� ��
	TAGATTACKPLAYER _attackplayer;				//�÷��̾� ���� 
	TAGATTACKMOTION _attacmove;				 //�÷��̾� ���� ���� 

	image* _playerimg;							//�÷��̾� �̹���

	RECT _playerrect;						//�÷��̾� �⺻ rect
	RECT _collisionplayer;				//�÷��̾� �浹 rect �浹�ϰ� ���� �κ� ������ �� rect�� �̿��� ��


	int _playercount;						//�÷��̾� �̹��� ī����
	int _playerindex;						//�÷��̾� �̹��� �ε��� 
	int  HP;										//HP

	float x, y;									//�÷��̾� x, y

	bool _isattackmove;					//ĳ������ ���ݵ����� �˷��ִ� bool��
	bool _ischageweapon;			//ĳ������ ���� ü����

};

class player : public singletonBase<player>//public gameNode //public singletonBase<player>
{
private:
	tagplayer _player;  //shop player ���� 

	bool _isanimation;	 //�ִϸ��̼� ���� �������ΰ�? �ƴϸ� �����¿� ����ΰ�?

	float time;					//TIMEMANAGER�� �̿��Ͽ� ���� �� �ذ�(�ձ����� ����)

	float attacktime;			//TIMEMANAGER�� �̿��Ͽ� ���� �� �� ��(KEYMANAGER->isOnceKeyDown('K')) ����



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
	void attackmove();						// ���� �÷��̾� ���� �Լ� 
	void allplayerimage();				// �÷��̾� �̹��� ����

	int getHP() { return _player.HP; }
	void setHP(int hp) { _player.HP = hp; }

	RECT getPlayercollision() { return _player._collisionplayer; }		 //�÷��̾� �Լ�
};

