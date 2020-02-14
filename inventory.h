#pragma once
#include "gameNode.h"
#include "cursor.h"


struct  tagplayerinven
{
	image*_inventoryimg;
	RECT _inventoryrect;
	float x, y;
	bool _isleft;
};

struct taggrab
{
	image* _grabimg;
	RECT _temp;			//����ִ� �κ��丮 ��ҵ��� ��ƺ���
	bool _isopen;		//J�� ���� ���¿��� ������ �� 
};

struct tagshowitem
{
	image* _showitemimg;
	RECT _showitemrc;
};

class inventory :public gameNode
{
private:
	tagplayerinven _playerinventory; //�÷��̾� �κ��丮
	tagplayerinven _removeGlass;		// �������� ������ ��ȯ�ϴ� �̹���
	tagplayerinven  _inventorybg;
	tagplayerinven _invenotryelement[29];				//�κ��丮 ĭ
	tagplayerinven _zbutton;					// z��ư
	tagplayerinven _playerprofile;		//�÷��̾�������
	tagplayerinven _weaponiright;			//������ ��Ȱ ��ȭ z
	tagplayerinven _weaponirighting;	// ������ Ȱ ��ȭ z
	tagplayerinven _weaponileft;			//���� ��Ȱ ��ȭ z
	tagplayerinven _weaponilefting;		//�� ��Ȱ ��ȭ z


	//tagplayerinven _sworleft;

	taggrab _grab;			// �׷�

	tagshowitem   _showitem;

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

	bool _openinventorywin;  //�κ��丮 â�� ���� ���� ��
	bool test;				//������ â�� �̿��ϱ� ���� �Ұ�
	bool _storageOpen;		//������ â�� �̿��ϱ� ���� �Ұ�
	bool _isweapon;			//���� ��ȯ�ϱ� ���� �Ұ�.. �̹����θ�


public:
	inventory();
	~inventory();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void moverender(HDC hdc);			//����ҿ��� ������ ����
	void itemrender(HDC hdc);
	void bkrender(HDC hdc);

	void setOpen(bool open) { _openinventorywin = open; }

	void inventoryItem();					//�κ��丮 ��� �ȿ� ���¸� �˸��� ���� �Լ�
	void cursormove();						//Ŀ�� �̵� ������ 
	void grabmove();							//J�� ������ ���
	void grabitemremove();				//J�� ������ 
	void isweaponing();					//z��ư���� ���� ������ ��ȯ


	vector<item> getvInven() { return _vInven; }			//����  ������ �ִ� ������ 
	vector<item>::iterator getviterInven() { return _viInven; }
	vector<item> getvTemp() { return _vTemp; }


	int getcusornumber() { return _cursorNumber; }

	bool getTest() { return test; }
	void setTest(bool t) { test = t; }

	bool getStorageOpen() { return _storageOpen; }
	void setStprageOpen(bool storageOpen) { _storageOpen = storageOpen; }

	//�ѹ� �ù������� 
	RECT geteRect() { return _cursorrect; }
	void setRect(RECT _rect) { _cursorrect = _rect; }


	//�߰��Ѱ�
	void swapItem(item swapItem);
	void tempClear() {

		_vTemp.clear();
		test = false;
		_cursorNumber = 0;

	}
};
