#include "stdafx.h"
#include "monsterManager.h"

monsterManager::monsterManager()
{
}


monsterManager::~monsterManager()
{
}
//몬스터 생성 및 배치
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
//몬스터 업데이트
void monsterManager::update()
{
	_viMinion = _vMinion.begin();
	
	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
	(*_viMinion)->update();
	}
	//총알업데이트
	_bullet->update();

	//충돌
	collision();
	//총알발사
	this->minionBulletFire();
}
//몬스터 랜더
void monsterManager::render()
{
	
	_viMinion = _vMinion.begin();

	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}
	//총알 랜더
	_bullet->render();
}
//몬스터 배치
void monsterManager::setMinion()
{
	
	for (int i = 0; i < 3; i++)
	{
		monster* golemTurret;
		golemTurret = new turretMinion;
		golemTurret->init(MONSTER_TYPE_GOLEMTURRET, MONSTER_STATE_ATK, MONSTER_DIRECTION_DOWN, 700, 200+i * 100);
		_vMinion.push_back(golemTurret);
	}
	for (int i = 0; i < 3; i++)
	{
		monster* golemSoldier;
		golemSoldier = new soldierMinion;
		golemSoldier->init(MONSTER_TYPE_GOLEMSOLDIER, MONSTER_STATE_IDLE, MONSTER_DIRECTION_DOWN, 600, 200 + i * 100);
		_vMinion.push_back(golemSoldier);
	}
	for (int i = 0; i < 3; i++)
	{
		monster* slimeGauntlet;
		slimeGauntlet = new slimeGauntletMinion;
		slimeGauntlet->init(MONSTER_TYPE_SLIMEGAUNTLET, MONSTER_STATE_IDLE, MONSTER_DIRECTION_DOWN, 500, 200 + i * 100);
		_vMinion.push_back(slimeGauntlet);
	}
	for (int i = 0; i < 3; i++)
	{
		monster* golemBoss;
		golemBoss = new bossMinion;
		golemBoss->init(MONSTER_TYPE_GOLEMBOSS, MONSTER_STATE_IDLE, MONSTER_DIRECTION_DOWN, 400, 200 + i * 100);
		_vMinion.push_back(golemBoss);
	}
}
//골렘터렛총알발사
void monsterManager::minionBulletFire()
{
	_viMinion = _vMinion.begin();

	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		//공격시
		int type = (*_viMinion)->getType();
		if (type==0&&(*_viMinion)->golemTurretAtk())
		{
			////일직선 발사
			RECT rc = (*_viMinion)->getRect();
			int direct = (*_viMinion)->getDirection();
			switch (direct) {
			case MONSTER_DIRECTION_LEFT:
				_bullet->fire((rc.left+rc.right)/2 - 30 , (rc.bottom+rc.top)/2, PI, 500.f);
				break;
			case MONSTER_DIRECTION_RIGHT:
				_bullet->fire((rc.left + rc.right) / 2 + 30 , (rc.bottom + rc.top) / 2, 2 * PI, 500.f);
				break;
			case MONSTER_DIRECTION_DOWN:
				_bullet->fire((rc.left + rc.right) / 2 , (rc.bottom + rc.top) / 2 + 30, -PI_2, 500.f);
				break;
			case MONSTER_DIRECTION_UP:
				_bullet->fire((rc.left + rc.right) / 2 , (rc.bottom + rc.top) / 2 - 30, PI_2, 500.f);
				break;
			}
		}
	}
}
//몬스터 벡터에서 제거
void monsterManager::removeMinion(int arrNum)
{
	_vMinion.erase(_vMinion.begin() + arrNum);
}
//충돌
void monsterManager::collision()
{
	for (int i = 0; i < _bullet->getVBullet().size(); i++)
	{
		RECT rc;
		//충돌시
		//if (IntersectRect(&rc, &_bullet->getVBullet()[i].rc, &_rocket->getRocketImage()->getBoundingBox()))
		//{
		//	_bullet->removeMissile(i);
		//	_rocket->hitDamage(10);
		//}
	}
}

