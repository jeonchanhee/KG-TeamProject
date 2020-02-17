#include "stdafx.h"
#include "buyNPC.h"

buyNPC::buyNPC()
{
}

buyNPC::~buyNPC()
{
}

HRESULT buyNPC::init(RECT _tableRect)
{
	num = 0;
	//넘버값을 받아 맞는 이미지
	switch (num) {
	case 0:_img = IMAGEMANAGER->findImage("여자"); break;
	case 1:_img = IMAGEMANAGER->findImage("남자"); break;
	}
	//_img = IMAGEMANAGER->findImage("여자");
	//이미지 사각형과 애니메이션 
	_rc = RectMakeCenter(300, 600, _img->getFrameWidth(), _img->getFrameHeight());
	_ani = ANIMATIONMANAGER->findAnimation("여자정지L");
	//표정찾기
	_tableRc = _tableRect;
	talkImg = IMAGEMANAGER->findImage("표정");
	step = 0;
	//initTime = TIMEMANAGER->getWorldTime();
	return S_OK;
}

void buyNPC::release()
{
}

void buyNPC::update(vector<item>_vSellItem)
{
	//NPC모션변경
	aniChange();
	//이동
	if (_move)
	{
		if (isLeft)
		{
			_rc.left -= 1;
			_rc.right -= 1;
		}
		if (isUp) {
			_rc.top -= 1;
			_rc.bottom -= 1;
		}
		if (isRight)
		{
			_rc.left += 1;
			_rc.right += 1;
		}
		if (isDown) {
			_rc.top += 1;
			_rc.bottom += 1;
		}
	}
	//판매대로 이동
	if (step == 0)
	{
		isLeft = true;
		_move = true;
	}
	//판매대와 닿으면 멈춤
	if (PtInRect(&_rc, PointMake(_tableRc.right, (_tableRc.top + _tableRc.bottom) / 2)) && step == 0)
	{
		step = 1;
		_move = false;
		isTalk = true;
	}
	//감정시작
	if (isTalk)
	{
		talkCount++;
		//감정중
		if (talkCount < 100 && !talkChange) {
			talking();
			talkChange = true;
		}
		//토크카운트200일때
		talk(_vSellItem);
		if (talkCount >= 100 && talkChange&&talkCount <= 200) {
			soso();
			talkChange = false;
		}
		//토크카운트200이상일때
		if (talkCount > 200 && !talkChange)
		{
			if (isExpensive)
			{
				expensive();
			}
			if (isVeryExpensive)
			{
				veryExpensive();
			}
			if (isCheap)
			{
				cheap();
			}
			if (isVeryCheap)
			{
				veryCheap();
			}
			talkChange = true;
		}
		//talkCount300보다 커지면 다음단계로
		if (talkCount > 300)
		{
			isTalk = false;
			talkCount = 0;
		}
	}
	//감정후 구매를 위해 플레이어쪽으로 걸어감
	if (isTalk == false && step == 2)
	{
		isLeft = false;
		_move = true;
		if (PLAYER->getPlayerY() + 100 <= (_rc.top + _rc.bottom) / 2)
		{
			_rc.top -= 2;
			_rc.bottom -= 2;
		}
		else
		{
			_move = false;
			step = 3;
		}
		if (PLAYER->getPlayerX() >= (_rc.left + _rc.right) / 2)
		{
			isRight = true;
		}
	}
	//감정후 안맞으면 문으로 이동 후 사라짐
	if (isTalk == false && step == 5)
	{
		isLeft = false;
		isRight = true;
		_move = true;
		exit++;
	}
	//step3일때 waitCount증가
	if (step == 3)
	{
		isWait = true;
		waitCount++;
		if (waitCount >= 0)
		{
			talkRc = RectMakeCenter((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2 - 100, _talkAni->getFrameWidth(), _talkAni->getFrameHeight());
			wait();
		}
		//200count이상 기다리거나 판매완료on시 
		if (waitCount > 200 || sell())
		{
			isRight = false;
			isWait = false;
			step = 4;
			waitCount = 0;
		}
	}
	//물건 구매후 사라짐
	if (step == 4)
	{
		isDown = true;
		_move = true;
		exit++;
	}
	if (step == 2 || step == 3 || step == 4) {
		//아이템rc 만들기
		itemRc = RectMakeCenter((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2, itemImg->getWidth(), itemImg->getHeight());
	}
}

void buyNPC::render()
{
	if (exit <= 200)
	{
		//NPC사각형
		//RectangleMake(getMemDC(), _rc.left, _rc.top, _img->getFrameWidth(),_img->getFrameHeight());
		//NPC출력
		_img->aniRender(getMemDC(), _rc.left, _rc.top, _ani);
		//감정출력
		if (isTalk || isWait) {
			talkImg->aniRender(getMemDC(), talkRc.left, talkRc.top, _talkAni);
		}
		//아이템출력
		if (step == 2 || step == 3 || step == 4) {
			itemImg->render(getMemDC(), itemRc.left, itemRc.top);
		}
	}
}
//모션변경
void buyNPC::aniChange()
{
	if (isLeft&&_move && !motionChange) {
		motionChange = true;
		_ani = ANIMATIONMANAGER->findAnimation("여자L");
		ANIMATIONMANAGER->start("여자L");
	}
	if (isLeft && !_move &&motionChange)
	{
		motionChange = false;
		_ani = ANIMATIONMANAGER->findAnimation("여자정지L");
		ANIMATIONMANAGER->start("여자정지L");
	}
	if (isRight && _move && !motionChange) {
		motionChange = true;
		_ani = ANIMATIONMANAGER->findAnimation("여자R");
		ANIMATIONMANAGER->start("여자R");
	}
	if (isRight && !_move &&motionChange)
	{
		motionChange = false;
		_ani = ANIMATIONMANAGER->findAnimation("여자정지R");
		ANIMATIONMANAGER->start("여자정지R");
	}
	if (isUp&&_move && !motionChange) {
		motionChange = true;
		_ani = ANIMATIONMANAGER->findAnimation("여자U");
		ANIMATIONMANAGER->start("여자U");
	}
	if (isUp && !_move &&motionChange)
	{
		motionChange = false;
		_ani = ANIMATIONMANAGER->findAnimation("여자정지U");
		ANIMATIONMANAGER->start("여자정지U");
	}
	if (isDown&&_move && !motionChange) {
		motionChange = true;
		_ani = ANIMATIONMANAGER->findAnimation("여자D");
		ANIMATIONMANAGER->start("여자D");
	}
	if (isDown && !_move &&motionChange)
	{
		motionChange = false;
		_ani = ANIMATIONMANAGER->findAnimation("여자정지D");
		ANIMATIONMANAGER->start("여자정지D");
	}

}
//아이템 감정
void buyNPC::talk(vector<item>_vSellItem)
{
	//진열된 아이템 개수가져온후 랜덤으로 고르기
	int isNum = 0;
	for (int i = 0; i < _vSellItem.size(); i++)
	{
		if (_vSellItem[i].getItemInfo().itemName != "비어있음")
		{
			isNum++;
		}
		itemRndNum = RND->getFromIntTo(0, isNum);
	}
	//아이템 이미지 크기 원가 판매가 가져오기
	itemImg = _vSellItem[3].getItemInfo().image;
	//playerPrice = _vSellItem[3].getItemInfo().playerPrice;
	playerPrice = 100;
	itemRc = _vSellItem[3].getItemInfo().rc;
	oriPrice = _vSellItem[3].getItemInfo().orignalPrice;
	//토크rc 만들기
	talkRc = RectMakeCenter((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2 - 100, _talkAni->getFrameWidth(), _talkAni->getFrameHeight());

	if (playerPrice > oriPrice + oriPrice * 0.5)//매우비쌈
	{
		isVeryExpensive = true;
	}
	if (playerPrice > oriPrice&&playerPrice <= oriPrice + oriPrice * 0.5)//비쌈
	{
		isExpensive = true;
	}
	if (playerPrice <= oriPrice && playerPrice >= oriPrice - oriPrice * 0.5)//쌈
	{
		isCheap = true;
	}
	if (playerPrice < oriPrice - oriPrice * 0.5)//매우쌈
	{
		isVeryCheap = true;
	}



}
//감정중
void buyNPC::talking()
{
	_talkAni = ANIMATIONMANAGER->findAnimation("감정중");
	_talkAni->start();
}

void buyNPC::soso()
{
	_talkAni = ANIMATIONMANAGER->findAnimation("보통");
	_talkAni->start();
}

bool buyNPC::sell()
{
	//기다림상태일때 j누르면
	if (step == 3 && KEYMANAGER->isOnceKeyDown('J'))
	{
		//수정불가?돈추가
		//PLAYER->setMoney()=PLAYER->getMoney() + playerPrice;
		return true;
	}
	return false;
}

void buyNPC::cheap()
{
	_talkAni = ANIMATIONMANAGER->findAnimation("쌈");
	_talkAni->start();
	step = 2;
}

void buyNPC::expensive()
{
	_talkAni = ANIMATIONMANAGER->findAnimation("비쌈");
	_talkAni->start();
	step = 5;
}

void buyNPC::veryCheap()
{
	_talkAni = ANIMATIONMANAGER->findAnimation("매우쌈");
	_talkAni->start();
	step = 2;
}

void buyNPC::veryExpensive()
{
	_talkAni = ANIMATIONMANAGER->findAnimation("매우비쌈");
	_talkAni->start();
	step = 5;
}

void buyNPC::wait()
{
	_talkAni = ANIMATIONMANAGER->findAnimation("기다림");
	_talkAni->start();
}

