#include "stdafx.h"
#include "mapTool.h"

mapTool::mapTool() {}

mapTool::~mapTool() {}

HRESULT mapTool::init()
{
	setUp();
	setSampleBook();

	page = 0;

	for (int i = 0; i < 8; i++)
	{
		sampleImage[i] = new image;
		sampleImage[i]->init("images/����.bmp", 600 * 2, 550 * 2, 12, 11, true, RGB(255, 0, 255));
	}
	//������ 1~7 ����
	//������ 8~14 ����
	//������ 15~16 ���̺�ε�
	first = false;
	mouse = false;

	for (int i = 0; i < 4; i++)
	{	
		saveLoad[i] = RectMakeCenter(WINSIZEX / 2 - 250 + (i % 2 * 110), WINSIZEY / 2+50 + (i / 2 *110), 100, 100);
		saveLoadImg_Dungeon[i] = IMAGEMANAGER->findImage("���������ư");
	}
	for (int i = 4; i < 8; i++)
	{
		saveLoad[i] = RectMakeCenter(WINSIZEX / 2 + 150 + (i % 2 * 110), WINSIZEY / 2 - 170 + (i / 2 * 110), 100, 100);
		saveLoadImg_Village[i-4] = IMAGEMANAGER->findImage("���������ư");
	}
	return S_OK;
}

void mapTool::relaese() {}

void mapTool::update()
{



	if (PtInRect(&_sampleBook.rc, m_ptMouse))
	{
		mouse = true;
	}
	else
	{
		mouse = false;
	}


	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		_end.x = m_ptMouse.x;
		_end.y = m_ptMouse.y;

		drage();
	}


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
			if (_tiles[i].terrain == TERAIN_NONE) Rectangle(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].rc.right, _tiles[i].rc.bottom);
			else IMAGEMANAGER->frameRender("����", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);

			if (_tiles[i].obj == OBJ_NONE) continue;

			IMAGEMANAGER->frameRender("����", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
		}
	}

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (CAMERAX - 100 < _tiles[i].x && _tiles[i].x < CAMERAX + WINSIZEX + 100 && CAMERAY - 100 < _tiles[i].y&& _tiles[i].y < CAMERAY + WINSIZEY + 100)
		{
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
		else if (page > 0 && page < 15)
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
				sampleImage[i]->frameRender(CAMERAMANAGER->getCameraDC(), rc[i].left, rc[i].top);
			}
		}
		else if (page > 14)
		{
			for (int i = 0; i < 3; i++)
			{
				_sampleBook.bottun[i].img->render(CAMERAMANAGER->getCameraDC(), _sampleBook.bottun[i].rc.left, _sampleBook.bottun[i].rc.top);
			}

			for (int i = 0; i < 2; i++)
			{
				bottun[i].img->render(CAMERAMANAGER->getCameraDC(), bottun[i].rc.left, bottun[i].rc.top);
			}
			for (int i = 0; i < 4; i++)
			{
				saveLoadImg_Dungeon[i]->render(CAMERAMANAGER->getCameraDC(), saveLoad[i].left, saveLoad[i].top);
			}
			for (int i = 4; i < 8; i++)
			{
				saveLoadImg_Village[i-4]->render(CAMERAMANAGER->getCameraDC(), saveLoad[i].left, saveLoad[i].top);
			}
		}
	}
}

//���̺�
void mapTool::save()
{
	for (int i = 0; i < 8; i++)
	{
		if (PtInRect(&saveLoad[i], m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			HANDLE file;
			DWORD write;
			int arrNum;
			arrNum = i;
			char save[128];
			wsprintf(save, "save/��%d.map", arrNum + 1);

			for (int i = 0; i < TILEX* TILEY; i++)
			{
				_temp[i] = _tiles[i];
			}

			file = CreateFile
			(save,				//������ ���϶Ǵ� �� ��ġ�� �����̸�
				GENERIC_WRITE,			//�����̳� ��ġ�� ����ų� ���� ����� ����
				0,						//���� ���� ����Է�
				NULL,					//���϶Ǵ� ��ġ�� ���� ���� �� Ư��
				CREATE_ALWAYS,			//�����̳� ��ġ�� ���� ���� �ൿ
				FILE_ATTRIBUTE_NORMAL,  //�����̳� ��ġ�� ���� ���� �� Ư��
				NULL);					//������� ������ ���� �� Ư�� Ȯ�� Ư���� ���� ����

			WriteFile(file, _temp, sizeof(tagTile) * TILEX * TILEY, &write, NULL);
			CloseHandle(file);
		}

	}
}

//�ε�
void mapTool::load()
{
	for (int i = 0; i < 8; i++)
	{
		if (PtInRect(&saveLoad[i], m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{

			HANDLE file;
			DWORD read;
			int arrNum;
			arrNum = i;
			char save[128];
			wsprintf(save, "save/��%d.map", arrNum + 1);

			file = CreateFile
			(save,			//������ ���϶Ǵ� �� ��ġ�� �����̸�
				GENERIC_READ,		//�����̳� ��ġ�� ����ų� ���� ����� ����
				0,					//���� ���� ����Է�
				NULL,				//���϶Ǵ� ��ġ�� ���� ���� �� Ư��
				OPEN_EXISTING,		//�����̳� ��ġ�� ���� ���� �ൿ
				FILE_ATTRIBUTE_NORMAL, //�����̳� ��ġ�� ���� ���� �� Ư��
				NULL);				//������� ������ ���� �� Ư�� Ȯ�� Ư���� ���� ����

			ReadFile(file, _temp, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
			CloseHandle(file);

			for (int i = 0; i < TILEX* TILEY; i++)
			{
				_tiles[i] = _temp[i];
			}
		}
	}
}

//ī�޶� �̵�
void mapTool::cameraMove()
{
	if (KEYMANAGER->isStayKeyDown('A') && CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2 > 0)
	{
		CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x - 50, CAMERAMANAGER->getCameraCenter().y));
	}

	if (KEYMANAGER->isStayKeyDown('D') && CAMERAMANAGER->getCameraCenter().x + WINSIZEX / 2 < TILESIZEX)
	{
		CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x + 50, CAMERAMANAGER->getCameraCenter().y));
	}

	if (KEYMANAGER->isStayKeyDown('W') && CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2 > 0)
	{
		CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x, CAMERAMANAGER->getCameraCenter().y - 50));
	}

	if (KEYMANAGER->isStayKeyDown('S') && CAMERAMANAGER->getCameraCenter().y + WINSIZEY / 2 < TILESIZEY)
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
		if (mouse)
		{
			if (page > 0) setSampleMap();
		}
		else
		{
			setMap();

			_start.x = m_ptMouse.x;
			_start.y = m_ptMouse.y;
		}


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


		if (_sampleBook.Summons)	sampleBookBottunControl();
	}

	if (_sampleBook.Summons) setSampleBookBottun();

	if (!_sampleBook.Summons) page = 0;

	if (page > 0) _select = TRRAINDRAW;
	if (page > 2 && page < 8) _select = OBJDRAW;
	if (page >= 8 && page < 13) _select = TRRAINDRAW;
	if (page >= 13 && page < 15) _select = OBJDRAW;

	if (KEYMANAGER->isOnceKeyDown('H')) _select = ERASER;


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
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) && KEYMANAGER->isStayKeyDown('A') && _sampleBook.rc.left > 0)
		{
			_sampleBook.x -= 5;
		}

		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) && KEYMANAGER->isStayKeyDown('D'))
		{
			_sampleBook.x += 5;
		}

		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) && KEYMANAGER->isStayKeyDown('W') && _sampleBook.rc.top > 0)
		{
			_sampleBook.y -= 5;
		}

		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) && KEYMANAGER->isStayKeyDown('S'))
		{
			_sampleBook.y += 5;
		}

		if (page == 0)
		{
			if (KEYMANAGER->isOnceKeyDown('1'))
			{
				page = 1;
			}

			if (KEYMANAGER->isOnceKeyDown('2'))
			{
				page = 8;
			}

			if (KEYMANAGER->isOnceKeyDown('3'))
			{
				page = 15;
			}

			if (KEYMANAGER->isOnceKeyDown('4'))
			{
				page = 16;
			}
		}

		if (page > 0)
		{
			if (KEYMANAGER->isOnceKeyDown('Q'))
			{
				page--;
			}

			if (KEYMANAGER->isOnceKeyDown('E'))
			{
				page++;
			}
		}
	}

}
//���ú� ��ư ����
void mapTool::setSampleBookBottun()
{
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
		setPageSample();
		if (page > 0 && page < 15)
		{
			sampleSetRc();
		}
	}
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
	else if (page > 0 && page < 2)
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
	else if (page > 2 && page < 8)
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
	else if (page >= 8 && page < 13)
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
	else if (page >= 13 && page < 15)
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
	else if (page == 15) //���̺�
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
		save();
	}
	else if (page == 16) //�ε�
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

		load();
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
				if (i == 1) page = 8;

				if (i == 2) page = 15;
				if (i == 3) page = 16;
			}
			else if (page > 0 && page < 15)
			{
				if (i == 1) page = 15;
				if (i == 3) page == 16;
			}
			else if (page == 15)
			{
				if (i == 1) page == 16;
			}
			else if (page == 16)
			{
				if (i == 1) page = 15;
			}
		}
	}
}
//������ �ѷ��� ��Ʈ
void mapTool::sampleSetRc()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (page > 0 && page < 4)
			{
				rc[i] = RectMakeCenter((_sampleBook.rc.left + 150) + i * 150, _sampleBook.rc.top + 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
				rc[i + 2] = RectMakeCenter((_sampleBook.rc.right - 300) + i * 150, _sampleBook.rc.top + 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
				rc[i + 4] = RectMakeCenter((_sampleBook.rc.left + 150) + i * 150, _sampleBook.rc.bottom - 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
				rc[i + 6] = RectMakeCenter((_sampleBook.rc.right - 300) + i * 150, _sampleBook.rc.bottom - 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
			}
			else if (page == 4)
			{
				rc[i] = RectMakeCenter((_sampleBook.rc.left + 150) + i * 150, _sampleBook.rc.top + 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
				rc[i + 2] = RectMakeCenter((_sampleBook.rc.right - 300) + i * 150, _sampleBook.rc.top + 219, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
				rc[i + 4] = RectMakeCenter((_sampleBook.rc.left + 150) + i * 150, _sampleBook.rc.bottom - 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
				rc[i + 6] = RectMakeCenter((_sampleBook.rc.right - 300) + i * 150, _sampleBook.rc.bottom - 219, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
			}
			else if (page == 5)
			{
				rc[i] = RectMakeCenter((_sampleBook.rc.left + 150) + i * 150, _sampleBook.rc.top + 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
				rc[i + 2] = RectMakeCenter((_sampleBook.rc.right - 300) + i * 86, _sampleBook.rc.top + 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
				rc[i + 4] = RectMakeCenter((_sampleBook.rc.left + 150) + i * 150, _sampleBook.rc.bottom - 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
				rc[i + 6] = RectMakeCenter((_sampleBook.rc.right - 300) + i * 86, _sampleBook.rc.bottom - 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
			}
			//������ ����ִ°�
			else if (page == 6)
			{
				rc[i] = RectMakeCenter((_sampleBook.rc.left + 150) + i * 150, _sampleBook.rc.top + 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
				rc[i + 2] = RectMakeCenter((_sampleBook.rc.right - 300) + i * 86, _sampleBook.rc.top + 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
				rc[i + 4] = RectMakeCenter((_sampleBook.rc.left + 150) + i * 150, _sampleBook.rc.bottom - 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
				rc[i + 6] = RectMakeCenter((_sampleBook.rc.right - 300) + i * 86, _sampleBook.rc.bottom - 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
			}
			else if (page == 7)
			{
				rc[i] = RectMakeCenter((_sampleBook.rc.left + 150) + i * 150, _sampleBook.rc.top + 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
				rc[i + 2] = RectMakeCenter((_sampleBook.rc.right - 300) + i * 86, _sampleBook.rc.top + 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
				rc[i + 4] = RectMakeCenter((_sampleBook.rc.left + 150) + i * 150, _sampleBook.rc.bottom - 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
				rc[i + 6] = RectMakeCenter((_sampleBook.rc.right - 300) + i * 86, _sampleBook.rc.bottom - 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
			}
			else if (page == 8)
			{
				rc[i] = RectMakeCenter((_sampleBook.rc.left + 150) + i * 150, _sampleBook.rc.top + 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
				rc[i + 2] = RectMakeCenter((_sampleBook.rc.right - 300) + i * 86, _sampleBook.rc.top + 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
				rc[i + 4] = RectMakeCenter((_sampleBook.rc.left + 150) + i * 150, _sampleBook.rc.bottom - 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
				rc[i + 6] = RectMakeCenter((_sampleBook.rc.right - 300) + i * 86, _sampleBook.rc.bottom - 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
			}
			else if (page == 9)
			{
				rc[i] = RectMakeCenter((_sampleBook.rc.left + 150) + i * 150, _sampleBook.rc.top + 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
				rc[i + 2] = RectMakeCenter((_sampleBook.rc.right - 300) + i * 86, _sampleBook.rc.top + 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
				rc[i + 4] = RectMakeCenter((_sampleBook.rc.left + 150) + i * 150, _sampleBook.rc.bottom - 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
				rc[i + 6] = RectMakeCenter((_sampleBook.rc.right - 300) + i * 86, _sampleBook.rc.bottom - 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
			}
			else if (page == 10)
			{
				rc[i] = RectMakeCenter((_sampleBook.rc.left + 150) + i * 150, _sampleBook.rc.top + 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
				rc[i + 2] = RectMakeCenter((_sampleBook.rc.right - 300) + i * 86, _sampleBook.rc.top + 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
				rc[i + 4] = RectMakeCenter((_sampleBook.rc.left + 150) + i * 150, _sampleBook.rc.bottom - 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
				rc[i + 6] = RectMakeCenter((_sampleBook.rc.right - 300) + i * 86, _sampleBook.rc.bottom - 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
			}
			else if (page == 11)
			{
				rc[i] = RectMakeCenter((_sampleBook.rc.left + 150) + i * 150, _sampleBook.rc.top + 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
				rc[i + 2] = RectMakeCenter((_sampleBook.rc.right - 300) + i * 86, _sampleBook.rc.top + 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
				rc[i + 4] = RectMakeCenter((_sampleBook.rc.left + 150) + i * 150, _sampleBook.rc.bottom - 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
				rc[i + 6] = RectMakeCenter((_sampleBook.rc.right - 300) + i * 86, _sampleBook.rc.bottom - 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
			}
			else if (page == 12)
			{
				rc[i] = RectMakeCenter((_sampleBook.rc.left + 150) + i * 150, _sampleBook.rc.top + 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
				rc[i + 2] = RectMakeCenter((_sampleBook.rc.right - 300) + i * 86, _sampleBook.rc.top + 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
				rc[i + 4] = RectMakeCenter((_sampleBook.rc.left + 150) + i * 150, _sampleBook.rc.bottom - 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
				rc[i + 6] = RectMakeCenter((_sampleBook.rc.right - 300) + i * 86, _sampleBook.rc.bottom - 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
			}
			else if (page == 13)
			{
				rc[i] = RectMakeCenter((_sampleBook.rc.left + 150) + i * 150, _sampleBook.rc.top + 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
				rc[i + 2] = RectMakeCenter((_sampleBook.rc.right - 300) + i * 86, _sampleBook.rc.top + 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
				rc[i + 4] = RectMakeCenter((_sampleBook.rc.left + 150) + i * 150, _sampleBook.rc.bottom - 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
				rc[i + 6] = RectMakeCenter((_sampleBook.rc.right - 300) + i * 86, _sampleBook.rc.bottom - 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
			}
			else if (page == 14)
			{
				rc[i] = RectMakeCenter((_sampleBook.rc.left + 150) + i * 150, _sampleBook.rc.top + 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
				rc[i + 2] = RectMakeCenter((_sampleBook.rc.right - 300) + i * 86, _sampleBook.rc.top + 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
				rc[i + 4] = RectMakeCenter((_sampleBook.rc.left + 150) + i * 150, _sampleBook.rc.bottom - 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
				rc[i + 6] = RectMakeCenter((_sampleBook.rc.right - 300) + i * 86, _sampleBook.rc.bottom - 200, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
			}
		}
	}
}

void mapTool::setPageSample()
{
	for (int i = 0; i < 8; i++)
	{
		if (page == 1)
		{
			if (i < 4)
			{
				sampleImage[i]->setFrameX(i);
				sampleImage[i]->setFrameY(0);
			}
			else
			{
				sampleImage[i]->setFrameX(i - 4);
				sampleImage[i]->setFrameY(1);
			}

		}
		else if (page == 2)
		{
			if (i < 4)
			{
				sampleImage[i]->setFrameX(i);
				sampleImage[i]->setFrameY(2);
			}
			else
			{
				sampleImage[i]->setFrameX(i - 4);
				sampleImage[i]->setFrameY(3);
			}
		}
		else if (page == 3)
		{
			if (i < 4)
			{
				sampleImage[i]->setFrameX(i + 4);
				sampleImage[i]->setFrameY(0);
			}
			else
			{
				sampleImage[i]->setFrameX(i);
				sampleImage[i]->setFrameY(1);
			}
		}
		else if (page == 4)
		{
			if (i < 4)
			{
				sampleImage[i]->setFrameX(i + 8);
				sampleImage[i]->setFrameY(0);
			}
			else
			{
				sampleImage[i]->setFrameX(i + 4);
				sampleImage[i]->setFrameY(1);
			}
		}
		else if (page == 5)
		{
			if (i < 4)
			{
				sampleImage[i]->setFrameX(i + 4);
				sampleImage[i]->setFrameY(2);
			}
			else
			{
				sampleImage[i]->setFrameX(i);
				sampleImage[i]->setFrameY(3);
			}
		}
		//������ �߰��ϴ���
		else if (page == 6)
		{
			if (i < 4)
			{
				sampleImage[i]->setFrameX(i);
				sampleImage[i]->setFrameY(4);
			}
			else
			{
				sampleImage[i]->setFrameX(i - 4);
				sampleImage[i]->setFrameY(5);
			}
		}
		else if (page == 7)
		{
			if (i < 4)
			{
				sampleImage[i]->setFrameX(i + 4);
				sampleImage[i]->setFrameY(4);
			}
			else
			{
				sampleImage[i]->setFrameX(i);
				sampleImage[i]->setFrameY(5);
			}
		}
		else if (page == 8)
		{
			if (i < 4)
			{
				sampleImage[i]->setFrameX(i);
				sampleImage[i]->setFrameY(6);
			}
			else
			{
				sampleImage[i]->setFrameX(i);
				sampleImage[i]->setFrameY(6);
			}
		}
		else if (page == 9)
		{
			if (i < 4)
			{
				sampleImage[i]->setFrameX(i);
				sampleImage[i]->setFrameY(7);
			}
			else
			{
				sampleImage[i]->setFrameX(i - 4);
				sampleImage[i]->setFrameY(8);
			}
		}
		else if (page == 10)
		{
			if (i < 4)
			{
				sampleImage[i]->setFrameX(i);
				sampleImage[i]->setFrameY(9);
			}
			else
			{
				sampleImage[i]->setFrameX(i - 4);
				sampleImage[i]->setFrameY(10);
			}
		}
		else if (page == 11)
		{
			if (i < 4)
			{
				sampleImage[i]->setFrameX(i + 4);
				sampleImage[i]->setFrameY(7);
			}
			else
			{
				sampleImage[i]->setFrameX(i);
				sampleImage[i]->setFrameY(8);
			}
		}
		else if (page == 12)
		{
			if (i < 4)
			{
				sampleImage[i]->setFrameX(i + 4);
				sampleImage[i]->setFrameY(9);
			}
			else
			{
				sampleImage[i]->setFrameX(i);
				sampleImage[i]->setFrameY(10);
			}
		}
		else if (page == 13)
		{
			if (i < 4)
			{
				sampleImage[i]->setFrameX(i + 8);
				sampleImage[i]->setFrameY(6);
			}
			else
			{
				sampleImage[i]->setFrameX(i + 4);
				sampleImage[i]->setFrameY(7);
			}
		}
		else if (page == 14)
		{
			if (i < 4)
			{
				sampleImage[i]->setFrameX(i + 8);
				sampleImage[i]->setFrameY(8);
			}
			else
			{
				sampleImage[i]->setFrameX(i + 4);
				sampleImage[i]->setFrameY(9);
			}
		}
	}
}

void mapTool::setMap()
{


	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (PtInRect(&_tiles[i].rc, m_ptMouse))
		{
			if (_select == TRRAINDRAW)
			{
				_tiles[i].terrainFrameX = _currnetTile.x;
				_tiles[i].terrainFrameY = _currnetTile.y;

				if (page < 8) _tiles[i].terrain = dungeonTerrainSelect(_currnetTile.x, _currnetTile.y);
				else _tiles[i].terrain = villageTerrainSelect(_currnetTile.x, _currnetTile.y);
			}
			if (_select == OBJDRAW)
			{
				_tiles[i].objFrameX = _currnetTile.x;
				_tiles[i].objFrameY = _currnetTile.y;

				if (page < 8)_tiles[i].obj = dungeonObjSelect(_currnetTile.x, _currnetTile.y);
				else _tiles[i].obj = villageObjSelect(_currnetTile.x, _currnetTile.y);

			}
			if (_select == ERASER)
			{
				if (_tiles[i].obj != OBJ_NONE)
				{
					_tiles[i].objFrameX = NULL;
					_tiles[i].objFrameY = NULL;

					_tiles[i].obj = OBJ_NONE;
				}
				else
				{
					_tiles[i].terrainFrameX = NULL;
					_tiles[i].terrainFrameY = NULL;

					_tiles[i].terrain = TERAIN_NONE;
				}
			}
		}
	}
}

void mapTool::setSampleMap()
{
	for (int i = 0; i < 8; i++)
	{
		if (PtInRect(&rc[i], m_ptMouse))
		{
			_currnetTile.x = sampleImage[i]->getFrameX();
			_currnetTile.y = sampleImage[i]->getFrameY();
			break;
		}
	}
}

void mapTool::drage()
{
	if (_start.x == NULL && _start.y == NULL) return;

	POINT temp;

	if (_start.x > _end.x)
	{
		temp.x = _start.x;
		_start.x = _end.x;
		_end.x = temp.x;
	}

	if (_start.y > _end.y)
	{
		temp.y = _start.y;
		_start.y = _end.y;
		_end.y = temp.y;
	}

	RECT d_rc;

	SetRect(&d_rc, _start.x, _start.y, _end.x, _end.y);

	RECT tempRc;

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (IntersectRect(&tempRc, &d_rc, &_tiles[i].rc))
		{
			if (_select == TRRAINDRAW)
			{
				_tiles[i].terrainFrameX = _currnetTile.x;
				_tiles[i].terrainFrameY = _currnetTile.y;

				_tiles[i].terrain = dungeonTerrainSelect(_currnetTile.x, _currnetTile.y);
			}
			else if (_select == OBJDRAW)
			{
				_tiles[i].objFrameX = _currnetTile.x;
				_tiles[i].objFrameY = _currnetTile.y;

				_tiles[i].obj = dungeonObjSelect(_currnetTile.x, _currnetTile.y);
			}
			else if (_select == ERASER)
			{
				if (_tiles[i].obj != OBJ_NONE)
				{
					_tiles[i].objFrameX = NULL;
					_tiles[i].objFrameY = NULL;

					_tiles[i].obj = OBJ_NONE;
				}
				else
				{
					_tiles[i].terrainFrameX = NULL;
					_tiles[i].terrainFrameY = NULL;

					_tiles[i].terrain = TERAIN_NONE;
				}
			}
		}
	}

	_start.x = NULL;
	_start.y = NULL;
	_end.x = NULL;
	_end.y = NULL;
}

TERRAIN mapTool::dungeonTerrainSelect(int frameX, int frameY)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			if (frameX == i && frameY == j || frameX == 3 && frameY == 2 || frameX == 3 && frameY == 3)
			{
				return TERAIN_WALL;
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 3; j < 4; j++)
		{
			return TERAIN_GROUND;
		}
	}

	return TERAIN_NONE;
}

OBJECT mapTool::dungeonObjSelect(int frameX, int frameY)
{
	for (int i = 5; i < 13; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			//������Ʈ ��
			if (i <= 5 && j == 0 || i == 0 && j == 1)
			{
				if (frameX == i && frameY == j) return OBJ_WALL;
			}

			//�ذ� ������Ʈ
			if (i >= 4 && i <= 5 && j == 0)
			{
				if (frameX == i && frameY == j) return OBJ_SKULL;
			}

			//�� ������Ʈ
			if (i >= 8 && j >= 0 && j <= 1)
			{
				if (frameX == i && frameY == j) return OBJ_DOOR;
			}
			//�׾Ƹ� ������Ʈ
			if (i >= 4 && i <= 5 && j == 1)
			{
				if (frameX == i && frameY == j) return OBJ_JAR;
			}

			//���
			if (i == 6 && j == 0) return OBJ_PILLAR;

			if (i >= 0 && i <= 7 && j >= 4 && j <= 5)
			{
				return OBJ_HELL_SPA;
			}

			if (i == 7 && j == 0) return OBJ_BOX;

			if (i >= 4 && i <= 6 && j >= 2 && j <= 3) return OBJ_TENT;
		}
	}

	return OBJ_NONE;
}

TERRAIN mapTool::villageTerrainSelect(int frameX, int frameY)
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 6; j < 11; j++)
		{
			if (frameX == i && frameY == j || frameX == 3 && frameY == 2 || frameX == 3 && frameY == 3)
			{
				return TERAIN_GROUND;
			}
		}
	}

	return TERAIN_NONE;
}

OBJECT mapTool::villageObjSelect(int frameX, int frameY)
{
	for (int i = 9; i < 13; i++)
	{
		for (int j = 6; j < 11; j++)
		{
			//������Ʈ ����+�칰
			if (i >= 9 && j >= 6 && j <= 7)
			{
				if (frameX == i && frameY == j) return OBJ_WALL;
			}
			//������Ʈ ����
			if (i >= 9 && i <= 10 && j >= 8 && j <= 9)
			{
				if (frameX == i && frameY == j) return OBJ_WALL;
			}
			//������Ʈ ����
			if (i == 12 && j == 9)
			{
				if (frameX == i && frameY == j) return OBJ_WALL;
			}
			//������Ʈ ��������
			if (i >= 11 && i <= 12 && j == 8)
			{
				if (frameX == i && frameY == j) return OBJ_JAR;
			}
			//������Ʈ ��ũ��
			if (i >= 11 && j == 9)
			{
				if (frameX == i && frameY == j) return OBJ_JAR;
			}
		}
	}

	return OBJ_NONE;
}
