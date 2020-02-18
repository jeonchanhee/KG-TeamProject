#pragma once
#include"singletonBase.h"
#include "bullet.h"																				// ����(����) Ŭ���� 
#include "progressBar.h"
#include "inventory.h"

//�÷��̾� ��ġ 
enum PLAYERLOCATION
{
	SHOP_PLAYER_VERSION,																// shop �÷��̾� ����
	DUNGEON_PLAYER_VERSION														 // dungeon �÷��̾� ����
};
//�÷��̾� ���� ����
enum PLAYERMOVING
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
//���� �÷��̾�Ը� ����� �� �ִ� ��  
enum TAGATTACKPLAYER
{
	PLAYER_SWORD,																											//��
	PLAYER_ARROW,																											// ȭ��
	PLAYER_SPEAR
};

enum TAGATTACKMOTION
{
	PLAYER_ATK_STOP,
	PLAYER_ATK_LEFT,																											//����
	PLAYER_ATK_RIGHT,																										//������
	PLAYER_ATK_UP,																												//��
	PLAYER_ATK_DOWN																										//�Ʒ�
};
//�÷��̾� ����ü
struct tagplayer
{
	PLAYERLOCATION  _playerLocation;																				//�÷��̾� ��ġ ���� shop�̸� �� �÷��̾� ���� �Ǵ� �����̸� ����, ���� ���¸� ǥ����
	PLAYERMOVING  _playermove;																						//�÷��̾� �����̴� �̳� ��
	TAGATTACKPLAYER _attackplayer;																					//�÷��̾� ���� 
	TAGATTACKMOTION _attacmove;																					//�÷��̾� ���� ���� 

	image* _playerimg;																											//�÷��̾� �̹���

	RECT _playerrect;																												//�÷��̾� �⺻ rect
	RECT _collisionplayer;																										//�÷��̾� �浹 rect �浹�ϰ� ���� �κ� ������ �� rect�� �̿��� ��


	int _playercount;																												//�÷��̾� �̹��� ī����
	int _playerindex;																												//�÷��̾� �̹��� �ε��� 
	int _pmoney;																														// �÷��̾� �� 
	int attskill;																															//���ݷ�
	int speed;																															//���ǵ�
	int shield;																															//����

	float x, y;																															//�÷��̾� x, y
	float height, width;																											//�÷��̾� Ȯ��

	bool _isattackmove;																											//ĳ������ ���ݵ����� �˷��ִ� bool��
	bool  _isFire;																														//Ȱ�� ����?

};
// ���α׷�����
struct taghpbar
{
	PlayerHpbar* _hpbar;																										// ���α׷�����
	int  _HP;																																//���� HP
	int _maxhp;																															//
};


class player : public singletonBase<player>
{
private:
	tagplayer _player;																										//shop player ���� 
	taghpbar _playerhp;																									//player�� hp 

	bool _isanimation;																										 //�ִϸ��̼� ���� �������ΰ�? �ƴϸ� �����¿� ����ΰ�?

	float time;																														//TIMEMANAGER�� �̿��Ͽ� ���� �� �ذ�(�ձ����� ����)

	float attacktime;																											//TIMEMANAGER�� �̿��Ͽ� ���� �� �� ��(KEYMANAGER->isOnceKeyDown('K')) ����

	weapons* _arrowfirst;																							   // ȭ�� 
	inventory* _inventory;																								//����

	RECT _swordrect;

	bool _ishwing;																												// Į�� �ֵѷ��� ���ֵѷ���?(���ֵθ�)
	bool sizeUp;
public:
	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void invenRender(HDC hdc);


	void playerKeyControl();																									// �÷��̾� Ű
	void playerAtt();																												//�÷��̾� ���� 
	void playermoveversion();																								 //�÷��̾� �̵� ���
	void attackmove();																											// ���� �÷��̾� ���� �Լ� 
	void allplayerimage();																										//�÷��̾� �̹��� ����
	void arrowFIre(WEAPONMOVE weponMove);
	void monsterbattle();																										//���� ��Ʋ
	void playerhitDameage(int _damage);																			//�Ǳ�� �Լ�
	void buyplayermoney(int _money);																				//������ �춧
	void sellplayermoney(int _money);																				//������ �ȶ�
	void  recoveryHp(int _hp);																								//ĳ���� ȸ��

	int getX() { return _player.x; }
	int getY() { return _player.y; }

	int getHP() { return _playerhp._HP; }
	void setHP(int hp) { _playerhp._HP = hp; }

	RECT getPlayercollision() { return _player._collisionplayer; }										 //�÷��̾� rect �Լ�(�����۰� â���?)
	RECT getplayerandMonster() { return _player._playerrect; }										//�÷��̾��  ���� �����ϱ� ���� rect �Լ�

	float getPlayerX() { return _player.x; }																				// ���Ͱ� �÷��̾ ������� ���� x
	float getPlayerY() { return _player.y; }																				// ���Ͱ� �÷��̾ ������� ���� y

	int getMoney() { return _player._pmoney; }																	//�����̳� �κ��丮 ��
	void setMoney(int money) { _player._pmoney = money; }											//�����̳� �κ��丮��

	int getattskill() { return _player.attskill; }																			//���� 
	void setattskill(int speed) { _player.attskill = speed; }

	int getspeed() { return _player.speed; }																			//���ǵ� �Լ�
	void setspeed(int _speed) { _player.speed = _speed; }

	int getshield() { return _player.shield; }																			//����
	void setshield(int _shield) { _player.shield = _shield; }

	RECT getattacksword() { return _swordrect; }

	inventory* getinventory() { return _inventory; }

	PLAYERLOCATION getPlayerLocation() { return _player._playerLocation; }
	void setPlayerLocation(PLAYERLOCATION location) { _player._playerLocation = location; }

	PLAYERMOVING getPlayerMoving() { return _player._playermove; }
	void setPlayerMoving(PLAYERMOVING _playmove) { _player._playermove = _playmove; }
};