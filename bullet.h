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
	float angle;			//각도
	float speed;			//속도
	bool fire;				//발사여부
	int count;				//카운트

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
	void fire(float x, float y, float angle, float speed);
	//이동
	void move();

	//총알 제거
	void removeMissile(int arrNum);
	//총알 구별하는 함수
	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }



};
