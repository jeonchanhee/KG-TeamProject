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

	_player._playerimg = IMAGEMANAGER->findImage("��ĳ����");
	_player.x = WINSIZEX / 2;  //_player._playerrect�� �ֱ�  ���� int x ��
	_player.y = WINSIZEY / 2;  //_player._playerrect�� �ֱ� ���� int y ��

	//��Ʈ��
	_player._playerrect = RectMakeCenter(_player.x, _player.y, _player._playerimg->getFrameWidth(), _player._playerimg->getHeight());  // �̹��� ��Ʈ... 
	_player._collisionplayer = RectMakeCenter((_player._playerrect.left + _player._playerrect.right) / 2, (_player._playerrect.top + _player._playerrect.bottom) / 2, 50, 70); //  �浹�� �� �ʿ���  ��Ʈ ->���� ���� �̹��� ũ�� ������ _playerrect �ʹ� Ŀ�� �ȿ� �׳� ����� �� �� ��

	_isanimation = false;  //������ ���¿� ������ ���� ���¸� �Ǻ��ϴ� bool


	_player._playerLocation = SHOP_PLAYER_VERSION;				//shop_player
	_player._playermove = PLAYER_DOWN_IDLE;						//�ڼ� �ʱ�ȭ
	_player._attackplayer = PLAYER_SWORD;
	//_player._attackplayer = PLAYER_ARROW;
	_player._playercount = 0;
	_player._playerindex = 0;


	_player.HP = 100;

	_player._isattackmove = false;						//  false�϶��� �Ϲ� ���� ������� 
	_player._ischageweapon = false;					// ���� ü���� 

	return S_OK;
}

void player::release() {}

void player::update()
{

	playermoveversion(); //���� �Լ� �÷��̰� shop���� dugeon���� ��Ÿ���� �Լ�..?
	shopPlayermove();
	dungeonPlayermove();
	attackmove();

	if (KEYMANAGER->isOnceKeyDown('1'))  //��������� �߰��Ѱ� 1�� ��ĳ����
	{
		_player._playerimg = IMAGEMANAGER->findImage("��ĳ����");
		_player._playerLocation = SHOP_PLAYER_VERSION;
	}
	if (KEYMANAGER->isOnceKeyDown('2')) //��������� �߰��Ѱ� 2�� ����ĳ���� ���
	{
		_player._playerimg = IMAGEMANAGER->findImage("����ĳ����");
		_player._playerLocation = DUNGEON_PLAYER_VERSION;
	}

	if (_player._isattackmove)
	{
		if (_player._playerLocation == DUNGEON_PLAYER_VERSION)
		{
			_player._isattackmove = false;
			_player._ischageweapon = false;

			if (!_player._ischageweapon)
			{
				if (_player._attackplayer == PLAYER_SWORD)
				{
					_player._playerimg = IMAGEMANAGER->findImage("���� ��� �ִ� ����ĳ����");
				}
			}
			if (_player._ischageweapon)
			{
				if (_player._attackplayer == PLAYER_ARROW)
				{
					_player._playerimg = IMAGEMANAGER->findImage("ȭ���� ��� �ִ� ����ĳ����");
				}
			}
		}
	}

	_player._collisionplayer = RectMakeCenter((_player._playerrect.left + _player._playerrect.right) / 2, (_player._playerrect.top + _player._playerrect.bottom) / 2, 50, 70);
}

//===========================================================
//														���� ĳ����
//===========================================================


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
	if (TIMEMANAGER->getWorldTime() - time >= 1.5)
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
	if (KEYMANAGER->isOnceKeyDown('K'))
	{
		_player._isattackmove = false;									//��������  K�� �����ٰ� 2��Ű�� ������ �ٷ� ���ݸ���� ���� �߰��� ��
	}

	_player._playerrect = RectMakeCenter(_player.x, _player.y, _player._playerimg->getFrameWidth(), _player._playerimg->getFrameHeight());   // ĳ���� rect��
}


//===========================================================
//														���� ĳ����
//===========================================================

void player::dungeonPlayermove()
{
	if (!_isanimation)
	{
		if (!_player._isattackmove)
		{
			if (KEYMANAGER->isStayKeyDown('S'))			//�Ʒ�
			{
				_player._playermove = PLAYER_DOWN;
				_player.y += 2.0f;
				OffsetRect(&_player._collisionplayer, 0, 2);
			}
			if (KEYMANAGER->isOnceKeyUp('S'))
			{
				_player._playermove = PLAYER_DOWN_IDLE;
			}
			if (KEYMANAGER->isStayKeyDown('A'))		//����
			{
				_player._playermove = PLAYER_LEFT;
				_player.x -= 2.0f;
				OffsetRect(&_player._collisionplayer, -2, 0);
			}
			if (KEYMANAGER->isOnceKeyUp('A'))
			{
				_player._playermove = PLAYER_LEFT_IDLE;
			}
			if (KEYMANAGER->isStayKeyDown('D'))		//������
			{
				_player._playermove = PLAYER_RIGHT;
				OffsetRect(&_player._collisionplayer, 2, 0);
				_player.x += 2.0f;
			}
			if (KEYMANAGER->isOnceKeyUp('D'))
			{
				_player._playermove = PLAYER_RIGHT_IDLE;

			}
			if (KEYMANAGER->isStayKeyDown('W'))		//��
			{
				_player._playermove = PLAYER_UP;
				_player.y -= 2.0f;
			}
			if (KEYMANAGER->isOnceKeyUp('W'))
			{
				_player._playermove = PLAYER_UP_IDLE;
			}
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
		if (_player._playermove == PLAYER_UP || _player._playermove == PLAYER_UP_IDLE)					// UP
		{
			_player._playermove = PLAYER_UP_ROLL;
		}
		if (_player._playermove == PLAYER_DOWN || _player._playermove == PLAYER_DOWN_IDLE)		//DOWN
		{
			_player._playermove = PLAYER_BACK_ROLL;
		}
	}
	if (TIMEMANAGER->getWorldTime() - time > 1.5)
	{
		_isanimation = false;
		if (_player._playermove == PLAYER_BACK_ROLL)		  //��
		{
			_player._playermove = PLAYER_DOWN_IDLE;
		}
		if (_player._playermove == PLAYER_UP_ROLL)			//��
		{
			_player._playermove = PLAYER_UP_IDLE;
		}
		if (_player._playermove == PLAYER_RIGHT_ROLL)			//������
		{
			_player._playermove = PLAYER_RIGHT_IDLE;
		}
		if (_player._playermove == PLAYER_LEFT_ROLL)			//����
		{
			_player._playermove = PLAYER_LEFT_IDLE;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))  //���� ü���� Ű
	{
		if (!_player._ischageweapon)
		{
			_player._ischageweapon = true;
			_player._playerimg = IMAGEMANAGER->findImage("ȭ���� ��� �ִ� ����ĳ����");
		}
		else
		{
			_player._ischageweapon = false;
			_player._attacmove = PLAYER_ATK_STOP;
			_player._playermove = PLAYER_UP_IDLE;
			_player._playerimg = IMAGEMANAGER->findImage("���� ��� �ִ� ����ĳ����");
		}
	}

	if (KEYMANAGER->isOnceKeyDown('K'))      // K�� ������ ���� ���� ����
	{
		attacktime = TIMEMANAGER->getWorldTime();
		_player._isattackmove = true;
		if (!_player._ischageweapon)
		{
			if (_player._attackplayer == PLAYER_SWORD)   //���̳� 
			{
				if (_player._playermove == PLAYER_LEFT || _player._playermove == PLAYER_LEFT_IDLE)
				{
					_player._attacmove = PLAYER_ATK_LEFT;
				}
				if (_player._playermove == PLAYER_RIGHT || _player._playermove == PLAYER_RIGHT_IDLE)
				{
					_player._attacmove = PLAYER_ATK_RIGHT;
				}
				if (_player._playermove == PLAYER_UP || _player._playermove == PLAYER_UP_IDLE)
				{
					_player._attacmove = PLAYER_ATK_UP;
				}
				if (_player._playermove == PLAYER_DOWN || _player._playermove == PLAYER_DOWN_IDLE)
				{
					_player._attacmove = PLAYER_ATK_DOWN;
				}
			}
		}
		if (_player._ischageweapon)
		{
			if (_player._attackplayer == PLAYER_ARROW) //ȭ���̳�
			{
				if (_player._playermove == PLAYER_LEFT || _player._playermove == PLAYER_LEFT_IDLE)
				{
					_player._attacmove = PLAYER_ATK_LEFT;
				}
				if (_player._playermove == PLAYER_RIGHT || _player._playermove == PLAYER_RIGHT_IDLE)
				{
					_player._attacmove = PLAYER_ATK_RIGHT;
				}
				if (_player._playermove == PLAYER_DOWN || _player._playermove == PLAYER_DOWN_IDLE)
				{
					_player._attacmove = PLAYER_ATK_DOWN;
				}
				if (_player._playermove == PLAYER_UP || _player._playermove == PLAYER_UP_IDLE)
				{
					_player._attacmove = PLAYER_ATK_UP;
				}
			}
		}
	}
	if (TIMEMANAGER->getWorldTime() - attacktime >= 1.0f)
	{
		_player._isattackmove = false;
		if (!_player._ischageweapon)
		{
			if (_player._attackplayer == PLAYER_SWORD)   //���̳� 
			{
				if (_player._attacmove == PLAYER_ATK_LEFT)
				{
					_player._playermove = PLAYER_LEFT_IDLE;
					_player._attacmove = PLAYER_ATK_STOP;
					_player._playerimg = IMAGEMANAGER->findImage("����ĳ����");
				}
				if (_player._attacmove == PLAYER_ATK_RIGHT)
				{
					_player._playermove = PLAYER_RIGHT_IDLE;
					_player._attacmove = PLAYER_ATK_STOP;
					_player._playerimg = IMAGEMANAGER->findImage("����ĳ����");
				}
				if (_player._attacmove == PLAYER_ATK_DOWN)
				{
					_player._playermove = PLAYER_DOWN_IDLE;
					_player._attacmove = PLAYER_ATK_STOP;
					_player._playerimg = IMAGEMANAGER->findImage("����ĳ����");
				}
				if (_player._attacmove == PLAYER_ATK_UP)
				{
					_player._playermove = PLAYER_UP_IDLE;
					_player._attacmove = PLAYER_ATK_STOP;
					_player._playerimg = IMAGEMANAGER->findImage("����ĳ����");
				}
			}
		}
		if (_player._ischageweapon)
		{
			if (_player._attackplayer == PLAYER_ARROW)
			{
				if (_player._attacmove == PLAYER_ATK_LEFT)
				{
					_player._playermove = PLAYER_LEFT_IDLE;
					_player._attacmove = PLAYER_ATK_STOP;
					_player._playerimg = IMAGEMANAGER->findImage("����ĳ����");
				}
				if (_player._attacmove == PLAYER_ATK_RIGHT)
				{
					_player._playermove = PLAYER_RIGHT_IDLE;
					_player._attacmove = PLAYER_ATK_STOP;
					_player._playerimg = IMAGEMANAGER->findImage("����ĳ����");
				}
				if (_player._attacmove == PLAYER_ATK_UP)
				{
					_player._playermove = PLAYER_UP_IDLE;
					_player._attacmove = PLAYER_ATK_STOP;
					_player._playerimg = IMAGEMANAGER->findImage("����ĳ����");
				}
				if (_player._attacmove == PLAYER_ATK_DOWN)
				{
					_player._playermove = PLAYER_DOWN_IDLE;
					_player._attacmove = PLAYER_ATK_STOP;
					_player._playerimg = IMAGEMANAGER->findImage("����ĳ����");
				}
			}
		}
	}

	/*
	�� -> false
	ȭ�� -> arrow
	*/

}

void player::playermoveversion() //�÷��̾� ���� �Լ�
{
	switch (_player._playerLocation)
	{
	case SHOP_PLAYER_VERSION: //shop player ���� 
		switch (_player._playermove)
		{
		case PLAYER_DOWN_IDLE:  //�Ʒ� ����
			_player._playercount++;
			_player._playerimg->setFrameY(5);
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

		case PLAYER_DOWN: // �Ʒ���
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

		case PLAYER_UP_IDLE: //�� ����
			_player._playercount++;
			_player._playerimg->setFrameY(7);
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

		case PLAYER_UP:					//���� �� 
			_player._playercount++;
			_player._playerimg->setFrameY(6);
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

		case PLAYER_LEFT_IDLE:					//���� ����
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

		case PLAYER_LEFT:					// ���� ��
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

		case PLAYER_RIGHT_IDLE:			//������ ����
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

		case PLAYER_RIGHT: //������ �� 
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

		case PLAYER_RIGHT_ROLL:  // shop �����ʱ�����
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

		case PLAYER_LEFT_ROLL:  // shop ���� ������
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

		case PLAYER_UP_ROLL:  // shop ������ ������
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

		case PLAYER_BACK_ROLL: // shop �ڷ� ������
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
			_player.y += 2;
			break;
		}
		break;
	case DUNGEON_PLAYER_VERSION:    //dungeon player ����
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
				if (_player._playerindex >= _player._playerimg->getMaxFrameX() - 3)
				{
					_player._playerindex = 0;
				}
				_player._playerimg->setFrameX(_player._playerindex);
			}
			break;
		case PLAYER_UP_IDLE:
			_player._playercount++;
			_player._playerimg->setFrameY(10);
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
			if (_player._playercount % 9 == 0)
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
		}
		break;
	}
}


void player::attackmove()
{
	switch (_player._attackplayer)
	{
	case PLAYER_SWORD:							//�� 
		switch (_player._attacmove)
		{
		case PLAYER_ATK_LEFT:
			_player._playerimg->setFrameY(3);
			_player._playercount++;
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
		case PLAYER_ATK_RIGHT:
			_player._playerimg->setFrameY(2);
			_player._playercount++;
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
		case PLAYER_ATK_UP:
			_player._playerimg->setFrameY(0);
			_player._playercount++;
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
		case PLAYER_ATK_DOWN:
			_player._playercount++;
			_player._playerimg->setFrameY(1);
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
	case PLAYER_ARROW:						//  ȭ��
		switch (_player._attacmove)
		{
		case PLAYER_ATK_LEFT:
			_player._playercount++;
			_player._playerimg->setFrameY(3);
			if (_player._playercount % 15 == 0)
			{
				_player._playerindex++;
				_player._playercount = 0;
				if (_player._playerindex >= _player._playerimg->getMaxFrameX())
				{
					_player._playerindex = 0;
				}
				_player._playerimg->setFrameX(_player._playerindex);
			}
			break;
		case PLAYER_ATK_RIGHT:
			_player._playercount++;
			_player._playerimg->setFrameY(2);
			if (_player._playercount % 15 == 0)
			{
				_player._playerindex++;
				_player._playercount = 0;
				if (_player._playerindex >= _player._playerimg->getMaxFrameX())
				{
					_player._playerindex = 0;
				}
				_player._playerimg->setFrameX(_player._playerindex);
			}
			break;
		case PLAYER_ATK_UP:
			_player._playercount++;
			_player._playerimg->setFrameY(0);
			if (_player._playercount % 17 == 0)
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
		case PLAYER_ATK_DOWN:				
			_player._playercount++;
			_player._playerimg->setFrameY(1);
			if (_player._playercount % 17 == 0)
			{
				_player._playerindex++;
				_player._playercount = 0;
				if (_player._playerindex >= _player._playerimg->getMaxFrameX())
				{
					_player._playerindex = 0;
				}
				_player._playerimg->setFrameX(_player._playerindex);
			}
			break;
		}
		break;
	case PLAYER_SPEAR:		// â 
		break;
	}

}



void player::render(HDC hdc)
{


	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(hdc, _player._playerrect.left, _player._playerrect.top, _player._playerrect.right, _player._playerrect.bottom);
		Rectangle(hdc, _player._collisionplayer.left, _player._collisionplayer.top, _player._collisionplayer.right, _player._collisionplayer.bottom);
	}

	_player._playerimg->frameRender(hdc, _player._playerrect.left, _player._playerrect.top);

}