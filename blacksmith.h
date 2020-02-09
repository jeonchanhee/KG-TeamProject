#pragma once
#include"gameNode.h"
#include"cursor.h"
#define SLOTNUM 9
class blacksmith:public gameNode
{
private:

	//image* ���� �ΰ����̹���

	image*   _armorTabImg;					//�� �����ִ���
	image*   _swordTabImg;					//�� �����ִ���
	image*   _bowTabImg;					//Ȱ �����ִ���
	image*   _showImg;						//�� �����ۺ����ִ� â
	image*   _itemSlotImg[9];				//���׷��̵��� �����ִ� ����
	image*   _titleImg;						//������ ���尣 Ÿ��Ʋ
	image*   _npcImg;						//�����̹���
	image*   _recipeImg;					//���׷��̵���� �� �����۽��Ⱥ����ִ�â
	image*   _recipeSlotImg[3];				//���׷��̵���� ������ �̹���
			 
	RECT	 _armorTab;			
	RECT	 _swordTab;
	RECT	 _bowTab;
	int		 _currentTab;						//���� ���� ����Ű�� ����

	RECT	 _itemSlot[9];						//���׷��̵���
	RECT	 _recipeSlot[3];					//�����

	RECT	_npcRc;
	bool _showWindow;				//true�� �Ǹ� ���尣 â�� ��

	//Ŀ��
	RECT _choiceSlot;				//�ۼ����ϴ·�Ʈ
	int _choiceNum;					//��������� ���õǾ�����
	image* _grab;	
	cursor* _cursor;

public:

	blacksmith();
	~blacksmith();

	HRESULT init();
	void release();
	void update();
	void render();

	void cursorControl();								//Ŀ���� ������WASD
	void tabControl();									//���尣���� �������� �����ϴ� �Լ�. ���� ���� Ȱ��
	void setShow(bool show) { _showWindow = show; }		//true�� �Ǹ� ���尣 â�� ��

	RECT getRECT() { return _npcRc; }					//�÷��̾�� �浹�Ҷ���
};

