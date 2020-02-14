#include "stdafx.h"
#include "bullet.h"

bullet::bullet()
{
}


bullet::~bullet()
{
}

HRESULT bullet::init(char * imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void bullet::release()
{
	_vBullet.clear();
}

void bullet::update()
{
	move();
}

void bullet::render()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{

		//적 총알 렉트
		Rectangle(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, _viBullet->rc.right, _viBullet->rc.bottom);
		_viBullet->bulletImage->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
	}
}
//총알 발사
void bullet::fire(float x, float y, int direct, float speed)
{
	//if (_bulletMax < _vBullet.size()) return;
	//총알 구조체 선언
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new image;
	switch (direct) {
	case 0:bullet.bulletImage = IMAGEMANAGER->findImage("터렛미사일L");
	case 1:bullet.bulletImage = IMAGEMANAGER->findImage("터렛미사일U");
	case 2:bullet.bulletImage = IMAGEMANAGER->findImage("터렛미사일R");
	case 3:bullet.bulletImage = IMAGEMANAGER->findImage("터렛미사일D");
	}
	bullet.speed = speed;
	bullet.direct = direct;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());

	//벡터에 담기
	_vBullet.push_back(bullet);

}
//총알 이동
void bullet::move()
{
	//float elpasedTime = TIMEMANAGER->getElapsedTime();

	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		switch (_viBullet->direct)
		{
		case 0:_viBullet->x -= _viBullet->speed; break;
		case 1:_viBullet->y -= _viBullet->speed; break;
		case 2:_viBullet->x += _viBullet->speed; break;
		case 3:_viBullet->y += _viBullet->speed; break;
		}
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());

		if (_range < getDistance(_viBullet->x, _viBullet->y, _viBullet->fireX, _viBullet->fireY))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}
//총알 제거
void bullet::removeMissile(int arrNum)
{
	_vBullet.push_back(_vBullet[0]);
	_vBullet.erase(_vBullet.begin() + arrNum);

}

weapons::weapons()
{
}

weapons::~weapons()
{
}

HRESULT weapons::init()
{

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (i == 0)
			{
				_arrow._arrow = ARROW_LEFT;
				_arrow._waponimg = new  image;
				_arrow._waponimg->init("images/arrow/arrow_left.bmp", 52, 10, true, RGB(255, 0, 255));
			}
			if (i == 1)
			{
				_arrow._arrow = ARROW_RIGHT;
				_arrow._waponimg = new image;
				_arrow._waponimg->init("images/arrow/arrow_right.bmp", 52, 10, true, RGB(255, 0, 255));
			}
			if (i == 2)
			{
				_arrow._arrow = ARROW_UP;
				_arrow._waponimg = new image;
				_arrow._waponimg->init("images/arrow/arrow_up.bmp", 10, 52, true, RGB(255, 0, 255));
			}
			if (i == 3)
			{
				_arrow._arrow = ARROW_DOWN;
				_arrow._waponimg = new image;
				_arrow._waponimg->init("images/arrow/arrow_down.bmp", 10, 52, true, RGB(255, 0, 255));
			}

			_arrow._spped = 5.0f;
			_arrow._isfire = false;

			_varrow.push_back(_arrow);

		}
	}
	return S_OK;
}
//===============================================================
//													플레이어가 사용할 크랠스 
//===============================================================

void weapons::release()
{
}

void weapons::update()
{
	move();
}

void weapons::fire(float x, float y, WEAPONMOVE weponMove)
{
	_viterarrow = _varrow.begin();

	for (; _viterarrow != _varrow.end(); ++_viterarrow)
	{
		if (_viterarrow->_isfire) continue;

		if (_viterarrow->_arrow == weponMove)
		{
			_viterarrow->_isfire = true;
			_viterarrow->x = _viterarrow->fireX = x;
			_viterarrow->y = _viterarrow->fireY = y;
			_viterarrow->_rc = RectMakeCenter(_viterarrow->x, _viterarrow->y, _viterarrow->_waponimg->getWidth(),
				_viterarrow->_waponimg->getHeight());
			break;
		}
	}
}

void weapons::move()
{
	_viterarrow = _varrow.begin();
	for (_viterarrow; _viterarrow != _varrow.end(); ++_viterarrow)
	{
		if (!_viterarrow->_isfire) continue;
		//_viterarrow->y -= _viterarrow->_spped; 
		if (_viterarrow->_arrow == ARROW_LEFT)
		{
			_viterarrow->x -= _viterarrow->_spped;
		}
		if (_viterarrow->_arrow == ARROW_RIGHT)
		{
			_viterarrow->x += _viterarrow->_spped;
		}
		if (_viterarrow->_arrow == ARROW_UP)
		{
			_viterarrow->y -= _viterarrow->_spped;
		}
		if (_viterarrow->_arrow == ARROW_DOWN)
		{
			_viterarrow->y += _viterarrow->_spped;
		}

		_viterarrow->_rc = RectMakeCenter(_viterarrow->x, _viterarrow->y, _viterarrow->_waponimg->getWidth(), _viterarrow->_waponimg->getHeight());
	}
}

void weapons::render()
{
	_viterarrow = _varrow.begin();
	for (_viterarrow; _viterarrow != _varrow.end(); ++_viterarrow)
	{
		if (!_viterarrow->_isfire) continue;
		_viterarrow->_waponimg->render(getMemDC(), _viterarrow->_rc.left, _viterarrow->_rc.top);
	}
}