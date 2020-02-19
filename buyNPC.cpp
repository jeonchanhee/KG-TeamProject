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
	_rc = RectMakeCenter(600, 500, _img->getFrameWidth(), _img->getFrameHeight());
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

void buyNPC::update(item& item1, item& item2, item& item3, item& item4)
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
	if (PtInRect(&_rc, PointMake(_tableRc.right, _tableRc.bottom)) && step == 0)
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
		if (talkCount < 200 && !talkChange) {
			talking();
			talkChange = true;
		}
		//토크카운트200일때
		if (talkCount == 200)talk(item1, item2, item3, item4);
		if (talkCount >= 200 && talkChange&&talkCount <= 200) {
			soso();
			talkChange = false;
		}
		//토크카운트200이상일때
		if (talkCount > 300 && !talkChange)
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
		if (talkCount > 400)
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
		if (KEYMANAGER->isToggleKey(VK_TAB)) RectangleMake(getMemDC(), _tableRc.left, _tableRc.top, _tableRc.right-_tableRc.left, _tableRc.bottom-_tableRc.top);
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
void buyNPC::talk(item& item1, item& item2, item& item3, item& item4)
{
	//진열된 아이템 개수가져온후 랜덤으로 고르기
	//1 o
	if (item1.getItemInfo().itemName != "비어있음") {
		//1 o 2 o
		if (item2.getItemInfo().itemName != "비어있음")
		{
			//1 o 2 o 3 o
			if (item3.getItemInfo().itemName != "비어있음")
			{
				//1 o 2 o 3 o 4 o
				if (item4.getItemInfo().itemName != "비어있음")
				{
					//랜덤 4
					itemRndNum = RND->getFromIntTo(1, 4);
					//랜덤숫자가 1일때
					if (itemRndNum == 1)
					{
						itemImg = item1.getItemInfo().image;
						playerPrice = item1.getItemInfo().playerPrice;
						itemRc = item1.getItemInfo().rc;
						oriPrice = item1.getItemInfo().orignalPrice;
					}
					//랜덤숫자가 2일떄
					if (itemRndNum == 2)
					{
						itemImg = item2.getItemInfo().image;
						playerPrice = item2.getItemInfo().playerPrice;
						itemRc = item2.getItemInfo().rc;
						oriPrice = item2.getItemInfo().orignalPrice;
					}
					//랜덤숫자가 3일때
					if (itemRndNum == 3)
					{
						itemImg = item3.getItemInfo().image;
						playerPrice = item3.getItemInfo().playerPrice;
						itemRc = item3.getItemInfo().rc;
						oriPrice = item3.getItemInfo().orignalPrice;
					}
					//랜덤숫자가 4일때
					if (itemRndNum == 4)
					{
						itemImg = item4.getItemInfo().image;
						playerPrice = item4.getItemInfo().playerPrice;
						itemRc = item4.getItemInfo().rc;
						oriPrice = item4.getItemInfo().orignalPrice;
					}
				}
				//1 o 2 o 3 o 4 x
				else
				{
					//랜덤 3
					itemRndNum = RND->getFromIntTo(1, 3);
					//랜덤숫자가 1일때
					if (itemRndNum == 1)
					{
						itemImg = item1.getItemInfo().image;
						playerPrice = item1.getItemInfo().playerPrice;
						itemRc = item1.getItemInfo().rc;
						oriPrice = item1.getItemInfo().orignalPrice;
					}
					//랜덤숫자가 2일떄
					if (itemRndNum == 2)
					{
						itemImg = item2.getItemInfo().image;
						playerPrice = item2.getItemInfo().playerPrice;
						itemRc = item2.getItemInfo().rc;
						oriPrice = item2.getItemInfo().orignalPrice;
					}
					//랜덤숫자가 3일때
					if (itemRndNum == 3)
					{
						itemImg = item3.getItemInfo().image;
						playerPrice = item3.getItemInfo().playerPrice;
						itemRc = item3.getItemInfo().rc;
						oriPrice = item3.getItemInfo().orignalPrice;
					}
				}
			}
			// o 2 o 3 x
			else
			{
				//1 o 2 o 3 x 4 o
				if (item4.getItemInfo().itemName != "비어있음")
				{
					//랜덤 3
					itemRndNum = RND->getFromIntTo(1, 3);
					//랜덤숫자가 1일때
					if (itemRndNum == 1)
					{
						itemImg = item1.getItemInfo().image;
						playerPrice = item1.getItemInfo().playerPrice;
						itemRc = item1.getItemInfo().rc;
						oriPrice = item1.getItemInfo().orignalPrice;
					}
					//랜덤숫자가 2일떄
					if (itemRndNum == 2)
					{
						itemImg = item2.getItemInfo().image;
						playerPrice = item2.getItemInfo().playerPrice;
						itemRc = item2.getItemInfo().rc;
						oriPrice = item2.getItemInfo().orignalPrice;
					}
					//랜덤숫자가 3일때
					if (itemRndNum == 3)
					{
						itemImg = item4.getItemInfo().image;
						playerPrice = item4.getItemInfo().playerPrice;
						itemRc = item4.getItemInfo().rc;
						oriPrice = item4.getItemInfo().orignalPrice;
					}
				}
				//1 o 2 o 3 x 4 x
				else
				{
					//랜덤 2
					itemRndNum = RND->getFromIntTo(1, 2);
					//랜덤숫자가 1일때
					if (itemRndNum == 1)
					{
						itemImg = item1.getItemInfo().image;
						playerPrice = item1.getItemInfo().playerPrice;
						itemRc = item1.getItemInfo().rc;
						oriPrice = item1.getItemInfo().orignalPrice;
					}
					//랜덤숫자가 2일떄
					if (itemRndNum == 2)
					{
						itemImg = item2.getItemInfo().image;
						playerPrice = item2.getItemInfo().playerPrice;
						itemRc = item2.getItemInfo().rc;
						oriPrice = item2.getItemInfo().orignalPrice;
					}
				}
			}
		}
		//1 o 2 x
		else
		{
			//1 o 2 x 3 o
			if (item3.getItemInfo().itemName != "비어있음")
			{
				//1 o 2 x 3 o 4 o
				if (item4.getItemInfo().itemName != "비어있음")
				{
					//랜덤 3
					itemRndNum = RND->getFromIntTo(1, 3);
					//랜덤숫자가 1일때 1아이템
					if (itemRndNum == 1)
					{
						itemImg = item1.getItemInfo().image;
						playerPrice = item1.getItemInfo().playerPrice;
						itemRc = item1.getItemInfo().rc;
						oriPrice = item1.getItemInfo().orignalPrice;
					}
					//랜덤숫자가 2일때 3아이템
					if (itemRndNum == 2)
					{
						itemImg = item3.getItemInfo().image;
						playerPrice = item3.getItemInfo().playerPrice;
						itemRc = item3.getItemInfo().rc;
						oriPrice = item3.getItemInfo().orignalPrice;
					}
					//랜덤숫자가 3일때 4아이템
					if (itemRndNum == 2)
					{
						itemImg = item4.getItemInfo().image;
						playerPrice = item4.getItemInfo().playerPrice;
						itemRc = item4.getItemInfo().rc;
						oriPrice = item4.getItemInfo().orignalPrice;
					}
				}
				//1 o 2 x 3 o 4 x
				else
				{
					//랜덤 3
					itemRndNum = RND->getFromIntTo(1, 2);
					//랜덤숫자가 1일때 1아이템
					if (itemRndNum == 1)
					{
						itemImg = item1.getItemInfo().image;
						playerPrice = item1.getItemInfo().playerPrice;
						itemRc = item1.getItemInfo().rc;
						oriPrice = item1.getItemInfo().orignalPrice;
					}
					//랜덤숫자가 2일때 3아이템
					if (itemRndNum == 2)
					{
						itemImg = item3.getItemInfo().image;
						playerPrice = item3.getItemInfo().playerPrice;
						itemRc = item3.getItemInfo().rc;
						oriPrice = item3.getItemInfo().orignalPrice;
					}
				}
			}
			//1 o 2 x 3 x
			else
			{
				//1 o 2 x 3 x 4 o
				if (item4.getItemInfo().itemName != "비어있음")
				{
					//랜덤 2
					itemRndNum = RND->getFromIntTo(1, 2);
					//랜덤숫자가 1일때 1아이템
					if (itemRndNum == 1)
					{
						itemImg = item1.getItemInfo().image;
						playerPrice = item1.getItemInfo().playerPrice;
						itemRc = item1.getItemInfo().rc;
						oriPrice = item1.getItemInfo().orignalPrice;
					}
					//랜덤숫자가 2일때 3아이템
					if (itemRndNum == 2)
					{
						itemImg = item4.getItemInfo().image;
						playerPrice = item4.getItemInfo().playerPrice;
						itemRc = item4.getItemInfo().rc;
						oriPrice = item4.getItemInfo().orignalPrice;
					}
				}
				//1 o 2 x 3 x 4 x
				else
				{
					itemImg = item1.getItemInfo().image;
					playerPrice = item1.getItemInfo().playerPrice;
					itemRc = item1.getItemInfo().rc;
					oriPrice = item1.getItemInfo().orignalPrice;
				}
			}
		}
	}
	//1 x
	else {
		//1 x 2 o
		if (item2.getItemInfo().itemName != "비어있음")
		{
			//1 x 2 o 3 o
			if (item3.getItemInfo().itemName != "비어있음")
			{
				//1 x 2 o 3 o 4 o
				if (item4.getItemInfo().itemName != "비어있음")
				{
					//랜덤 2
					itemRndNum = RND->getFromIntTo(1, 3);
					//랜덤숫자가 1일때 1아이템
					if (itemRndNum == 1)
					{
						itemImg = item2.getItemInfo().image;
						playerPrice = item2.getItemInfo().playerPrice;
						itemRc = item2.getItemInfo().rc;
						oriPrice = item2.getItemInfo().orignalPrice;
					}
					//랜덤숫자가 2일때 3아이템
					if (itemRndNum == 2)
					{
						itemImg = item3.getItemInfo().image;
						playerPrice = item3.getItemInfo().playerPrice;
						itemRc = item3.getItemInfo().rc;
						oriPrice = item3.getItemInfo().orignalPrice;
					}
					if (itemRndNum == 3)
					{
						itemImg = item4.getItemInfo().image;
						playerPrice = item4.getItemInfo().playerPrice;
						itemRc = item4.getItemInfo().rc;
						oriPrice = item4.getItemInfo().orignalPrice;
					}
				}
				//1 x 2 o 3 o 4 x
				else
				{
					//랜덤 2
					itemRndNum = RND->getFromIntTo(1, 2);
					//랜덤숫자가 1일때 1아이템
					if (itemRndNum == 1)
					{
						itemImg = item2.getItemInfo().image;
						playerPrice = item2.getItemInfo().playerPrice;
						itemRc = item2.getItemInfo().rc;
						oriPrice = item2.getItemInfo().orignalPrice;
					}
					//랜덤숫자가 2일때 3아이템
					if (itemRndNum == 2)
					{
						itemImg = item3.getItemInfo().image;
						playerPrice = item3.getItemInfo().playerPrice;
						itemRc = item3.getItemInfo().rc;
						oriPrice = item3.getItemInfo().orignalPrice;
					}
				}
			}
			//1 x 2 o 3 x
			else
			{
				//1 x 2 o 3 x 4 o
				if (item4.getItemInfo().itemName != "비어있음")
				{
					itemRndNum = RND->getFromIntTo(1, 2);
					//랜덤숫자가 1일때 1아이템
					if (itemRndNum == 1)
					{
						itemImg = item2.getItemInfo().image;
						playerPrice = item2.getItemInfo().playerPrice;
						itemRc = item2.getItemInfo().rc;
						oriPrice = item2.getItemInfo().orignalPrice;
					}
					//랜덤숫자가 2일때 3아이템
					if (itemRndNum == 2)
					{
						itemImg = item4.getItemInfo().image;
						playerPrice = item4.getItemInfo().playerPrice;
						itemRc = item4.getItemInfo().rc;
						oriPrice = item4.getItemInfo().orignalPrice;
					}
				}
				//1 x 2 o 3 x 4 x
				else
				{
					itemImg = item2.getItemInfo().image;
					playerPrice = item2.getItemInfo().playerPrice;
					itemRc = item2.getItemInfo().rc;
					oriPrice = item2.getItemInfo().orignalPrice;
				}
			}
		}
		//1 x 2 x
		else {
			//1 x 2 x 3 o
			if (item3.getItemInfo().itemName != "비어있음")
			{
				//1 x 2 x 3 o 4 o
				if (item4.getItemInfo().itemName != "비어있음")
				{
					itemRndNum = RND->getFromIntTo(1, 2);
					//랜덤숫자가 1일때 1아이템
					if (itemRndNum == 1)
					{
						itemImg = item3.getItemInfo().image;
						playerPrice = item3.getItemInfo().playerPrice;
						itemRc = item3.getItemInfo().rc;
						oriPrice = item3.getItemInfo().orignalPrice;
					}
					//랜덤숫자가 2일때 3아이템
					if (itemRndNum == 2)
					{
						itemImg = item4.getItemInfo().image;
						playerPrice = item4.getItemInfo().playerPrice;
						itemRc = item4.getItemInfo().rc;
						oriPrice = item4.getItemInfo().orignalPrice;
					}
				}
				//1 x 2 x 3 o 4 x
				else
				{
					itemImg = item3.getItemInfo().image;
					playerPrice = item3.getItemInfo().playerPrice;
					itemRc = item3.getItemInfo().rc;
					oriPrice = item3.getItemInfo().orignalPrice;
				}
			}
			//1 x 2 x 3 x
			else
			{
				//1 x 2 x 3 x 4 o
				if (item4.getItemInfo().itemName != "비어있음")
				{
					itemImg = item4.getItemInfo().image;
					playerPrice = item4.getItemInfo().playerPrice;
					itemRc = item4.getItemInfo().rc;
					oriPrice = item4.getItemInfo().orignalPrice;
				}
				//1 x 2 x 3 x 4 x
				else
				{
					step = 5;
				}
			}
		}
	}

	playerPrice = 5;
	

	if (playerPrice > oriPrice + oriPrice * 0.5)//매우비쌈
	{
		isVeryExpensive = true;
	}
	else if (playerPrice > oriPrice&&playerPrice <= oriPrice + oriPrice * 0.5)//비쌈
	{
		isExpensive = true;
	}
	else if (playerPrice <= oriPrice && playerPrice >= oriPrice - oriPrice * 0.5)//쌈
	{
		isCheap = true;
	}
	else if (playerPrice < oriPrice - oriPrice * 0.5)//매우쌈
	{
		isVeryCheap = true;
	}
	//아이템 제거
	if (isCheap == true || isVeryCheap == true)
	{
		//진열된 아이템 개수가져온후 랜덤으로 고르기
		//1 o
		if (item1.getItemInfo().itemName != "비어있음") {
			//1 o 2 o
			if (item2.getItemInfo().itemName != "비어있음")
			{
				//1 o 2 o 3 o
				if (item3.getItemInfo().itemName != "비어있음")
				{
					//1 o 2 o 3 o 4 o
					if (item4.getItemInfo().itemName != "비어있음")
					{
						//랜덤 4
						//랜덤숫자가 1일때
						if (itemRndNum == 1)
						{
							item1.setItemCnt_equal(0);
						}
						//랜덤숫자가 2일떄
						if (itemRndNum == 2)
						{
							item2.setItemCnt_equal(0);
						}
						//랜덤숫자가 3일때
						if (itemRndNum == 3)
						{
							item3.setItemCnt_equal(0);
						}
						//랜덤숫자가 4일때
						if (itemRndNum == 4)
						{
							item4.setItemCnt_equal(0);
						}
					}
					//1 o 2 o 3 o 4 x
					else
					{
						//랜덤 3
						//랜덤숫자가 1일때
						if (itemRndNum == 1)
						{
							item1.setItemCnt_equal(0);
						}
						//랜덤숫자가 2일떄
						if (itemRndNum == 2)
						{
							item2.setItemCnt_equal(0);
						}
						//랜덤숫자가 3일때
						if (itemRndNum == 3)
						{
							item3.setItemCnt_equal(0);
						}
					}
				}
				// o 2 o 3 x
				else
				{
					//1 o 2 o 3 x 4 o
					if (item4.getItemInfo().itemName != "비어있음")
					{
						//랜덤 3
						//랜덤숫자가 1일때
						if (itemRndNum == 1)
						{
							item1.setItemCnt_equal(0);
						}
						//랜덤숫자가 2일떄
						if (itemRndNum == 2)
						{
							item2.setItemCnt_equal(0);
						}
						//랜덤숫자가 3일때
						if (itemRndNum == 3)
						{
							item4.setItemCnt_equal(0);
						}
					}
					//1 o 2 o 3 x 4 x
					else
					{
						//랜덤 2
						//랜덤숫자가 1일때
						if (itemRndNum == 1)
						{
							item1.setItemCnt_equal(0);
						}
						//랜덤숫자가 2일떄
						if (itemRndNum == 2)
						{
							item2.setItemCnt_equal(0);
						}
					}
				}
			}
			//1 o 2 x
			else
			{
				//1 o 2 x 3 o
				if (item3.getItemInfo().itemName != "비어있음")
				{
					//1 o 2 x 3 o 4 o
					if (item4.getItemInfo().itemName != "비어있음")
					{
						//랜덤 3
						//랜덤숫자가 1일때 1아이템
						if (itemRndNum == 1)
						{
							item1.setItemCnt_equal(0);
						}
						//랜덤숫자가 2일때 3아이템
						if (itemRndNum == 2)
						{
							item3.setItemCnt_equal(0);
						}
						//랜덤숫자가 3일때 4아이템
						if (itemRndNum == 2)
						{
							item4.setItemCnt_equal(0);
						}
					}
					//1 o 2 x 3 o 4 x
					else
					{
						//랜덤 3
						//랜덤숫자가 1일때 1아이템
						if (itemRndNum == 1)
						{
							item1.setItemCnt_equal(0);
						}
						//랜덤숫자가 2일때 3아이템
						if (itemRndNum == 2)
						{
							item3.setItemCnt_equal(0);
						}
					}
				}
				//1 o 2 x 3 x
				else
				{
					//1 o 2 x 3 x 4 o
					if (item4.getItemInfo().itemName != "비어있음")
					{
						//랜덤 2
						//랜덤숫자가 1일때 1아이템
						if (itemRndNum == 1)
						{
							item1.setItemCnt_equal(0);
						}
						//랜덤숫자가 2일때 3아이템
						if (itemRndNum == 2)
						{
							item4.setItemCnt_equal(0);
						}
					}
					//1 o 2 x 3 x 4 x
					else
					{
						item1.setItemCnt_equal(0);
					}
				}
			}
		}
		//1 x
		else {
			//1 x 2 o
			if (item2.getItemInfo().itemName != "비어있음")
			{
				//1 x 2 o 3 o
				if (item3.getItemInfo().itemName != "비어있음")
				{
					//1 x 2 o 3 o 4 o
					if (item4.getItemInfo().itemName != "비어있음")
					{
						//랜덤 2
						//랜덤숫자가 1일때 1아이템
						if (itemRndNum == 1)
						{
							item2.setItemCnt_equal(0);
						}
						//랜덤숫자가 2일때 3아이템
						if (itemRndNum == 2)
						{
							item3.setItemCnt_equal(0);
						}
						if (itemRndNum == 3)
						{
							item4.setItemCnt_equal(0);
						}
					}
					//1 x 2 o 3 o 4 x
					else
					{
						//랜덤 2
						//랜덤숫자가 1일때 1아이템
						if (itemRndNum == 1)
						{
							item2.setItemCnt_equal(0);
						}
						//랜덤숫자가 2일때 3아이템
						if (itemRndNum == 2)
						{
							item3.setItemCnt_equal(0);
						}
					}
				}
				//1 x 2 o 3 x
				else
				{
					//1 x 2 o 3 x 4 o
					if (item4.getItemInfo().itemName != "비어있음")
					{
						//랜덤숫자가 1일때 1아이템
						if (itemRndNum == 1)
						{
							item2.setItemCnt_equal(0);
						}
						//랜덤숫자가 2일때 3아이템
						if (itemRndNum == 2)
						{
							item4.setItemCnt_equal(0);
						}
					}
					//1 x 2 o 3 x 4 x
					else
					{
						item2.setItemCnt_equal(0);
					}
				}
			}
			//1 x 2 x
			else {
				//1 x 2 x 3 o
				if (item3.getItemInfo().itemName != "비어있음")
				{
					//1 x 2 x 3 o 4 o
					if (item4.getItemInfo().itemName != "비어있음")
					{
						//랜덤숫자가 1일때 1아이템
						if (itemRndNum == 1)
						{
							item3.setItemCnt_equal(0);
						}
						//랜덤숫자가 2일때 3아이템
						if (itemRndNum == 2)
						{
							item4.setItemCnt_equal(0);
						}
					}
					//1 x 2 x 3 o 4 x
					else
					{
						item3.setItemCnt_equal(0);
					}
				}
				//1 x 2 x 3 x
				else
				{
					//1 x 2 x 3 x 4 o
					if (item4.getItemInfo().itemName != "비어있음")
					{
						item4.setItemCnt_equal(0);
					}
					//1 x 2 x 3 x 4 x
					else
					{

					}
				}
			}
		}
	}


}
//감정표현
void buyNPC::talking()
{
	//토크rc 만들기
	_talkAni = ANIMATIONMANAGER->findAnimation("감정중");
	_talkAni->start();
	talkRc = RectMakeCenter((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2 - 100, _talkAni->getFrameWidth(), _talkAni->getFrameHeight());
}

void buyNPC::soso()
{
	_talkAni = ANIMATIONMANAGER->findAnimation("보통");
	_talkAni->start();
}
//j눌러서 판매확인
bool buyNPC::sell()
{
	//기다림상태일때 j누르면
	if (step == 3 && KEYMANAGER->isOnceKeyDown('J'))
	{
		//돈추가
		PLAYER->setMoney(PLAYER->getMoney() + playerPrice);
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

