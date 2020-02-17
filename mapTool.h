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

enum SELECT
{
	TRRAINDRAW,
	OBJDRAW,
	ERASER
};



class mapTool : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY];
	tagSampleTile _sampleTile[SAMPLETILEX * SAMPLETILEY];
	tagCurrentTile _currnetTile;

	tagSampleBook _sampleBook;

	tagBottun bottun[4];

	RECT rc[8];

	int page;
	//������ 1~7 ����
	//������ 8~14 ����
	//������ 15~16 ���̺�ε�
	image* sampleImage[8]; // �������� ���缭 �Է��� �̹���
	bool first;
	bool mouse;

	SELECT _select;

	POINT _start;
	POINT _end;


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
	void sampleBookKey();
	void setSampleBookBottun();
	void sampleBookBottunControl();
	void setSampleTile();
	void sampleSetRc();
	void setPageSample();
	void setMap();
	void setSampleMap();

	void drage();

	TERRAIN dungeonTerrainSelect(int frameX, int frameY);
	OBJECT	dungeonObjSelect(int frameX, int frameY);
	TERRAIN villageTerrainSelect(int frameX, int frameY);
	OBJECT	villageObjSelect(int frameX, int frameY);
};

