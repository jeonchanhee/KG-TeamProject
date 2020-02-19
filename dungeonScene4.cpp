#include "stdafx.h"
#include "dungeonScene4.h"

dungeonScene4::dungeonScene4()
{
}

dungeonScene4::~dungeonScene4()
{
}

HRESULT dungeonScene4::init()
{
	if (SOUNDMANAGER->getCurrentSong() != "ȸ������")
	{
		SOUNDMANAGER->stop(SOUNDMANAGER->getCurrentSong());
		SOUNDMANAGER->setCurrentNum(4);
		SOUNDMANAGER->play("ȸ������", 1);
	}
	PLAYER->setPlayerLocation(DUNGEON_PLAYER_VERSION);
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

	HANDLE file;
	DWORD read;

	file = CreateFile
	("save/��3.map",			//������ ���϶Ǵ� �� ��ġ�� �����̸�
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

	door[0] = RectMakeCenter(WINSIZEX / 2, 50, 100, 100);
	door[1] = RectMakeCenter(WINSIZEX / 2, WINSIZEY-22, 100, 100);
	healSpa = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 300, 300);
	return S_OK;
}

void dungeonScene4::relaese()
{
}

void dungeonScene4::update()
{
	ANIMATIONMANAGER->update();
	PLAYER->update();
	RECT temp;
	if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &door[0]))
	{
		SCENEMANAGER->changeScene("����5");
		PLAYER->setXY(WINSIZEX / 2, WINSIZEY - 50);
	}
	if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &door[1]))
	{
		SCENEMANAGER->changeScene("����1");
		PLAYER->setXY(WINSIZEX / 2, 150);
	}


	if (IntersectRect(&temp, &healSpa, &PLAYER->getPlayercollision()))
	{
		if(PLAYER->getHP() <= 100) PLAYER->setHP(PLAYER->getHP()+10);
	}
}

void dungeonScene4::render()
{
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
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (int i = 0; i < 3; i++)
		{
			Rectangle(getMemDC(), door[i].left, door[i].top, door[i].right, door[i].bottom);
		}
	}
	PLAYER->render(getMemDC());
}
