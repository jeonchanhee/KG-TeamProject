#pragma once
#include"gameNode.h"
#include"monsterProgressBar.h"
//���� ����
enum MONSTER_TYPE
{
	MONSTER_TYPE_GOLEMTURRET,		//���ͷ�
	MONSTER_TYPE_GOLEMSOLDIER,		//�񷽼���
	MONSTER_TYPE_FLYINGGOLEM,		//�ö��װ�
	MONSTER_TYPE_SLIME,				//������
	MONSTER_TYPE_SLIMEGAUNTLET,		//�����Ӱ�Ʋ��
	MONSTER_TYPE_GOLEMBOSS			//�񷽺���
};
//���� ����
enum MONSTER_STATE
{
	MONSTER_STATE_IDLE,		//���
	MONSTER_STATE_MOVE,		//�̵�
	MONSTER_STATE_ATK,		//����
	MONSTER_STATE_HIT,		//�ǰ�
	MONSTER_STATE_DEAD		//����
};
//���� ����
enum MONSTER_DIRECTION
{
	MONSTER_DIRECTION_LEFT,		//����
	MONSTER_DIRECTION_UP,	//������
	MONSTER_DIRECTION_RIGHT,		//��
	MONSTER_DIRECTION_DOWN		//�Ʒ�
};

class monster : public gameNode
{
private:
	MONSTER_TYPE _monType;	//Ÿ��
	MONSTER_STATE _monState;	//����
	MONSTER_DIRECTION _monDirect;//����
	image * _monsterImg;	//�̹���
	animation* _ani;			//�ִϸ��̼�
	animation* _aniAtk;			//�ִϸ��̼�
	monsterProgressBar* _hpBar;	//ü�¹�
	RECT rc;				//�ǰݹ���
	int atk;				//���ݷ�
	int maxHp;				//ü��
	int currentHp;			//����ü��
	int speed;				//�̵��ӵ�
	int _x, _y;				//�ʱ� ��ǥ
	int currentX, currentY;	//�̵� ��ǥ
	int count;				//ī��Ʈ
	int dropItemNum1;		//��������� ������ ��ȣ
	int dropItemNum2;		//��������� ������ ��ȣ
	int dropItemNum3;		//��������� ������ ��ȣ
	int fireCount;			//�߻������		

public:
	monster();
	~monster();

	HRESULT init();
	HRESULT init(
		MONSTER_TYPE monType,		//Ÿ��
		MONSTER_STATE monState,		//����
		MONSTER_DIRECTION monDirect,//����
		int x,
		int y						//�ʱ� ��ǥ
	);
	void release();
	void update();
	void render();

	//�׷��ִ� 
	virtual void draw();
	//�ִϸ��̼� �Լ�
	virtual void animation();



	bool attack(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect);	//����
	bool hit();		//�ǰ�
	bool move();	//�̵�
	bool die();		//���, �����۵��
	//get
	RECT getRect() { return rc; }
	MONSTER_DIRECTION getDirection() { return _monDirect; }
	MONSTER_TYPE getType() { return _monType; }

	//set
	void setMonDirect(MONSTER_DIRECTION MonDirect) { _monDirect = MonDirect; }

	//�̹����ҷ�����
	void golemTurretDirectImg(MONSTER_DIRECTION monDirect);
	void golemSoldierDirectImg(MONSTER_DIRECTION monDirect);
	void slimeGauntletDirectImg(MONSTER_DIRECTION monDirect);
	void golemBossDirectImg(MONSTER_DIRECTION monDirect);

	bool golemTurretAtk();//���ͷ�����
	bool golemSoldierAtk(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect);//�񷽼�������
	bool slimeGauntletAtk(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect);//�����Ӱ�Ʋ������
	bool golemBossAtk(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect);//�񷽺�������

	//���� HP��
	void viewProgressBar();

};

