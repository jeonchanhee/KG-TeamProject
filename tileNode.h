#pragma once

//Ÿ�ϻ�����
#define TILESIZE 50

//ũ��
#define TILEX 50
#define TILEY 50

//Ÿ�� �� ������
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

//Ÿ�ϼ� (����Ÿ��)
#define SAMPLETILEX 12
#define SAMPLETILEY 8

//����
enum TERRAIN
{
	//�ƹ��͵�����	��			��
	TERAIN_NONE, TERAIN_WALL, TERAIN_GROUND
};

//������Ʈ
enum OBJECT
{
	//			��		�׾Ƹ�	�ذ�			���			������õ			��Ʈ		��ġ��		��
	OBJ_NONE, OBJ_WALL, OBJ_JAR, OBJ_SKULL, OBJ_PILLAR, OBJ_HELL_SPA, OBJ_TENT, OBJ_HOLDER, OBJ_DOOR, OBJ_BOX
};

//������ ����
enum POS
{

};

//Ÿ�ϱ���ü
struct tagTile
{
	TERRAIN terrain;			//����
	OBJECT obj;					//������Ʈ
	RECT rc;					//��Ʈ
	int terrainFrameX;			//���� �����ӹ�ȣ
	int terrainFrameY;			
	int objFrameX;				//������Ʈ �����ӹ�ȣ
	int objFrameY;
	int x, y;					//Ÿ�� ������ǥ
};

//����Ÿ�� ����ü
struct tagSampleTile
{
	RECT rcTile;				//����Ÿ�� ��Ʈ
	int terrainFrameX;			//����Ÿ�� ������ ��ȣ
	int terrainFrameY;			
};

//����Ÿ��(���� Ŭ���� Ÿ�� ���� �����)
struct tagCurrentTile
{
	int x;
	int y;
};