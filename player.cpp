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

	allplayerimage();  //이미지 모여있는 곳 
	allplayerani(); // 애니메이션 모여있는 곳 

	_player._playerimg = IMAGEMANAGER->findImage("샵캐릭터");
	_player._playerrect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 - 200, 100, 100);


	_player._playerani = ANIMATIONMANAGER->findAnimation("shop_up_Idle");	//시작애니메이션 설정
	ANIMATIONMANAGER->resume("shop_up_Idle"); //첫동작은 front idle로부터 시작한다. 

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
	playermoveversion(); //버전 함수 플레이가 shop인지 dugeon인지 나타내는 함수..?

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


void player::playermoveversion() //플레이어 버전 함수
{
	switch (_player._playerversions)
	{
	case SHOP_PLAYER_VERSION: //shop player 버전 
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

		case PLAYER_RIGHT_ROLL:  // shop 오른쪽구르기
			_player._playerani = ANIMATIONMANAGER->findAnimation("shop_right_roll");
			ANIMATIONMANAGER->resume("shop_right_roll");
			OffsetRect(&_player._playerrect, 2, 0);
			break;

		case PLAYER_LEFT_ROLL:  // shop 왼쪽 구르기
			_player._playerani = ANIMATIONMANAGER->findAnimation("shop_left_roll");
			ANIMATIONMANAGER->resume("shop_left_roll");
			OffsetRect(&_player._playerrect, -2, 0);
			break;

		case PLAYER_UP_ROLL:  // shop 앞으로 구르기
			_player._playerani = ANIMATIONMANAGER->findAnimation("shop_up_roll");
			ANIMATIONMANAGER->resume("shop_up_roll");
			OffsetRect(&_player._playerrect, 0, -2);
			break;

		case PLAYER_BACK_ROLL: // shop 뒤로 구르기
			_player._playerani = ANIMATIONMANAGER->findAnimation("shop_back_roll");
			ANIMATIONMANAGER->resume("shop_back_roll");
			OffsetRect(&_player._playerrect, 0, 2);
			break;
		}
		break;
		/*case DUNGEON_PLAYER_VERSION:    //dungeon player 버전

			break;*/
	}
}


void player::render()
{
	_player._playerimg->aniRender(getMemDC(), _player._playerrect.left, _player._playerrect.top, _player._playerani);

}