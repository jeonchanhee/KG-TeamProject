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
#define SAMPLETILEX
#define SAMPLETILEY

//����
enum TERRAIN
{

};

//������Ʈ
enum OBJECT
{

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