#pragma once
#include"gameNode.h"
#include "singletonBase.h"

#define MAGNETPOWER 5
enum itemType //������ ����
{
	ITEM_EMPTY,		 //�������
	ITEM_ARMOR,		 //�� 
	ITEM_ARROW,		 //Ȱ
	ITEM_SWORD,		 //�˰� ����
	ITEM_ETC,		 //����(�����)
	ITEM_END
};

struct itemInfo //�������� �Ӽ�
{
	image*		image;			//�̹���
	string		name;			//�̸�
	string		description;	//����
	itemType	type;			//�������� ����
	RECT		rc;				//��Ʈ
	RECT		magnetRc;		//�ٴڿ� ������ ���¿��� �ֺ��� �÷��̾ �����ϴ� ��Ʈ
	bool		move;			//�ٴڿ� ������ ���������� �ƴ���

	int			orignalPrice;	//����
	int			playerPrice;	//�÷��̾ ���� ����

	int			atk;			//���ݷ�
	int			def;			//����
	int			speed;			//�ӵ� 
};

class item : public gameNode, public singletonBase<item>
{
private:
	itemInfo m_initItem;		//������ ���Ϳ� ���� �뵵�� ����

	vector<itemInfo> m_vItem;  //�������� ���� ����
	vector<itemInfo>::iterator m_viItem;

	
	RECT test;
public:
	item();
	~item();

	HRESULT init();
	void release();
	void update();
	void render();

	void magnet(RECT playerRc); //�ٴڿ� ������ �������ΰ�� �÷��̾�� �������� �Լ�

	itemInfo addItem(string itemName);  //�̸����� �������� ã�Ƽ� �����ִ� �Լ�
	void removeItem(int arrNum);		//�������� ���Ϳ��� ����� �Լ�
	vector<itemInfo> getItemList() { return m_vItem; } //������ ���� ��ü�� ������ �Լ�
};

