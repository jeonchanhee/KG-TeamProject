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

	setMinion();
	//_dieImg = IMAGEMANAGER->findImage("��������");
	//dRc = RectMakeCenter(300, 400, _dieImg->getFrameWidth(), _dieImg->getFrameHeight());
	_bullet = new bullet;
	_bullet->init("bullet", 1000, 600);

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

	for (int i = 0; i < _vMinion.size(); i++)
	{
		if (_vMinion[i]->getCurrentHp() <= 0)removeMinion(i);
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
	//_dieImg->aniRender(getMemDC(), dRc.left, dRc.top, _aniDead);
}
//���� ��ġ
void monsterManager::setMinion()
{

	for (int i = 0; i < 2; i++)
	{
		monster* golemTurret;
		golemTurret = new turretMinion;
		golemTurret->init("���ͷ�", MONSTER_TYPE_GOLEMTURRET, MONSTER_STATE_ATK, MONSTER_DIRECTION_LEFT, 700, 200 + i * 100, 10, 100, 100, 50, 0);
		_vMinion.push_back(golemTurret);
	}
	for (int i = 0; i < 2; i++)
	{
		monster* golemSoldier;
		golemSoldier = new soldierMinion;
		golemSoldier->init("�񷽼���", MONSTER_TYPE_GOLEMSOLDIER, MONSTER_STATE_MOVE, MONSTER_DIRECTION_LEFT, 500, 200 + i * 100, 10, 100, 100, 50, 5);
		_vMinion.push_back(golemSoldier);
	}
	for (int i = 0; i < 2; i++)
	{
		monster* slimeGauntlet;
		slimeGauntlet = new slimeGauntletMinion;
		slimeGauntlet->init("�����Ӱ�Ʋ��", MONSTER_TYPE_SLIMEGAUNTLET, MONSTER_STATE_ATK, MONSTER_DIRECTION_DOWN, 300, 200 + i * 100, 10, 100, 100, 50, 0);
		_vMinion.push_back(slimeGauntlet);
	}
	for (int i = 0; i < 1; i++)
	{
		monster* golemBoss;
		golemBoss = new bossMinion;
		golemBoss->init("�񷽺���", MONSTER_TYPE_GOLEMBOSS, MONSTER_STATE_MOVE, MONSTER_DIRECTION_RIGHT, 100, 200 + i * 100, 10, 100, 100, 50, 5);
		_vMinion.push_back(golemBoss);
	}
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

		//���ͷ� ���ݽ�
		if (type == 0 && (*_viMinion)->golemTurretAtk((*_viMinion)->getType(), (*_viMinion)->getDirection()))
		{
			////������ �߻�
			RECT hRc = (*_viMinion)->getHRect();
			int direct = (*_viMinion)->getDirection();
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
		if (type == 1 && (*_viMinion)->attack((*_viMinion)->getType(), (*_viMinion)->getDirection()))
		{
			//���ݹ���RECT����
			aRc = (*_viMinion)->getARect();

			//(*_viMinion)->golemSoldierAtk((*_viMinion)->getDirection());
		}
		//�����Ӱ�Ʋ���̰� ������ true�϶�
		if (type == 4 && (*_viMinion)->attack((*_viMinion)->getType(), (*_viMinion)->getDirection()))
		{
			//���ݹ���RECT����
			aRc = (*_viMinion)->getARect();
			RECT rc;
			if (IntersectRect(&rc, &aRc, &PLAYER->getPlayercollision()))
			{
				PLAYER->setHP(PLAYER->getHP() - 10);
			}
		}
		//�񷽺����̰� ������ true�϶�
		if (type == 5 && (*_viMinion)->attack((*_viMinion)->getType(), (*_viMinion)->getDirection()))
		{
			//���ݹ���RECT����
			aRc = (*_viMinion)->getARect();
			RECT rc;
			if (IntersectRect(&rc, &aRc, &PLAYER->getPlayercollision()))
			{
				PLAYER->setHP(PLAYER->getHP() - 10);
			}

		}
	}
}

//���� ���Ϳ��� ����
void monsterManager::removeMinion(int arrNum)
{
	//MONSTER_TYPE type = (*_viMinion)->getType();
	//if ((*_viMinion)->die(type)) {
	//	_vMinion.erase(_vMinion.begin() + arrNum);
	//}
	_vMinion.erase(_vMinion.begin() + arrNum);

	//_aniDead = ANIMATIONMANAGER->findAnimation("�����ֱ�");
	//ANIMATIONMANAGER->start("�����ֱ�");
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

