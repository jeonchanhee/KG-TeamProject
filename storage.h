#pragma once
#include"gameNode.h"
#include "cursor.h"

#define SLOTNUM 28
struct slot
{
	image* img;
	RECT   rc;
	item   item;
	float  x, y;
};

class storage : public gameNode
{
private:

	string _name;
	image* _boxImg;					//�����̹���
	RECT _boxRc;					//���ڰ� ��ġ�� ��
	animation* _storageAni;			//â�� �ִϸ��̼�
	image* _mainImage;				//���ڸ����� ������ â���κ��丮 �̹���

	slot _slotInfo;
	vector<slot> _vSlot;			//������ ���� ����
	vector<slot> _vTemp;			//������ ���� ����

	//�κ� ���� �����ۺ����ִ�â
	image* _showItem;
	RECT _showItemRc;

	bool _showWindow;				//�÷��̾ j��ư�� ������ true�� �ż� â�� â�� ���

	//Ŀ��
	cursor* _cursor;
	RECT _cursorSlot;				//�ۼ����ϴ·�Ʈ(Ŀ��)
	int _cursorNum;					//��������� ���õǾ�����
	image* _grab;					//Ŀ���� ���� �������� ���

	RECT temp;
public:

	storage();
	~storage();

	HRESULT init(string storageName, POINT xy);
	void release();
	void update();
	void render();


	RECT getRECT() { return _boxRc; }

	void setStorageItem();						// â�� �������� ��ġ�� ������Ʈ����
	void storageRender();						//â���� �ִϸ��̼� ���
	void cursorControl();						//Ŀ�� ����

	void itemArrange();							//�������� �������� ���ִ� ��� ..�̿ϼ�

	void removeItem();										//â�� ������ �����

	void grab();											//Ŀ���� �������� �������

	void invenplayer();									//    -->â��� �κ��丮�� �ְ� �޴� �Լ�
	void invenplayermove();							//	-->��� �ִ� �ڸ��� ä���		
};