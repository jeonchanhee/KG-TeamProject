#include "stdafx.h"
#include "playerShop.h"

playerShop::playerShop()
{
}

playerShop::~playerShop()
{
}

HRESULT playerShop::init()
{
	setStorage();
	for (int i = 0; i < 9; i++)
	{
		_storage1.vStorstorage.push_back(ITEMMANAGER->addItem("��������"));
	}
	_showItemRc = RectMakeCenter(WINSIZEX - 70, 250, _showItem->getWidth(), _showItem->getHeight());

	//Ŀ���ʱ�ȭ
	_cursor.image = IMAGEMANAGER->findImage("Ŀ��");
		_cursor.cursorState = CURSOR_IDLE;
	_cursor.rc = RectMake(_slot[0].left-10, _slot[0].top-10, 40, 40);

	int arrlen1[] = { 0,1,0 };
	ANIMATIONMANAGER->addAnimation("Ŀ���ִ�", "Ŀ��", arrlen1, 3, 10, false);
	_cursor.ani = ANIMATIONMANAGER->findAnimation("Ŀ���ִ�");
	_cursor.cursorMove = 0;

	return S_OK;
}

void playerShop::release()
{
}

void playerShop::update()
{
	controlStorage();
	controlCursor();
	if (KEYMANAGER->isOnceKeyDown('Q'))_storage1.vStorstorage.push_back(ITEMMANAGER->addItem("�������� �ܰ�"));
}

void playerShop::render()
{
	//Rectangle(getMemDC(), _storage1.rc.left, _storage1.rc.top, _storage1.rc.right, _storage1.rc.bottom);
	//Rectangle(getMemDC(), _storage2.rc.left, _storage2.rc.top, _storage2.rc.right, _storage2.rc.bottom);
	//Rectangle(getMemDC(), testPlayer.left, testPlayer.top, testPlayer.right, testPlayer.bottom);
	storageRender();
	cursorRender();
}

void playerShop::setStorage()
{
	//â��2�� + â���κ��丮 �ʱ�ȭ
	_open = IMAGEMANAGER->addImage("����", "images/shop/����.bmp", 193 / 2, 87 / 2, true, RGB(255, 0, 255));
	_storage1.inGameImage = IMAGEMANAGER->findImage("â��1");
	_storage2.inGameImage = IMAGEMANAGER->findImage("â��2");
	int arrlen1[] = { 0,1,2 };
	int arrlen2[] = { 3,4,5 };
	ANIMATIONMANAGER->addAnimation("â��1����", "â��1", arrlen1, 3, 10, false);
	ANIMATIONMANAGER->addAnimation("â��1Ŭ����", "â��1", arrlen2, 3, 10, false);
	int arrlen3[] = { 0,1,2,3 };
	int arrlen4[] = { 4,5,6,7 };
	ANIMATIONMANAGER->addAnimation("â��2����", "â��2", arrlen3, 3, 10, false);
	ANIMATIONMANAGER->addAnimation("â��2Ŭ����", "â��2", arrlen4, 3, 10, false);
	_storage1.storageAni = ANIMATIONMANAGER->findAnimation("â��1����");
	_storage1.rc = RectMakeCenter(WINSIZEX / 2 / 2, WINSIZEY / 2 / 2 + 150, _storage1.inGameImage->getFrameWidth(), _storage1.inGameImage->getFrameHeight());
	_storage1.storageState = STORAGE_CLOSE;

	_storage2.storageAni = ANIMATIONMANAGER->findAnimation("â��2����");
	_storage2.rc = RectMakeCenter(WINSIZEX / 2 / 2, WINSIZEY / 2 / 2, _storage2.inGameImage->getFrameWidth(), _storage2.inGameImage->getFrameHeight());
	_storage2.storageState = STORAGE_CLOSE;


	_mainImage = IMAGEMANAGER->findImage("â����");
	_showItem = IMAGEMANAGER->findImage("�ۺ����ֱ�");
	//â���κ��丮 ���� �ʱ�ȭ
	for (int i = 0; i < 28; i++)
	{
		int k, j;
		k = i % 7;
		j = i / 7;
		_slot[i] = RectMakeCenter(WINSIZEX / 2 + 20 + (k * 60), WINSIZEY / 2 - 60 + (j * 60), 40,40);
		_slotImage[i] = IMAGEMANAGER->findImage("�����̹���");
	}
}

void playerShop::controlStorage()
{
	if (IntersectRect(&temp, &_storage1.rc, &PLAYER->getPlayercollision())) //�÷��̾�� â�� �������
	{
		_openRc = RectMakeCenter(_storage1.rc.right, _storage1.rc.top, _open->getWidth(), _open->getHeight());
		if (KEYMANAGER->isOnceKeyDown('J'))
		{
			_storage1.storageAni->start();
			_cursor.rc = RectMake(_slot[0].left - 10, _slot[0].top - 10, 40, 40);
			_storage1.storageState = STORAGE_OPEN;
		}
	}
	if (IntersectRect(&temp, &_storage2.rc, &PLAYER->getPlayercollision()))
	{
		_openRc = RectMakeCenter(_storage2.rc.right, _storage2.rc.top, _open->getWidth(), _open->getHeight());
		if (KEYMANAGER->isOnceKeyDown('J'))
		{
			_storage2.storageAni->start();
			_cursor.rc = RectMake(_slot[0].left - 10, _slot[0].top - 10, 40, 40);
			_storage2.storageState = STORAGE_OPEN;
		}
	}

	switch (_storage1.storageState)	
	{
	case STORAGE_OPEN:
		if(KEYMANAGER->isOnceKeyDown('I'))_storage1.storageState = STORAGE_CLOSE;
		break;
	case STORAGE_CLOSE:
		break;
	}

	switch (_storage2.storageState)
	{
	case STORAGE_OPEN:
		if (KEYMANAGER->isOnceKeyDown('I'))_storage2.storageState = STORAGE_CLOSE;
		break;
	case STORAGE_CLOSE:
		break;
	}

}

void playerShop::storageRender()
{
	_storage1.inGameImage->aniRender(getMemDC(), _storage1.rc.left, _storage1.rc.top, _storage1.storageAni);
	_storage2.inGameImage->aniRender(getMemDC(), _storage2.rc.left, _storage2.rc.top, _storage2.storageAni);

	if (IntersectRect(&temp, &_storage1.rc, &PLAYER->getPlayercollision())) //�÷��̾�� â�� �������
	{
		_open->render(getMemDC(), _openRc.left, _openRc.top); //�����̹����� ������
	}
	if (IntersectRect(&temp, &_storage2.rc, &PLAYER->getPlayercollision()))
	{
		_open->render(getMemDC(), _openRc.left, _openRc.top);
	}


	switch (_storage1.storageState)
	{
	case STORAGE_OPEN:
		_mainImage->render(getMemDC(), WINSIZEX/2-70, 100, _mainImage->getWidth(), _mainImage->getHeight());
		_showItem->render(getMemDC(), _showItemRc.left,_showItemRc.top, _showItem->getWidth(), _showItem->getHeight());
		for (int i = 0; i < 28; i++)
		{
			//Rectangle(getMemDC(), slot[i].left, slot[i].top, slot[i].right, slot[i].bottom);
			_slotImage[i]->render(getMemDC(), _slot[i].left, _slot[i].top);
			if (i < _storage1.vStorstorage.size())
			{
				_storage1.vStorstorage[i].setRect(_slot[i]);
			}
		}
		for (int i = 0; i < _storage1.vStorstorage.size(); i++)
		{
			_storage1.vStorstorage[i].getItemInfo().image->render(getMemDC(), _slot[i].left, _slot[i].top);
			RECT temp;
		
			if (IntersectRect(&temp, &_cursor.rc, &_storage1.vStorstorage[i].getRECT()))// Ŀ���� �������� �浹�� ���¶��
			{
				_storage1.vStorstorage[i].getItemInfo().image->render(getMemDC(), _showItemRc.left, _showItemRc.top);
				
			}
		}
		_cursor.image->aniRender(getMemDC(), _cursor.rc.left, _cursor.rc.top, _cursor.ani);
	
		break;
	case STORAGE_CLOSE:
		//_storageAni1 = ANIMATIONMANAGER->findAnimation("â��1Ŭ����");
		//_storageAni1->start();
		break;
	}

	switch (_storage2.storageState)
	{
	case STORAGE_OPEN:
		break;
	case STORAGE_CLOSE:
		/*_storageAni2 = ANIMATIONMANAGER->findAnimation("â��2Ŭ����");
		_storageAni2->start();*/
		break;
	}

}

void playerShop::controlCursor()
{
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		_cursor.cursorMove--;
		_cursor.rc = RectMake(_slot[_cursor.cursorMove].left - 10, _slot[_cursor.cursorMove].top - 10, 40, 40);
		_cursor.ani->start();
	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		_cursor.cursorMove++;
		_cursor.rc = RectMake(_slot[_cursor.cursorMove].left - 10, _slot[_cursor.cursorMove].top - 10, 40, 40);
		_cursor.ani->start();
	}
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		_cursor.cursorMove -= 7;
		_cursor.rc = RectMake(_slot[_cursor.cursorMove].left - 10, _slot[_cursor.cursorMove].top - 10, 40, 40);
		_cursor.ani->start();
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		_cursor.cursorMove += 7;
		_cursor.rc = RectMake(_slot[_cursor.cursorMove].left - 10, _slot[_cursor.cursorMove].top - 10, 40, 40);
		_cursor.ani->start();
	}
}

void playerShop::cursorRender()
{
	
	switch (_cursor.cursorState)
	{
	CURSOR_IDLE:
		break;
	CURSOR_MOVE:
		break;
	CURSOR_GRAB:
		break;

	}
}
