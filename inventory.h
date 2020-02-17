#pragma once
#include "gameNode.h"
#include "cursor.h"

//������ ����
enum ITEMKIND
{
	ITEM_STORGE,												 	//�κ��丮(�����)�� ���̴� �� 
	ITEM_EQUOMENT,										 	//�κ��丮 ���(����, ����)
	ITEM_GARBAGE											 	//������ ��
};
//�κ��丮 ���� 					
struct  tagplayerinven
{
	ITEMKIND _itemkind;									 	//������ ���� 
	image*_inventoryimg;
	RECT _inventoryrect;
	item _item;
	float x, y;
	//bool _isleft;													//-->�κ��丮(�÷��̾��) �Ǵ� â��븸 ���̴��� ��Ÿ���� ����
};

//������ �̹��� 
struct taginvenimg
{
	image* _invenimg;
	RECT _inventoryrc;
	float x, y;

};
//�׷� ����
struct taggrab
{
	image* _grabimg;
	RECT _temp;														//����ִ� �κ��丮 ��ҵ��� ��ƺ���
	bool _isopen;													//J�� ���� ���¿��� ������ �� 
};
//�����ֱ�� ����
struct tagshowitem
{
	image* _showitemimg;
	RECT _showitemrc;
};

class inventory :public gameNode
{
private:
	image* _bgimag;												 // ���ķ��� ó���� ���ȭ��
	tagplayerinven _playerinventory;					//�÷��̾� �κ��丮
	tagplayerinven _removeGlass;						// �������� ������ ��ȯ�ϴ� �̹���
	tagplayerinven  _inventorybg;						//�κ��丮(�÷��̿�) & �κ��丮(â���)
	tagplayerinven _inventoryelement;				//�κ��丮 ĭ
	tagplayerinven _zbutton;								// z��ư
	tagplayerinven _playerprofile;						//�÷��̾�������
	tagplayerinven _weaponiright;						//������ ��Ȱ ��ȭ z
	tagplayerinven _weaponirighting;				// ������ Ȱ ��ȭ z
	tagplayerinven _weaponileft;						//���� ��Ȱ ��ȭ z
	tagplayerinven _weaponilefting;					//�� ��Ȱ ��ȭ z



	taggrab _grab;													// �׷�(�ӽú��� �̹���)
	tagshowitem   _showitem;								//������ ���ִ� �̹���

	//Ŀ��
	cursor* _cursor;												// �κ��丮 ���콺
	RECT _cursorrect;
	int _cursorNumber;


	//������ ���� ���� 
	vector< tagplayerinven> _vInven;
	vector< tagplayerinven>::iterator _viInven;


	RECT _temp;
	vector<tagplayerinven> _vTemp;					//�ӽ÷� ���� ����



	bool _openinventorywin;								//�κ��丮 â�� ���� ���� ��
	bool test;															//������ â�� �̿��ϱ� ���� �Ұ�
	bool _storageOpen;											//������ â�� �̿��ϱ� ���� �Ұ�
	bool _storageusing;											//������ â�� �̿��ϱ� ���� �Ұ�
	bool _isweapon;												//���� ��ȯ�ϱ� ���� �Ұ�.. �̹����θ�


public:
	inventory();
	~inventory();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void moverender(HDC hdc);								//����ҿ��� ������ ����
	void itemrender(HDC hdc);
	void bkrender(HDC hdc);

	bool getOpen() { return _openinventorywin; }

	void inventoryItem();					//�κ��丮 ��� �ȿ� ���¸� �˸��� ���� �Լ�
	void cursormove();						//Ŀ�� �̵� ������ 
	void grabmove();							//J�� ������ ���
	void grabitemremove();				//J�� ������ 
	void isweaponing();					//z��ư���� ���� ������ ��ȯ
	void resetelement();											//�������ִ� �Լ�
	void getitem(string _stritem);						   //������ �Ա� ��, �����̳� �������� ������ֽñ� �ٶ� (�ϴ� ����� ����� ���� ��...)

	vector<tagplayerinven> getvInven() { return _vInven; }											//����  ������ �ִ� ������ 
	vector<tagplayerinven>::iterator getviterInven() { return _viInven; }
	vector<tagplayerinven> getvTemp() { return _vTemp; }

	int getcusornumber() { return _cursorNumber; }

	bool getstorgeuding() { return _storageusing; }											//�κ��丮(â���)
	void setstorgeuding(bool _using) { _storageusing = _using; }					//�κ��丮(â���) �Ѿ�� ���� �Լ�

	bool getStorageOpen() { return _storageOpen; }
	void setStprageOpen(bool storageOpen) { _storageOpen = storageOpen; }

	//�ѹ� �ù������� 
	RECT geteRect() { return _cursorrect; }
	void setRect(RECT _rect) { _cursorrect = _rect; }

	void setOpen(bool open) { _openinventorywin = open; }

	//�߰��Ѱ�
  void swapItem(item swapItem);
	void tempClear() {
		_vTemp.clear();
		test = false;
		_cursorNumber = 0;
	}
};
