#pragma once
#include "gameNode.h"
#define SLOTNUM 4
class sellStand : public gameNode
{
private:
	image*		_img;				 //�ǸŴ� �̹���
	RECT		_rc;				 //�ǸŴ� ��Ʈ

	image*		_sellImag;		 //�Ǹ�â �̹���

	image*		_slotImage[SLOTNUM];
	RECT		_slot[SLOTNUM];			 //�Ǹ�â�� ������ ����
	RECT		_sellInfo[SLOTNUM];		 //�Ǹž����� ���� ���ϴ� �κ��� ��Ʈ
	
	vector<item> _vSellItem;  //�Ǹ� �������� ���� ����

	bool _showWindow;
public:
	sellStand();
	~sellStand();

	HRESULT init();
	void release();
	void update();
	void render();

	RECT getRECT() { return _rc; }

	void setShow(bool show) { _showWindow = show; }
};

