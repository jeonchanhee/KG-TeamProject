#include "stdafx.h"
#include "player.h"


player::player()
{
}


player::~player()
{
}

HRESULT player::init()
{

	allplayerimage();  //�̹��� ���ִ� �� 
	allplayerani(); // �ִϸ��̼� ���ִ� �� 

	_player._playerimg = IMAGEMANAGER->findImage("��ĳ����");
	_player._playerrect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 - 200, 100, 100);


	_player._playerani = ANIMATIONMANAGER->findAnimation("shop_up_Idle");	//���۾ִϸ��̼� ����
	ANIMATIONMANAGER->resume("shop_up_Idle"); //ù������ front idle�κ��� �����Ѵ�. 

	_isanimation = false;
	return S_OK;
}

void player::release()
{
	SAFE_DELETE(_player._playerani);
}

void player::update()
{
	//shopPlayermove();
	playermoveversion(); //���� �Լ� �÷��̰� shop���� dugeon���� ��Ÿ���� �Լ�..?

}

void player::shopPlayermove()
{
	if (!_isanimation)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_player._playermove = PLAYER_LEFT;
			_player._playerrect.left -= 2.0f;
			_player._playerrect.right -= 2.0f;

		}
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			_player._playermove = PLAYER_LEFT_IDLE;
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_player._playermove = PLAYER_RIGHT;
			_player._playerrect.left += 2.0f;
			_player._playerrect.right += 2.0f;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			_player._playermove = PLAYER_RIGHT_IDLE;
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			_player._playermove = PLAYER_UP;
			_player._playerrect.top -= 2.0f;
			_player._playerrect.bottom -= 2.0f;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_UP))
		{
			_player._playermove = PLAYER_UP_IDLE;
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_player._playermove = PLAYER_DOWN;
			_player._playerrect.top += 2.0f;
			_player._playerrect.bottom += 2.0f;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
		{
			_player._playermove = PLAYER_DOWN_IDLE;

		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_isanimation = true;
		if (_player._playermove == PLAYER_LEFT || _player._playermove == PLAYER_LEFT_IDLE)
		{
			_player._playermove = PLAYER_LEFT_ROLL;
		}
		if (_player._playermove == PLAYER_RIGHT || _player._playermove == PLAYER_RIGHT_IDLE)
		{
			_player._playermove = PLAYER_RIGHT_ROLL;
		}
		if (_player._playermove == PLAYER_DOWN || _player._playermove == PLAYER_DOWN_IDLE)
		{
			_player._playermove = PLAYER_BACK_ROLL;
		}
		if (_player._playermove == PLAYER_UP || _player._playermove == PLAYER_UP_IDLE)
		{
			_player._playermove = PLAYER_UP_ROLL;
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_SPACE))
	{
		_isanimation = false;

	}
}


void player::playermoveversion() //�÷��̾� ���� �Լ�
{
	switch (_player._playerversions)
	{
	case SHOP_PLAYER_VERSION: //shop player ���� 
		shopPlayermove();
		switch (_player._playermove)
		{
		case PLAYER_DOWN_IDLE:
			_player._playerani = ANIMATIONMANAGER->findAnimation("shop_up_Idle");
			ANIMATIONMANAGER->resume("shop_up_Idle");
			break;

		case PLAYER_DOWN:
			_player._playerani = ANIMATIONMANAGER->findAnimation("shop_up_walking");
			ANIMATIONMANAGER->resume("shop_up_walking");
			break;

		case PLAYER_UP_IDLE:
			_player._playerani = ANIMATIONMANAGER->findAnimation("shop_back_Idle");
			ANIMATIONMANAGER->resume("shop_back_Idle");
			break;

		case PLAYER_UP:
			_player._playerani = ANIMATIONMANAGER->findAnimation("shop_back_walking");
			ANIMATIONMANAGER->resume("shop_back_walking");
			break;

		case PLAYER_LEFT_IDLE:
			_player._playerani = ANIMATIONMANAGER->findAnimation("shop_left_Idle");
			ANIMATIONMANAGER->resume("shop_left_Idle");
			break;

		case PLAYER_LEFT:
			_player._playerani = ANIMATIONMANAGER->findAnimation("shop_left_walking");
			ANIMATIONMANAGER->resume("shop_left_walking");
			break;

		case PLAYER_RIGHT_IDLE:
			_player._playerani = ANIMATIONMANAGER->findAnimation("shop_right_Idle");
			ANIMATIONMANAGER->resume("shop_right_Idle");
			break;

		case PLAYER_RIGHT:
			_player._playerani = ANIMATIONMANAGER->findAnimation("shop_right_walking");
			ANIMATIONMANAGER->resume("shop_right_walking");
			break;

		case PLAYER_RIGHT_ROLL:  // shop �����ʱ�����
			_player._playerani = ANIMATIONMANAGER->findAnimation("shop_right_roll");
			ANIMATIONMANAGER->resume("shop_right_roll");
			OffsetRect(&_player._playerrect, 2, 0);
			break;

		case PLAYER_LEFT_ROLL:  // shop ���� ������
			_player._playerani = ANIMATIONMANAGER->findAnimation("shop_left_roll");
			ANIMATIONMANAGER->resume("shop_left_roll");
			OffsetRect(&_player._playerrect, -2, 0);
			break;

		case PLAYER_UP_ROLL:  // shop ������ ������
			_player._playerani = ANIMATIONMANAGER->findAnimation("shop_up_roll");
			ANIMATIONMANAGER->resume("shop_up_roll");
			OffsetRect(&_player._playerrect, 0, -2);
			break;

		case PLAYER_BACK_ROLL: // shop �ڷ� ������
			_player._playerani = ANIMATIONMANAGER->findAnimation("shop_back_roll");
			ANIMATIONMANAGER->resume("shop_back_roll");
			OffsetRect(&_player._playerrect, 0, 2);
			break;
		}
		break;
		/*case DUNGEON_PLAYER_VERSION:    //dungeon player ����

			break;*/
	}
}


void player::render()
{
	_player._playerimg->aniRender(getMemDC(), _player._playerrect.left, _player._playerrect.top, _player._playerani);

}