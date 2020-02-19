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
	("save/��1.map",			//������ ���϶Ǵ� �� ��ġ�� �����̸�
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

	door[0] = RectMakeCenter(50, WINSIZEY / 2, 100, 100);
	door[2] = RectMakeCenter(WINSIZEX / 2, 50, 100, 100);
	door[1] = RectMakeCenter(WINSIZEX - 75, WINSIZEY / 2, 100, 100);

	return S_OK;
}

void dungeonScene4::relaese()
{
}

void dungeonScene4::update()
{
}

void dungeonScene4::render()
{
}
