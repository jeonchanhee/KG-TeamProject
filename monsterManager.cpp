#include "stdafx.h"
#include "monsterManager.h"

monsterManager::monsterManager()
{
}


monsterManager::~monsterManager()
{
}
//���� ���� �� ��ġ
//ù��°��
HRESULT monsterManager::init1()
{
	setMinion1();
	_bullet = new bullet;
	_bullet->init("bullet", 1000, 600);
	return S_OK;
}
//�ι�°��
HRESULT monsterManager::init2()
{

	setMinion2();
	_bullet = new bullet;
	_bullet->init("bullet", 1000, 600);

	return S_OK;
}
//����°��
HRESULT monsterManager::init3()
{
	setMinion3();
	_bullet = new bullet;
	_bullet->init("bullet", 1000, 600);
	return S_OK;
}
//�׹�°��
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
//���� ������Ʈ
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

	//�Ѿ˾�����Ʈ
	_bullet->update();
	//���� ������Ʈ
	attackMinion();
	//�浹
	collision();

	//�Ѿ˹߻�
	//minionBulletFire();
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
void monsterManager::setMinion1()
{
	for (int i = 0; i < 4; i++)
	{
		monster* slimeGauntlet;
		slimeGauntlet = new slimeGauntletMinion;
		if (i < 2) {
			slimeGauntlet->init("�����Ӱ�Ʋ��", MONSTER_TYPE_SLIMEGAUNTLET, MONSTER_STATE_ATK, MONSTER_DIRECTION_DOWN, 200 + i * 600, 200, 10, 100, 100, 50, 0);
		}
		else
		{
			slimeGauntlet->init("�����Ӱ�Ʋ��", MONSTER_TYPE_SLIMEGAUNTLET, MONSTER_STATE_ATK, MONSTER_DIRECTION_DOWN, 200 + (i - 2) * 600, 650, 10, 100, 100, 50, 0);
		}
		_vMinion.push_back(slimeGauntlet);
	}
	for (int i = 0; i < 2; i++)
	{
		monster* slime;
		slime = new slimeMinion;
		slime->init("������", MONSTER_TYPE_SLIME, MONSTER_STATE_MOVE, MONSTER_DIRECTION_DOWN, 200, 200 + i * 100, 10, 100, 100, 50, 0);
		_vMinion.push_back(slime);
	}
}
void monsterManager::setMinion2()
{

	for (int i = 0; i < 4; i++)
	{
		monster* golemTurret;
		golemTurret = new turretMinion;
		golemTurret->init("���ͷ�", MONSTER_TYPE_GOLEMTURRET, MONSTER_STATE_ATK, MONSTER_DIRECTION_LEFT, 700, 100 + i * 200, 10, 100, 100, 50, 0);
		_vMinion.push_back(golemTurret);
	}
	monster* golemSoldier;
	golemSoldier = new soldierMinion;
	golemSoldier->init("�񷽼���", MONSTER_TYPE_GOLEMSOLDIER, MONSTER_STATE_MOVE, MONSTER_DIRECTION_LEFT, 500, 500, 10, 100, 100, 50, 5);
	_vMinion.push_back(golemSoldier);
}
void monsterManager::setMinion3()
{
	for (int i = 0; i < 3; i++)
	{
		monster* flyingGolem;
		flyingGolem = new flyingMinion;
		flyingGolem->init("�ö��װ�", MONSTER_TYPE_FLYINGGOLEM, MONSTER_STATE_MOVE, MONSTER_DIRECTION_DOWN, 200, 200 + i * 100, 10, 100, 100, 50, 0);
		_vMinion.push_back(flyingGolem);
	}
	monster* golemSoldier;
	golemSoldier = new soldierMinion;
	golemSoldier->init("�񷽼���", MONSTER_TYPE_GOLEMSOLDIER, MONSTER_STATE_MOVE, MONSTER_DIRECTION_RIGHT, 500, 500, 10, 100, 100, 50, 5);
	_vMinion.push_back(golemSoldier);
}
void monsterManager::setMinion4()
{
	monster* golemBoss;
	golemBoss = new bossMinion;
	golemBoss->init("�񷽺���", MONSTER_TYPE_GOLEMBOSS, MONSTER_STATE_MOVE, MONSTER_DIRECTION_DOWN, 500, 500, 10, 100, 100, 50, 5);
	_vMinion.push_back(golemBoss);
}
//���� ����
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
		int state = (*_viMinion)->getState();
		//���ͷ� ���ݽ�
		if (type == 0 && (*_viMinion)->golemTurretAtk((*_viMinion)->getType(), (*_viMinion)->getDirection()))
		{
			////������ �߻�
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

		//�񷽼����� ������ true�϶�
		if (type == 1 && (*_viMinion)->attack((*_viMinion)->getType(), (*_viMinion)->getDirection()) && state != 1)
		{
			//���ݹ���RECT����
			aRc = (*_viMinion)->getARect();

			//(*_viMinion)->golemSoldierAtk((*_viMinion)->getDirection());
		}
		//�ö��װ� ������ true�϶�
		if (type == 2 && (*_viMinion)->attack((*_viMinion)->getType(), (*_viMinion)->getDirection()) && state != 1)
		{
			//���ݹ���RECT����
			aRc = (*_viMinion)->getARect();
		}
		//�������̰� ������ true�϶�
		if (type == 3 && (*_viMinion)->attack((*_viMinion)->getType(), (*_viMinion)->getDirection()) && state != 1)
		{
			//���ݹ���RECT����
			aRc = (*_viMinion)->getARect();
		}
		//�����Ӱ�Ʋ���̰� ������ true�϶�
		if (type == 4 && (*_viMinion)->attack((*_viMinion)->getType(), (*_viMinion)->getDirection()) && state != 1)
		{
			//���ݹ���RECT����
			aRc = (*_viMinion)->getARect();
		}
		//�񷽺����̰� ������ true�϶�
		if (type == 5 && (*_viMinion)->attack((*_viMinion)->getType(), (*_viMinion)->getDirection()) && state != 1)
		{
			//���ݹ���RECT����
			aRc = (*_viMinion)->getARect();
		}
	}
}

//���� ���Ϳ��� ����
void monsterManager::removeMinion(int arrNum)
{
	_vMinion.erase(_vMinion.begin() + arrNum);
}
//�Ѿ��浹
void monsterManager::collision()
{
	//�Ѿ˺��Ϳ� �÷��̾� �浹
	for (int i = 0; i < _bullet->getVBullet().size(); i++)
	{
		RECT rc;
		//�浹��
		if (IntersectRect(&rc, &_bullet->getVBullet()[i].rc, &PLAYER->getPlayercollision()))
		{
			_bullet->removeMissile(i);
			PLAYER->setHP(PLAYER->getHP() - 10);
		}
	}
}

