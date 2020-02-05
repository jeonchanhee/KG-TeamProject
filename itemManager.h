#pragma once
#include"item.h"
#include "singletonBase.h"

class itemManager : public item, public singletonBase<itemManager>
{
private:
	item _item;		//�������� �ʱ�ȭ�� ����

	vector<item> _vItem;  //�������� ���� ����
	vector<item>::iterator _viItem;


public:
	itemManager();
	~itemManager();

	HRESULT init();
	void release();
	void update();
	void render();

	item addItem(string itemName);  //�̸����� �������� ã�Ƽ� �����ִ� �Լ�
	vector<item> getItemList() { return _vItem; } //������ ���� ��ü�� ������ �Լ�

};

