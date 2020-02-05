#pragma once

//타일사이즈
#define TILESIZE 50

//크기
#define TILEX 50
#define TILEY 50

//타일 총 사이즈
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

//타일셋 (셈플타일)
#define SAMPLETILEX
#define SAMPLETILEY

//지형
enum TERRAIN
{

};

//오브젝트
enum OBJECT
{

};

//포지션 정의
enum POS
{

};

//타일구조체
struct tagTile
{
	TERRAIN terrain;			//지형
	OBJECT obj;					//오브젝트
	RECT rc;					//렉트
	int terrainFrameX;			//지형 프레임번호
	int terrainFrameY;			
	int objFrameX;				//오브젝트 프레임번호
	int objFrameY;
};

//셈플타일 구조체
struct tagSampleTile
{
	RECT rcTile;				//셈플타일 렉트
	int terrainFrameX;			//셈플타일 프레임 번호
	int terrainFrameY;			
};

//현재타일(내가 클릭한 타일 정보 저장용)
struct tagCurrentTile
{
	int x;
	int y;
};