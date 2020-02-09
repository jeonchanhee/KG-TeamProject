#include "stdafx.h"
#include "monsterManager.h"

monsterManager::monsterManager()
{
}


monsterManager::~monsterManager()
{
}
//���� ���� �� ��ġ
HRESULT monsterManager::init()
{

	this->setMinion();

	_bullet = new bullet;
	_bullet->init("bullet", 10, 600);

	return S_OK;
}

void monsterManager::release()
{
	SAFE_DELETE(_bullet);
}
//���� ������Ʈ
void monsterManager::update()
{
	_viMinion = _vMinion.begin();

	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->update();
	}
	//�Ѿ˾�����Ʈ
	_bullet->update();
	//���� ������Ʈ
	this->attackMinion();
	//�浹
	collision();
	//�Ѿ˹߻�
	this->minionBulletFire();
}
//���� ����
void monsterManager::render()
{

	_viMinion = _vMinion.begin();

	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}
	//�Ѿ� ����
	_bullet->render();
}
//���� ��ġ
void monsterManager::setMinion()
{

	for (int i = 0; i < 2; i++)
	{
		monster* golemTurret;
		golemTurret = new turretMinion;
		golemTurret->init(MONSTER_TYPE_GOLEMTURRET, MONSTER_STATE_ATK, MONSTER_DIRECTION_LEFT, 700, 200 + i * 100);
		_vMinion.push_back(golemTurret);
	}
	for (int i = 0; i < 2; i++)
	{
		monster* golemSoldier;
		golemSoldier = new soldierMinion;
		golemSoldier->init(MONSTER_TYPE_GOLEMSOLDIER, MONSTER_STATE_ATK, MONSTER_DIRECTION_DOWN, 500, 200 + i * 100);
		_vMinion.push_back(golemSoldier);
	}
	for (int i = 0; i < 2; i++)
	{
		monster* slimeGauntlet;
		slimeGauntlet = new slimeGauntletMinion;
		slimeGauntlet->init(MONSTER_TYPE_SLIMEGAUNTLET, MONSTER_STATE_ATK, MONSTER_DIRECTION_DOWN, 300, 200 + i * 100);
		_vMinion.push_back(slimeGauntlet);
	}
	for (int i = 0; i < 2; i++)
	{
		monster* golemBoss;
		golemBoss = new bossMinion;
		golemBoss->init(MONSTER_TYPE_GOLEMBOSS, MONSTER_STATE_ATK, MONSTER_DIRECTION_RIGHT, 100, 200 + i * 100);
		_vMinion.push_back(golemBoss);
	}
}

void monsterManager::attackMinion()
{
	_viMinion = _vMinion.begin();

	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		//���ݽ�
		//Ÿ�� ������
		int type = (*_viMinion)->getType();
		//���� ������
		int direct = (*_viMinion)->getDirection();
		//���̰� ������ true�϶�
		if (type == 1 && (*_viMinion)->attack((*_viMinion)->getType(), (*_viMinion)->getDirection()))
		{
			RECT rc = (*_viMinion)->getRect();
			//(*_viMinion)->golemSoldierAtk((*_viMinion)->getDirection());
		}
		//�����Ӱ�Ʋ���̰� ������ true�϶�
		if (type == 4 && (*_viMinion)->attack((*_viMinion)->getType(), (*_viMinion)->getDirection()))
		{
			RECT rc = (*_viMinion)->getRect();
		}
		//�񷽺����̰� ������ true�϶�
		if (type == 5 && (*_viMinion)->attack((*_viMinion)->getType(), (*_viMinion)->getDirection()))
		{
			RECT rc = (*_viMinion)->getRect();

		}
	}
}

//���ͷ��Ѿ˹߻�
void monsterManager::minionBulletFire()
{

	_viMinion = _vMinion.begin();

	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		//���� Ÿ���� 0(���ͷ�)�̸� �����Լ��� �����Ҷ� �̻����� �߻�
		int type = (*_viMinion)->getType();
		if (type == 0 && (*_viMinion)->golemTurretAtk())
		{
			////������ �߻�
			RECT rc = (*_viMinion)->getRect();
			int direct = (*_viMinion)->getDirection();
			switch (direct) {
			case MONSTER_DIRECTION_LEFT:
				_bullet->fire((rc.left + rc.right) / 2 - 30, (rc.bottom + rc.top) / 2, PI, 500.f);
				break;
			case MONSTER_DIRECTION_RIGHT:
				_bullet->fire((rc.left + rc.right) / 2 + 30, (rc.bottom + rc.top) / 2, 2 * PI, 500.f);
				break;
			case MONSTER_DIRECTION_DOWN:
				_bullet->fire((rc.left + rc.right) / 2, (rc.bottom + rc.top) / 2 + 30, -PI_2, 500.f);
				break;
			case MONSTER_DIRECTION_UP:
				_bullet->fire((rc.left + rc.right) / 2, (rc.bottom + rc.top) / 2 - 30, PI_2, 500.f);
				break;
			}
		}
	}
}
//���� ���Ϳ��� ����
void monsterManager::removeMinion(int arrNum)
{
	_vMinion.erase(_vMinion.begin() + arrNum);
}
//�浹
void monsterManager::collision()
{
	for (int i = 0; i < _bullet->getVBullet().size(); i++)
	{
		RECT rc;
		//�浹��
		//if (IntersectRect(&rc, &_bullet->getVBullet()[i].rc, &_rocket->getRocketImage()->getBoundingBox()))
		//{
		//	_bullet->removeMissile(i);
		//	_rocket->hitDamage(10);
		//}
	}
}

