#include "stdafx.h"
#include "monsterManager.h"

monsterManager::monsterManager()
{
}


monsterManager::~monsterManager()
{
}

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

void monsterManager::update()
{
	_viMinion = _vMinion.begin();

	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
	(*_viMinion)->update();
	}
	//ufo √—æÀ
	_bullet->update();


	collision();

	this->minionBulletFire();
}

void monsterManager::render()
{
	_viMinion = _vMinion.begin();

	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}

	_bullet->render();
}

void monsterManager::setMinion()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			monster* golemTurret;
			golemTurret = new minion;
			golemTurret->init(MONSTER_TYPE_GOLEMTURRET, MONSTER_STATE_ATK, MONSTER_DIRECTION_LEFT, 700, j * 100);
			_vMinion.push_back(golemTurret);
		}
	}
}
//∞Ò∑Ω≈Õ∑ø√—æÀπﬂªÁ
void monsterManager::minionBulletFire()
{
	_viMinion = _vMinion.begin();

	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		if ((*_viMinion)->attack())
		{
			////¿œ¡˜º± πﬂªÁ
			RECT rc = (*_viMinion)->getRect();
			int direct = (*_viMinion)->getDirection();
			switch (direct) {
			case 0:
				_bullet->fire(rc.left, rc.top, PI, 1000.f);
				break;
			case 1:
				_bullet->fire(rc.left, rc.top, 2 * PI, 1000.f);
				break;
			case 2:
				_bullet->fire(rc.left, rc.top, PI, 1000.f);
				break;
			case 3:
				_bullet->fire(rc.left, rc.top, -PI, 1000.f);
				break;
			}


		}
	}
}
//∞Ò∑Ω≈Õ∑ø ∫§≈Õø°º≠ ¡¶∞≈
void monsterManager::removeMinion(int arrNum)
{
	_vMinion.erase(_vMinion.begin() + arrNum);
}
//√Êµπ
void monsterManager::collision()
{
	for (int i = 0; i < _bullet->getVBullet().size(); i++)
	{
		RECT rc;
		//√ÊµπΩ√
		//if (IntersectRect(&rc, &_bullet->getVBullet()[i].rc, &_rocket->getRocketImage()->getBoundingBox()))
		//{
		//	_bullet->removeMissile(i);
		//	_rocket->hitDamage(10);
		//}
	}
}

