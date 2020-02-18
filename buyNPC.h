#pragma once
#include"gameNode.h"
#define PLAYERSPEED 1
#define CAMERASPEED 1

class buyNPC : public gameNode
{
private:
	image * _img;		//�̹���
	animation * _ani;	//�ִ�
	animation * _talkAni;	//��ũ�ִ�
	int _x, _y;			//�߽���ǥ
	RECT _rc;			//�̹��� �簢��
	POINT point;		//������ ������ ��ġ
	bool isLeft;
	bool isRight;
	bool isUp;
	bool isDown;
	int itemRndNum;
	bool _move;
	bool isTalk;
	bool isTalking;
	bool isCheap;
	bool isExpensive;
	bool isVeryCheap;
	bool isVeryExpensive;
	image * itemImg;	//�������̹���
	image * talkImg;	//��ũ�̹���
	int playerPrice;	//�÷��̾��
	int oriPrice;		//����
	RECT itemRc;		//�����۷�Ʈ
	RECT talkRc;		//��ũ�̹�����Ʈ
	int talkCount;		//��ũ ī��Ʈ
	int waitCount;		//��ٸ� ī��Ʈ
	int exit;			//�ð��Ǹ� �����
	bool motionChange;	//����̹����ٲ�
	bool talkChange;	//��ũ�̹����ٲ�
	int step;			//0�϶� ��ǰ���� �ɾ. 1�϶� ����. 2�϶� �÷��̾�� �ɾ. 3�϶� ����. 4�϶� ������ ����
	bool isWait;
public:
	RECT _tableRc;
	int num;
	buyNPC();
	~buyNPC();

	HRESULT init(RECT _tableRect);
	void release();
	void update(item& item1, item& item2, item& item3, item& item4);
	void render();
	void aniChange();	//������ ������ ��ġ�� ã�� �̵�
	void talk(item& item1, item& item2, item& item3, item& item4);	//����
	void talking();		//�������
	void soso();
	void cheap();
	void expensive();
	void veryCheap();
	void veryExpensive();
	void wait();
	bool sell();	//�ǸŹ� �ݾ׼���
	int reduceItemNum;
	//get
	int getReduceItemNum() { return reduceItemNum; }
	//set
};

