#pragma once

#define MAGNETPOWER 2

enum itemType //������ ����
{
	ITEM_EMPTY,		 //�������
	ITEM_ARMOR,		 //�� 
	ITEM_HELMET,	 //���
	ITEM_BOOTS,		 //����
	ITEM_BOW,		 //Ȱ
	ITEM_SWORD,		 //�˰� ����
	ITEM_POTION,	 //����
	ITEM_ETC,		 //����(�����)
	ITEM_END
};
struct itemInfo
{
	image*		image;			//�̹���
	string		itemName;		//�̸�
	itemType	type;			//�������� ����
	RECT		rc;				//��Ʈ
	RECT		magnetRc;		//�ٴڿ� ������ ���¿��� �ֺ��� �÷��̾ �����ϴ� ��Ʈ

	bool		move;			//�ٴڿ� ������ ���������� �ƴ���

	int			orignalPrice;	//����
	int			playerPrice;	//�÷��̾ ���� ����

	int			atk;			//���ݷ�
	int			def;			//����
	int			speed;			//�ӵ� 
	int			hp;				//ü��

	int			heal;			//������ ȸ����
	int			cnt;			//��������
	int			maxCnt;			//�κ��丮 1ĭ�� �ִ��������
};

class item
{
private:
	itemInfo _item;

	bool updown; // �ٴڿ� ������ ���� ���Ʒ��� ��鸱�� ���� ����
	int waveCnt; //�ٴڿ� ������ ���� ���Ʒ��� ��鸱�� ���� ����
	RECT test;
public:
	item();
	~item();

	HRESULT init(const char* name, itemType type, bool move, int orignalPrice, int playerPrice,
				 int atk, int def, int speed, int hp, int heal, int cnt, int maxCnt);
	void release();
	void update();
	void render();

	void magnet(RECT playerRc); // �÷��̾�� �������� ���
	void wave(); //�ٴڿ� ������ �������� �ణ ��鸮�� ���
	itemInfo getItemInfo() {return _item;} //������ ������ ������
	RECT getRECT() { return _item.rc; } //�������� ��Ʈ�� ������
	// ��Ʈ�� ��ġ�� ����
	void setRect(int x, int y) { _item.rc = RectMakeCenter(x, y, _item.image->getWidth(), _item.image->getHeight()); } 
	void setRect(RECT rc) { _item.rc = rc; } 
	
	//�������� ���¸� �ٲ���(�κ��� ������ false, �ٴڿ� ������������ true)
	void setMove(bool move) { _item.move = move; } 

	void setItemCnt() { _item.cnt++; } // ����1����
	void setItemCnt(int num) { _item.cnt+= num; } //������ num��ŭ ����
	void setPlayerPrice(int price) { _item.playerPrice = price; } //�÷��̾ �����۰����� �����Ҷ� ���� �Լ�
																													  
	//string getType() { return _type; } // �̸��� ������
	//RECT getRect() { return _rc; } //rc�� ������



};

