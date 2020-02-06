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

	_player._playerimg = IMAGEMANAGER->findImage("샵캐릭터");
	_player.x = WINSIZEX / 2;
	_player.y = WINSIZEY / 2;

	_player._playerrect = RectMakeCenter(_player.x, _player.y, _player._playerimg->getFrameWidth(), _player._playerimg->getHeight());
	_player._collisionplayer = RectMakeCenter((_player._playerrect.left + _player._playerrect.right) / 2, (_player._playerrect.top + _player._playerrect.bottom) / 2, 50, 70);
	_isanimation = false;

	_player._playerLocation = SHOP_PLAYER_VERSION;
	_player._playermove = PLAYER_DOWN_IDLE;
	_player._playercount = 0;
	_player._playerindex = 0;
	_player.HP = 100;

	return S_OK;
}

void player::release()
{
	SAFE_DELETE(_player._playerani);
}

void player::update()
{

	playermoveversion(); //버전 함수 플레이가 shop인지 dugeon인지 나타내는 함수..?
	shopPlayermove();
	//	dungeonPlayermove();


	if (KEYMANAGER->isOnceKeyDown('1'))  //예비용으로 추가한것 1번 샵캐릭터
	{
		_player._playerimg = IMAGEMANAGER->findImage("샵캐릭터");
		_player._playerLocation = SHOP_PLAYER_VERSION;
	}
	if (KEYMANAGER->isOnceKeyDown('2')) //예비용으로 추가한것 2번 던전캐릭터 모션
	{
		_player._playerimg = IMAGEMANAGER->findImage("던전캐릭터");
		_player._playerLocation = DUNGEON_PLAYER_VERSION;
	}
}

void player::shopPlayermove()
{
	if (!_isanimation)
	{
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			_player._playermove = PLAYER_LEFT;
			OffsetRect(&_player._collisionplayer, -2, 0);
			_player.x -= 2.0f;
		}
		if (KEYMANAGER->isOnceKeyUp('A'))
		{
			_player._playermove = PLAYER_LEFT_IDLE;
		}
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			_player._playermove = PLAYER_RIGHT;
			OffsetRect(&_player._collisionplayer, 2, 0);
			_player.x += 2.0f;

		}
		if (KEYMANAGER->isOnceKeyUp('D'))
		{
			_player._playermove = PLAYER_RIGHT_IDLE;
		}
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			_player._playermove = PLAYER_UP;
			_player.y -= 2.0f;
			OffsetRect(&_player._collisionplayer, 0, -2);
		}
		if (KEYMANAGER->isOnceKeyUp('S'))
		{
			_player._playermove = PLAYER_DOWN_IDLE;
		}
		if (KEYMANAGER->isStayKeyDown('S'))
		{
			_player._playermove = PLAYER_DOWN;
			OffsetRect(&_player._collisionplayer, 0, 2);
			_player.y += 2.0f;
		}
		if (KEYMANAGER->isOnceKeyUp('W'))
		{
			_player._playermove = PLAYER_UP_IDLE;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		time = TIMEMANAGER->getWorldTime();
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
	if (TIMEMANAGER->getWorldTime() - time >= 1)
	{
		_isanimation = false;
		if (_player._playermove == PLAYER_LEFT_ROLL)
		{
			_player._playermove = PLAYER_LEFT_IDLE;
		}
		if (_player._playermove == PLAYER_BACK_ROLL)
		{
			_player._playermove = PLAYER_DOWN_IDLE;
		}
		if (_player._playermove == PLAYER_RIGHT_ROLL)
		{
			_player._playermove = PLAYER_RIGHT_IDLE;
		}
		if (_player._playermove == PLAYER_UP_ROLL)
		{
			_player._playermove = PLAYER_UP_IDLE;
		}
	}

	_player._playerrect = RectMakeCenter(_player.x, _player.y, _player._playerimg->getFrameWidth(), _player._playerimg->getFrameHeight());
}

void player::dungeonPlayermove()
{
	if (!_isanimation)
	{
		if (KEYMANAGER->isStayKeyDown('S'))			//아래
		{
			_player._playermove = PLAYER_DOWN;
			_player.y += 2;
			OffsetRect(&_player._collisionplayer, 0, 2);
		}
		if (KEYMANAGER->isOnceKeyUp('S'))
		{
			_player._playermove = PLAYER_DOWN_IDLE;
		}
		if (KEYMANAGER->isStayKeyDown('A'))		//왼쪽
		{
			_player._playermove = PLAYER_LEFT;
			_player.x -= 2;
			OffsetRect(&_player._collisionplayer, -2, 0);
		}
		if (KEYMANAGER->isOnceKeyUp('A'))
		{
			_player._playermove = PLAYER_LEFT_IDLE;
		}
		if (KEYMANAGER->isStayKeyDown('D'))		//오른쪽
		{
			_player._playermove = PLAYER_RIGHT;
			OffsetRect(&_player._collisionplayer, 2, 0);
			_player.x += 2;
		}
		if (KEYMANAGER->isOnceKeyUp('D'))
		{
			_player._playermove = PLAYER_RIGHT_IDLE;
		}
		if (KEYMANAGER->isStayKeyDown('W'))		//위
		{
			_player._playermove = PLAYER_UP;
			_player.y -= 2;
		}
		if (KEYMANAGER->isOnceKeyUp('W'))
		{
			_player._playermove = PLAYER_UP_IDLE;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		time = TIMEMANAGER->getWorldTime();
		_isanimation = true;
		if (_player._playermove == PLAYER_LEFT || _player._playermove == PLAYER_LEFT_IDLE)			//LEFT
		{
			_player._playermove = PLAYER_LEFT_ROLL;

		}
		if (_player._playermove == PLAYER_RIGHT || _player._playermove == PLAYER_RIGHT_IDLE)		//RIGHT
		{
			_player._playermove = PLAYER_RIGHT_ROLL;

		}
		if (_player._playermove == PLAYER_UP || _player._playermove == PLAYER_UP_IDLE)
		{
			_player._playermove = PLAYER_UP_ROLL;

		}
		if (_player._playermove == PLAYER_DOWN || _player._playermove == PLAYER_DOWN_IDLE)
		{
			_player._playermove = PLAYER_BACK_ROLL;
		}
	}
	if (TIMEMANAGER->getWorldTime() - time > 1.5)
	{
		_isanimation = false;
		if (_player._playermove == PLAYER_BACK_ROLL)		  //앞
		{
			_player._playermove = PLAYER_DOWN_IDLE;
		}
		if (_player._playermove == PLAYER_UP_ROLL)			//뒤
		{
			_player._playermove = PLAYER_UP_IDLE;
		}
		if (_player._playermove == PLAYER_RIGHT_ROLL)			//오른쪽
		{
			_player._playermove = PLAYER_RIGHT_IDLE;
		}
		if (_player._playermove == PLAYER_LEFT_ROLL)			//왼쪽
		{
			_player._playermove = PLAYER_LEFT_IDLE;
		}
	}

}


void player::playermoveversion() //플레이어 버전 함수
{
	switch (_player._playerLocation)
	{
	case SHOP_PLAYER_VERSION: //shop player 버전 
		switch (_player._playermove)
		{
		case PLAYER_DOWN_IDLE:  //아래 멈춤
			_player._playercount++;
			_player._playerimg->setFrameY(5);
			if (_player._playercount % 7 == 0)
			{
				_player._playercount = 0;
				_player._playerindex++;
				if (_player._playerindex >= _player._playerimg->getMaxFrameX())
				{
					_player._playerindex = 0;
				}
				_player._playerimg->setFrameX(_player._playerindex);
			}
			break;

		case PLAYER_DOWN: // 아래런
			_player._playercount++;
			_player._playerimg->setFrameY(4);
			if (_player._playercount % 7 == 0)
			{
				_player._playercount = 0;
				_player._playerindex++;
				if (_player._playerindex >= _player._playerimg->getMaxFrameX() - 3)
				{
					_player._playerindex = 0;
				}
				_player._playerimg->setFrameX(_player._playerindex);
			}
			break;

		case PLAYER_UP_IDLE: //위 멈춤
			_player._playercount++;
			_player._playerimg->setFrameY(7);
			if (_player._playercount % 7 == 0)
			{
				_player._playercount = 0;
				_player._playerindex++;
				if (_player._playerindex >= _player._playerimg->getMaxFrameX())
				{
					_player._playerindex = 0;
				}
				_player._playerimg->setFrameX(_player._playerindex);
			}
			break;

		case PLAYER_UP:					//위쪽 런 
			_player._playercount++;
			_player._playerimg->setFrameY(6);
			if (_player._playercount % 10 == 0)
			{
				_player._playercount = 0;
				_player._playerindex++;
				if (_player._playerindex >= _player._playerimg->getMaxFrameX() - 2)
				{
					_player._playerindex = 0;
				}
				_player._playerimg->setFrameX(_player._playerindex);
			}
			break;

		case PLAYER_LEFT_IDLE:					//왼쪽 멈춤
			_player._playercount++;
			_player._playerimg->setFrameY(3);
			if (_player._playercount % 7 == 0)
			{
				_player._playercount = 0;
				_player._playerindex++;
				if (_player._playerindex >= _player._playerimg->getMaxFrameX())
				{
					_player._playerindex = 0;
				}
				_player._playerimg->setFrameX(_player._playerindex);
			}
			break;

		case PLAYER_LEFT:					// 왼쪽 런
			_player._playercount++;
			_player._playerimg->setFrameY(2);
			if (_player._playercount % 7 == 0)
			{
				_player._playercount = 0;
				_player._playerindex++;
				if (_player._playerindex >= _player._playerimg->getMaxFrameX() - 2)
				{
					_player._playerindex = 0;
				}
				_player._playerimg->setFrameX(_player._playerindex);
			}
			break;

		case PLAYER_RIGHT_IDLE:			//오른쪽 멈춤
			_player._playercount++;
			_player._playerimg->setFrameY(1);
			if (_player._playercount % 7 == 0)
			{
				_player._playercount = 0;
				_player._playerindex++;
				if (_player._playerindex >= _player._playerimg->getMaxFrameX() - 2)
				{
					_player._playerindex = 0;
				}
				_player._playerimg->setFrameX(_player._playerindex);
			}
			break;

		case PLAYER_RIGHT: //오른쪽 런 
			_player._playercount++;
			_player._playerimg->setFrameY(0);
			if (_player._playercount % 7 == 0)
			{
				_player._playercount = 0;
				_player._playerindex++;
				if (_player._playerindex >= _player._playerimg->getMaxFrameX() - 2)
				{
					_player._playerindex = 0;
				}
				_player._playerimg->setFrameX(_player._playerindex);
			}
			break;

		case PLAYER_RIGHT_ROLL:  // shop 오른쪽구르기
			_player._playercount++;
			_player._playerimg->setFrameY(9);
			if (_player._playercount % 9 == 0)
			{
				_player._playercount = 0;
				_player._playerindex++;
				if (_player._playerindex >= _player._playerimg->getMaxFrameX() - 2)
				{
					_player._playerindex = 0;
				}
				_player._playerimg->setFrameX(_player._playerindex);
			}
			OffsetRect(&_player._collisionplayer, 2, 0);
			_player.x += 2.0f;

			break;

		case PLAYER_LEFT_ROLL:  // shop 왼쪽 구르기
			_player._playercount++;
			_player._playerimg->setFrameY(8);
			if (_player._playercount % 9 == 0)
			{
				_player._playercount = 0;
				_player._playerindex++;
				if (_player._playerindex >= _player._playerimg->getMaxFrameX() - 2)
				{
					_player._playerindex = 0;
				}
				_player._playerimg->setFrameX(_player._playerindex);
			}
			OffsetRect(&_player._collisionplayer, -2, 0);
			_player.x -= 2.0f;
			break;

		case PLAYER_UP_ROLL:  // shop 앞으로 구르기
			_player._playercount++;
			_player._playerimg->setFrameY(11);
			if (_player._playercount % 9 == 0)
			{
				_player._playercount = 0;
				_player._playerindex++;
				if (_player._playerindex >= _player._playerimg->getMaxFrameX() - 2)
				{
					_player._playerindex = 0;
				}
				_player._playerimg->setFrameX(_player._playerindex);
			}
			OffsetRect(&_player._collisionplayer, 0, -2);
			_player.y -= 2.0f;
			break;

		case PLAYER_BACK_ROLL: // shop 뒤로 구르기
			_player._playercount++;
			_player._playerimg->setFrameY(10);
			if (_player._playercount % 9 == 0)
			{
				_player._playercount = 0;
				_player._playerindex++;
				if (_player._playerindex >= _player._playerimg->getMaxFrameX() - 2)
				{
					_player._playerindex = 0;
				}
				_player._playerimg->setFrameX(_player._playerindex);
			}
			OffsetRect(&_player._collisionplayer, 0, 2);
			_player.y += 2.0f;
			break;
		}
		break;
	case DUNGEON_PLAYER_VERSION:    //dungeon player 버전
		dungeonPlayermove();
		switch (_player._playermove)
		{

		case PLAYER_DOWN:
			_player._playercount++;
			_player._playerimg->setFrameY(1);
			if (_player._playercount % 7 == 0)
			{
				_player._playercount = 0;
				_player._playerindex++;
				if (_player._playerindex >= _player._playerimg->getMaxFrameX() - 2)
				{
					_player._playerindex = 0;
				}
				_player._playerimg->setFrameX(_player._playerindex);
			}
			break;
		case PLAYER_UP_IDLE:
			_player._playercount++;
			_player._playerimg->setFrameY(10);
			if (_player._playercount % 10 == 0)
			{
				_player._playercount = 0;
				_player._playerindex++;
				if (_player._playerindex >= _player._playerimg->getMaxFrameX())
				{
					_player._playerindex = 0;
				}
				_player._playerimg->setFrameX(_player._playerindex);
			}
			break;
		case 	PLAYER_UP:
			_player._playercount++;
			_player._playerimg->setFrameY(0);
			if (_player._playercount % 7 == 0)
			{
				_player._playercount = 0;
				_player._playerindex++;
				if (_player._playerindex >= _player._playerimg->getMaxFrameX() - 2)
				{
					_player._playerindex = 0;
				}
				_player._playerimg->setFrameX(_player._playerindex);
			}
			break;
		case PLAYER_LEFT_IDLE:
			_player._playercount++;
			_player._playerimg->setFrameY(9);
			if (_player._playercount % 7 == 0)
			{
				_player._playercount = 0;
				_player._playerindex++;
				if (_player._playerindex >= _player._playerimg->getMaxFrameX())
				{
					_player._playerindex = 0;
				}
				_player._playerimg->setFrameX(_player._playerindex);
			}
			break;
		case PLAYER_LEFT:
			_player._playercount++;
			_player._playerimg->setFrameY(3);
			if (_player._playercount % 7 == 0)
			{
				_player._playercount = 0;
				_player._playerindex++;
				if (_player._playerindex >= _player._playerimg->getMaxFrameX() - 2)
				{
					_player._playerindex = 0;
				}
				_player._playerimg->setFrameX(_player._playerindex);
			}
			break;
		case PLAYER_RIGHT_IDLE:
			_player._playercount++;
			_player._playerimg->setFrameY(8);
			if (_player._playercount % 7 == 0)
			{
				_player._playercount = 0;
				_player._playerindex++;
				if (_player._playerindex >= _player._playerimg->getMaxFrameX())
				{
					_player._playerindex = 0;
				}
				_player._playerimg->setFrameX(_player._playerindex);
			}
			break;
		case PLAYER_RIGHT:
			_player._playercount++;
			_player._playerimg->setFrameY(2);
			if (_player._playercount % 10 == 0)
			{
				_player._playercount = 0;
				_player._playerindex++;
				if (_player._playerindex >= _player._playerimg->getMaxFrameX() - 2)
				{
					_player._playerindex = 0;
				}
				_player._playerimg->setFrameX(_player._playerindex);
			}
			break;
		case PLAYER_RIGHT_ROLL:
			_player._playercount++;
			_player._playerimg->setFrameY(4);
			if (_player._playercount % 9 == 0)
			{
				_player._playercount = 0;
				_player._playerindex++;
				if (_player._playerindex >= _player._playerimg->getMaxFrameX() - 2)
				{
					_player._playerindex = 0;
				}
				_player._playerimg->setFrameX(_player._playerindex);
			}
			OffsetRect(&_player._collisionplayer, 2, 0);
			_player.x += 2.0f;

			break;
		case PLAYER_LEFT_ROLL:
			_player._playercount++;
			_player._playerimg->setFrameY(5);
			if (_player._playercount % 9 == 0)
			{
				_player._playercount = 0;
				_player._playerindex++;
				if (_player._playerindex >= _player._playerimg->getMaxFrameX() - 2)
				{
					_player._playerindex = 0;
				}
				_player._playerimg->setFrameX(_player._playerindex);
			}
			OffsetRect(&_player._collisionplayer, -2, 0);
			_player.x -= 2.0f;
			break;
		case PLAYER_UP_ROLL:
			_player._playercount++;
			_player._playerimg->setFrameY(6);
			if (_player._playercount % 9 == 0)
			{
				_player._playercount = 0;
				_player._playerindex++;
				if (_player._playerindex >= _player._playerimg->getMaxFrameX() - 2)
				{
					_player._playerindex = 0;
				}
				_player._playerimg->setFrameX(_player._playerindex);
			}
			OffsetRect(&_player._collisionplayer, 0, -2);
			_player.y -= 2.0f;
			break;
		case PLAYER_BACK_ROLL:
			_player._playercount++;
			_player._playerimg->setFrameY(7);
			if (_player._playercount % 9 == 0)
			{
				_player._playercount = 0;
				_player._playerindex++;
				if (_player._playerindex >= _player._playerimg->getMaxFrameX() - 2)
				{
					_player._playerindex = 0;
				}
				_player._playerimg->setFrameX(_player._playerindex);
			}
			OffsetRect(&_player._collisionplayer, 0, 2);
			_player.y += 2.0f;
			break;
		case PLAYER_DIE:
			_player._playercount++;
			_player._playerimg->setFrameY(12);
			if (_player._playercount % 10 == 0)
			{
				_player._playercount = 0;
				_player._playerindex++;
				if (_player._playerimg->getMaxFrameX())
				{
					_player._playerindex = 0;
				}
				_player._playerimg->setFrameX(_player._playerindex);
			}
			break;
		case PLAYER_DOWN_IDLE:
			_player._playercount++;
			_player._playerimg->setFrameY(11);
			if (_player._playercount % 10 == 0)
			{
				_player._playercount = 0;
				_player._playerindex++;
				if (_player._playerindex >= _player._playerimg->getMaxFrameX())
				{
					_player._playerindex = 0;
				}
				_player._playerimg->setFrameX(_player._playerindex);
			}
			break;
		}
		break;
	}
}


void player::render(HDC hdc)
{

	_player._playerimg->frameRender(hdc, _player._playerrect.left, _player._playerrect.top);

}