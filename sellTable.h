#pragma once
#include "gameNode.h"
#include "cursor.h"
#define SLOTNUM 4

struct sellSlot
{
	image*		img;		//���� �̹���
	RECT		rc;			//�Ǹ�â�� ������ ����
	item		item;
	float  x, y;
};
class sellTable : public gameNode
{
private:
	RECT		 _tableRc;					//�ǸŴ� ��Ʈ

	image*		 _sellMainImg;				//�Ǹ�â �̹���
	RECT		 _sellInfo[SLOTNUM];		//�Ǹž����� ���� ���ϴ� �κ��� ��Ʈ

	sellSlot _sellSlot;
	vector<sellSlot>	_vSlot;
	vector<sellSlot>	_vTemp;;


	int  _playerPrice[SLOTNUM][8];			//������ ���� �迭
	int  _BoxChoiceNum;						//�� ������ ����ؼ� _playerPrice �迭�� �̵��ϸ� Ű����� ������ ����


	bool   _selectNum;						//_sellInfo��Ʈ���� j�� ������ true�� �Ǿ� �������� ���ϴ� ��尡 ��
	image* _selectUpdownImg;				//�������Ҷ� ���Ʒ� ȭ��ǥ�ߴ� �̹���
	RECT   _selectUpdownRc;					//�������Ҷ� ���Ʒ� ȭ��ǥ�ߴ� �̹����� ��Ʈ

	//Ŀ��
	cursor* _cursor;
	RECT _cursorSlot;						//�ۼ����ϴ·�Ʈ(Ŀ��)
	int _cursorNum;							//��������� ���õǾ�����
	image* _grab;							//Ŀ���� ���� �������� ���
	bool _test;

	bool _showWindow;						//Ʈ��� â�� �����
	RECT temp;								//��Ʈ�浹��
	char str[128];							//�ؽ�Ʈ�ƿ� ��¿�

public:
	sellTable();
	~sellTable();

	HRESULT init();
	void release();
	void update();
	void render();

	void cursorControl();									//Ŀ�� ������ ����
	void selectPrice();										//������ ���ҋ�
	void removeItem();										//â�� ������ �����
	void grab();											//Ŀ���� �������� �������

};

