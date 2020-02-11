#pragma once
#include "gameNode.h"
#include "cursor.h"


struct  tagplayerinven
{
	image*_inventoryimg;
	RECT _inventoryrect;

	float x, y;
};

struct taggrab
{
	image* _grabimg;
	RECT _temp;			//����ִ� �κ��丮 ��ҵ��� ��ƺ���
	bool _isopen;		//J�� ���� ���¿��� ������ �� 
};


class inventory :public gameNode
{
private:
	tagplayerinven _playerinventory; //�÷��̾� �κ��丮
	tagplayerinven _moneyicon;		//��������
	tagplayerinven _removeGlass;		// �������� ������ ��ȯ�ϴ� �̹���
	tagplayerinven _invenotryelement[21];				//�κ��丮 ĭ
	tagplayerinven _playerprofile;		//�÷��̾�������

	taggrab _grab;			// �׷�

	//Ŀ��
	cursor* _cursor;		// �κ��丮 ���콺
	RECT _cursorrect;
	int _cursorNumber;

	image* _bgimag;	 // ���ķ��� ó���� ���ȭ��

	//������ ���� ���� 
	vector<item> _vInven;
	vector<item>::iterator _viInven;

	item _item;			//������	

	RECT _temp;
	vector<item> _vTemp;				//�ӽ÷� ���� ����

	int _itemcount;					// 'J'�� ������ŭ �������� �ű�� �� 
	int money;

	bool _openinventorywin;  //�κ��丮 â�� ���� ���� ��

public:
	inventory();
	~inventory();

	HRESULT init();
	void release();
	void update();
	void render();
	void itemrender();

	void setOpen(bool open) { _openinventorywin = open; }

	void moneyitem();		// �������� ���� �ٲٴ� �Լ�
	void inventoryItem();   //�κ��丮 ��� �ȿ� ���¸� �˸��� ���� �Լ�
	void cursormove();			//Ŀ�� �̵� ������ 
	void grabmove();
};
