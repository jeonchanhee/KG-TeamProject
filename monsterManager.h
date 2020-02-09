#pragma once
#include"gameNode.h"
#include"minion.h"
#include"turretMinion.h"
#include"soldierMinion.h"
#include"slimeGauntletMinion.h"
#include"bossMinion.h"
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
public:
	monsterManager();
	~monsterManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//���� ����
	void setMinion();
	//���� ����
	void attackMinion();
	//�Ѿ� �߻�
	void minionBulletFire();
	//get
	vMonster	getVMonster() { return _vMinion; }
	viMonster	getViMonster() { return _viMinion; }
	//����
	void removeMinion(int arrNum);
	//�浹
	void collision();

	//void setRocketMemoryLink(rocket* rocket) { _rocket = rocket; }

};

