#include "stdafx.h"
#include "mapTool.h"

mapTool::mapTool()
{
}

mapTool::~mapTool()
{
}

HRESULT mapTool::init()
{
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			SetRect(&_tiles[i * TILEX + j].rc, j * TILESIZE, i * TILESIZE, j* TILESIZE + TILESIZE, i * TILESIZE + TILESIZE);
		}
	}



	return S_OK;
}

void mapTool::relaese()
{

}

void mapTool::update()
{



}

void mapTool::render()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		Rectangle(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].rc.right, _tiles[i].rc.bottom);

		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			char str[128];
			sprintf_s(str, "%d", i);
			TextOut(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, str, strlen(str));
		}
	}



}

void mapTool::save()
{
}

void mapTool::load()
{
}
