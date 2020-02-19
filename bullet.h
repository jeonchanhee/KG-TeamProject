#pragma once
#include"gameNode.h"
//골렘터렛 미사일 구조체
struct tagBullet
{
	image* bulletImage;		//이미지
	animation* bulletAni;	//프레임이미지
	RECT rc;				//총알범위
	float x, y;				//좌표
	float fireX, fireY;		//발사위치
	float radius;			//지름
	float speed;			//속도
	int direct;				//방향
	bool fire;				//발사여부
	int count;				//카운트

};


enum WEAPONMOVE   //플레이어가 사용할 화살무브
{
	ARROW_LEFT,
	ARROW_RIGHT,
	ARROW_UP,
	ARROW_DOWN,
};

struct tagweapon			 //플레이어가 사용할 화살 정보
{
	WEAPONMOVE _arrow;
	image* _waponimg;
	RECT _rc;
	float  fireX, fireY;
	float x, y;
	float _spped;
	bool _isfire;
};




class bullet :public gameNode
{
private:
	//총알벡터 선언
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	//이미지 이름
	const char* _imageName;
	//범위
	float _range;
	//총알갯수
	int _bulletMax;

public:
	bullet();
	~bullet();

	HRESULT init(char* imageName, int bulletMax, float range);
	void release();
	void update();
	void render();
	//발사
	void fire(float x, float y, int direct, float speed);
	//이동
	void move();

	//총알 제거
	void removeMissile(int arrNum);
	//총알 구별하는 함수
	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }



};

//===============================================================
//													플레이어가 사용할 크랠스 
//===============================================================


class weapons : public gameNode // 플레이어만  사용하는 화살
{
private:

	//tagweapon _arrow;
	vector<tagweapon> _varrow;
	vector<tagweapon>::iterator  _viterarrow;

	tagweapon _arrow;


private:
	float _range;

public:
	weapons();
	~weapons();

	HRESULT init();
	void release();
	void update();
	void render();
	void remove(int num);


	void fire(float x, float y, WEAPONMOVE weponMove);
	void move();


	vector<tagweapon> getvarrow() { return _varrow; }
	vector<tagweapon>::iterator  getviterarrow() { return _viterarrow; }
};


class Catapultbow : public gameNode
{
private:
	float _range;
	tagweapon _catapult;
	vector<tagweapon> _catapultarrpw;
	vector<tagweapon>::iterator  _itercatapultarrpw;
public:
	Catapultbow();
	~Catapultbow();

	HRESULT init();
	void release();
	void update();
	void render();

	void fire(float x, float y, WEAPONMOVE weponMove);
	void move();

	vector<tagweapon> getcataarrow() { return _catapultarrpw; }
	vector<tagweapon>::iterator  getcataiterarrow() { return _itercatapultarrpw; }

	RECT getcataarrowRect() { return _itercatapultarrpw->_rc; }   // 화살 
};
