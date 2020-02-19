#include "stdafx.h"
#include "monsterManager.h"

monsterManager::monsterManager()
{
}


monsterManager::~monsterManager()
{
}
//몬스터 생성 및 배치
//첫번째방
HRESULT monsterManager::init1()
{
	setMinion1();
	_bullet = new bullet;
	_bullet->init("bullet", 1000, 600);
	return S_OK;
}
//두번째방
HRESULT monsterManager::init2()
{

	setMinion2();
	_bullet = new bullet;
	_bullet->init("bullet", 1000, 600);

	return S_OK;
}
//세번째방
HRESULT monsterManager::init3()
{
	setMinion3();
	_bullet = new bullet;
	_bullet->init("bullet", 1000, 600);
	return S_OK;
}
//네번째방
HRESULT monsterManager::init4()
{
	setMinion4();
	_bullet = new bullet;
	_bullet->init("bullet", 1000, 600);
	return S_OK;
}


void monsterManager::release()
{
	SAFE_DELETE(_bullet);
}
//몬스터 업데이트
void monsterManager::update(vector<item> & item)
{
	_viMinion = _vMinion.begin();

	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->update();
	}

	for (int i = 0; i < _vMinion.size(); i++)
	{
		if (_vMinion[i]->getState() == MONSTER_STATE_DEAD)
		{
			dropItem = _vMinion[i]->getItem();
			itemImg = dropItem.getItemInfo().image;
			dropItem.setRect(RectMakeCenter(_vMinion[i]->getCurrentX(), _vMinion[i]->getCurrentY(),
				dropItem.getRECT().right - dropItem.getRECT().left, dropItem.getRECT().bottom - dropItem.getRECT().top));
			dropItem.setMove(true);
			dropItem.setWave(true);
			item.push_back(dropItem);
			removeMinion(i);
		}
	}

	//총알업데이트
	_bullet->update();
	//공격 업데이트
	attackMinion();
	//충돌
	collision();

	//총알발사
	//minionBulletFire();
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
void monsterManager::setMinion1()
{
	for (int i = 0; i < 4; i++)
	{
		monster* slimeGauntlet;
		slimeGauntlet = new slimeGauntletMinion;
		if (i < 2) {
			slimeGauntlet->init("슬라임건틀렛", MONSTER_TYPE_SLIMEGAUNTLET, MONSTER_STATE_ATK, MONSTER_DIRECTION_DOWN, 200 + i * 600, 200, 10, 100, 100, 50, 0);
		}
		else
		{
			slimeGauntlet->init("슬라임건틀렛", MONSTER_TYPE_SLIMEGAUNTLET, MONSTER_STATE_ATK, MONSTER_DIRECTION_DOWN, 200 + (i - 2) * 600, 650, 10, 100, 100, 50, 0);
		}
		_vMinion.push_back(slimeGauntlet);
	}
	for (int i = 0; i < 2; i++)
	{
		monster* slime;
		slime = new slimeMinion;
		slime->init("슬라임", MONSTER_TYPE_SLIME, MONSTER_STATE_MOVE, MONSTER_DIRECTION_DOWN, 200, 200 + i * 100, 10, 100, 100, 50, 0);
		_vMinion.push_back(slime);
	}
}
void monsterManager::setMinion2()
{

	for (int i = 0; i < 3; i++)
	{
		monster* golemTurret;
		golemTurret = new turretMinion;
		golemTurret->init("골렘터렛", MONSTER_TYPE_GOLEMTURRET, MONSTER_STATE_ATK, MONSTER_DIRECTION_LEFT, 300, 250 + i * 150, 10, 100, 100, 50, 0);
		_vMinion.push_back(golemTurret);
	}
	monster* golemSoldier;
	golemSoldier = new soldierMinion;
	golemSoldier->init("골렘솔저", MONSTER_TYPE_GOLEMSOLDIER, MONSTER_STATE_MOVE, MONSTER_DIRECTION_LEFT, 500, 500, 10, 100, 100, 50, 5);
	_vMinion.push_back(golemSoldier);
}
void monsterManager::setMinion3()
{
	for (int i = 0; i < 3; i++)
	{
		monster* flyingGolem;
		flyingGolem = new flyingMinion;
		flyingGolem->init("플라잉골렘", MONSTER_TYPE_FLYINGGOLEM, MONSTER_STATE_MOVE, MONSTER_DIRECTION_DOWN, 550, 200 + i * 100, 10, 100, 100, 50, 0);
		_vMinion.push_back(flyingGolem);
	}
	monster* golemSoldier;
	golemSoldier = new soldierMinion;
	golemSoldier->init("골렘솔저", MONSTER_TYPE_GOLEMSOLDIER, MONSTER_STATE_MOVE, MONSTER_DIRECTION_RIGHT, 500, 500, 10, 100, 100, 50, 5);
	_vMinion.push_back(golemSoldier);
}
void monsterManager::setMinion4()
{
	monster* golemBoss;
	golemBoss = new bossMinion;
	golemBoss->init("골렘보스", MONSTER_TYPE_GOLEMBOSS, MONSTER_STATE_MOVE, MONSTER_DIRECTION_DOWN, 500, 300, 10, 100, 100, 50, 5);
	_vMinion.push_back(golemBoss);
}
//몬스터 공격
void monsterManager::attackMinion()
{
	_viMinion = _vMinion.begin();

	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		//공격시
		//타입 가져옴
		int type = (*_viMinion)->getType();
		//방향 가져옴
		int direct = (*_viMinion)->getDirection();
		int state = (*_viMinion)->getState();
		//골렘터렛 공격시
		if (type == 0 && (*_viMinion)->golemTurretAtk((*_viMinion)->getType(), (*_viMinion)->getDirection()))
		{
			////일직선 발사
			RECT hRc = (*_viMinion)->getHRect();
			//int direct = (*_viMinion)->getDirection();
			switch (direct) {
			case MONSTER_DIRECTION_LEFT:
				_bullet->fire((hRc.left + hRc.right) / 2 - 30, (hRc.bottom + hRc.top) / 2, MONSTER_DIRECTION_LEFT, 7.0f);
				break;
			case MONSTER_DIRECTION_RIGHT:
				_bullet->fire((hRc.left + hRc.right) / 2 + 30, (hRc.bottom + hRc.top) / 2, MONSTER_DIRECTION_RIGHT, 7.0f);
				break;
			case MONSTER_DIRECTION_DOWN:
				_bullet->fire((hRc.left + hRc.right) / 2, (hRc.bottom + hRc.top) / 2 + 30, MONSTER_DIRECTION_DOWN, 7.0f);
				break;
			case MONSTER_DIRECTION_UP:
				_bullet->fire((hRc.left + hRc.right) / 2, (hRc.bottom + hRc.top) / 2 - 30, MONSTER_DIRECTION_UP, 7.0f);
				break;
			}
		}

		//골렘솔저고 공격이 true일때
		if (type == 1 && (*_viMinion)->attack((*_viMinion)->getType(), (*_viMinion)->getDirection()) && state != 1)
		{
			//공격범위RECT생성
			aRc = (*_viMinion)->getARect();

			//(*_viMinion)->golemSoldierAtk((*_viMinion)->getDirection());
		}
		//플라잉골렘 공격이 true일때
		if (type == 2 && (*_viMinion)->attack((*_viMinion)->getType(), (*_viMinion)->getDirection()) && state != 1)
		{
			//공격범위RECT생성
			aRc = (*_viMinion)->getARect();
		}
		//슬라임이고 공격이 true일때
		if (type == 3 && (*_viMinion)->attack((*_viMinion)->getType(), (*_viMinion)->getDirection()) && state != 1)
		{
			//공격범위RECT생성
			aRc = (*_viMinion)->getARect();
		}
		//슬라임건틀렛이고 공격이 true일때
		if (type == 4 && (*_viMinion)->attack((*_viMinion)->getType(), (*_viMinion)->getDirection()) && state != 1)
		{
			//공격범위RECT생성
			aRc = (*_viMinion)->getARect();
		}
		//골렘보스이고 공격이 true일때
		if (type == 5 && (*_viMinion)->attack((*_viMinion)->getType(), (*_viMinion)->getDirection()) && state != 1)
		{
			//공격범위RECT생성
			aRc = (*_viMinion)->getARect();
		}
	}
}

//몬스터 벡터에서 제거
void monsterManager::removeMinion(int arrNum)
{
	_vMinion.erase(_vMinion.begin() + arrNum);
}
//총알충돌
void monsterManager::collision()
{
	//총알벡터와 플레이어 충돌
	for (int i = 0; i < _bullet->getVBullet().size(); i++)
	{
		RECT rc;
		//충돌시
		if (IntersectRect(&rc, &_bullet->getVBullet()[i].rc, &PLAYER->getPlayercollision()))
		{
			_bullet->removeMissile(i);
			PLAYER->setHP(PLAYER->getHP() - 10);
		}
	}
}

