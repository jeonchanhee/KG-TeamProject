#pragma once
#include "gameNode.h"
#include "item.h"

class cursor : public gameNode
{
	image*			_image;				//커서의 이미지
	RECT			_rc;				    //커서의 위치
	animation*		_ani;				//커서의 애니메이션
	vector<item>	_vTemp;

	bool _bigSmall;// 큰 상태인지 작은상태인지 체크용
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

