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
	
	for (int i = 0; i < 3; i++)
	{
		monster* golemTurret;
		golemTurret = new minion;
		golemTurret->init(MONSTER_TYPE_GOLEMTURRET, MONSTER_STATE_ATK, MONSTER_DIRECTION_LEFT, 700, 200+i * 100);
		_vMinion.push_back(golemTurret);
	}
}
//���ͷ��Ѿ˹߻�
void monsterManager::minionBulletFire()
{
	_viMinion = _vMinion.begin();

	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		//���ݽ�
		if ((*_viMinion)->attack())
		{
			////������ �߻�
			RECT rc = (*_viMinion)->getRect();
			int direct = (*_viMinion)->getDirection();
			switch (direct) {
			case 0:
				_bullet->fire((rc.left+rc.right)/2 - 30 , (rc.bottom+rc.top)/2, PI, 500.f);
				break;
			case 1:
				_bullet->fire((rc.left + rc.right) / 2 + 30 , (rc.bottom + rc.top) / 2, 2 * PI, 500.f);
				break;
			case 2:
				_bullet->fire((rc.left + rc.right) / 2 , (rc.bottom + rc.top) / 2 - 30, PI_2, 500.f);
				break;
			case 3:
				_bullet->fire((rc.left + rc.right) / 2 , (rc.bottom + rc.top) / 2 + 30, -PI_2, 500.f);
				break;
			}


		}
	}
}
//���ͷ� ���Ϳ��� ����
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

