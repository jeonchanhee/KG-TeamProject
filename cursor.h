#pragma once
#include "gameNode.h"
#include "item.h"

class cursor : public gameNode
{
	image*			_image;				//Ŀ���� �̹���
	RECT			_rc;				    //Ŀ���� ��ġ
	animation*		_ani;				//Ŀ���� �ִϸ��̼�
	vector<item>	_vTemp;

	bool _bigSmall;// ū �������� ������������ üũ��
public:
	cursor();
	~cursor();

	HRESULT init();
	void release();
	void update(RECT choiceSlot);
	void render();

	void setRc(RECT rc) { _rc = rc; }
	animation* getAni() { return _ani; }

	void setBigCursor();
	void setSmallCursor();
};

