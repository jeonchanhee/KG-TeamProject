#include "stdafx.h"
#include "monster.h"

monster::monster()
{
}

monster::~monster()
{
}

HRESULT monster::init()
{
	return S_OK;
}

HRESULT monster::init(
	MONSTER_TYPE monType,	//Ÿ��
	MONSTER_STATE monState,	//����
	MONSTER_DIRECTION monDirect,//����
	int x,
	int y		//�ʱ���ǥ
)
{

	
	
	
	//���� Ÿ�Կ� ���� ���Ͱ� �ֱ�
	switch (monType)
	{
	case MONSTER_TYPE_GOLEMTURRET://���ͷ�
		_monsterImg = IMAGEMANAGER->findImage("golemTurret");
		//���Ⱚ���� �´� ���� �̹��� ã��
		golemTurretDirectImg(monDirect);//�̹�������
		
		//���� �ǰݹ���
		rc = RectMakeCenter(x, y,
			_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
		atk = 10;					//���ݷ�
		maxHp = 100;				//ü��
		currentHp = 100;			//����ü��
		speed = 0;					//�̵��ӵ�
		_x = x;						//�ʱ���ǥ
		_y = y;
		dropItemNum1 = 0;			//��������� ������ ��ȣ
		dropItemNum2 = 1;			//��������� ������ ��ȣ
		dropItemNum3 = 2;			//��������� ������ ��ȣ
		break;
	case MONSTER_TYPE_GOLEMSOLDIER://�񷽼���
		_monsterImg = IMAGEMANAGER->findImage("golemSoldier");
		//���Ⱚ���� �´� ���� �̹��� ã��
		golemSoldierDirectImg(monDirect);//�̹�������
		//���� �ǰݹ���
		rc = RectMakeCenter(x, y,
			_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
		atk = 15;					//���ݷ�
		maxHp = 100;				//ü��
		currentHp = 100;				//����ü��
		speed = 5;					//�̵��ӵ�
		_x = x;						//�ʱ���ǥ
		_y = y;
		dropItemNum1 = 1;			//��������� ������ ��ȣ
		dropItemNum2 = 3;			//��������� ������ ��ȣ
		dropItemNum3 = 2;			//��������� ������ ��ȣ
		break;
	case MONSTER_TYPE_SLIMEGAUNTLET:
		_monsterImg = IMAGEMANAGER->findImage("slimeGauntlet");
		//���Ⱚ���� �´� ���� �̹��� ã��
		slimeGauntletDirectImg(monDirect);//�̹�������
		//���� �ǰݹ���
		rc = RectMakeCenter(x, y,
			_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
		atk = 15;					//���ݷ�
		maxHp = 100;				//ü��
		currentHp = 100;				//����ü��
		speed = 0;					//�̵��ӵ�
		_x = x;						//�ʱ���ǥ
		_y = y;
		dropItemNum1 = 1;			//��������� ������ ��ȣ
		dropItemNum2 = 3;			//��������� ������ ��ȣ
		dropItemNum3 = 2;			//��������� ������ ��ȣ
		break;
	case MONSTER_TYPE_GOLEMBOSS:
		_monsterImg = IMAGEMANAGER->findImage("golemBoss");
		//���Ⱚ���� �´� ���� �̹��� ã��
		golemBossDirectImg(monDirect);//�̹�������
		//���� �ǰݹ���
		rc = RectMakeCenter(x, y,
			_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
		atk = 15;					//���ݷ�
		maxHp = 100;				//ü��
		currentHp = 100;				//����ü��
		speed = 0;					//�̵��ӵ�
		_x = x;						//�ʱ���ǥ
		_y = y;
		dropItemNum1 = 1;			//��������� ������ ��ȣ
		dropItemNum2 = 3;			//��������� ������ ��ȣ
		dropItemNum3 = 2;			//��������� ������ ��ȣ
		break;
	}
	
	//�ش� ������ ���� �� �ֱ�
	_monType = monType;			//���� ����
	_monState = monState;		//���� ����
	_monDirect = monDirect;		//���� ����
	count = 0;					//ī��Ʈ
	_hpBar = new monsterProgressBar;
	_hpBar->init("images/monster/progressBarFront.bmp", "images/monster/progressBarBack.bmp", 0, 0, 50, 10);
	_hpBar->setGauge(currentHp, maxHp);
	_hpBar->setX(x - 25);
	_hpBar->setY(y - 70);
	return S_OK;
}

void monster::release()
{
}

void monster::update()
{
	viewProgressBar();
	//animation();
}

void monster::render()
{
	draw();
}
//�������̹��� �׷���
void monster::draw()
{
	//���ͷ� ����
	_monsterImg->aniRender(getMemDC(), rc.left, rc.top, _ani);
	_hpBar->render();
	//���� �ǰݹ���
	//RectangleMake(getMemDC(), rc.left, rc.top, _monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
}

void monster::animation()
{
}
//����
bool monster::attack(MONSTER_TYPE monType)
{
	switch (monType) {
	case MONSTER_TYPE_GOLEMTURRET:
		golemTurretAtk();
		break;
	case MONSTER_TYPE_GOLEMSOLDIER:
		
		break;
	}

	//���ͷ��� ������ ���ʹ� ������ �÷��̾ ������ ī��Ʈ�� �ö󰣴�.
	return false;
}

void monster::golemTurretDirectImg(MONSTER_DIRECTION monDirect)
{
	_monsterImg = IMAGEMANAGER->findImage("golemTurret");
	//���Ⱚ���� �´� ���� �̹��� ã��
	switch (monDirect)
	{
	case 0:
		_ani = ANIMATIONMANAGER->findAnimation("golemTurretL");
		ANIMATIONMANAGER->start("golemTurretL");
		break;
	case 1:
		_ani = ANIMATIONMANAGER->findAnimation("golemTurretU");
		ANIMATIONMANAGER->start("golemTurretU");
		break;
	case 2:
		_ani = ANIMATIONMANAGER->findAnimation("golemTurretR");
		ANIMATIONMANAGER->start("golemTurretR");
		break;
	case 3:
		_ani = ANIMATIONMANAGER->findAnimation("golemTurretB");
		ANIMATIONMANAGER->start("golemTurretB");
		break;
	}
}

void monster::golemSoldierDirectImg(MONSTER_DIRECTION monDirect)
{
	_monsterImg = IMAGEMANAGER->findImage("golemSoldier");
	//���Ⱚ���� �´� ���� �̹��� ã��
	switch (monDirect)
	{
	case 0:
		_ani = ANIMATIONMANAGER->findAnimation("golemSoldierL");
		ANIMATIONMANAGER->start("golemSoldierL");
		break;
	case 1:
		_ani = ANIMATIONMANAGER->findAnimation("golemSoldierU");
		ANIMATIONMANAGER->start("golemSoldierU");
		break;
	case 2:
		_ani = ANIMATIONMANAGER->findAnimation("golemSoldierR");
		ANIMATIONMANAGER->start("golemSoldierR");
		break;
	case 3:
		_ani = ANIMATIONMANAGER->findAnimation("golemSoldierB");
		ANIMATIONMANAGER->start("golemSoldierB");
		break;
	}
}

void monster::slimeGauntletDirectImg(MONSTER_DIRECTION monDirect)
{
	_monsterImg = IMAGEMANAGER->findImage("slimeGauntlet");
	//���Ⱚ���� �´� ���� �̹��� ã��
	switch (monDirect)
	{
	case 0:
		_ani = ANIMATIONMANAGER->findAnimation("slimeGauntletL");
		ANIMATIONMANAGER->start("slimeGauntletL");
		break;
	case 1:
		_ani = ANIMATIONMANAGER->findAnimation("slimeGauntletU");
		ANIMATIONMANAGER->start("slimeGauntletU");
		break;
	case 2:
		_ani = ANIMATIONMANAGER->findAnimation("slimeGauntletR");
		ANIMATIONMANAGER->start("slimeGauntletR");
		break;
	case 3:
		_ani = ANIMATIONMANAGER->findAnimation("slimeGauntletB");
		ANIMATIONMANAGER->start("slimeGauntletB");
		break;
	}
}

void monster::golemBossDirectImg(MONSTER_DIRECTION monDirect)
{
	_monsterImg = IMAGEMANAGER->findImage("golemBoss");
	//���Ⱚ���� �´� ���� �̹��� ã��
	switch (monDirect)
	{
	case 0:
		_ani = ANIMATIONMANAGER->findAnimation("golemBossL");
		ANIMATIONMANAGER->start("golemBossL");
		break;
	case 1:
		_ani = ANIMATIONMANAGER->findAnimation("golemBossU");
		ANIMATIONMANAGER->start("golemBossU");
		break;
	case 2:
		_ani = ANIMATIONMANAGER->findAnimation("golemBossR");
		ANIMATIONMANAGER->start("golemBossR");
		break;
	case 3:
		_ani = ANIMATIONMANAGER->findAnimation("golemBossB");
		ANIMATIONMANAGER->start("golemBossB");
		break;
	}
}


//���ͷ�����
bool monster::golemTurretAtk()
{
	//if (monType == 0) {
		count++;
		//ī��Ʈ�� 30�϶� ����
		if (count == 30)
		{
			//_rndFireCount = RND->getFromIntTo(1, 1000);
			count = 0;
			return true;
		}
	//}
	return false;
}

//�񷽼�������
bool monster::golemSoldierAtk()
{
	//if (monType == 0) {
	count++;
	//ī��Ʈ�� 30�϶� ����
	if (count == 30)
	{
		_monState = MONSTER_STATE_ATK;
		
		//_rndFireCount = RND->getFromIntTo(1, 1000);
		count = 0;
		return true;
	}
	//}
	return false;
}

bool monster::slimeGauntletAtk()
{
	//if (monType == 0) {
	count++;
	//ī��Ʈ�� 30�϶� ����
	if (count == 30)
	{
		_monState = MONSTER_STATE_ATK;
		//_rndFireCount = RND->getFromIntTo(1, 1000);
		count = 0;
		return true;
	}
	//}
	return false;
}

bool monster::golemBossAtk()
{
	//if (monType == 0) {
	count++;
	//ī��Ʈ�� 30�϶� ����
	if (count == 30)
	{
		_monState = MONSTER_STATE_ATK;
		//_rndFireCount = RND->getFromIntTo(1, 1000);
		count = 0;
		return true;
	}
	//}
	return false;
}

//ü�� �����ִ� �Լ�
void monster::viewProgressBar()
{
	_hpBar->setGauge(currentHp, maxHp);
	_hpBar->update();
}