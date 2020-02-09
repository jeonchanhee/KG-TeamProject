#include "stdafx.h"
#include "cursor.h"

cursor::cursor()
{
}

cursor::~cursor()
{
}

HRESULT cursor::init()
{
	//커서초기화
	_image = IMAGEMANAGER->findImage("커서");


	int arrlen1[] = { 0,1,0 };
	ANIMATIONMANAGER->addAnimation("커서애니", "커서", arrlen1, 3, 10, false);
	_ani = ANIMATIONMANAGER->findAnimation("커서애니");

	_cursorMove = 0;
	return S_OK;
}

void cursor::release()
{
}

void cursor::update(RECT choiceSlot)
{
	_rc = choiceSlot;
}

void cursor::render()
{
	_image->aniRender(getMemDC(), _rc.left-10, _rc.top-10, _ani);

}
