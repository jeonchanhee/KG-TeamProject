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
	//�ѹ����� �޾� �´� �̹���
	switch (num) {
	case 0:_img = IMAGEMANAGER->findImage("����"); break;
	case 1:_img = IMAGEMANAGER->findImage("����"); break;
	}
	//_img = IMAGEMANAGER->findImage("����");
	//�̹��� �簢���� �ִϸ��̼� 
	_rc = RectMakeCenter(300, 600, _img->getFrameWidth(), _img->getFrameHeight());
	_ani = ANIMATIONMANAGER->findAnimation("��������L");
	//ǥ��ã��
	_tableRc = _tableRect;
	talkImg = IMAGEMANAGER->findImage("ǥ��");
	step = 0;
	//initTime = TIMEMANAGER->getWorldTime();
	return S_OK;
}

void buyNPC::release()
{
}

void buyNPC::update(item& item1, item& item2, item& item3, item& item4)
{
	//NPC��Ǻ���
	aniChange();
	
	//�̵�
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
	//�ǸŴ�� �̵�
	if (step == 0)
	{
		isLeft = true;
		_move = true;
	}
	//�ǸŴ�� ������ ����
	if (PtInRect(&_rc, PointMake(_tableRc.right, (_tableRc.top + _tableRc.bottom) / 2)) && step == 0)
	{
		step = 1;
		_move = false;
		isTalk = true;
	}
	//��������
	if (isTalk)
	{
		talkCount++;
		//������
		if (talkCount < 100 && !talkChange) {
			talking();
			talkChange = true;
		}
		//��ũī��Ʈ200�϶�
		if(talkCount==100)talk(item1, item2, item3, item4);
		if (talkCount >= 100 && talkChange&&talkCount <= 200) {
			soso();
			talkChange = false;
		}
		//��ũī��Ʈ200�̻��϶�
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
		//talkCount300���� Ŀ���� �����ܰ��
		if (talkCount > 300)
		{
			isTalk = false;
			talkCount = 0;
		}
	}
	//������ ���Ÿ� ���� �÷��̾������� �ɾ
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
	//������ �ȸ����� ������ �̵� �� �����
	if (isTalk == false && step == 5)
	{
		isLeft = false;
		isRight = true;
		_move = true;
		exit++;
	}
	//step3�϶� waitCount����
	if (step == 3)
	{
		isWait = true;
		waitCount++;
		if (waitCount >= 0)
		{
			talkRc = RectMakeCenter((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2 - 100, _talkAni->getFrameWidth(), _talkAni->getFrameHeight());
			wait();
		}
		//200count�̻� ��ٸ��ų� �ǸſϷ�on�� 
		if (waitCount > 200 || sell())
		{
			isRight = false;
			isWait = false;
			step = 4;
			waitCount = 0;
		}
	}
	//���� ������ �����
	if (step == 4)
	{
		isDown = true;
		_move = true;
		exit++;
	}
	if (step == 2 || step == 3 || step == 4) {
		//������rc �����
		itemRc = RectMakeCenter((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2, itemImg->getWidth(), itemImg->getHeight());
	}
}

void buyNPC::render()
{
	if (exit <= 200)
	{
		//NPC�簢��
		//RectangleMake(getMemDC(), _rc.left, _rc.top, _img->getFrameWidth(),_img->getFrameHeight());
		//NPC���
		_img->aniRender(getMemDC(), _rc.left, _rc.top, _ani);
		//�������
		if (isTalk || isWait) {
			talkImg->aniRender(getMemDC(), talkRc.left, talkRc.top, _talkAni);
		}
		//���������
		if (step == 2 || step == 3 || step == 4) {
			itemImg->render(getMemDC(), itemRc.left, itemRc.top);
		}
	}
}
//��Ǻ���
void buyNPC::aniChange()
{
	if (isLeft&&_move && !motionChange) {
		motionChange = true;
		_ani = ANIMATIONMANAGER->findAnimation("����L");
		ANIMATIONMANAGER->start("����L");
	}
	if (isLeft && !_move &&motionChange)
	{
		motionChange = false;
		_ani = ANIMATIONMANAGER->findAnimation("��������L");
		ANIMATIONMANAGER->start("��������L");
	}
	if (isRight && _move && !motionChange) {
		motionChange = true;
		_ani = ANIMATIONMANAGER->findAnimation("����R");
		ANIMATIONMANAGER->start("����R");
	}
	if (isRight && !_move &&motionChange)
	{
		motionChange = false;
		_ani = ANIMATIONMANAGER->findAnimation("��������R");
		ANIMATIONMANAGER->start("��������R");
	}
	if (isUp&&_move && !motionChange) {
		motionChange = true;
		_ani = ANIMATIONMANAGER->findAnimation("����U");
		ANIMATIONMANAGER->start("����U");
	}
	if (isUp && !_move &&motionChange)
	{
		motionChange = false;
		_ani = ANIMATIONMANAGER->findAnimation("��������U");
		ANIMATIONMANAGER->start("��������U");
	}
	if (isDown&&_move && !motionChange) {
		motionChange = true;
		_ani = ANIMATIONMANAGER->findAnimation("����D");
		ANIMATIONMANAGER->start("����D");
	}
	if (isDown && !_move &&motionChange)
	{
		motionChange = false;
		_ani = ANIMATIONMANAGER->findAnimation("��������D");
		ANIMATIONMANAGER->start("��������D");
	}

}
//������ ����
void buyNPC::talk(item& item1, item& item2, item& item3, item& item4)
{
	//������ ������ ������������ �������� ����
	//1 o
	if (item1.getItemInfo().itemName != "�������") {
		//1 o 2 o
		if (item2.getItemInfo().itemName != "�������")
		{
			//1 o 2 o 3 o
			if (item3.getItemInfo().itemName != "�������")
			{
				//1 o 2 o 3 o 4 o
				if (item4.getItemInfo().itemName != "�������")
				{
					//���� 4
					itemRndNum = RND->getFromIntTo(1, 4);
					//�������ڰ� 1�϶�
					if (itemRndNum == 1)
					{
						itemImg = item1.getItemInfo().image;
						playerPrice = item1.getItemInfo().playerPrice;
						itemRc = item1.getItemInfo().rc;
						oriPrice = item1.getItemInfo().orignalPrice;
					}
					//�������ڰ� 2�ϋ�
					if (itemRndNum == 2)
					{
						itemImg = item2.getItemInfo().image;
						playerPrice = item2.getItemInfo().playerPrice;
						itemRc = item2.getItemInfo().rc;
						oriPrice = item2.getItemInfo().orignalPrice;
					}
					//�������ڰ� 3�϶�
					if (itemRndNum == 3)
					{
						itemImg = item3.getItemInfo().image;
						playerPrice = item3.getItemInfo().playerPrice;
						itemRc = item3.getItemInfo().rc;
						oriPrice = item3.getItemInfo().orignalPrice;
					}
					//�������ڰ� 4�϶�
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
					//���� 3
					itemRndNum = RND->getFromIntTo(1, 3);
					//�������ڰ� 1�϶�
					if (itemRndNum == 1)
					{
						itemImg = item1.getItemInfo().image;
						playerPrice = item1.getItemInfo().playerPrice;
						itemRc = item1.getItemInfo().rc;
						oriPrice = item1.getItemInfo().orignalPrice;
					}
					//�������ڰ� 2�ϋ�
					if (itemRndNum == 2)
					{
						itemImg = item2.getItemInfo().image;
						playerPrice = item2.getItemInfo().playerPrice;
						itemRc = item2.getItemInfo().rc;
						oriPrice = item2.getItemInfo().orignalPrice;
					}
					//�������ڰ� 3�϶�
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
				if (item4.getItemInfo().itemName != "�������")
				{
					//���� 3
					itemRndNum = RND->getFromIntTo(1, 3);
					//�������ڰ� 1�϶�
					if (itemRndNum == 1)
					{
						itemImg = item1.getItemInfo().image;
						playerPrice = item1.getItemInfo().playerPrice;
						itemRc = item1.getItemInfo().rc;
						oriPrice = item1.getItemInfo().orignalPrice;
					}
					//�������ڰ� 2�ϋ�
					if (itemRndNum == 2)
					{
						itemImg = item2.getItemInfo().image;
						playerPrice = item2.getItemInfo().playerPrice;
						itemRc = item2.getItemInfo().rc;
						oriPrice = item2.getItemInfo().orignalPrice;
					}
					//�������ڰ� 3�϶�
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
					//���� 2
					itemRndNum = RND->getFromIntTo(1, 2);
					//�������ڰ� 1�϶�
					if (itemRndNum == 1)
					{
						itemImg = item1.getItemInfo().image;
						playerPrice = item1.getItemInfo().playerPrice;
						itemRc = item1.getItemInfo().rc;
						oriPrice = item1.getItemInfo().orignalPrice;
					}
					//�������ڰ� 2�ϋ�
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
			if (item3.getItemInfo().itemName != "�������")
			{
				//1 o 2 x 3 o 4 o
				if (item4.getItemInfo().itemName != "�������")
				{
					//���� 3
					itemRndNum = RND->getFromIntTo(1, 3);
					//�������ڰ� 1�϶� 1������
					if (itemRndNum == 1)
					{
						itemImg = item1.getItemInfo().image;
						playerPrice = item1.getItemInfo().playerPrice;
						itemRc = item1.getItemInfo().rc;
						oriPrice = item1.getItemInfo().orignalPrice;
					}
					//�������ڰ� 2�϶� 3������
					if (itemRndNum == 2)
					{
						itemImg = item3.getItemInfo().image;
						playerPrice = item3.getItemInfo().playerPrice;
						itemRc = item3.getItemInfo().rc;
						oriPrice = item3.getItemInfo().orignalPrice;
					}
					//�������ڰ� 3�϶� 4������
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
					//���� 3
					itemRndNum = RND->getFromIntTo(1, 2);
					//�������ڰ� 1�϶� 1������
					if (itemRndNum == 1)
					{
						itemImg = item1.getItemInfo().image;
						playerPrice = item1.getItemInfo().playerPrice;
						itemRc = item1.getItemInfo().rc;
						oriPrice = item1.getItemInfo().orignalPrice;
					}
					//�������ڰ� 2�϶� 3������
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
				if (item4.getItemInfo().itemName != "�������")
				{
					//���� 2
					itemRndNum = RND->getFromIntTo(1, 2);
					//�������ڰ� 1�϶� 1������
					if (itemRndNum == 1)
					{
						itemImg = item1.getItemInfo().image;
						playerPrice = item1.getItemInfo().playerPrice;
						itemRc = item1.getItemInfo().rc;
						oriPrice = item1.getItemInfo().orignalPrice;
					}
					//�������ڰ� 2�϶� 3������
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
		if (item2.getItemInfo().itemName != "�������")
		{
			//1 x 2 o 3 o
			if (item3.getItemInfo().itemName != "�������")
			{
				//1 x 2 o 3 o 4 o
				if (item4.getItemInfo().itemName != "�������")
				{
					//���� 2
					itemRndNum = RND->getFromIntTo(1, 3);
					//�������ڰ� 1�϶� 1������
					if (itemRndNum == 1)
					{
						itemImg = item2.getItemInfo().image;
						playerPrice = item2.getItemInfo().playerPrice;
						itemRc = item2.getItemInfo().rc;
						oriPrice = item2.getItemInfo().orignalPrice;
					}
					//�������ڰ� 2�϶� 3������
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
					//���� 2
					itemRndNum = RND->getFromIntTo(1, 2);
					//�������ڰ� 1�϶� 1������
					if (itemRndNum == 1)
					{
						itemImg = item2.getItemInfo().image;
						playerPrice = item2.getItemInfo().playerPrice;
						itemRc = item2.getItemInfo().rc;
						oriPrice = item2.getItemInfo().orignalPrice;
					}
					//�������ڰ� 2�϶� 3������
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
				if (item4.getItemInfo().itemName != "�������")
				{
					itemRndNum = RND->getFromIntTo(1, 2);
					//�������ڰ� 1�϶� 1������
					if (itemRndNum == 1)
					{
						itemImg = item2.getItemInfo().image;
						playerPrice = item2.getItemInfo().playerPrice;
						itemRc = item2.getItemInfo().rc;
						oriPrice = item2.getItemInfo().orignalPrice;
					}
					//�������ڰ� 2�϶� 3������
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
			if (item3.getItemInfo().itemName != "�������")
			{
				//1 x 2 x 3 o 4 o
				if (item4.getItemInfo().itemName != "�������")
				{
					itemRndNum = RND->getFromIntTo(1, 2);
					//�������ڰ� 1�϶� 1������
					if (itemRndNum == 1)
					{
						itemImg = item3.getItemInfo().image;
						playerPrice = item3.getItemInfo().playerPrice;
						itemRc = item3.getItemInfo().rc;
						oriPrice = item3.getItemInfo().orignalPrice;
					}
					//�������ڰ� 2�϶� 3������
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
				if (item4.getItemInfo().itemName != "�������")
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
	//�����ۼ��� �ϳ����� ���Ϳ����� ���߱�
	reduceItemNum = reduceItemNum - 1;
	playerPrice = 1000;
	//��ũrc �����
	talkRc = RectMakeCenter((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2 - 100, _talkAni->getFrameWidth(), _talkAni->getFrameHeight());

	if (playerPrice > oriPrice + oriPrice * 0.5)//�ſ���
	{
		isVeryExpensive = true;
	}
	else if (playerPrice > oriPrice&&playerPrice <= oriPrice + oriPrice * 0.5)//���
	{
		isExpensive = true;
	}
	else if (playerPrice <= oriPrice && playerPrice >= oriPrice - oriPrice * 0.5)//��
	{
		isCheap = true;
	}
	else if (playerPrice < oriPrice - oriPrice * 0.5)//�ſ��
	{
		isVeryCheap = true;
	}
	//������ ����
	if (isCheap == true || isVeryCheap == true)
	{
		//������ ������ ������������ �������� ����
	//1 o
		if (item1.getItemInfo().itemName != "�������") {
			//1 o 2 o
			if (item2.getItemInfo().itemName != "�������")
			{
				//1 o 2 o 3 o
				if (item3.getItemInfo().itemName != "�������")
				{
					//1 o 2 o 3 o 4 o
					if (item4.getItemInfo().itemName != "�������")
					{
						//���� 4
						//�������ڰ� 1�϶�
						if (itemRndNum == 1)
						{
							item1.setItemCnt_equal(0);
						}
						//�������ڰ� 2�ϋ�
						if (itemRndNum == 2)
						{
							item2.setItemCnt_equal(0);
						}
						//�������ڰ� 3�϶�
						if (itemRndNum == 3)
						{
							item3.setItemCnt_equal(0);
						}
						//�������ڰ� 4�϶�
						if (itemRndNum == 4)
						{
							item4.setItemCnt_equal(0);
						}
					}
					//1 o 2 o 3 o 4 x
					else
					{
						//���� 3
						//�������ڰ� 1�϶�
						if (itemRndNum == 1)
						{
							item1.setItemCnt_equal(0);
						}
						//�������ڰ� 2�ϋ�
						if (itemRndNum == 2)
						{
							item2.setItemCnt_equal(0);
						}
						//�������ڰ� 3�϶�
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
					if (item4.getItemInfo().itemName != "�������")
					{
						//���� 3
						//�������ڰ� 1�϶�
						if (itemRndNum == 1)
						{
							item1.setItemCnt_equal(0);
						}
						//�������ڰ� 2�ϋ�
						if (itemRndNum == 2)
						{
							item2.setItemCnt_equal(0);
						}
						//�������ڰ� 3�϶�
						if (itemRndNum == 3)
						{
							item4.setItemCnt_equal(0);
						}
					}
					//1 o 2 o 3 x 4 x
					else
					{
						//���� 2
						//�������ڰ� 1�϶�
						if (itemRndNum == 1)
						{
							item1.setItemCnt_equal(0);
						}
						//�������ڰ� 2�ϋ�
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
				if (item3.getItemInfo().itemName != "�������")
				{
					//1 o 2 x 3 o 4 o
					if (item4.getItemInfo().itemName != "�������")
					{
						//���� 3
						//�������ڰ� 1�϶� 1������
						if (itemRndNum == 1)
						{
							item1.setItemCnt_equal(0);
						}
						//�������ڰ� 2�϶� 3������
						if (itemRndNum == 2)
						{
							item3.setItemCnt_equal(0);
						}
						//�������ڰ� 3�϶� 4������
						if (itemRndNum == 2)
						{
							item4.setItemCnt_equal(0);
						}
					}
					//1 o 2 x 3 o 4 x
					else
					{
						//���� 3
						//�������ڰ� 1�϶� 1������
						if (itemRndNum == 1)
						{
							item1.setItemCnt_equal(0);
						}
						//�������ڰ� 2�϶� 3������
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
					if (item4.getItemInfo().itemName != "�������")
					{
						//���� 2
						//�������ڰ� 1�϶� 1������
						if (itemRndNum == 1)
						{
							item1.setItemCnt_equal(0);
						}
						//�������ڰ� 2�϶� 3������
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
			if (item2.getItemInfo().itemName != "�������")
			{
				//1 x 2 o 3 o
				if (item3.getItemInfo().itemName != "�������")
				{
					//1 x 2 o 3 o 4 o
					if (item4.getItemInfo().itemName != "�������")
					{
						//���� 2
						//�������ڰ� 1�϶� 1������
						if (itemRndNum == 1)
						{
							item2.setItemCnt_equal(0);
						}
						//�������ڰ� 2�϶� 3������
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
						//���� 2
						//�������ڰ� 1�϶� 1������
						if (itemRndNum == 1)
						{
							item2.setItemCnt_equal(0);
						}
						//�������ڰ� 2�϶� 3������
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
					if (item4.getItemInfo().itemName != "�������")
					{
						//�������ڰ� 1�϶� 1������
						if (itemRndNum == 1)
						{
							item2.setItemCnt_equal(0);
						}
						//�������ڰ� 2�϶� 3������
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
				if (item3.getItemInfo().itemName != "�������")
				{
					//1 x 2 x 3 o 4 o
					if (item4.getItemInfo().itemName != "�������")
					{
						//�������ڰ� 1�϶� 1������
						if (itemRndNum == 1)
						{
							item3.setItemCnt_equal(0);
						}
						//�������ڰ� 2�϶� 3������
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
					if (item4.getItemInfo().itemName != "�������")
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
//����ǥ��
void buyNPC::talking()
{
	_talkAni = ANIMATIONMANAGER->findAnimation("������");
	_talkAni->start();
}

void buyNPC::soso()
{
	_talkAni = ANIMATIONMANAGER->findAnimation("����");
	_talkAni->start();
}
//j������ �Ǹ�Ȯ��
bool buyNPC::sell()
{
	//��ٸ������϶� j������
	if (step == 3 && KEYMANAGER->isOnceKeyDown('J'))
	{
		//���߰�
		PLAYER->setMoney(PLAYER->getMoney() + playerPrice);
		return true;
	}
	return false;
}

void buyNPC::cheap()
{
	_talkAni = ANIMATIONMANAGER->findAnimation("��");
	_talkAni->start();
	step = 2;
}

void buyNPC::expensive()
{
	_talkAni = ANIMATIONMANAGER->findAnimation("���");
	_talkAni->start();
	step = 5;
}

void buyNPC::veryCheap()
{
	_talkAni = ANIMATIONMANAGER->findAnimation("�ſ��");
	_talkAni->start();
	step = 2;
}

void buyNPC::veryExpensive()
{
	_talkAni = ANIMATIONMANAGER->findAnimation("�ſ���");
	_talkAni->start();
	step = 5;
}

void buyNPC::wait()
{
	_talkAni = ANIMATIONMANAGER->findAnimation("��ٸ�");
	_talkAni->start();
}

