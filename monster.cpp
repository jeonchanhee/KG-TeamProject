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

	_golemTurret = IMAGEMANAGER->findImage("golemTurret");

	//���� Ÿ�� 0(���ͷ�)
	switch (monType)
	{
	case 0:
		//�̹�������
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

		//�ش� ������ ���� �� �ֱ�
		_monType = monType;			//���� ����
		_monState = monState;		//���� ����
		_monDirect = monDirect;		//���� ����
		count = 0;					//ī��Ʈ
		rc = RectMakeCenter(x, y,
			_golemTurret->getFrameWidth(), _golemTurret->getFrameHeight());
		//���� �ǰݹ���
		atk = 10;					//���ݷ�
		hp = 50;					//ü��
		speed = 5;					//�̵��ӵ�
		_x = x;						//�ʱ���ǥ
		_y = y;
		dropItemNum1 = 0;			//��������� ������ ��ȣ
		dropItemNum2 = 1;			//��������� ������ ��ȣ
		dropItemNum3 = 2;			//��������� ������ ��ȣ
		break;

	}
	return S_OK;
}

void monster::release()
{
}

void monster::update()
{

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
	_golemTurret->aniRender(getMemDC(), rc.left, rc.top, _ani);

	//���� �ǰݹ���
	//RectangleMake(getMemDC(), rc.left, rc.top, _golemTurret->getFrameWidth(), _golemTurret->getFrameHeight());
}

void monster::animation()
{
}

bool monster::attack()
{

	count++;

	if (count == 30)
	{
		//_rndFireCount = RND->getFromIntTo(1, 1000);
		count = 0;
		return true;
	}


	return false;
}