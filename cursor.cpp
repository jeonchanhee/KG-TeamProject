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
	_bigSmall = false;

	int arrlen1[] = { 0,1,0 };
	ANIMATIONMANAGER->addAnimation("Ŀ���ִ�", "Ŀ��", arrlen1, 3, 10, false);
	ANIMATIONMANAGER->addAnimation("Ŀ���ִ�2", "��Ŀ��", arrlen1, 3, 10, false);

	_ani = ANIMATIONMANAGER->findAnimation("Ŀ���ִ�");
	return S_OK;
}

void cursor::release()
{
}

void cursor::update(RECT choiceSlot)
{
	//_rc = choiceSlot;
}

void cursor::render()
{
	if (_bigSmall) _image->aniRender(getMemDC(), _rc.left - 30, _rc.top - 20, _ani);
	if (!_bigSmall) _image->aniRender(getMemDC(), _rc.left - 10, _rc.top - 10, _ani);
}

void cursor::setBigCursor()
{
	_image = IMAGEMANAGER->findImage("��Ŀ��");
	_ani = ANIMATIONMANAGER->findAnimation("Ŀ���ִ�2");
	_bigSmall = true;
}

void cursor::setSmallCursor()
{
	_image = IMAGEMANAGER->findImage("Ŀ��");
	_ani = ANIMATIONMANAGER->findAnimation("Ŀ���ִ�");
	_bigSmall = false;
}

