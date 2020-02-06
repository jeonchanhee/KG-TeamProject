#pragma once
#include"gameNode.h"
#include"tileNode.h"

struct tagBottun
{
	RECT rc;
	image* img;
	int x, y;
};


struct tagSampleBook
{
	tagBottun bottun[3];
	RECT rc;
	RECT sampleRc[10];
	image* img;
	bool Summons;
	int x, y;
};


class mapTool : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY];
	tagSampleTile _sampleTile[SAMPLETILEX * SAMPLETILEY];
	
	tagSampleBook _sampleBook;
	
public:
	mapTool();
	~mapTool();

	HRESULT init();
	void relaese();
	void update();
	void render();
	
	void save();
	void load();

	void cameraMove();
	void setUp();
	void mapInit();
	void setSampleBook();
	void controlSampleBook();
	void setSampleTile();


	TERRAIN dungeonTerrainSelect(int frameX, int frameY);
	OBJECT	dungeonObjSelect(int frameX, int frameY);
};

