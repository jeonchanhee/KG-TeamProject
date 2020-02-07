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

void mapTool::relaese(){}

void mapTool::update()
{
	cameraMove();
	controlSampleBook();
}

void mapTool::render()
{
	//타일
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (CAMERAX - 100 < _tiles[i].x && _tiles[i].x < CAMERAX + WINSIZEX + 100 && CAMERAY - 100 < _tiles[i].y&& _tiles[i].y < CAMERAY + WINSIZEY + 100)
		{
			if (_tiles[i].terrain != TERAIN_NONE) continue;

			Rectangle(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].rc.right, _tiles[i].rc.bottom);

			if (KEYMANAGER->isToggleKey(VK_TAB))
			{
				SetBkMode(getMemDC(), TRANSPARENT);
				//색상
				SetTextColor(getMemDC(), RGB(255, 0, 0));

				char str[128];
				sprintf_s(str, "%d", i);
				TextOut(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, str, strlen(str));
			}
		}
	}

	//셈플북
	_sampleBook.img->render(getMemDC(), _sampleBook.rc.left, _sampleBook.rc.top);

	if (_sampleBook.Summons)
	{
		for (int i = 0; i < 3; i++)
		{
			_sampleBook.bottun[i].img->render(getMemDC(), _sampleBook.bottun[i].rc.left, _sampleBook.bottun[i].rc.top);
		}
	}

}

//세이브
void mapTool::save()
{

}

//로드
void mapTool::load()
{

}

//카메라 이동
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

//타일 셋업
void mapTool::setUp()
{
	//타일 셋팅
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

//타일 초기 설정
void mapTool::mapInit()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		// 지형 초기설정
		_tiles[i].terrain = TERAIN_NONE;
		
		_tiles[i].terrainFrameX = 0;
		_tiles[i].terrainFrameY = 0;
		
		//오브젝트 초기 설정
		_tiles[i].obj = OBJ_NONE;

		_tiles[i].objFrameX = 0;
		_tiles[i].objFrameY = 0;
		
	}
}

void mapTool::setSampleBook()
{
	_sampleBook.Summons = false;
	_sampleBook.img = IMAGEMANAGER->findImage("옆셈플북");
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
		_sampleBook.img = IMAGEMANAGER->findImage("셈플북");
		_sampleBook.x = WINSIZEX / 2;
		_sampleBook.y = WINSIZEY - _sampleBook.img->getHeight() / 2;
	}
	else
	{
		_sampleBook.img = IMAGEMANAGER->findImage("옆셈플북");
		_sampleBook.x = WINSIZEX - _sampleBook.img->getWidth() / 2;
		_sampleBook.y = WINSIZEY / 2;
	}
	
	_sampleBook.rc = RectMakeCenter(_sampleBook.x, _sampleBook.y, _sampleBook.img->getWidth(), _sampleBook.img->getHeight());


	//버튼 설정
	if (_sampleBook.Summons)
	{
		_sampleBook.bottun[0].img = IMAGEMANAGER->findImage("닫기");
		_sampleBook.bottun[0].x = _sampleBook.rc.right - _sampleBook.bottun[0].img->getWidth();
		_sampleBook.bottun[0].y = _sampleBook.rc.top + _sampleBook.bottun[0].img->getHeight();
		_sampleBook.bottun[0].rc = RectMakeCenter(_sampleBook.bottun[0].x, _sampleBook.bottun[0].y, _sampleBook.bottun[0].img->getWidth(), _sampleBook.bottun[0].img->getHeight());

		_sampleBook.bottun[1].img = IMAGEMANAGER->findImage("뒤로");
		_sampleBook.bottun[1].x = _sampleBook.rc.left + _sampleBook.bottun[1].img->getWidth();
		_sampleBook.bottun[1].y = _sampleBook.rc.bottom - _sampleBook.bottun[1].img->getHeight() - 20;
		_sampleBook.bottun[1].rc = RectMakeCenter(_sampleBook.bottun[1].x, _sampleBook.bottun[1].y, _sampleBook.bottun[1].img->getWidth(), _sampleBook.bottun[1].img->getHeight());

		_sampleBook.bottun[2].img = IMAGEMANAGER->findImage("앞으로");
		_sampleBook.bottun[2].x = _sampleBook.rc.right - _sampleBook.bottun[2].img->getWidth();
		_sampleBook.bottun[2].y = _sampleBook.rc.bottom - _sampleBook.bottun[2].img->getHeight() - 20;
		_sampleBook.bottun[2].rc = RectMakeCenter(_sampleBook.bottun[2].x, _sampleBook.bottun[2].y, _sampleBook.bottun[2].img->getWidth(), _sampleBook.bottun[2].img->getHeight());
	}
}

void mapTool::setSampleTile()
{
	


}

TERRAIN mapTool::dungeonTerrainSelect(int frameX, int frameY)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (frameX == i && frameY == j)
			{
				return TERAIN_WALL;
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 2; j < 4; j++)
		{
			return TERAIN_GROUND;
		}
	}

	return TERAIN_NONE;
}

OBJECT mapTool::dungeonObjSelect(int frameX, int frameY)
{
	for (int i = 4; i < 12; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			//오브젝트 벽
			if (i <= 5 && j == 0 || i == 0 && j == 1)
			{	
				if(frameX == i && frameY == j) return OBJ_WALL;
			}

			//해골 오브젝트
			if (i >= 6 && i <= 9 && j == 0 || i >= 7 && i <= 8 && j == 1 )
			{
				if (frameX == i && frameY == j) return OBJ_SKULL;
			}

			//문 오브젝트
			if (i >= 10 && j <= 3)
			{
				if (frameX == i && frameY == j) return OBJ_DOOR;
			}

			//기둥
			if (i == 4 && j == 2) return OBJ_PILLAR;

			if (i >= 5 && i <= 8 && j >= 2)
			{
				return OBJ_HELL_SPA;
			}

			if (i == 9 && j == 2) return OBJ_BOX;

			if (i >= 9 && j >= 4) return OBJ_TENT;
		}
	}

	return OBJ_NONE;
}



