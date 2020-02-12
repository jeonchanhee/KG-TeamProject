#pragma once
#include "gameNode.h"
#include "cursor.h"
#define SLOTNUM 4
class sellTable : public gameNode
{
private:
	RECT		_tableRc;				 //�ǸŴ� ��Ʈ

	image*		_sellMainImg;		 //�Ǹ�â �̹���

	image*		_slotImage[SLOTNUM];
	RECT		_slot[SLOTNUM];			 //�Ǹ�â�� ������ ����
	RECT		_sellInfo[SLOTNUM];		 //�Ǹž����� ���� ���ϴ� �κ��� ��Ʈ
	RECT temp;
	vector<item> _vSellItem;  //�Ǹ� �������� ���� ����

	int playerPrice;



	//Ŀ��
	cursor* _cursor;
	RECT _cursorSlot;				//�ۼ����ϴ·�Ʈ(Ŀ��)
	int _cursorNum;					//��������� ���õǾ�����
	item _itemTemp;			//�������� �ӽ÷� ���� ����
	image* _grab;					//Ŀ���� ���� �������� ���

	bool _showWindow;
	bool _choiceItem;				//�������� �����ߴ���
public:
	sellTable();
	~sellTable();

	HRESULT init();
	void release();
	void update();
	void render();

	void cursorControl();
	void playerCollision();
};

