#pragma once
#include"gameNode.h"
#include"cursor.h"
#define SLOTNUM 9
class NPCshopBase :public gameNode
{
private:

protected:
	string _name;
	image*   _npcImg;                  //������ NPC���
	animation* _npcAni;                  //npc�ִ�
	image*   _titleImg;                  //â�� �߸� �߾� ��ܿ� ������ Ÿ��Ʋ
	image*   _showImg;                  //������ ������ �����ִ� â
	image*   _itemSlotImg[9];            //���׷��̵����� ���ִ� ����
	image*   _recipeImg;               //���׷��̵���� �� �����۽��� �����ִ�â
	image*   _recipeSlotImg[3];            //���׷��̵���� ������ �̹���

	RECT    _itemSlot[9];               //������ ����
	RECT    _recipeSlot[3];            //�����

	int      _OKcnt[3];                  //������� �����ִ��� Ȯ���ϴ� �뵵. OKcnt�� ���� 0�̵Ǹ� ���Ž���   
	int       _currentTab;               //���� ���� ����Ű�� ����

	RECT   _npcRc;                     //�÷��̾ �̳༮�� �浹�ϸ� ȭ���� ����
	bool   _showWindow;               //true�� �Ǹ� ���尣 â�� ��
	int _index;                        //�ִϸ��̼� ����� ����

	//Ŀ��
	RECT _cursorSlot;                  //�ۼ����ϴ·�Ʈ
	int _cursorNum;                     //��������� ���õǾ�����
	image* _grab;
	cursor* _cursor;

	//�����ۺ���
	vector<item> _vShowItem;            //���׷��̵� �������� ����� �����ֱ�..
	vector<item> _vShowRecipe;            //���׷��̵� �������� ��� �����ֱ�
	item _temp;                        //Ŀ���� ����Ű�� �ִ� ������.
	int _itemSetSlot;


	RECT temp;                        //��Ʈ�浹��      
	char str[128];                     //�ؽ�Ʈ�ƿ� ��¿�
public:

	NPCshopBase();
	~NPCshopBase();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void tabControl();
	virtual void cursorControl();               //Ŀ���� ������WASD

	void setRecipeItem();                     //Ŀ���� ����Ű�� ���� �����Ǹ� �����ϴ� �Լ�
	void makeRecipe(string makeItemName, string RecipeItemName1, string RecipeItemName2, string RecipeItemName3,
		int forNum, int itemCnt1, int itemCnt2, int itemCnt3); //�����Ǹ� �����ϴ� �Լ�

	void buy();                              //���Ű� �������� Ȯ���ϴ� �Լ�
	void buyItem();                           //���Ű� ����Ǵ� �Լ�
	void baseRender();                        //�⺻���� ����

	void playerCollision();                     //����ݱ�
};