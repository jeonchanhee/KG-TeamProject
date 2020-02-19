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
	RECT _dunitem;				//던전 아이템 충돌용 
	for (int i = 0; i < dungeonItem.size(); i++)
	{
		dungeonItem[i].update();
		if (IntersectRect(&_dunitem, &dungeonItem[i].getRECT(), &PLAYER->getPlayercollision()))
		{
			PLAYER->getinventory()->eatitem(dungeonItem[i]);
			dungeonItem.erase(dungeonItem.begin() + i);
			break;
		}
	}
	RECT temp;
	if (IntersectRect(&temp, &door[2], &PLAYER->getPlayercollision()))// && _monster->getVMonster().empty()
	{
		SCENEMANAGER->changeScene("던전4");
		PLAYER->setXY(WINSIZEX / 2, WINSIZEY- 150);
	}
	if (IntersectRect(&temp, &door[0], &PLAYER->getPlayercollision()))// && _monster->getVMonster().empty()
	{
		SCENEMANAGER->changeScene("던전2");
		PLAYER->setXY(WINSIZEX- 150, WINSIZEY/2);
	}
	if (IntersectRect(&temp, &door[1], &PLAYER->getPlayercollision()))// && _monster->getVMonster().empty()
	{
		SCENEMANAGER->changeScene("던전3");
		PLAYER->setXY(150, WINSIZEY/2);
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

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (int i = 0; i < 3; i++)
		{
			Rectangle(getMemDC(), door[i].left, door[i].top, door[i].right, door[i].bottom);
		}
	}
}
