#include "stdafx.h"
#include "monsterProgressBar.h"

monsterProgressBar::monsterProgressBar()
{
}

monsterProgressBar::~monsterProgressBar()
{
}

HRESULT monsterProgressBar::init(char * frontImage, char * backImage, float x, float y, int width, int height)
{
	_x = x;
	_y = y;

	_rcProgress = RectMake(x, y, width, height);

	_progressBarFront = new image;
	_progressBarFront->init(frontImage, x, y, width, height, true, RGB(255, 0, 255));

	_progressBarBack = new image;
	_progressBarBack->init(backImage, x, y, width, height, true, RGB(255, 0, 255));


	_width = _progressBarFront->getWidth();

	return S_OK;
}

void monsterProgressBar::release()
{
	SAFE_DELETE(_progressBarFront);
	SAFE_DELETE(_progressBarBack);
}

void monsterProgressBar::update()
{
	_rcProgress = RectMakeCenter(_x + _progressBarBack->getWidth() / 2,
		_y + _progressBarBack->getHeight() / 2,
		_progressBarBack->getWidth(), _progressBarBack->getHeight());
}

void monsterProgressBar::render()
{

	progressBarCount -= 2;
	_progressBarBack->alphaRender(getMemDC(), _rcProgress.left, _y, 0, 0, _progressBarBack->getWidth(), _progressBarBack->getHeight(), progressBarCount * 2);

	_progressBarFront->alphaRender(getMemDC(), _rcProgress.left, _y, 0, 0, _width, _progressBarBack->getHeight(), progressBarCount * 2);
}

void monsterProgressBar::setGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge)* _progressBarBack->getWidth();
}
