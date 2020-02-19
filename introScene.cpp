#include "stdafx.h"
#include "introScene.h"

introScene::introScene(){}

introScene::~introScene(){}

HRESULT introScene::init()
{
	butoonInit();
	SOUNDMANAGER->play("인트로브금", 1);
	
	backGround = IMAGEMANAGER->findImage("인트로배경");
	backGround->setFrameY(0);

	logo = IMAGEMANAGER->findImage("로고");
	logoRc = RectMakeCenter(WINSIZEX / 2, 200, logo->getWidth(), logo->getHeight());

	index = 0;
	count = 0;

	return S_OK;
}

void introScene::relaese()
{
	for (int i = 0; i < 4; i++)
	{
		SAFE_DELETE(buttonImg[i]);
	}
}

void introScene::update()
{
	buttonSelect();

	count++;

	if (count % 10 == 0)
	{
		index++;

		if (index > backGround->getMaxFrameX())
		{
			index = 0;
		}
	}

	backGround->setFrameX(index);
}

void introScene::render()
{

	backGround->frameRender(getMemDC(), 0, 0);

	logo->render(getMemDC(), logoRc.left, logoRc.top);

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (int i = 0; i < 4; i++)
		{
			Rectangle(getMemDC(), buttonRc[i].left, buttonRc[i].top, buttonRc[i].right, buttonRc[i].bottom);
		}
	}

	for (int i = 0; i < 4; i++)
	{
		buttonImg[i]->render(getMemDC(), buttonRc[i].left, buttonRc[i].top);
	}

}

void introScene::butoonInit()
{
	buttonImg[0] = IMAGEMANAGER->findImage("인트로시작");
	buttonImg[1] = IMAGEMANAGER->findImage("인트로맵툴");
	buttonImg[2] = IMAGEMANAGER->findImage("인트로옵션");
	buttonImg[3] = IMAGEMANAGER->findImage("인트로나가기");


	for (int i = 0; i < 4; i++)
	{
		buttonRc[i] = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + i * 100, buttonImg[i]->getWidth(), buttonImg[i]->getHeight());
	}
}

void introScene::buttonSelect()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < 4; i++)
		{
			if (PtInRect(&buttonRc[i], m_ptMouse))
			{
				if (i == 0)
				{
					SOUNDMANAGER->stop(SOUNDMANAGER->getCurrentSong());
					SCENEMANAGER->changeScene("마을씬");
				}
				else if (i == 1)
				{
					SCENEMANAGER->changeScene("맵툴");
				}
				else if (i == 2)
				{
					SCENEMANAGER->changeScene("옵션");
				}
				else if (i == 3)
				{

				}

				break;
			}
		}
	}
}
