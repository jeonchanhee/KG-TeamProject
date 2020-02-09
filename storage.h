#pragma once
#include"gameNode.h"
#include "cursor.h"

#define SLOTNUM 28

class storage : public gameNode
{
private:


	image* _boxImg;			 //�����̹���
	RECT _boxRc;			 //���ڰ� ��ġ�� ��
	animation* _storageAni;	 //â�� �ִϸ��̼�
	vector<item> _vStorage;	 //�������� ���� ����

	image* _mainImage;				//���ڸ����� ������ â���κ��丮 �̹���
	image* _slotImage[SLOTNUM];		//â�� �������� �����۽��� (�� 28ĭ)
	RECT _slot[SLOTNUM];

	image* _showItem;				//�κ� ������ �����ۺ����ִ�â
	RECT _showItemRc;

	bool _showWindow;				//�÷��̾ j��ư�� ������ true�� �ż� â�� â�� ���


	//Ŀ��
	RECT _choiceSlot;				//�ۼ����ϴ·�Ʈ(Ŀ��)
	int _choiceNum;					//��������� ���õǾ�����
	image* _grab;					//Ŀ���� ���� �������� ���
	vector<item> _vTemp;			//�������� �ӽ÷� ���� ����

	cursor* _cursor;

	RECT temp;
public:

	storage();
	~storage();

	HRESULT init(string storageName, POINT xy);
	void release();
	void update();
	void render();

	void setAni(string name){_storageAni = ANIMATIONMANAGER->findAnimation(name);} 
	void setShow(bool show) { _showWindow = show; } // true�� �Ǹ� â��â�����
	void setStorageItem();		// â�� �������� ��ġ�� ������Ʈ����
	void storageRender();		//â���� �ִϸ��̼� ���
	void cursorControl();

	RECT getRECT() { return _boxRc; }
	RECT getSlot(int arrNum) { return _slot[arrNum]; }
	animation* getAni() { return _storageAni; }
	
	void itemArrange();			//�������� �������� ���ִ� ���
	void resetChoiceNum();		//��â���������� Ŀ����ġ �ʱ�ȭ
	void addItem(item itemName) { _vStorage.push_back(itemName); }

	void grab(); //Ŀ���� �������� �������
};



