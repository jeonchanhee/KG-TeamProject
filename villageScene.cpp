#include "stdafx.h"
#include "villageScene.h"

villageScene::villageScene(){}
villageScene::~villageScene(){}

HRESULT villageScene::init()
{
	if (SOUNDMANAGER->getCurrentSong() != "�������")
	{
		SOUNDMANAGER->stop(SOUNDMANAGER->getCurrentSong());
		SOUNDMANAGER->setCurrentNum(1);
		SOUNDMANAGER->play("�������", 1);
	}
	PLAYER->setPlayerLocation(SHOP_PLAYER_VERSION);
	PLAYER->setPlayerMoving(PLAYER_DOWN_IDLE);

	_npcImg_witch = IMAGEMANAGER->findImage("��ġ");
	_npcAni_witch = ANIMATIONMANAGER->findAnimation("��ġ�⺻���");
	_npcImg_black = IMAGEMANAGER->findImage("����");
	_npcAni_black = ANIMATIONMANAGER->findAnimation("�����⺻���");


	//npc���� 2�� �ʱ�ȭ
	_potionShop = new NPCpotionShop;
	_potionShop->init(PointMake(WINSIZEX - 120, WINSIZEY-420));
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
	("save/��5.map",			//������ ���϶Ǵ� �� ��ġ�� �����̸�
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

	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		SCENEMANAGER->changeScene("����1");
	}
	RECT temp;
	_potionShop->update();
	_blacksmith->update();
	_potionShop->buy();
	_blacksmith->buy();
	if (IntersectRect(&temp, &_dungeon, &PLAYER->getPlayercollision()))
	{
		SCENEMANAGER->changeScene("����a1");
		PLAYER->setXY(WINSIZEX / 2, WINSIZEY - 10);
	}
	if (IntersectRect(&temp, &_shop, &PLAYER->getPlayercollision()))
	{
		SCENEMANAGER->changeScene("�÷��̾������");
		
	}
	if(IntersectRect(&temp,&_dungeon,&PLAYER->getPlayercollision()))SCENEMANAGER->changeScene("����1");
	if (IntersectRect(&temp, &_shop, &PLAYER->getPlayercollision()))SCENEMANAGER->changeScene("�÷��̾������");
	
}

void villageScene::render()
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

	Rectangle(getMemDC(), _dungeon.left, _dungeon.top, _dungeon.right, _dungeon.bottom);
	Rectangle(getMemDC(), _shop.left, _shop.top, _shop.right, _shop.bottom);
	_npcImg_witch->aniRender(getMemDC(), _potionShop->getNpcRc().left, _potionShop->getNpcRc().top, _npcAni_witch);
	_npcImg_black->aniRender(getMemDC(), _blacksmith->getNpcRc().left, _blacksmith->getNpcRc().top, _npcAni_black);
	IMAGEMANAGER->render("�������尣�̹���", getMemDC(), WINSIZEX - 220, WINSIZEY - 200);
	IMAGEMANAGER->render("�������ǻ����̹���", getMemDC(), WINSIZEX - 330, WINSIZEY - 700);
	IMAGEMANAGER->render("�÷��̾�����̹���", getMemDC(), WINSIZEX / 2-200, 80);
	IMAGEMANAGER->render("������", getMemDC(), -10, -50);
	_potionShop->render();
	_blacksmith->render();
	PLAYER->render(getMemDC());
}
