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
	float speed;			//�ӵ�
	int direct;				//����
	bool fire;				//�߻翩��
	int count;				//ī��Ʈ

};


enum WEAPONMOVE   //�÷��̾ ����� ȭ�칫��
{
	ARROW_LEFT,
	ARROW_RIGHT,
	ARROW_UP,
	ARROW_DOWN,
};

struct tagweapon			 //�÷��̾ ����� ȭ�� ����
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
	void fire(float x, float y, int direct, float speed);
	//�̵�
	void move();

	//�Ѿ� ����
	void removeMissile(int arrNum);
	//�Ѿ� �����ϴ� �Լ�
	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }



};

//===============================================================
//													�÷��̾ ����� ũ���� 
//===============================================================


class weapons : public gameNode // �÷��̾  ����ϴ� ȭ��
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


	void fire(float x, float y, WEAPONMOVE weponMove);
	void move();


	vector<tagweapon> getvarrow() { return _varrow; }
	vector<tagweapon>::iterator  getviterarrow() { return _viterarrow; }

	//RECT getarrowRect() { return _viterarrow[0]._rc; }   // ȭ�� 

};


