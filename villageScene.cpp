#include "stdafx.h"
#include "villageScene.h"

villageScene::villageScene(){}
villageScene::~villageScene(){}

HRESULT villageScene::init()
{
	if (SOUNDMANAGER->getCurrentSong() != "마을브금")
	{
		SOUNDMANAGER->stop(SOUNDMANAGER->getCurrentSong());
		SOUNDMANAGER->setCurrentNum(1);
		SOUNDMANAGER->play("마을브금", 1);
	}
	PLAYER->setPlayerLocation(SHOP_PLAYER_VERSION);
	PLAYER->setPlayerMoving(PLAYER_DOWN_IDLE);

	_npcImg_witch = IMAGEMANAGER->findImage("위치");
	_npcAni_witch = ANIMATIONMANAGER->findAnimation("위치기본모션");
	_npcImg_black = IMAGEMANAGER->findImage("벌컨");
	_npcAni_black = ANIMATIONMANAGER->findAnimation("벌컨기본모션");


	//npc상점 2개 초기화
	_potionShop = new NPCpotionShop;
	_potionShop->init(PointMake(WINSIZEX - 100, WINSIZEY-420));
	_blacksmith = new NPCblacksmith;
	_blacksmith->init(PointMake(WINSIZEX - 120, WINSIZEY - 200));


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
	("save/맵5.map",			//생성할 파일또는 열 장치나 파일이름
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

	_dungeon = RectMake(0, -60, 100, 100);
	_shop = RectMake(WINSIZEX/2 - 100, 200, 100, 100);
	return S_OK;
}

void villageScene::relaese(){
	SAFE_DELETE(_potionShop);
	SAFE_DELETE(_blacksmith);
}

void villageScene::update()
{
	PLAYER->update();
	ANIMATIONMANAGER->update();
	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		SCENEMANAGER->changeScene("던전1");
	}
	RECT temp;
	_potionShop->update();
	_blacksmith->update();
	if(_potionShop->getOpen())_potionShop->buy();
	if (_blacksmith->getOpen())_blacksmith->buy();
	if (IntersectRect(&temp, &_dungeon, &PLAYER->getPlayercollision()))
	{
		SCENEMANAGER->changeScene("던전1");
		PLAYER->setXY(WINSIZEX / 2, WINSIZEY - 10);
	}
	if (IntersectRect(&temp, &_shop, &PLAYER->getPlayercollision()))
	{
		SCENEMANAGER->changeScene("플레이어상점씬");
		PLAYER->setXY(WINSIZEX / 2+100, WINSIZEY-250);
		
	}

}

void villageScene::render()
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

	if (KEYMANAGER->isToggleKey(VK_TAB))Rectangle(getMemDC(), _dungeon.left, _dungeon.top, _dungeon.right, _dungeon.bottom);
	if (KEYMANAGER->isToggleKey(VK_TAB))Rectangle(getMemDC(), _shop.left, _shop.top, _shop.right, _shop.bottom);
	_npcImg_witch->aniRender(getMemDC(), _potionShop->getNpcRc().left, _potionShop->getNpcRc().top+30, _npcAni_witch);
	_npcImg_black->aniRender(getMemDC(), _blacksmith->getNpcRc().left, _blacksmith->getNpcRc().top+20, _npcAni_black);
	IMAGEMANAGER->render("마을대장간이미지", getMemDC(), WINSIZEX - 200, WINSIZEY - 200);
	IMAGEMANAGER->render("마을포션상점이미지", getMemDC(), WINSIZEX - 310, WINSIZEY - 700);
	IMAGEMANAGER->render("플레이어상점이미지", getMemDC(), WINSIZEX / 2-200, 80);
	IMAGEMANAGER->render("던전문", getMemDC(), -10, -50);
	_potionShop->render();
	_blacksmith->render();
	PLAYER->render(getMemDC());
}
