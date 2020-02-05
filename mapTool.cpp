#include "stdafx.h"
#include "mapTool.h"

mapTool::mapTool(){}

mapTool::~mapTool(){}

HRESULT mapTool::init()
{
	setUp();
	setSampleBook();

	

	return S_OK;
}

void mapTool::relaese()
{

}

void mapTool::update()
{
	cameraMove();
	controlSampleBook();
}

void mapTool::render()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (CAMERAX - 100 < _tiles[i].x && _tiles[i].x < CAMERAX + WINSIZEX + 100 && CAMERAY - 100 < _tiles[i].y&& _tiles[i].y < CAMERAY + WINSIZEY + 100)
		{
			if (_tiles[i].terrain != TERAIN_NONE) continue;

			Rectangle(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].rc.right, _tiles[i].rc.bottom);

			if (KEYMANAGER->isToggleKey(VK_TAB))
			{
				SetBkMode(getMemDC(), TRANSPARENT);
				//»ö»ó
				SetTextColor(getMemDC(), RGB(255, 0, 0));

				char str[128];
				sprintf_s(str, "%d", i);
				TextOut(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, str, strlen(str));
			}
		}
	}

	_sampleBook.img->render(CAMERAMANAGER->getCameraDC(), _sampleBook.rc.left, _sampleBook.rc.top);

	if (_sampleBook.Summons)
	{
		for (int i = 0; i < 3; i++)
		{
			_sampleBook.bottun[i].img->render(CAMERAMANAGER->getCameraDC(), _sampleBook.bottun[i].rc.left, _sampleBook.bottun[i].rc.top);
		}
	}
}

void mapTool::save()
{
}

void mapTool::load()
{
}

void mapTool::cameraMove()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2 > 0)
	{
		CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x - 50, CAMERAMANAGER->getCameraCenter().y));
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && CAMERAMANAGER->getCameraCenter().x + WINSIZEX / 2 < TILESIZEX)
	{
		CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x + 50, CAMERAMANAGER->getCameraCenter().y));
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP) && CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2 > 0)
	{
		CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x, CAMERAMANAGER->getCameraCenter().y - 50));
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && CAMERAMANAGER->getCameraCenter().y + WINSIZEY / 2 < TILESIZEY)
	{
		CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x, CAMERAMANAGER->getCameraCenter().y + 50));
	}
}

void mapTool::setUp()
{
	//Å¸ÀÏ ¼ÂÆÃ
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			SetRect(&_tiles[i * TILEX + j].rc, j * TILESIZE, i * TILESIZE, j* TILESIZE + TILESIZE, i * TILESIZE + TILESIZE);
		}
	}

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		_tiles[i].x = _tiles[i].rc.left + (_tiles[i].rc.right - _tiles[i].rc.left) / 2;
		_tiles[i].y = _tiles[i].rc.top + (_tiles[i].rc.bottom - _tiles[i].rc.top) / 2;
	}

	mapInit();
}

void mapTool::mapInit()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		// ÁöÇü ÃÊ±â¼³Á¤
		_tiles[i].terrain = TERAIN_NONE;
		
		_tiles[i].terrainFrameX = 0;
		_tiles[i].terrainFrameY = 0;
		
		//¿ÀºêÁ§Æ® ÃÊ±â ¼³Á¤
		_tiles[i].obj = OBJ_NONE;

		_tiles[i].objFrameX = 0;
		_tiles[i].objFrameY = 0;
		
	}


}

void mapTool::setSampleBook()
{
	_sampleBook.Summons = false;
	_sampleBook.img = IMAGEMANAGER->findImage("¿·¼ÀÇÃºÏ");
	_sampleBook.x = WINSIZEX - _sampleBook.img->getWidth() / 2;
	_sampleBook.y = WINSIZEY / 2;
	_sampleBook.rc = RectMakeCenter(_sampleBook.x, _sampleBook.y, _sampleBook.img->getWidth(), _sampleBook.img->getHeight());
}

void mapTool::controlSampleBook()
{
	
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_sampleBook.rc, m_ptMouse))
		{
			_sampleBook.Summons = true;
		}

		for (int i = 0; i < 3; i++)
		{
			if (PtInRect(&_sampleBook.bottun[i].rc, m_ptMouse))
			{
				if (i == 0) _sampleBook.Summons = false;
			}
		}
	}
	

	if (_sampleBook.Summons)
	{
		_sampleBook.img = IMAGEMANAGER->findImage("¼ÀÇÃºÏ");
		_sampleBook.x = WINSIZEX / 2;
		_sampleBook.y = WINSIZEY - _sampleBook.img->getHeight() / 2;
	}
	else
	{
		_sampleBook.img = IMAGEMANAGER->findImage("¿·¼ÀÇÃºÏ");
		_sampleBook.x = WINSIZEX - _sampleBook.img->getWidth() / 2;
		_sampleBook.y = WINSIZEY / 2;
	}
	
	_sampleBook.rc = RectMakeCenter(_sampleBook.x, _sampleBook.y, _sampleBook.img->getWidth(), _sampleBook.img->getHeight());


	//¹öÆ° ¼³Á¤
	if (_sampleBook.Summons)
	{
		_sampleBook.bottun[0].img = IMAGEMANAGER->findImage("´Ý±â");
		_sampleBook.bottun[0].x = _sampleBook.rc.right - _sampleBook.bottun[0].img->getWidth();
		_sampleBook.bottun[0].y = _sampleBook.rc.top + _sampleBook.bottun[0].img->getHeight();
		_sampleBook.bottun[0].rc = RectMakeCenter(_sampleBook.bottun[0].x, _sampleBook.bottun[0].y, _sampleBook.bottun[0].img->getWidth(), _sampleBook.bottun[0].img->getHeight());

		_sampleBook.bottun[1].img = IMAGEMANAGER->findImage("µÚ·Î");
		_sampleBook.bottun[1].x = _sampleBook.rc.left + _sampleBook.bottun[1].img->getWidth();
		_sampleBook.bottun[1].y = _sampleBook.rc.bottom - _sampleBook.bottun[1].img->getHeight() - 20;
		_sampleBook.bottun[1].rc = RectMakeCenter(_sampleBook.bottun[1].x, _sampleBook.bottun[1].y, _sampleBook.bottun[1].img->getWidth(), _sampleBook.bottun[1].img->getHeight());

		_sampleBook.bottun[2].img = IMAGEMANAGER->findImage("¾ÕÀ¸·Î");
		_sampleBook.bottun[2].x = _sampleBook.rc.right - _sampleBook.bottun[2].img->getWidth();
		_sampleBook.bottun[2].y = _sampleBook.rc.bottom - _sampleBook.bottun[2].img->getHeight() - 20;
		_sampleBook.bottun[2].rc = RectMakeCenter(_sampleBook.bottun[2].x, _sampleBook.bottun[2].y, _sampleBook.bottun[2].img->getWidth(), _sampleBook.bottun[2].img->getHeight());
	}


}
