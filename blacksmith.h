#pragma once
#include"gameNode.h"
#include"cursor.h"
#define SLOTNUM 9
class blacksmith :public gameNode
{
private:

	//image* �ΰ����̹���

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
	RECT	 _itemSlot[9];						//���׷��̵���
	RECT	 _recipeSlot[3];					//�����

	int		OKcnt[3];							//������� �����ִ��� Ȯ���ϴ� �뵵. OKcnt�� ���� 0�̵Ǹ� ���Ž���	
	int		 _currentTab;						//���� ���� ����Ű�� ����

	RECT	_npcRc;	//�÷��̾ �̳༮�� �浹�ϸ� ȭ���� ����
	bool	_showWindow;				//true�� �Ǹ� ���尣 â�� ��

	//Ŀ��
	RECT _cursorSlot;				//�ۼ����ϴ·�Ʈ
	int _cursorNum;					//��������� ���õǾ�����
	image* _grab;
	cursor* _cursor;

	//�����ۺ���
	vector<item> _vShowItem;	//���׷��̵� �������� ����� �����ֱ�..
	vector<item> _vShowRecipe;	//���׷��̵� �������� ��� �����ֱ�
	item _temp;					//Ŀ���� ����Ű�� �ִ� ������.

	RECT temp;
	int _itemSetSlot;			
	char str[128];				//�ؽ�Ʈ�ƿ� ��¿�
public:

	blacksmith();
	~blacksmith();

	HRESULT init();
	void release();
	void update();
	void render();
	void setShow(bool show) { _showWindow = show; }	//true�� �Ǹ� ���尣 �����찡 ��
	RECT getRECT() { return _npcRc; }			

	void cursorControl();							//Ŀ���� ������WASD
	void tabControl();								//���尣���� ���� ���� �ִ� ���� �����ϴ� �Լ�. ��,��,Ȱ


	void setRecipeItem();							//Ŀ���� ����Ű�� ���� �����Ǹ� �����ϴ� �Լ�
	void makeRecipe(string makeItemName, string RecipeItemName1, string RecipeItemName2, string RecipeItemName3, 
					int forNum, int itemCnt1, int itemCnt2, int itemCnt3); //�����Ǹ� �����ϴ� �Լ�

	void buy(vector<item> &storage);		//���Ű� �������� Ȯ���ϴ� �Լ�
	void buyItem(vector<item> &storage);	//���Ű� ����Ǵ� �Լ�

};