#pragma once
#include "gameNode.h"
#include "item.h"

class cursor : public gameNode
{
	image*			_image;				//커서의 이미지
	RECT			_rc;				    //커서의 위치
	animation*		_ani;				//커서의 애니메이션
	int				_cursorMove;				//커서의 움직임을 담당할 변수. 창고슬롯 배열을돌아다녀서 커서를 움직임.
	vector<item>	_vTemp;

public:
	cursor();
	~cursor();

	HRESULT init();
	void release();
	void update(RECT choiceSlot);
	void render();

	void setRc(RECT rc) { _rc = rc; }
	animation* getAni() { return _ani; }

};

