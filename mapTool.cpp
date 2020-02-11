#include "stdafx.h"
#include "mapTool.h"

mapTool::mapTool(){}

mapTool::~mapTool(){}

HRESULT mapTool::init()
{
	setUp();
	setSampleBook();

	page = 0;

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
	//Ÿ��
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (CAMERAX - 100 < _tiles[i].x && _tiles[i].x < CAMERAX + WINSIZEX + 100 && CAMERAY - 100 < _tiles[i].y&& _tiles[i].y < CAMERAY + WINSIZEY + 100)
		{
			if (_tiles[i].terrain != TERAIN_NONE) continue;

			Rectangle(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].rc.right, _tiles[i].rc.bottom);

			if (KEYMANAGER->isToggleKey(VK_TAB))
			{
				SetBkMode(getMemDC(), TRANSPARENT);
				//����
				SetTextColor(getMemDC(), RGB(255, 0, 0));

				char str[128];
				sprintf_s(str, "%d", i);
				TextOut(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, str, strlen(str));
			}
		}
	}

	//���ú�
	_sampleBook.img->render(CAMERAMANAGER->getCameraDC(), _sampleBook.rc.left, _sampleBook.rc.top);

	if (_sampleBook.Summons)
	{
	
		if (page == 0)
		{
			_sampleBook.bottun[0].img->render(CAMERAMANAGER->getCameraDC(), _sampleBook.bottun[0].rc.left, _sampleBook.bottun[0].rc.top);

			for (int i = 0; i < 4; i++)
			{
				bottun[i].img->render(CAMERAMANAGER->getCameraDC(), bottun[i].rc.left, bottun[i].rc.top);
			}
		}
		else if( page > 0 && page < 10)
		{
			for (int i = 0; i < 3; i++)
			{
				_sampleBook.bottun[i].img->render(CAMERAMANAGER->getCameraDC(), _sampleBook.bottun[i].rc.left, _sampleBook.bottun[i].rc.top);
			}

			for (int i = 0; i < 4; i++)
			{
				bottun[i].img->render(CAMERAMANAGER->getCameraDC(), bottun[i].rc.left, bottun[i].rc.top);
			}

			for (int i = 0; i < 8; i++)
			{
				Rectangle(CAMERAMANAGER->getCameraDC(), rc[i].left, rc[i].top, rc[i].right, rc[i].bottom);
			}
		}
		else if(page > 9)
		{
			for (int i = 0; i < 3; i++)
			{
				_sampleBook.bottun[i].img->render(CAMERAMANAGER->getCameraDC(), _sampleBook.bottun[i].rc.left, _sampleBook.bottun[i].rc.top);
			}

			for (int i = 0; i < 2; i++)
			{
				bottun[i].img->render(CAMERAMANAGER->getCameraDC(), bottun[i].rc.left, bottun[i].rc.top);
			}
		}
	}

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (int i = 0; i < 4; i++)
		{
			Rectangle(CAMERAMANAGER->getCameraDC(), bottun[i].rc.left, bottun[i].rc.top, bottun[i].rc.right, bottun[i].rc.bottom);
		}

		SetBkMode(CAMERAMANAGER->getCameraDC(), TRANSPARENT);
		//����
		SetTextColor(CAMERAMANAGER->getCameraDC(), RGB(255, 0, 0));

		char str[128];
		sprintf_s(str, "%d", page);
		TextOut(CAMERAMANAGER->getCameraDC(), 100, 500, str, strlen(str));
	}

}

//���̺�
void mapTool::save()
{

}

//�ε�
void mapTool::load()
{

}

//ī�޶� �̵�
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

//Ÿ�� �¾�
void mapTool::setUp()
{
	//Ÿ�� ����
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

//Ÿ�� �ʱ� ����
void mapTool::mapInit()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		// ���� �ʱ⼳��
		_tiles[i].terrain = TERAIN_NONE;
		
		_tiles[i].terrainFrameX = 0;
		_tiles[i].terrainFrameY = 0;
		
		//������Ʈ �ʱ� ����
		_tiles[i].obj = OBJ_NONE;

		_tiles[i].objFrameX = 0;
		_tiles[i].objFrameY = 0;
		
	}
}
//����Ÿ�� ����
void mapTool::setSampleTile()
{
	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			_sampleTile[i * SAMPLETILEX + j].terrainFrameX = j;
			_sampleTile[i * SAMPLETILEX + j].terrainFrameY = i;

			/*SetRect(&_sampleTile[i * SAMPLETILEX + j].rcTile, (WINSIZEX - IMAGEMANAGER->findImage("��������")->getWidth()) + j * TILESIZE / 2, i * TILESIZE / 3,
				(WINSIZEX - IMAGEMANAGER->findImage("��������")->getWidth()) + j * TILESIZE / 3 + TILESIZE / 3,
				i * TILESIZE / 3 + TILESIZE / 3);*/
		}
	}


}

//=================================================================================
//
//				��					��						��	
//
//=================================================================================

//���ú� ����
void mapTool::setSampleBook()
{
	_sampleBook.Summons = false;
	_sampleBook.img = IMAGEMANAGER->findImage("�����ú�");
	_sampleBook.x = WINSIZEX - _sampleBook.img->getWidth() / 2;
	_sampleBook.y = WINSIZEY / 2;
	_sampleBook.rc = RectMakeCenter(_sampleBook.x, _sampleBook.y, _sampleBook.img->getWidth(), _sampleBook.img->getHeight());
}
//���ú� Ŭ������ ����
void mapTool::controlSampleBook()
{
	sampleBookKey();
	
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

		if (PtInRect(&_sampleBook.bottun[1].rc, m_ptMouse))
		{
			if (page > 0) page--;
		}

		if (PtInRect(&_sampleBook.bottun[2].rc, m_ptMouse))
		{
			if (page > 0) page++;
		}

		if (_sampleBook.Summons)
		{
			_sampleBook.img = IMAGEMANAGER->findImage("���ú�");
			_sampleBook.x = WINSIZEX / 2;
			_sampleBook.y = WINSIZEY - _sampleBook.img->getHeight() / 2;
		}
		else
		{
			_sampleBook.img = IMAGEMANAGER->findImage("�����ú�");
			_sampleBook.x = WINSIZEX - _sampleBook.img->getWidth() / 2;
			_sampleBook.y = WINSIZEY / 2;
		}


		sampleBookBottunControl();
	}



	//��ư ����
	if (_sampleBook.Summons)
	{
		_sampleBook.bottun[0].img = IMAGEMANAGER->findImage("�ݱ�");
		_sampleBook.bottun[0].x = _sampleBook.rc.right - _sampleBook.bottun[0].img->getWidth();
		_sampleBook.bottun[0].y = _sampleBook.rc.top + _sampleBook.bottun[0].img->getHeight();
		_sampleBook.bottun[0].rc = RectMakeCenter(_sampleBook.bottun[0].x, _sampleBook.bottun[0].y, _sampleBook.bottun[0].img->getWidth(), _sampleBook.bottun[0].img->getHeight());

		if (page > 0)
		{
			_sampleBook.bottun[1].img = IMAGEMANAGER->findImage("�ڷ�");
			_sampleBook.bottun[1].x = _sampleBook.rc.left + _sampleBook.bottun[1].img->getWidth();
			_sampleBook.bottun[1].y = _sampleBook.rc.bottom - _sampleBook.bottun[1].img->getHeight() - 20;
			_sampleBook.bottun[1].rc = RectMakeCenter(_sampleBook.bottun[1].x, _sampleBook.bottun[1].y, _sampleBook.bottun[1].img->getWidth(), _sampleBook.bottun[1].img->getHeight());

			_sampleBook.bottun[2].img = IMAGEMANAGER->findImage("������");
			_sampleBook.bottun[2].x = _sampleBook.rc.right - _sampleBook.bottun[2].img->getWidth();
			_sampleBook.bottun[2].y = _sampleBook.rc.bottom - _sampleBook.bottun[2].img->getHeight() - 20;
			_sampleBook.bottun[2].rc = RectMakeCenter(_sampleBook.bottun[2].x, _sampleBook.bottun[2].y, _sampleBook.bottun[2].img->getWidth(), _sampleBook.bottun[2].img->getHeight());
		}

		if (page > 0 && page < 10)
		{
			sampleSetRc();
		}
		setSampleBookBottun();
	}
	
	if (!_sampleBook.Summons) page = 0;
	
	_sampleBook.rc = RectMakeCenter(_sampleBook.x, _sampleBook.y, _sampleBook.img->getWidth(), _sampleBook.img->getHeight());

}
//���ú� Ű����
void mapTool::sampleBookKey()
{
	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		if (_sampleBook.Summons) _sampleBook.Summons = false;
		else _sampleBook.Summons = true;

		if (_sampleBook.Summons)
		{
			_sampleBook.img = IMAGEMANAGER->findImage("���ú�");
			_sampleBook.x = WINSIZEX / 2;
			_sampleBook.y = WINSIZEY - _sampleBook.img->getHeight() / 2;
		}
		else
		{
			_sampleBook.img = IMAGEMANAGER->findImage("�����ú�");
			_sampleBook.x = WINSIZEX - _sampleBook.img->getWidth() / 2;
			_sampleBook.y = WINSIZEY / 2;
		}
	}

	if (_sampleBook.Summons)
	{
		if (KEYMANAGER->isStayKeyDown('A') && _sampleBook.rc.left > 0)
		{
			_sampleBook.x -= 5;
		}

		if (KEYMANAGER->isStayKeyDown('D') && _sampleBook.rc.right < WINSIZEX )
		{
			_sampleBook.x += 5;
		}

		if (KEYMANAGER->isStayKeyDown('W') && _sampleBook.rc.top > 0)
		{
			_sampleBook.y -= 5;
		}

		if (KEYMANAGER->isStayKeyDown('S') && _sampleBook.rc.bottom < WINSIZEY)
		{
			_sampleBook.y += 5;
		}
	}

}
//���ú� ��ư ����
void mapTool::setSampleBookBottun()
{
	if (page == 0)
	{
		bottun[0].img = IMAGEMANAGER->findImage("����");
		bottun[1].img = IMAGEMANAGER->findImage("����");
		bottun[2].img = IMAGEMANAGER->findImage("���̺�");
		bottun[3].img = IMAGEMANAGER->findImage("�ε�");
		
		for (int i = 0; i < 4; i++)
		{
			bottun[i].x = _sampleBook.rc.right - bottun[i].img->getWidth();
			bottun[i].y = _sampleBook.rc.top + bottun[i].img->getHeight() * 2;
			bottun[i].rc = RectMakeCenter(bottun[i].x, bottun[i].y + i * 100, bottun[i].img->getWidth(), bottun[i].img->getHeight());
		}
	}
	else if (page > 0 && page < 4)
	{
		bottun[0].img = IMAGEMANAGER->findImage("����");
		bottun[1].img = IMAGEMANAGER->findImage("���̺�");
		bottun[2].img = IMAGEMANAGER->findImage("����");
		bottun[3].img = IMAGEMANAGER->findImage("�ε�");

		for (int i = 0; i < 4; i++)
		{
			if (i == 0)
			{
				bottun[i].x = _sampleBook.x;
				bottun[i].y = _sampleBook.rc.top + bottun[i].img->getHeight() + 20;

			}
			else
			{
				bottun[i].x = _sampleBook.rc.left + 10;
				bottun[i].y = _sampleBook.rc.bottom - bottun[i].img->getHeight() - 50;
			}
			bottun[i].rc = RectMakeCenter(bottun[i].x + i * 200, bottun[i].y, bottun[i].img->getWidth(), bottun[i].img->getHeight());
		}
	}
	else if( page > 3 && page < 10)
	{
		bottun[0].img = IMAGEMANAGER->findImage("����");
		bottun[1].img = IMAGEMANAGER->findImage("���̺�");
		bottun[2].img = IMAGEMANAGER->findImage("������Ʈ");
		bottun[3].img = IMAGEMANAGER->findImage("�ε�");

		for (int i = 0; i < 4; i++)
		{
			if (i == 0)
			{
				bottun[i].x = _sampleBook.x;
				bottun[i].y = _sampleBook.rc.top + bottun[i].img->getHeight() + 20;

			}
			else
			{
				bottun[i].x = _sampleBook.rc.left + 10;
				bottun[i].y = _sampleBook.rc.bottom - bottun[i].img->getHeight() - 50;
			}
			bottun[i].rc = RectMakeCenter(bottun[i].x + i * 200, bottun[i].y, bottun[i].img->getWidth(), bottun[i].img->getHeight());
		}
	}
	else if (page == 10)
	{
		bottun[0].img = IMAGEMANAGER->findImage("���̺�");
		bottun[1].img = IMAGEMANAGER->findImage("�ε�");

		for (int i = 0; i < 2; i++)
		{
			if (i == 0)
			{
				bottun[i].x = _sampleBook.x;
				bottun[i].y = _sampleBook.rc.top + bottun[i].img->getHeight() + 20;

			}
			else
			{
				bottun[i].x = _sampleBook.rc.left + 10;
				bottun[i].y = _sampleBook.rc.bottom - bottun[i].img->getHeight() - 50;
			}
			bottun[i].rc = RectMakeCenter(bottun[i].x + i * 200, bottun[i].y, bottun[i].img->getWidth(), bottun[i].img->getHeight());
		}
	}
	else if (page == 11)
	{
		bottun[0].img = IMAGEMANAGER->findImage("�ε�");
		bottun[1].img = IMAGEMANAGER->findImage("���̺�");

		for (int i = 0; i < 2; i++)
		{
			if (i == 0)
			{
				bottun[i].x = _sampleBook.x;
				bottun[i].y = _sampleBook.rc.top + bottun[i].img->getHeight() + 20;

			}
			else
			{
				bottun[i].x = _sampleBook.rc.left + 10;
				bottun[i].y = _sampleBook.rc.bottom - bottun[i].img->getHeight() - 50;
			}
			bottun[i].rc = RectMakeCenter(bottun[i].x + i * 200, bottun[i].y, bottun[i].img->getWidth(), bottun[i].img->getHeight());
		}
	}
}
//���ú� ���� ��ư
void mapTool::sampleBookBottunControl()
{
	for (int i = 0; i < 4; i++)
	{
		if (PtInRect(&bottun[i].rc, m_ptMouse))
		{
			if (page == 0)
			{
				if (i == 0) page = 1;
				if (i == 1) page = 4;
				if (i == 2) page = 10;
				if (i == 3) page = 11;
			}
			else if (page > 0 && page < 10)
			{
				if (i == 1) page = 10;
				if (i == 3) page == 11;
			}
			else if (page == 10)
			{
				if (i == 1) page == 11;
			}
			else if (page == 11)
			{
				if (i == 1) page = 10;
			}
		}
	}
}
//������ �ѷ��� ��Ʈ
void mapTool::sampleSetRc()
{
	for (int i = 0; i < 2; i++)
	{
		rc[i] = RectMakeCenter((_sampleBook.rc.left + 150) + i * 150, _sampleBook.rc.top + 200, 100, 100);
		rc[i + 2] = RectMakeCenter((_sampleBook.rc.right - 300) + i * 150, _sampleBook.rc.top + 200, 100, 100);
		rc[i + 4] = RectMakeCenter((_sampleBook.rc.left + 150) + i * 150, _sampleBook.rc.bottom - 200, 100, 100);
		rc[i + 6] = RectMakeCenter((_sampleBook.rc.right - 300) + i * 150, _sampleBook.rc.bottom - 200, 100, 100);
	}

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
			//������Ʈ ��
			if (i <= 5 && j == 0 || i == 0 && j == 1)
			{	
				if(frameX == i && frameY == j) return OBJ_WALL;
			}

			//�ذ� ������Ʈ
			if (i >= 6 && i <= 9 && j == 0 || i >= 7 && i <= 8 && j == 1 )
			{
				if (frameX == i && frameY == j) return OBJ_SKULL;
			}

			//�� ������Ʈ
			if (i >= 10 && j <= 3)
			{
				if (frameX == i && frameY == j) return OBJ_DOOR;
			}

			//���
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
