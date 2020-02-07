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
		_storage1.vStorstorage.push_back(ITEMMANAGER->addItem("나뭇가지"));
	}
	_showItemRc = RectMakeCenter(WINSIZEX - 70, 250, _showItem->getWidth(), _showItem->getHeight());

	//커서초기화
	_cursor.image = IMAGEMANAGER->findImage("커서");
		_cursor.cursorState = CURSOR_IDLE;
	_cursor.rc = RectMake(_slot[0].left-10, _slot[0].top-10, 40, 40);

	int arrlen1[] = { 0,1,0 };
	ANIMATIONMANAGER->addAnimation("커서애니", "커서", arrlen1, 3, 10, false);
	_cursor.ani = ANIMATIONMANAGER->findAnimation("커서애니");
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
	if (KEYMANAGER->isOnceKeyDown('Q'))_storage1.vStorstorage.push_back(ITEMMANAGER->addItem("흡혈귀의 단검"));
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
	//창고2개 + 창고인벤토리 초기화
	_open = IMAGEMANAGER->addImage("열기", "images/shop/열기.bmp", 193 / 2, 87 / 2, true, RGB(255, 0, 255));
	_storage1.inGameImage = IMAGEMANAGER->findImage("창고1");
	_storage2.inGameImage = IMAGEMANAGER->findImage("창고2");
	int arrlen1[] = { 0,1,2 };
	int arrlen2[] = { 3,4,5 };
	ANIMATIONMANAGER->addAnimation("창고1오픈", "창고1", arrlen1, 3, 10, false);
	ANIMATIONMANAGER->addAnimation("창고1클로즈", "창고1", arrlen2, 3, 10, false);
	int arrlen3[] = { 0,1,2,3 };
	int arrlen4[] = { 4,5,6,7 };
	ANIMATIONMANAGER->addAnimation("창고2오픈", "창고2", arrlen3, 3, 10, false);
	ANIMATIONMANAGER->addAnimation("창고2클로즈", "창고2", arrlen4, 3, 10, false);
	_storage1.storageAni = ANIMATIONMANAGER->findAnimation("창고1오픈");
	_storage1.rc = RectMakeCenter(WINSIZEX / 2 / 2, WINSIZEY / 2 / 2 + 150, _storage1.inGameImage->getFrameWidth(), _storage1.inGameImage->getFrameHeight());
	_storage1.storageState = STORAGE_CLOSE;

	_storage2.storageAni = ANIMATIONMANAGER->findAnimation("창고2오픈");
	_storage2.rc = RectMakeCenter(WINSIZEX / 2 / 2, WINSIZEY / 2 / 2, _storage2.inGameImage->getFrameWidth(), _storage2.inGameImage->getFrameHeight());
	_storage2.storageState = STORAGE_CLOSE;


	_mainImage = IMAGEMANAGER->findImage("창고내부");
	_showItem = IMAGEMANAGER->findImage("템보여주기");
	//창고인벤토리 슬롯 초기화
	for (int i = 0; i < 28; i++)
	{
		int k, j;
		k = i % 7;
		j = i / 7;
		_slot[i] = RectMakeCenter(WINSIZEX / 2 + 20 + (k * 60), WINSIZEY / 2 - 60 + (j * 60), 40,40);
		_slotImage[i] = IMAGEMANAGER->findImage("슬롯이미지");
	}
}

void playerShop::controlStorage()
{
	if (IntersectRect(&temp, &_storage1.rc, &PLAYER->getPlayercollision())) //플레이어와 창고가 닿았을때
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

	if (IntersectRect(&temp, &_storage1.rc, &PLAYER->getPlayercollision())) //플레이어와 창고가 닿았을때
	{
		_open->render(getMemDC(), _openRc.left, _openRc.top); //열기이미지를 보여줌
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
		
			if (IntersectRect(&temp, &_cursor.rc, &_storage1.vStorstorage[i].getRECT()))// 커서와 아이템이 충돌된 상태라면
			{
				_storage1.vStorstorage[i].getItemInfo().image->render(getMemDC(), _showItemRc.left, _showItemRc.top);
				
			}
		}
		_cursor.image->aniRender(getMemDC(), _cursor.rc.left, _cursor.rc.top, _cursor.ani);
	
		break;
	case STORAGE_CLOSE:
		//_storageAni1 = ANIMATIONMANAGER->findAnimation("창고1클로즈");
		//_storageAni1->start();
		break;
	}

	switch (_storage2.storageState)
	{
	case STORAGE_OPEN:
		break;
	case STORAGE_CLOSE:
		/*_storageAni2 = ANIMATIONMANAGER->findAnimation("창고2클로즈");
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
