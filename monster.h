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
	monsterProgressBar* _hpBar;	//ü�¹�
	RECT hRc;				//�ǰݹ���
	RECT aRc;				//���ݹ���
	int _atk;				//���ݷ�
	int _hp;				//ü��
	int _currentHp;			//����ü��
	int _speed;				//�̵��ӵ�
	int _x, _y;				//�ʱ� ��ǥ
	int _currentX, _currentY;	//�̵� ��ǥ
	float _distance;		//�÷��̾���ǰŸ�
	float _range;			//���ݹ���
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
		const char* imageName,
		MONSTER_TYPE monType,		//Ÿ��
		MONSTER_STATE monState,		//����
		MONSTER_DIRECTION monDirect,//����
		int x,
		int y,						//�ʱ� ��ǥ
		int atk,					//���ݷ�
		int hp,						//ü��
		int currentHp,				//����ü��
		float range,				//����
		int speed					//�̵��ӵ�
	);
	void release();
	void update();
	void render();


	//�׷��ִ� 
	virtual void draw();
	



	bool attack(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect);	//����
	bool hit();		//�ǰ�
	bool move(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect);	//�̵�
	bool die();		//���, �����۵��
	//get
	//�ǰݹ���
	RECT getHRect() { return hRc; }
	//���ݹ���
	RECT getARect() { return aRc; }

	MONSTER_DIRECTION getDirection() { return _monDirect; }
	MONSTER_TYPE getType() { return _monType; }

	//set
	void setMonDirect(MONSTER_DIRECTION MonDirect) { _monDirect = MonDirect; }

	//�̹����ҷ�����
	void golemTurretDirectImg();
	void golemSoldierDirectImg();
	void slimeGauntletDirectImg();
	void golemBossDirectImg();

	bool golemTurretAtk(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect);//���ͷ�����
	bool golemSoldierAtk(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect);//�񷽼�������
	bool slimeGauntletAtk(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect);//�����Ӱ�Ʋ������
	bool golemBossAtk(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect);//�񷽺�������
	void golemSoldierMove();//�񷽼����̵�
	void golemBossMove();//�񷽺����̵�

	//���� HP��
	void viewProgressBar();

};

