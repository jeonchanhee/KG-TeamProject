#pragma once
#include"gameNode.h"
#include"minion.h"
#include"turretMinion.h"
#include"soldierMinion.h"
#include"slimeGauntletMinion.h"
#include"slimeMinion.h"
#include"bossMinion.h"
#include"flyingMinion.h"
#include"bullet.h"

class monsterManager : public gameNode
{
private:

	typedef vector<monster*> vMonster;
	typedef vector<monster*>::iterator viMonster;

private:
	//���� ���� ����
	vMonster	_vMinion;
	viMonster	_viMinion;
	//�Ѿ� ���� ����
	bullet*		_bullet;
	RECT aRc;
	item dropItem;
	image * itemImg;
	int num;

public:
	monsterManager();
	~monsterManager();

	HRESULT init1();
	HRESULT init2();
	HRESULT init3();
	HRESULT init4();
	void release();
	void update(vector<item> & item);
	void render();

	//���� ����
	void setMinion1();
	void setMinion2();
	void setMinion3();
	void setMinion4();
	//���� ����
	void attackMinion();
	//�Ѿ� �߻�
	//void minionBulletFire();
	//get
	vMonster	getVMonster() { return _vMinion; }
	viMonster	getViMonster() { return _viMinion; }

	//void setDropItem(item _item) { dropItem = _item; }
	//����
	void removeMinion(int arrNum);
	//�浹
	void collision();
	//void setRocketMemoryLink(rocket* rocket) { _rocket = rocket; }

};

