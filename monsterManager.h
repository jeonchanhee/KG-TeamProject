#pragma once
#include"gameNode.h"
#include"minion.h"
#include"bullet.h"

class monsterManager : public gameNode
{
private:

	typedef vector<monster*> vMonster;
	typedef vector<monster*>::iterator viMonster;

private:
	vMonster	_vMinion;
	viMonster	_viMinion;
	bullet*		_bullet;
public:
	monsterManager();
	~monsterManager();

	HRESULT init();
	void release();
	void update();
	void render();


	void setMinion();
	void minionBulletFire();

	vMonster	getVMonster() { return _vMinion; }
	viMonster	getViMonster() { return _viMinion; }

	void removeMinion(int arrNum);

	void collision();

	//void setRocketMemoryLink(rocket* rocket) { _rocket = rocket; }

};

