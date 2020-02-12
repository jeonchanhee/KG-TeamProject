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
	RECT iRc;				//�̹�������
	RECT hRc;				//�ǰݹ���
	RECT aRc;				//���ݹ���
	int _atk;				//���ݷ�
	int _hp;				//ü��
	int _currentHp;			//����ü��
	int _speed;				//�̵��ӵ�
	int _x, _y;				//�ʱ� ��ǥ
	int _currentX, _currentY;	//�̵� ��ǥ
	float _range;			//���ݹ���
	int count;				//ī��Ʈ
	item item;
	int fireCount;			//�߻������		
	int hitCount;			//��Ʈī��Ʈ
	int atkCount;			//����ī��Ʈ
	bool _move;
	int imgCount;			//����������ī��Ʈ


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
	image* _dieImg;
	animation* _aniDead;
	RECT dRc;

	bool attack(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect);	//����
	bool hit(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect);		//�ǰ�
	bool move(MONSTER_TYPE monType);	//�̵�
	bool die(MONSTER_TYPE monType);		//���, �����۵��
	//get
	//�ǰݹ���
	RECT getHRect() { return hRc; }
	//���ݹ���
	RECT getARect() { return aRc; }
	//hp
	int getCurrentHp() { return _currentHp; }

	MONSTER_DIRECTION getDirection() { return _monDirect; }
	MONSTER_TYPE getType() { return _monType; }

	//set
	void setMonDirect(MONSTER_DIRECTION MonDirect) { _monDirect = MonDirect; }

	//�̹����ҷ�����
	void golemTurretDirectImg();
	void golemSoldierDirectImg();
	void slimeGauntletDirectImg();
	void golemBossDirectImg();
	//���� ����
	bool golemTurretAtk(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect);//���ͷ�����
	bool golemSoldierAtk(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect);//�񷽼�������
	bool slimeGauntletAtk(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect);//�����Ӱ�Ʋ������
	bool golemBossAtk(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect);//�񷽺�������
	//���� �̵�
	bool golemSoldierMove();//�񷽼����̵�
	bool golemBossMove();//�񷽺����̵�
	//���� �ǰ�
	bool golemTurretHit(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect);//���ͷ��ǰ�
	bool golemSoldierHit(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect);//�񷽼����ǰ�
	bool slimeGauntletHit(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect);//�����Ӱ�Ʋ���ǰ�
	bool golemBossHit(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect);//�񷽺����ǰ�
	//���� �ֱ�
	bool golemTurretDie(MONSTER_TYPE monType);//���ͷ��ֱ�
	bool golemSoldierDie(MONSTER_TYPE monType);//�񷽼����ֱ�
	bool slimeGauntletDie(MONSTER_TYPE monType);//�����Ӱ�Ʋ���ֱ�
	bool golemBossDie(MONSTER_TYPE monType);//�񷽺����ֱ�


	//���� HP��
	void viewProgressBar();

};

