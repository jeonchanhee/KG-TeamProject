#pragma once
#include"gameNode.h"

enum STORAGE_STATE
{
	STORAGE_OPEN,
	STORAGE_CLOSE
};
enum CURSOR_STATE
{
	CURSOR_IDLE,
	CURSOR_MOVE,
	CURSOR_GRAB
};
struct strorage
{
	image* inGameImage; //�����̹���
	RECT rc;	//���ڰ� ��ġ�� ��
	animation* storageAni; //â�� �ִϸ��̼�
	vector<item> vStorstorage; //�������� ���� ����
	STORAGE_STATE storageState; //â���� ����. ����orŬ����
};
struct storageCursor
{
	image* image; //Ŀ���� �̹���
	CURSOR_STATE cursorState; //Ŀ������
	RECT rc; //Ŀ���� ��ġ
	animation* ani; //Ŀ���� �ִϸ��̼�
	int cursorMove; //Ŀ���� �������� ����� ����. â���� �迭�����ƴٳ༭ Ŀ���� ������.
};

class playerShop : public gameNode
{
private:
	image* _mainImage; //���ڸ����� ������ â���κ��丮
	image* _slotImage[28];
	RECT _slot[28];		//â�� �������� �����۽���
	strorage _storage1;
	strorage _storage2;
	strorage _storage[2];

	image* _showItem;	//�κ� ������ �����ۺ����ִ�â
	RECT _showItemRc;

	storageCursor _cursor;
	image* _open;//���� �̹���
	RECT _openRc;//���� ��Ʈ
	RECT temp;

public:

	playerShop();
	~playerShop();

	HRESULT init();
	void release();
	void update();
	void render();

	void setStorage(); // â�� �ʱ�ȭ ���
	void controlStorage();// â�� ���
	void storageRender(); //â���� �ִϸ��̼� ���


	void controlCursor(); //Ŀ�������Ӵ��
	void cursorRender();//Ŀ�� �ִϸ��̼Ǵ��
};

