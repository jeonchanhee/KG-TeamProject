#pragma once
#include"gameNode.h"

class monsterProgressBar : public gameNode
{

private:

	RECT _rcProgress;		// 체력바 렉트
	int _x, _y;
	int _width;				//가로길이(요녀석으로 조정함)
	int progressBarCount;
	image* _progressBarFront;		//체력바 앞이미지
	image* _progressBarBack;		//체력바 뒤이미지


public:
	monsterProgressBar();
	~monsterProgressBar();
	HRESULT init(char* frontImage, char* backImage, float x, float y, int width, int height);
	void release();
	void update();
	void render();
	//게이지 셋팅
	void setGauge(float currentGauge, float maxGauge);

	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }

	RECT getRect() { return _rcProgress; }
};

