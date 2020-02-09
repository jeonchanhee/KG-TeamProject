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
		_monsterImg = IMAGEMANAGER->findImage("���ͷ�");
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
		_monsterImg = IMAGEMANAGER->findImage("�񷽼���");
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
		_monsterImg = IMAGEMANAGER->findImage("�����Ӱ�Ʋ��");
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
		_monsterImg = IMAGEMANAGER->findImage("�񷽺���");
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
	animation();
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
	//RectangleMakeCenter(getMemDC(), (rc.left+rc.right)/2, (rc.top+rc.bottom)/2, _monsterImg->getFrameWidth()/2, _monsterImg->getFrameHeight()/2);
}

void monster::animation()
{

}
//����
bool monster::attack(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect)
{
	switch (monType) {
	case MONSTER_TYPE_GOLEMTURRET:
		golemTurretAtk();
		break;
	case MONSTER_TYPE_GOLEMSOLDIER:
		golemSoldierAtk(monType, monDirect);
		break;
	case MONSTER_TYPE_SLIMEGAUNTLET:
		slimeGauntletAtk(monType, monDirect);
		break;
	case MONSTER_TYPE_GOLEMBOSS:
		golemBossAtk(monType, monDirect);
		break;
	}

	//���ͷ��� ������ ���ʹ� ������ �÷��̾ ������ ī��Ʈ�� �ö󰣴�.
	return false;
}

void monster::golemTurretDirectImg(MONSTER_DIRECTION monDirect)
{
	_monsterImg = IMAGEMANAGER->findImage("���ͷ�");
	//���Ⱚ���� �´� ���� �̹��� ã��
	switch (monDirect)
	{
	case 0:
		_ani = ANIMATIONMANAGER->findAnimation("���ͷ�L");
		ANIMATIONMANAGER->start("���ͷ�L");

		break;
	case 1:
		_ani = ANIMATIONMANAGER->findAnimation("���ͷ�U");
		ANIMATIONMANAGER->start("���ͷ�U");
		break;
	case 2:
		_ani = ANIMATIONMANAGER->findAnimation("���ͷ�R");
		ANIMATIONMANAGER->start("���ͷ�R");
		break;
	case 3:
		_ani = ANIMATIONMANAGER->findAnimation("���ͷ�B");
		ANIMATIONMANAGER->start("���ͷ�B");
		break;
	}
}

void monster::golemSoldierDirectImg(MONSTER_DIRECTION monDirect)
{
	_monsterImg = IMAGEMANAGER->findImage("�񷽼���");
	//���Ⱚ���� �´� ���� �̹��� ã��
	switch (monDirect)
	{
	case 0:
		_ani = ANIMATIONMANAGER->findAnimation("�񷽼���L");
		ANIMATIONMANAGER->start("�񷽼���L");
		break;
	case 1:
		_ani = ANIMATIONMANAGER->findAnimation("�񷽼���U");
		ANIMATIONMANAGER->start("�񷽼���U");
		break;
	case 2:
		_ani = ANIMATIONMANAGER->findAnimation("�񷽼���R");
		ANIMATIONMANAGER->start("�񷽼���R");
		break;
	case 3:
		_ani = ANIMATIONMANAGER->findAnimation("�񷽼���B");
		ANIMATIONMANAGER->start("�񷽼���B");
		break;
	}
}

void monster::slimeGauntletDirectImg(MONSTER_DIRECTION monDirect)
{
	_monsterImg = IMAGEMANAGER->findImage("�����Ӱ�Ʋ��");
	//���Ⱚ���� �´� ���� �̹��� ã��
	switch (monDirect)
	{
	case 0:
		_ani = ANIMATIONMANAGER->findAnimation("�����Ӱ�Ʋ��L");
		ANIMATIONMANAGER->start("�����Ӱ�Ʋ��L");
		break;
	case 1:
		_ani = ANIMATIONMANAGER->findAnimation("�����Ӱ�Ʋ��U");
		ANIMATIONMANAGER->start("�����Ӱ�Ʋ��U");
		break;
	case 2:
		_ani = ANIMATIONMANAGER->findAnimation("�����Ӱ�Ʋ��R");
		ANIMATIONMANAGER->start("�����Ӱ�Ʋ��R");
		break;
	case 3:
		_ani = ANIMATIONMANAGER->findAnimation("�����Ӱ�Ʋ��B");
		ANIMATIONMANAGER->start("�����Ӱ�Ʋ��B");
		break;
	}
}

void monster::golemBossDirectImg(MONSTER_DIRECTION monDirect)
{
	_monsterImg = IMAGEMANAGER->findImage("�񷽺���");
	//���Ⱚ���� �´� ���� �̹��� ã��
	switch (monDirect)
	{
	case 0:
		_ani = ANIMATIONMANAGER->findAnimation("�񷽺���L");
		ANIMATIONMANAGER->start("�񷽺���L");
		break;
	case 1:
		_ani = ANIMATIONMANAGER->findAnimation("�񷽺���U");
		ANIMATIONMANAGER->start("�񷽺���U");
		break;
	case 2:
		_ani = ANIMATIONMANAGER->findAnimation("�񷽺���R");
		ANIMATIONMANAGER->start("�񷽺���R");
		break;
	case 3:
		_ani = ANIMATIONMANAGER->findAnimation("�񷽺���B");
		ANIMATIONMANAGER->start("�񷽺���B");
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
bool monster::golemSoldierAtk(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect)
{
	//if (monType == 0) {
	count++;
	//ī��Ʈ�� 30�϶� ����
	if (count == 300)
	{
		_monState = MONSTER_STATE_ATK;
		switch (monDirect) {
		case MONSTER_DIRECTION_LEFT:
			_monsterImg = IMAGEMANAGER->findImage("�񷽼�������");
			rc = RectMakeH(rc.left, rc.bottom,
				_monsterImg->getFrameWidth() - 50, _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("�񷽼�������L");
			ANIMATIONMANAGER->start("�񷽼�������L");
			if (_monsterImg->getFrameX() == _monsterImg->getMaxFrameX())
			{
				_ani = ANIMATIONMANAGER->findAnimation("�񷽼�������L");
				ANIMATIONMANAGER->start("�񷽼�������L");
			}
			break;
		case MONSTER_DIRECTION_UP:
			_monsterImg = IMAGEMANAGER->findImage("�񷽼�������");
			rc = RectMakeCenter((rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight() - 50);
			_ani = ANIMATIONMANAGER->findAnimation("�񷽼�������U");
			ANIMATIONMANAGER->start("�񷽼�������U");
			break;
		case MONSTER_DIRECTION_RIGHT:
			_monsterImg = IMAGEMANAGER->findImage("�񷽼�������");
			rc = RectMakeCenter((rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2,
				_monsterImg->getFrameWidth() + 50, _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("�񷽼�������R");
			ANIMATIONMANAGER->start("�񷽼�������R");
			break;
		case MONSTER_DIRECTION_DOWN:
			_monsterImg = IMAGEMANAGER->findImage("�񷽼�������");
			rc = RectMakeCenter((rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight() + 50);
			_ani = ANIMATIONMANAGER->findAnimation("�񷽼�������B");
			ANIMATIONMANAGER->start("�񷽼�������B");
			break;
		}
		//_rndFireCount = RND->getFromIntTo(1, 1000);
		count = 0;
		return true;
	}
	//}
	return false;
}

bool monster::slimeGauntletAtk(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect)
{
	//if (monType == 0) {
	count++;
	//ī��Ʈ�� 30�϶� ����
	if (count == 300)
	{
		_monState = MONSTER_STATE_ATK;
		//_rndFireCount = RND->getFromIntTo(1, 1000);
		switch (monDirect) {
		case MONSTER_DIRECTION_LEFT:
			_monsterImg = IMAGEMANAGER->findImage("�����Ӱ�Ʋ������");
			rc = RectMakeCenter((rc.left + rc.right) / 2 + 10, (rc.top + rc.bottom) / 2 + 35,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("�����Ӱ�Ʋ������L");
			ANIMATIONMANAGER->start("�����Ӱ�Ʋ������L");
			if (_monsterImg->getFrameX() == _monsterImg->getMaxFrameX())
			{
				_ani = ANIMATIONMANAGER->findAnimation("�����Ӱ�Ʋ��L");
				ANIMATIONMANAGER->start("�����Ӱ�Ʋ��L");
			}
			break;
		case MONSTER_DIRECTION_UP:
			_monsterImg = IMAGEMANAGER->findImage("�����Ӱ�Ʋ������");
			rc = RectMakeCenter((rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2 + 40,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("�����Ӱ�Ʋ������U");
			ANIMATIONMANAGER->start("�����Ӱ�Ʋ������U");
			break;
		case MONSTER_DIRECTION_RIGHT:
			_monsterImg = IMAGEMANAGER->findImage("�����Ӱ�Ʋ������");
			rc = RectMakeCenter((rc.left + rc.right) / 2 + 15, (rc.top + rc.bottom) / 2 + 25,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("�����Ӱ�Ʋ������R");
			ANIMATIONMANAGER->start("�����Ӱ�Ʋ������R");
			break;
		case MONSTER_DIRECTION_DOWN:
			_monsterImg = IMAGEMANAGER->findImage("�����Ӱ�Ʋ������");
			rc = RectMakeCenter((rc.left + rc.right) / 2 + 10, (rc.top + rc.bottom) / 2 + 35,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight() + 50);
			_ani = ANIMATIONMANAGER->findAnimation("�����Ӱ�Ʋ������B");
			ANIMATIONMANAGER->start("�����Ӱ�Ʋ������B");
			break;
		}
		count = 0;
		return true;
	}
	//}
	return false;
}

bool monster::golemBossAtk(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect)
{
	//if (monType == 0) {
	count++;
	//ī��Ʈ�� 30�϶� ����
	if (count == 300)
	{
		_monState = MONSTER_STATE_ATK;
		//_rndFireCount = RND->getFromIntTo(1, 1000);
		switch (monDirect) {
		case MONSTER_DIRECTION_LEFT:
			_monsterImg = IMAGEMANAGER->findImage("�񷽺�������2");
			rc = RectMakeCenter((rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("�񷽺�������2L");
			ANIMATIONMANAGER->start("�񷽺�������2L");
			if (_monsterImg->getFrameX() == _monsterImg->getMaxFrameX())
			{
				_ani = ANIMATIONMANAGER->findAnimation("�񷽺���L");
				ANIMATIONMANAGER->start("�񷽺���L");
			}
			break;
		case MONSTER_DIRECTION_UP:
			_monsterImg = IMAGEMANAGER->findImage("�񷽺�������2");
			rc = RectMakeCenter((rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight() - 50);
			_ani = ANIMATIONMANAGER->findAnimation("�񷽺�������2U");
			ANIMATIONMANAGER->start("�񷽺�������2U");
			break;
		case MONSTER_DIRECTION_RIGHT:
			_monsterImg = IMAGEMANAGER->findImage("�񷽺�������2");
			rc = RectMakeCenter((rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2,
				_monsterImg->getFrameWidth() + 50, _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("�񷽺�������2R");
			ANIMATIONMANAGER->start("�񷽺�������2R");
			break;
		case MONSTER_DIRECTION_DOWN:
			_monsterImg = IMAGEMANAGER->findImage("�񷽺�������2");
			rc = RectMakeCenter((rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight() + 50);
			_ani = ANIMATIONMANAGER->findAnimation("�񷽺�������2B");
			ANIMATIONMANAGER->start("�񷽺�������2B");
			break;
		}
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