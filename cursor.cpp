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
	//Ŀ���ʱ�ȭ
	_image = IMAGEMANAGER->findImage("Ŀ��");


	int arrlen1[] = { 0,1,0 };
	ANIMATIONMANAGER->addAnimation("Ŀ���ִ�", "Ŀ��", arrlen1, 3, 10, false);
	_ani = ANIMATIONMANAGER->findAnimation("Ŀ���ִ�");

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
