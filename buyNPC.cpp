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

void buyNPC::update(vector<item>_vSellItem)
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
		talk(_vSellItem);
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
void buyNPC::talk(vector<item>_vSellItem)
{
	//������ ������ ������������ �������� ����
	int isNum = 0;
	for (int i = 0; i < _vSellItem.size(); i++)
	{
		if (_vSellItem[i].getItemInfo().itemName != "�������")
		{
			isNum++;
		}
		itemRndNum = RND->getFromIntTo(0, isNum);
	}
	//������ �̹��� ũ�� ���� �ǸŰ� ��������
	itemImg = _vSellItem[3].getItemInfo().image;
	//playerPrice = _vSellItem[3].getItemInfo().playerPrice;
	playerPrice = 100;
	itemRc = _vSellItem[3].getItemInfo().rc;
	oriPrice = _vSellItem[3].getItemInfo().orignalPrice;
	//��ũrc �����
	talkRc = RectMakeCenter((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2 - 100, _talkAni->getFrameWidth(), _talkAni->getFrameHeight());

	if (playerPrice > oriPrice + oriPrice * 0.5)//�ſ���
	{
		isVeryExpensive = true;
	}
	if (playerPrice > oriPrice&&playerPrice <= oriPrice + oriPrice * 0.5)//���
	{
		isExpensive = true;
	}
	if (playerPrice <= oriPrice && playerPrice >= oriPrice - oriPrice * 0.5)//��
	{
		isCheap = true;
	}
	if (playerPrice < oriPrice - oriPrice * 0.5)//�ſ��
	{
		isVeryCheap = true;
	}



}
//������
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

bool buyNPC::sell()
{
	//��ٸ������϶� j������
	if (step == 3 && KEYMANAGER->isOnceKeyDown('J'))
	{
		//�����Ұ�?���߰�
		//PLAYER->setMoney()=PLAYER->getMoney() + playerPrice;
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

