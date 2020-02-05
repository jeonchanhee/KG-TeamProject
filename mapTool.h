#pragma once
#include"gameNode.h"
#include"tileNode.h"


class mapTool : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY];
	tagSampleTile _sampleTile[SAMPLETILEX * SAMPLETILEY];
	
	
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

};

