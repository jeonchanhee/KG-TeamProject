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
	//몬스터 벡터 생성
	vMonster	_vMinion;
	viMonster	_viMinion;
	//총알 벡터 생성
	bullet*		_bullet;
	RECT aRc;

public:
	monsterManager();
	~monsterManager();

	image* _dieImg;
	animation* _aniDead;
	RECT dRc;
	int dCount = 0;			//주금카운트

	HRESULT init();
	void release();
	void update();
	void render();



	//몬스터 생성
	void setMinion();
	//몬스터 공격
	void attackMinion();
	//총알 발사
	//void minionBulletFire();
	//get
	vMonster	getVMonster() { return _vMinion; }
	viMonster	getViMonster() { return _viMinion; }
	//제거
	void removeMinion(int arrNum);
	//충돌
	void collision();

	//void setRocketMemoryLink(rocket* rocket) { _rocket = rocket; }

};

