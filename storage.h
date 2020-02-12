#pragma once
#include"gameNode.h"
#include "cursor.h"

#define SLOTNUM 28

class storage : public gameNode
{
private:

	string _name;
	image* _boxImg;					//�����̹���
	RECT _boxRc;					//���ڰ� ��ġ�� ��
	animation* _storageAni;			//â�� �ִϸ��̼�
	image* _mainImage;				//���ڸ����� ������ â���κ��丮 �̹���
	vector<item> _vStorage;			//�������� ���� ����


	//â�� �������� �����۽��� (�� 28ĭ)
	image* _slotImage[SLOTNUM];	
	RECT _slot[SLOTNUM];

	//�κ� ���� �����ۺ����ִ�â
	image* _showItem;				
	RECT _showItemRc;				

	bool _showWindow;				//�÷��̾ j��ư�� ������ true�� �ż� â�� â�� ���

	//Ŀ��
	cursor* _cursor;
	RECT _cursorSlot;				//�ۼ����ϴ·�Ʈ(Ŀ��)
	int _cursorNum;					//��������� ���õǾ�����
	vector<item> _vTemp;			//�������� �ӽ÷� ���� ����
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
	vector<item> getStorage() {return _vStorage;}
	vector<item>& getStorage_reference() {return _vStorage;}
	
	void setStorageItem();						// â�� �������� ��ġ�� ������Ʈ����
	void storageRender();						//â���� �ִϸ��̼� ���
	void cursorControl();						//Ŀ�� ����

	void itemArrange();							//�������� �������� ���ִ� ��� ..�̿ϼ�
	void resetCursor();							//��â���������� Ŀ����ġ �ʱ�ȭ
	void addItem(item item) { _vStorage.push_back(item); }	//â�� �����۳ֱ�
	void removeItem();										//â�� ������ �����

	void playerCollision();									// ����ݱ�
	void grab();											//Ŀ���� �������� �������
};



