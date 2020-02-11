#pragma once
//#include"gameNode.h"
#include"singletonBase.h"
#include "bullet.h"				// ����(����) Ŭ���� 


/*
	�κ��丮
	�ǰ�
	����

	�ð��� ������ UI�� �ϼ���
	�� ������ ���̾�α��ϼ���
	�ڵ带 ���״� ���� �����ϰ� �غ�����

	�����ý��丮 ��Ʈ

	�÷��̾� �����Դϴ�.
*/

enum PLAYERLOCATION  //�÷��̾� ��ġ 
{
	SHOP_PLAYER_VERSION,			  // shop �÷��̾� ����
	DUNGEON_PLAYER_VERSION	  // dungeon �÷��̾� ����
};

enum PLAYERMOVING		//�÷��̾� ���� ����
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
	int _pmoney;				// �÷��̾� �� 
	int attCount;

	float x, y;									//�÷��̾� x, y

	bool _isattackmove;					//ĳ������ ���ݵ����� �˷��ִ� bool��
	bool  _isFire;									//Ȱ�� ����?

};

class player : public singletonBase<player>//public gameNode //public singletonBase<player>
{
private:
	tagplayer _player;  //shop player ���� 

	bool _isanimation;	 //�ִϸ��̼� ���� �������ΰ�? �ƴϸ� �����¿� ����ΰ�?

	float time;					//TIMEMANAGER�� �̿��Ͽ� ���� �� �ذ�(�ձ����� ����)

	float attacktime;			//TIMEMANAGER�� �̿��Ͽ� ���� �� �� ��(KEYMANAGER->isOnceKeyDown('K')) ����

	weapons* _arrowfirst;   // ȭ�� 


public:
	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	//void shopPlayermove();				//���÷��̾� �̵� �Լ�
	//void dungeonPlayermove();		// ���� �÷��̾� �̵� �Լ�
	void playerKeyControl();				// �÷��̾� Ű
	void playerAtt();							//�÷��̾� ���� 
	void playermoveversion();		  //�÷��̾� �̵� ���
	void attackmove();						// ���� �÷��̾� ���� �Լ� 
	void arrowFIre(WEAPONMOVE weponMove);
	void allplayerimage();				// �÷��̾� �̹��� ����

	int getHP() { return _player.HP; }
	void setHP(int hp) { _player.HP = hp; }

	RECT getPlayercollision() { return _player._collisionplayer; }		 //�÷��̾� rect �Լ�(�����۰� â���?)
	RECT getplayerandMonster() { return _player._playerrect; }		//�÷��̾��  ���� �����ϱ� ���� rect �Լ�

	float getPlayerX() { return _player.x; }					// ���Ͱ� �÷��̾ ������� ���� x
	float getPlayerY() { return _player.y; }					// ���Ͱ� �÷��̾ ������� ���� y

	int getMoney() { return _player._pmoney; }
	void setMoney(int money) { _player._pmoney = money; }

};