#include "stdafx.h"
#include "introScene.h"

introScene::introScene(){}

introScene::~introScene(){}

HRESULT introScene::init()
{
	butoonInit();

	backGround = IMAGEMANAGER->findImage("��Ʈ�ι��");
	backGround->setFrameY(0);

	logo = IMAGEMANAGER->findImage("�ΰ�");
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
	buttonImg[0] = IMAGEMANAGER->findImage("��Ʈ�ν���");
	buttonImg[1] = IMAGEMANAGER->findImage("��Ʈ�θ���");
	buttonImg[2] = IMAGEMANAGER->findImage("��Ʈ�οɼ�");
	buttonImg[3] = IMAGEMANAGER->findImage("��Ʈ�γ�����");


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
					SCENEMANAGER->changeScene("������");
				}
				else if (i == 1)
				{
					SCENEMANAGER->changeScene("����");
				}
				else if (i == 2)
				{
					SCENEMANAGER->changeScene("�ɼ�");
				}
				else if (i == 3)
				{

				}

				break;
			}
		}
	}
}
