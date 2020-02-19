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
	if (SOUNDMANAGER->getCurrentSong() != "회복방브금")
	{
		SOUNDMANAGER->stop(SOUNDMANAGER->getCurrentSong());
		SOUNDMANAGER->setCurrentNum(4);
		SOUNDMANAGER->play("회복방브금", 1);
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
	("save/맵3.map",			//생성할 파일또는 열 장치나 파일이름
		GENERIC_READ,		//파일이나 장치를 만들거나 열때 사용할 권한
		0,					//파일 공유 모드입력
		NULL,				//파일또는 장치를 열때 보안 및 특성
		OPEN_EXISTING,		//파일이나 장치를 열때 취할 행동
		FILE_ATTRIBUTE_NORMAL, //파일이나 장치를 열때 갖게 될 특성
		NULL);				//만들어질 파일이 갖게 될 특성 확장 특성에 대한 정보

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
		SCENEMANAGER->changeScene("던전5");
		PLAYER->setXY(WINSIZEX / 2, WINSIZEY - 50);
	}
	if (IntersectRect(&temp, &PLAYER->getPlayercollision(), &door[1]))
	{
		SCENEMANAGER->changeScene("던전1");
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
			else IMAGEMANAGER->frameRender("맵툴", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);

			if (_tiles[i].obj == OBJ_NONE) continue;

			IMAGEMANAGER->frameRender("맵툴", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
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
