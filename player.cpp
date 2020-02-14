#include "stdafx.h"
#include "player.h"

player::player() {}
player::~player() {}

HRESULT player::init()
{
	allplayerimage();
	_player._playerimg = IMAGEMANAGER->findImage("샵캐릭터");
	_player.x = WINSIZEX / 2;  //_player._playerrect에 넣기  위한 int x 값
	_player.y = WINSIZEY / 2;  //_player._playerrect에 넣기 위한 int y 값

	//랙트들
	_player._playerrect = RectMakeCenter(_player.x, _player.y, _player._playerimg->getFrameWidth(), _player._playerimg->getFrameHeight());  // 이미지 랙트... 
	_player._collisionplayer = RectMakeCenter((_player._playerrect.left + _player._playerrect.right) / 2, (_player._playerrect.top + _player._playerrect.bottom) / 2, 50, 70); //  충돌할 때 필요한  랙트 ->만든 이유 이미지 크기 때문에 _playerrect 너무 커서 안에 그냥 만들어 준 것 뿐

	_isanimation = false;  //구르기 상태와 구르지 않은 상태를 판별하는 bool

	_player._playerLocation = SHOP_PLAYER_VERSION;				//shop_player
	_player._playermove = PLAYER_DOWN_IDLE;						//자세 초기화
	_player._attackplayer = PLAYER_SWORD;
	_player._attacmove = PLAYER_ATK_STOP;
	_player._playercount = 0;
	_player._playerindex = 0;
	_player.attCount = 0;
	_player._pmoney = 9999;


	_player._isattackmove = false;						//  false일때는 일반 던전 무브상태 
	_player._isFire = false;


	_arrowfirst = new weapons;
	_arrowfirst->init();

	//플레이어  프로그래스바
	_playerhp._HP = _playerhp._maxhp = 100;
	_playerhp._hpbar = new PlayerHpbar;
	_playerhp._hpbar->init("images/UI/blood.bmp", "images/UI/hpBar.bmp", 0, 0, 125, 35);
	_playerhp._hpbar->setGauge(_playerhp._HP, _playerhp._maxhp);

	_ishwing = false;		// 칼을 휘둘렀냐 안휘둘렀냐?(안휘두름)

	_inventory = new inventory;
	_inventory->init();



	return S_OK;
}

void player::release()
{
	SAFE_DELETE(_arrowfirst);
}

void player::update()
{
	playerKeyControl();
	monsterbattle();					//몬스터랑 배틀
	if (_player._isattackmove)	attackmove();
	else 	playermoveversion(); //버전 함수 플레이가 shop인지 dugeon인지 나타내는 함수..?
	if (_player._playerLocation == DUNGEON_PLAYER_VERSION)
	{
		playerAtt();
	}

	_inventory->update();
	_arrowfirst->update();
}

void player::playerKeyControl()
{
	if (!_isanimation || !_player._isattackmove)
	{
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			if (KEYMANAGER->isStayKeyDown('A'))
			{
				_player._playermove = PAYER_LEFT_UP;
			}
			else if (KEYMANAGER->isStayKeyDown('D'))
			{
				_player._playermove = PAYER_RIGHT_UP;
			}
			else
			{
				_player._playermove = PLAYER_UP;
			}
			_player.y -= 5;
		}

		if (KEYMANAGER->isStayKeyDown('S'))
		{
			if (KEYMANAGER->isStayKeyDown('A'))
			{
				_player._playermove = PAYER_LEFT_DOWN;
			}
			else if (KEYMANAGER->isStayKeyDown('D'))
			{
				_player._playermove = PAYER_RIGHT_DOWN;
			}
			else
			{
				_player._playermove = PLAYER_DOWN;
			}
			_player.y += 5;
		}

		if (KEYMANAGER->isStayKeyDown('A'))
		{
			if (_player._playermove != PAYER_LEFT_DOWN
				&& _player._playermove != PAYER_LEFT_UP) _player._playermove = PLAYER_LEFT;
			_player.x -= 5;
		}

		if (KEYMANAGER->isStayKeyDown('D'))
		{
			if (_player._playermove != PAYER_RIGHT_DOWN
				&& _player._playermove != PAYER_RIGHT_UP) 	_player._playermove = PLAYER_RIGHT;
			_player.x += 5;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))  //플레이어 샵이랑 겹침
	{
		if (!_isanimation)
		{
			_player._playerindex = 0;
			_isanimation = true;

			if (_player._playermove == PLAYER_UP || _player._playermove == PLAYER_UP_IDLE)
			{
				_player._playermove = PLAYER_UP_ROLL;
			}

			if (_player._playermove == PLAYER_DOWN || _player._playermove == PLAYER_DOWN_IDLE)
			{
				_player._playermove = PLAYER_BACK_ROLL;
			}

			if (_player._playermove == PLAYER_LEFT || _player._playermove == PLAYER_LEFT_IDLE)
			{
				_player._playermove = PLAYER_LEFT_ROLL;
			}

			if (_player._playermove == PLAYER_RIGHT || _player._playermove == PLAYER_RIGHT_IDLE)
			{
				_player._playermove = PLAYER_RIGHT_ROLL;
			}

			if (_player._playermove == PAYER_LEFT_DOWN)
			{
				_player._playermove = PAYER_LEFT_DOWN_ROLL;
			}

			if (_player._playermove == PAYER_RIGHT_DOWN)
			{
				_player._playermove = PAYER_RIGHT_DOWN_ROOL;
			}

			if (_player._playermove == PAYER_LEFT_UP)
			{
				_player._playermove = PAYER_LEFT_UP_ROLL;
			}

			if (_player._playermove == PAYER_RIGHT_UP)
			{
				_player._playermove = PAYER_RIGHT_UP_ROLL;
			}
		}
	}


	if (_player._attackplayer == PLAYER_SWORD)
	{
		if (KEYMANAGER->isOnceKeyDown('K'))
		{
			_player._isattackmove = true;
			_ishwing = true;
		}
		if (KEYMANAGER->isOnceKeyUp('K'))
		{
			_ishwing = false;
		}
	}
	else
	{
		if (KEYMANAGER->isStayKeyDown('K'))
		{
			_player._isattackmove = true;
		}

		if (KEYMANAGER->isOnceKeyUp('K'))
		{
			_player._isFire = true;

			if (_player._attacmove == PLAYER_ATK_LEFT) arrowFIre(ARROW_LEFT);
			if (_player._attacmove == PLAYER_ATK_RIGHT) arrowFIre(ARROW_RIGHT);
			if (_player._attacmove == PLAYER_ATK_UP) arrowFIre(ARROW_UP);
			if (_player._attacmove == PLAYER_ATK_DOWN) arrowFIre(ARROW_DOWN);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		if (_player._playerLocation == DUNGEON_PLAYER_VERSION)
		{
			if (_player._attackplayer == PLAYER_SWORD) _player._attackplayer = PLAYER_ARROW;
			else _player._attackplayer = PLAYER_SWORD;
		}
	}


	if (KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D') || KEYMANAGER->isOnceKeyUp('W')
		|| KEYMANAGER->isOnceKeyUp('S'))
	{
		if (_player._playermove == PLAYER_LEFT) _player._playermove = PLAYER_LEFT_IDLE;
		if (_player._playermove == PLAYER_RIGHT) _player._playermove = PLAYER_RIGHT_IDLE;
		if (_player._playermove == PLAYER_DOWN) _player._playermove = PLAYER_DOWN_IDLE;
		if (_player._playermove == PAYER_LEFT_DOWN) _player._playermove = PLAYER_DOWN_IDLE;
		if (_player._playermove == PAYER_RIGHT_DOWN) _player._playermove = PLAYER_DOWN_IDLE;
		if (_player._playermove == PLAYER_UP) _player._playermove = PLAYER_UP_IDLE;
		if (_player._playermove == PAYER_LEFT_UP) _player._playermove = PLAYER_UP_IDLE;
		if (_player._playermove == PAYER_RIGHT_UP) _player._playermove = PLAYER_UP_IDLE;
	}

	if (_isanimation)
	{
		if (_player._playermove == PLAYER_UP_ROLL)
		{
			_player.y -= 2;
		}

		if (_player._playermove == PLAYER_BACK_ROLL)
		{
			_player.y += 2;
		}

		if (_player._playermove == PLAYER_LEFT_ROLL)
		{
			_player.x -= 2;
		}

		if (_player._playermove == PLAYER_RIGHT_ROLL)
		{
			_player.x += 2;
		}

		if (_player._playermove == PAYER_LEFT_DOWN_ROLL)
		{
			_player.x -= 2;
			_player.y += 2;
		}

		if (_player._playermove == PAYER_RIGHT_DOWN_ROOL)
		{
			_player.x += 2;
			_player.y += 2;
		}

		if (_player._playermove == PAYER_LEFT_UP_ROLL)
		{
			_player.x -= 2;
			_player.y -= 2;
		}

		if (_player._playermove == PAYER_RIGHT_UP_ROLL)
		{
			_player.x += 2;
			_player.y -= 2;
		}
	}

	if (_player._isattackmove)
	{
		if (_player._playerLocation == DUNGEON_PLAYER_VERSION)
		{
			if (_player._playermove == PLAYER_UP || _player._playermove == PLAYER_UP_IDLE) _player._attacmove = PLAYER_ATK_UP;

			if (_player._playermove == PLAYER_DOWN || _player._playermove == PLAYER_DOWN_IDLE) _player._attacmove = PLAYER_ATK_DOWN;

			if (_player._playermove == PLAYER_LEFT || _player._playermove == PLAYER_LEFT_IDLE) _player._attacmove = PLAYER_ATK_LEFT;

			if (_player._playermove == PLAYER_RIGHT || _player._playermove == PLAYER_RIGHT_IDLE) _player._attacmove = PLAYER_ATK_RIGHT;
		}
	}
	else
	{
		_player._attacmove = PLAYER_ATK_STOP;
	}

	_player._playerrect = RectMakeCenter(_player.x, _player.y, _player._playerimg->getFrameWidth(), _player._playerimg->getFrameHeight());
	_player._collisionplayer = RectMakeCenter(_player.x, _player.y, 50, 70);
}

void player::playerAtt()
{
	if (_player._isattackmove)
	{
		if (_player._attackplayer == PLAYER_ARROW)
		{
			_player._playerimg = IMAGEMANAGER->findImage("화살을 들고 있는 던전캐릭터");
		}
		else if (_player._attackplayer == PLAYER_SWORD)
		{
			_player._playerimg = IMAGEMANAGER->findImage("검을 들고 있는 던전캐릭터");
		}
	}
	else
	{
		_player._playerimg = IMAGEMANAGER->findImage("던전캐릭터");
	}
}

//플레이어 이동 모션
void player::playermoveversion() //플레이어 버전 함수
{
	switch (_player._playermove)
	{
	case PLAYER_DOWN_IDLE:
		_player._playercount++;
		if (_player._playerLocation == SHOP_PLAYER_VERSION)
			_player._playerimg->setFrameY(5);
		if (_player._playerLocation == DUNGEON_PLAYER_VERSION)
			_player._playerimg->setFrameY(11);

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
	case PLAYER_DOWN: case PAYER_LEFT_DOWN: case PAYER_RIGHT_DOWN:
		_player._playercount++;
		if (_player._playerLocation == SHOP_PLAYER_VERSION)
			_player._playerimg->setFrameY(4);
		if (_player._playerLocation == DUNGEON_PLAYER_VERSION)
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
		if (_player._playerLocation == SHOP_PLAYER_VERSION)
			_player._playerimg->setFrameY(7);
		if (_player._playerLocation == DUNGEON_PLAYER_VERSION)
			_player._playerimg->setFrameY(10);

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
	case PLAYER_UP: case PAYER_LEFT_UP:  case PAYER_RIGHT_UP:
		_player._playercount++;
		if (_player._playerLocation == SHOP_PLAYER_VERSION)
			_player._playerimg->setFrameY(6);
		if (_player._playerLocation == DUNGEON_PLAYER_VERSION)
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
		if (_player._playerLocation == SHOP_PLAYER_VERSION)
			_player._playerimg->setFrameY(3);
		if (_player._playerLocation == DUNGEON_PLAYER_VERSION)
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
		if (_player._playerLocation == SHOP_PLAYER_VERSION)
			_player._playerimg->setFrameY(2);
		if (_player._playerLocation == DUNGEON_PLAYER_VERSION)
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
		if (_player._playerLocation == SHOP_PLAYER_VERSION)
			_player._playerimg->setFrameY(1);
		if (_player._playerLocation == DUNGEON_PLAYER_VERSION)
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
		if (_player._playerLocation == SHOP_PLAYER_VERSION)
			_player._playerimg->setFrameY(0);
		if (_player._playerLocation == DUNGEON_PLAYER_VERSION)
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
	case PLAYER_RIGHT_ROLL:
		_player._playercount++;
		if (_player._playerLocation == SHOP_PLAYER_VERSION)
			_player._playerimg->setFrameY(9);
		if (_player._playerLocation == DUNGEON_PLAYER_VERSION)
			_player._playerimg->setFrameY(4);

		if (_player._playercount % 7 == 0)
		{
			_player._playercount = 0;
			_player._playerindex++;
			if (_player._playerindex >= _player._playerimg->getMaxFrameX() - 2)
			{
				_player._playerindex = 0;
				_isanimation = false;
				_player._playermove = PLAYER_RIGHT_IDLE;
			}
			_player._playerimg->setFrameX(_player._playerindex);
		}
		break;
	case PLAYER_LEFT_ROLL:
		_player._playercount++;
		if (_player._playerLocation == SHOP_PLAYER_VERSION)
			_player._playerimg->setFrameY(8);
		if (_player._playerLocation == DUNGEON_PLAYER_VERSION)
			_player._playerimg->setFrameY(5);

		if (_player._playercount % 7 == 0)
		{
			_player._playercount = 0;
			_player._playerindex++;
			if (_player._playerindex >= _player._playerimg->getMaxFrameX() - 2)
			{
				_player._playerindex = 0;
				_isanimation = false;
				_player._playermove = PLAYER_LEFT_IDLE;
			}
			_player._playerimg->setFrameX(_player._playerindex);
		}
		break;
	case PLAYER_UP_ROLL: case PAYER_LEFT_UP_ROLL: case PAYER_RIGHT_UP_ROLL:
		_player._playercount++;
		if (_player._playerLocation == SHOP_PLAYER_VERSION)
			_player._playerimg->setFrameY(12);
		if (_player._playerLocation == DUNGEON_PLAYER_VERSION)
			_player._playerimg->setFrameY(6);

		if (_player._playercount % 7 == 0)
		{
			_player._playercount = 0;
			_player._playerindex++;
			if (_player._playerindex >= _player._playerimg->getMaxFrameX() - 2)
			{
				_player._playerindex = 0;
				_isanimation = false;
				_player._playermove = PLAYER_UP_IDLE;
			}
			_player._playerimg->setFrameX(_player._playerindex);
		}
		break;
	case PLAYER_BACK_ROLL: case PAYER_LEFT_DOWN_ROLL: case PAYER_RIGHT_DOWN_ROOL:
		_player._playercount++;
		if (_player._playerLocation == SHOP_PLAYER_VERSION)
			_player._playerimg->setFrameY(10);
		if (_player._playerLocation == DUNGEON_PLAYER_VERSION)
			_player._playerimg->setFrameY(7);

		if (_player._playercount % 7 == 0)
		{
			_player._playercount = 0;
			_player._playerindex++;
			if (_player._playerindex >= _player._playerimg->getMaxFrameX() - 2)
			{
				_player._playerindex = 0;
				_isanimation = false;
				_player._playermove = PLAYER_DOWN_IDLE;
			}
			_player._playerimg->setFrameX(_player._playerindex);
		}
		break;
	case PLAYER_DIE:
		_player._playercount++;
		if (_player._playerLocation == DUNGEON_PLAYER_VERSION)
			_player._playerimg->setFrameY(12);
		if (_player._playercount % 7 == 0)
		{
			_player._playercount = 0;
			_player._playerindex++;
			if (_player._playerindex >= _player._playerimg->getMaxFrameX())
			{
				_player._playerindex = 11;
				_isanimation = false;
			}
			_player._playerimg->setFrameX(_player._playerindex);
		}
	}

}

//플레이어 공격 모션
void player::attackmove()
{
	switch (_player._attacmove)
	{
	case PLAYER_ATK_LEFT:
		_player._playerimg->setFrameY(3);
		_player._playercount++;
		if (_player._playercount % 10 == 0)
		{
			_player._playercount = 0;
			_player._playerindex++;
			if (_player._attackplayer == PLAYER_SWORD)
			{
				if (_ishwing)
				{
					_swordrect[0] = RectMakeCenter(_player._playerrect.left, _player._playerrect.top + (_player._playerrect.bottom - _player._playerrect.top) / 2, 32, 10);
				}
				if (_player._playerindex >= _player._playerimg->getMaxFrameX())
				{

					_player._playerindex = 0;
					_player._isattackmove = false;

				}
			}
			else
			{
				if (!_player._isFire)
				{
					if (_player._playerindex >= 2)
					{
						_player._playerindex = 2;
					}
				}
				else
				{
					if (_player._playerindex >= _player._playerimg->getMaxFrameX())
					{
						_player._playerindex = 0;
						_player._isattackmove = false;
						_player._isFire = false;

					}
				}
			}
			_player._playerimg->setFrameX(_player._playerindex);
			_ishwing = false;
		}
		break;
	case PLAYER_ATK_RIGHT:
		_player._playercount++;
		_player._playerimg->setFrameY(2);
		if (_player._playercount % 10 == 0)
		{
			_player._playerindex++;
			_player._playercount = 0;
			if (_player._attackplayer == PLAYER_SWORD)
			{
				if (_ishwing)
				{
					_swordrect[1] = RectMakeCenter(_player._playerrect.right, _player._playerrect.top + (_player._playerrect.bottom - _player._playerrect.top) / 2, 42, 10);

				}
				if (_player._playerindex >= _player._playerimg->getMaxFrameX())
				{
					_player._playerindex = 0;
					_player._isattackmove = false;

				}
			}
			else
			{
				if (!_player._isFire)
				{
					if (_player._playerindex >= 2)
					{
						_player._playerindex = 2;
					}
				}
				else
				{
					if (_player._playerindex >= _player._playerimg->getMaxFrameX())
					{
						_player._playerindex = 0;
						_player._isattackmove = false;
						_player._isFire = false;
					}
				}
			}
			_player._playerimg->setFrameX(_player._playerindex);
		}
		break;
	case PLAYER_ATK_UP:
		_player._playercount++;
		_player._playerimg->setFrameY(0);
		if (_player._playercount % 10 == 0)
		{
			_player._playercount = 0;
			_player._playerindex++;
			if (_player._attackplayer == PLAYER_SWORD)
			{
				if (_ishwing)
				{
					_swordrect[2] = RectMakeCenter(_player._playerrect.left + (_player._playerrect.right - _player._playerrect.left) / 2, _player._playerrect.top, 10, 42);
				}
				if (_player._playerindex >= _player._playerimg->getMaxFrameX())
				{
					_player._playerindex = 0;
					_player._isattackmove = false;

				}
			}
			else
			{
				if (!_player._isFire)
				{
					if (_player._playerindex >= 2)
					{
						_player._playerindex = 2;
					}
				}
				else
				{
					if (_player._playerindex >= _player._playerimg->getMaxFrameX())
					{
						_player._playerindex = 0;
						_player._isattackmove = false;
						_player._isFire = false;
					}
				}
			}
			_player._playerimg->setFrameX(_player._playerindex);
		}
		break;
	case PLAYER_ATK_DOWN:
		_player._playercount++;
		_player._playerimg->setFrameY(1);
		if (_player._playercount % 10 == 0)
		{
			_player._playercount = 0;
			_player._playerindex++;
			if (_player._attackplayer == PLAYER_SWORD)
			{
				if (_ishwing)
				{
					_swordrect[3] = RectMakeCenter(_player._playerrect.left + (_player._playerrect.right - _player._playerrect.left) / 2, _player._playerrect.bottom, 10, 42);
				}
				if (_player._playerindex >= _player._playerimg->getMaxFrameX())
				{
					_player._playerindex = 0;
					_player._isattackmove = false;
				}
			}
			else
			{
				if (!_player._isFire)
				{
					if (_player._playerindex >= 2)
					{
						_player._playerindex = 2;
					}
				}
				else
				{
					if (_player._playerindex >= _player._playerimg->getMaxFrameX())
					{
						_player._playerindex = 0;
						_player._isattackmove = false;
						_player._isFire = false;
					}
				}
			}
			_player._playerimg->setFrameX(_player._playerindex);
		}
		break;
	}
}

void player::arrowFIre(WEAPONMOVE weponMove)
{
	_arrowfirst->fire(_player.x, _player.y, weponMove);
}

void player::monsterbattle()				//몬스터랑 배틀 몬스터랑 싸운는 함수 
{
	RECT temp;
	//if(IntersectRect(&temp, &_player._collisionplayer, &_몬스터,..))

	_playerhp._hpbar->setX(165);			//위치
	_playerhp._hpbar->setY(35);			//위치
	_playerhp._hpbar->setGauge(_playerhp._HP, _playerhp._maxhp);
	_playerhp._hpbar->update();

	if (_playerhp._HP <= 0)
	{

		if (_player._playerLocation == DUNGEON_PLAYER_VERSION)
			_player._playermove = PLAYER_DIE;
	}
}

void player::playerhitDameage(int _damage)
{
	_playerhp._HP -= _damage;

}

void player::buyplayermoney(int _money)
{
	_player._pmoney -= _money;
}

void player::sellplayermoney(int _money)
{
	_player._pmoney += _money;
}


void player::render(HDC hdc)
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(hdc, _player._playerrect.left, _player._playerrect.top, _player._playerrect.right, _player._playerrect.bottom);
		Rectangle(hdc, _player._collisionplayer.left, _player._collisionplayer.top, _player._collisionplayer.right, _player._collisionplayer.bottom);
	}

	_player._playerimg->frameRender(hdc, _player._playerrect.left, _player._playerrect.top);
	_arrowfirst->render();
	_playerhp._hpbar->render();
	_inventory->render(hdc);

	for (int i = 0; i < 4; i++)
	{
		//Rectangle(hdc, _swordrect[i].left, _swordrect[i].top, _swordrect[i].right, _swordrect[i].bottom);		//위치 조정 필요
	}
}