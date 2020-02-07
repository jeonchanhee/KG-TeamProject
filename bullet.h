#pragma once
#include"gameNode.h"
//���ͷ� �̻��� ����ü
struct tagBullet
{
	image* bulletImage;		//�̹���
	animation* bulletAni;	//�������̹���
	RECT rc;				//�Ѿ˹���
	float x, y;				//��ǥ
	float fireX, fireY;		//�߻���ġ
	float radius;			//����
	float angle;			//����
	float speed;			//�ӵ�
	bool fire;				//�߻翩��
	int count;				//ī��Ʈ

};

class bullet :public gameNode
{
private:
	//�Ѿ˺��� ����
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	//�̹��� �̸�
	const char* _imageName;
	//����
	float _range;
	//�Ѿ˰���
	int _bulletMax;

public:
	bullet();
	~bullet();

	HRESULT init(char* imageName, int bulletMax, float range);
	void release();
	void update();
	void render();
	//�߻�
	void fire(float x, float y, float angle, float speed);
	//�̵�
	void move();

	//�Ѿ� ����
	void removeMissile(int arrNum);
	//�Ѿ� �����ϴ� �Լ�
	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }



};
