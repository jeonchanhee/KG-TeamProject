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
	
	if (SOUNDMANAGER->getCurrentSong() != "던전브금")
	{
		SOUNDMANAGER->stop(SOUNDMANAGER->getCurrentSong());
		SOUNDMANAGER->setCurrentNum(2);
		SOUNDMANAGER->play("던전브금", 1);
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
	("save/맵1.map",			//생성할 파일또는 열 장치나 파일이름
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
			wsprintf(name, "던전%d", i + 2);
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
			else IMAGEMANAGER->frameRender("맵툴", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);

			if (_tiles[i].obj == OBJ_NONE) continue;

			IMAGEMANAGER->frameRender("맵툴", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
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
