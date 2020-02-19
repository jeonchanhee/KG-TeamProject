#include "stdafx.h"
#include "dungeonScene.h"
dungeonScene::dungeonScene()
{
}

dungeonScene::~dungeonScene()
{
}

HRESULT dungeonScene::init()
{
	
	if (SOUNDMANAGER->getCurrentSong() != "�������")
	{
		SOUNDMANAGER->stop(SOUNDMANAGER->getCurrentSong());
		SOUNDMANAGER->setCurrentNum(2);
		SOUNDMANAGER->play("�������", 1);
	}
	_monster = new monsterManager;
	_monster->init1();

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

void dungeonScene::relaese()
{
}

void dungeonScene::update()
{
	ANIMATIONMANAGER->update();
	PLAYER->update();
	_monster->update(dungeonItem);
	for (int i = 0; i < dungeonItem.size(); i++)
	{
		dungeonItem[i].update();
	}
	RECT temp;
	for (int i = 0; i < 3; i++)
	{
		if (IntersectRect(&temp, &door[i], &PLAYER->getPlayercollision()))
		{
			char name[128];
			wsprintf(name, "����%d", i + 2);
			SCENEMANAGER->changeScene(name);
		}
	}


}

void dungeonScene::render()
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
	_monster->render();
	if (!dungeonItem.empty()) {
		for (int i = 0; i < dungeonItem.size(); i++)
		{
			dungeonItem[i].getItemInfo().image->render(getMemDC(), dungeonItem[i].getItemInfo().rc.left, dungeonItem[i].getItemInfo().rc.top);
		}
	}

	PLAYER->render(getMemDC());

	for (int i = 0; i < 3; i++)
	{
		Rectangle(getMemDC(), door[i].left, door[i].top, door[i].right, door[i].bottom);
	}
}
