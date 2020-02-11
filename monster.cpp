#include "stdafx.h"
#include "monster.h"

monster::monster()
{
}

monster::~monster()
{
}

HRESULT monster::init()
{
	return S_OK;
}

HRESULT monster::init(
	const char* imageName,
	MONSTER_TYPE monType,
	MONSTER_STATE monState,
	MONSTER_DIRECTION monDirect,
	int x,
	int y,
	int atk,
	int hp,
	int currentHp,
	float range,
	int speed
)
{
	//�ش� ������ ���� �� �ֱ�
	_monsterImg = IMAGEMANAGER->findImage(imageName);
	_monType = monType;			//���� ����
	_monState = monState;		//���� ����
	_monDirect = monDirect;		//���� ����
	_x = x;
	_y = y;
	_currentX = x;
	_currentY = y;
	_atk = atk;
	_hp = hp;
	_range = range;
	_currentHp = currentHp;
	_speed = speed;
	hRc = RectMakeCenter(_x, _y, _monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
	//aRc = RectMakeCenter(_x, _y, _monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
	count = 0;					//ī��Ʈ

	_hpBar = new monsterProgressBar;
	_hpBar->init("images/monster/progressBarFront.bmp", "images/monster/progressBarBack.bmp", 0, 0, 50, 10);
	_hpBar->setGauge(_currentHp, _hp);
	_hpBar->setX(x - 25);
	_hpBar->setY(y - 70);

	switch (_monType)
	{
	case MONSTER_TYPE_GOLEMTURRET:
		golemTurretDirectImg();
		break;
	case MONSTER_TYPE_GOLEMSOLDIER:
		golemSoldierDirectImg();
		break;
	case MONSTER_TYPE_FLYINGGOLEM:
		break;
	case MONSTER_TYPE_SLIME:
		break;
	case MONSTER_TYPE_SLIMEGAUNTLET:
		slimeGauntletDirectImg();
		break;
	case MONSTER_TYPE_GOLEMBOSS:
		golemBossDirectImg();
		break;
	}
	return S_OK;
}

void monster::release()
{
}

void monster::update()
{

	//�÷��̾� ��ġ�� ���� ������ȯ
	if (PLAYER->getPlayerX() >= _currentX&&PLAYER->getPlayerY()>=_currentY)//4��и�
	{
		if (PLAYER->getPlayerX()-_currentX >= PLAYER->getPlayerY()-_currentY)
		{
			_monDirect = MONSTER_DIRECTION_RIGHT;
		}
		else
		{
			_monDirect = MONSTER_DIRECTION_DOWN;
		}
	}
	else if (PLAYER->getPlayerX() < _currentX&&PLAYER->getPlayerY() >= _currentY)//3��и�
	{
		if (-(PLAYER->getPlayerX() - _currentX) < PLAYER->getPlayerY() - _currentY)
		{
			_monDirect = MONSTER_DIRECTION_DOWN;
		}
		else
		{
			_monDirect = MONSTER_DIRECTION_LEFT;
		}
	}
	else if (PLAYER->getPlayerX() >= _currentX && PLAYER->getPlayerY() < _currentY)//1��и�
	{
		if (PLAYER->getPlayerX() - _currentX <= -(PLAYER->getPlayerY() - _currentY))
		{
			_monDirect = MONSTER_DIRECTION_UP;
		}
		else
		{
			_monDirect = MONSTER_DIRECTION_RIGHT;
		}
	}
	else if (PLAYER->getPlayerX() < _currentX&&PLAYER->getPlayerY() < _currentY)//2��и�
	{
		if (_currentX-PLAYER->getPlayerX() >= _currentY-PLAYER->getPlayerY())
		{
			_monDirect = MONSTER_DIRECTION_LEFT;
		}
		else
		{
			_monDirect = MONSTER_DIRECTION_UP;
		}
	}
	//���ð� ������ ���ÿ� �ȵǰ� �ϰ������ ��������
	if (!attack(_monType, _monDirect))
	{
		move(_monType, _monDirect);
	}
	else if (!move(_monType, _monDirect))
	{
		attack(_monType, _monDirect);
	}
	//hp�� ��ġ����
	_hpBar->setX(_currentX - 25);
	_hpBar->setY(_currentY - 70);
	//hp�� ���
	viewProgressBar();
	
	
	
}

void monster::render()
{
	draw();
}

//�������̹��� �׷���
void monster::draw()
{
	//���� ����
	_monsterImg->aniRender(getMemDC(), hRc.left, hRc.top, _ani);
	_hpBar->render();
	//���� �ǰݹ���
	//RectangleMakeCenter(getMemDC(), (hRc.left+ hRc.right)/2, (hRc.top+ hRc.bottom)/2, _monsterImg->getFrameWidth()/2, _monsterImg->getFrameHeight()/2);
	//���� ���ݹ���
	//RectangleMakeCenter(getMemDC(), (aRc.left + aRc.right) / 2, (aRc.top + aRc.bottom) / 2, aRc.right - aRc.left, aRc.bottom - aRc.top);
}

//����
bool monster::attack(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect)
{
	switch (monType) {
	case MONSTER_TYPE_GOLEMTURRET:
		golemTurretAtk(monType, monDirect);
		break;
	case MONSTER_TYPE_GOLEMSOLDIER:
		golemSoldierAtk(monType, monDirect);
		break;
	case MONSTER_TYPE_SLIMEGAUNTLET:
		slimeGauntletAtk(monType, monDirect);
		break;
	case MONSTER_TYPE_GOLEMBOSS:
		golemBossAtk(monType, monDirect);
		break;
	}

	//���ͷ��� ������ ���ʹ� ������ �÷��̾ ������ ī��Ʈ�� �ö󰣴�.
	return false;
}

bool monster::move(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect)
{
	switch (monType) {
	case MONSTER_TYPE_GOLEMSOLDIER:
		golemSoldierMove();
		break;
	case MONSTER_TYPE_GOLEMBOSS:
		golemBossMove();
		break;
	}
	return false;
}

void monster::golemTurretDirectImg()
{
	_monsterImg = IMAGEMANAGER->findImage("���ͷ�");
	//���Ⱚ���� �´� ���� �̹��� ã��
	switch (_monDirect)
	{
	case 0:
		_ani = ANIMATIONMANAGER->findAnimation("���ͷ�L");
		ANIMATIONMANAGER->start("���ͷ�L");

		break;
	case 1:
		_ani = ANIMATIONMANAGER->findAnimation("���ͷ�U");
		ANIMATIONMANAGER->start("���ͷ�U");
		break;
	case 2:
		_ani = ANIMATIONMANAGER->findAnimation("���ͷ�R");
		ANIMATIONMANAGER->start("���ͷ�R");
		break;
	case 3:
		_ani = ANIMATIONMANAGER->findAnimation("���ͷ�B");
		ANIMATIONMANAGER->start("���ͷ�B");
		break;
	}
}

void monster::golemSoldierDirectImg()
{
	_monsterImg = IMAGEMANAGER->findImage("�񷽼���");
	//���Ⱚ���� �´� ���� �̹��� ã��
	switch (_monDirect)
	{
	case 0:
		_ani = ANIMATIONMANAGER->findAnimation("�񷽼���L");
		ANIMATIONMANAGER->start("�񷽼���L");
		break;
	case 1:
		_ani = ANIMATIONMANAGER->findAnimation("�񷽼���U");
		ANIMATIONMANAGER->start("�񷽼���U");
		break;
	case 2:
		_ani = ANIMATIONMANAGER->findAnimation("�񷽼���R");
		ANIMATIONMANAGER->start("�񷽼���R");
		break;
	case 3:
		_ani = ANIMATIONMANAGER->findAnimation("�񷽼���B");
		ANIMATIONMANAGER->start("�񷽼���B");
		break;
	}
}

void monster::slimeGauntletDirectImg()
{
	_monsterImg = IMAGEMANAGER->findImage("�����Ӱ�Ʋ��");
	//���Ⱚ���� �´� ���� �̹��� ã��
	switch (_monDirect)
	{
	case 0:
		_ani = ANIMATIONMANAGER->findAnimation("�����Ӱ�Ʋ��L");
		ANIMATIONMANAGER->start("�����Ӱ�Ʋ��L");
		break;
	case 1:
		_ani = ANIMATIONMANAGER->findAnimation("�����Ӱ�Ʋ��U");
		ANIMATIONMANAGER->start("�����Ӱ�Ʋ��U");
		break;
	case 2:
		_ani = ANIMATIONMANAGER->findAnimation("�����Ӱ�Ʋ��R");
		ANIMATIONMANAGER->start("�����Ӱ�Ʋ��R");
		break;
	case 3:
		_ani = ANIMATIONMANAGER->findAnimation("�����Ӱ�Ʋ��B");
		ANIMATIONMANAGER->start("�����Ӱ�Ʋ��B");
		break;
	}
}

void monster::golemBossDirectImg()
{
	_monsterImg = IMAGEMANAGER->findImage("�񷽺���");
	//���Ⱚ���� �´� ���� �̹��� ã��
	switch (_monDirect)
	{
	case 0:
		_ani = ANIMATIONMANAGER->findAnimation("�񷽺���L");
		ANIMATIONMANAGER->start("�񷽺���L");
		break;
	case 1:
		_ani = ANIMATIONMANAGER->findAnimation("�񷽺���U");
		ANIMATIONMANAGER->start("�񷽺���U");
		break;
	case 2:
		_ani = ANIMATIONMANAGER->findAnimation("�񷽺���R");
		ANIMATIONMANAGER->start("�񷽺���R");
		break;
	case 3:
		_ani = ANIMATIONMANAGER->findAnimation("�񷽺���B");
		ANIMATIONMANAGER->start("�񷽺���B");
		break;
	}
}


//���ͷ�����
bool monster::golemTurretAtk(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect)
{
	//if (monType == 0) {
	count++;
	//ī��Ʈ�� 30�϶� ����
	if (count == 100)
	{
		_monsterImg = IMAGEMANAGER->findImage("���ͷ�");
		switch (monDirect) {
		case MONSTER_DIRECTION_LEFT:
			hRc = RectMakeH(hRc.left, hRc.bottom,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("���ͷ�L");
			ANIMATIONMANAGER->start("���ͷ�L");
			if (_monsterImg->getFrameX() == _monsterImg->getMaxFrameX())
			{
				_ani = ANIMATIONMANAGER->findAnimation("���ͷ�L");
				ANIMATIONMANAGER->start("���ͷ�L");
			}
			/*_x += cosf(getAngle(_monsterImg->getFrameX(), _monsterImg->getFrameY(),
				PLAYER->getPlayerX(), PLAYER->getPlayerY())*_speed);
			_y += -sinf(getAngle(_monsterImg->getFrameX(), _monsterImg->getFrameY(),
				PLAYER->getPlayerX(), PLAYER->getPlayerY())*_speed);*/
			break;
		case MONSTER_DIRECTION_UP:
			hRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight() - 50);
			_ani = ANIMATIONMANAGER->findAnimation("���ͷ�U");
			ANIMATIONMANAGER->start("���ͷ�U");
			break;
		case MONSTER_DIRECTION_RIGHT:
			hRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth() + 50, _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("���ͷ�R");
			ANIMATIONMANAGER->start("���ͷ�R");
			break;
		case MONSTER_DIRECTION_DOWN:
			hRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight() + 50);
			_ani = ANIMATIONMANAGER->findAnimation("���ͷ�B");
			ANIMATIONMANAGER->start("���ͷ�B");
			break;
		}
		//_rndFireCount = RND->getFromIntTo(1, 1000);
		count = 0;
		return true;
	}
	//}
	return false;
}

//�񷽼�������
bool monster::golemSoldierAtk(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect)
{
	//if (monType == 0) {
	count++;
	//ī��Ʈ�� 30�϶� ����
	if (count == 300&&MONSTER_STATE_ATK)
	{
		_monsterImg = IMAGEMANAGER->findImage("�񷽼�������");
		switch (monDirect) {
		case MONSTER_DIRECTION_LEFT:
			
			hRc = RectMakeH(hRc.left, hRc.bottom,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			aRc = RectMakeCenter((hRc.left + hRc.right) / 2 - 200, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("�񷽼�������L");
			ANIMATIONMANAGER->start("�񷽼�������L");
			/*_x += cosf(getAngle(_monsterImg->getFrameX(), _monsterImg->getFrameY(),
				PLAYER->getPlayerX(), PLAYER->getPlayerY())*_speed);
			_y += -sinf(getAngle(_monsterImg->getFrameX(), _monsterImg->getFrameY(),
				PLAYER->getPlayerX(), PLAYER->getPlayerY())*_speed);*/
			break;
		case MONSTER_DIRECTION_UP:
			hRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight() - 50);
			aRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2-200,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("�񷽼�������U");
			ANIMATIONMANAGER->start("�񷽼�������U");
			break;
		case MONSTER_DIRECTION_RIGHT:
			hRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth() + 50, _monsterImg->getFrameHeight());
			aRc = RectMakeCenter((hRc.left + hRc.right) / 2 + 200, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("�񷽼�������R");
			ANIMATIONMANAGER->start("�񷽼�������R");
			break;
		case MONSTER_DIRECTION_DOWN:
			hRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight() + 50);
			aRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2+200,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("�񷽼�������B");
			ANIMATIONMANAGER->start("�񷽼�������B");
			break;
		}
		//_rndFireCount = RND->getFromIntTo(1, 1000);
		count = 0;
		return true;
	}
	//}
	return false;
}

bool monster::slimeGauntletAtk(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect)
{
	//if (monType == 0) {
	count++;
	//ī��Ʈ�� 30�϶� ����
	if (count == 450)
	{
		_monsterImg = IMAGEMANAGER->findImage("�����Ӱ�Ʋ������");

		//_rndFireCount = RND->getFromIntTo(1, 1000);
		switch (monDirect) {
		case MONSTER_DIRECTION_LEFT:
			hRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			aRc = RectMakeCenter((hRc.left + hRc.right) / 2 - 200, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("�����Ӱ�Ʋ������L");
			ANIMATIONMANAGER->start("�����Ӱ�Ʋ������L");
			if (_monsterImg->getFrameX() == _monsterImg->getMaxFrameX())
			{
				_ani = ANIMATIONMANAGER->findAnimation("�����Ӱ�Ʋ��L");
				ANIMATIONMANAGER->start("�����Ӱ�Ʋ��L");
			}
			break;
		case MONSTER_DIRECTION_UP:
			hRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			aRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2-200,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("�����Ӱ�Ʋ������U");
			ANIMATIONMANAGER->start("�����Ӱ�Ʋ������U");
			break;
		case MONSTER_DIRECTION_RIGHT:
			hRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			aRc = RectMakeCenter((hRc.left + hRc.right) / 2-200, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("�����Ӱ�Ʋ������R");
			ANIMATIONMANAGER->start("�����Ӱ�Ʋ������R");
			break;
		case MONSTER_DIRECTION_DOWN:
			hRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight() + 50);
			aRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2 + 200,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("�����Ӱ�Ʋ������B");
			ANIMATIONMANAGER->start("�����Ӱ�Ʋ������B");
			break;
		}
		_ani->setFPS(12.0f);
		count = 0;
		return true;
	}
	//}
	return false;
}

bool monster::golemBossAtk(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect)
{
	count++;
	//ī��Ʈ�� 300�϶� ����
	if (count == 300)
	{
		//_rndFireCount = RND->getFromIntTo(1, 1000);
		switch (monDirect) {
		case MONSTER_DIRECTION_LEFT:
			_monsterImg = IMAGEMANAGER->findImage("�񷽺�������1");
			hRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			aRc = RectMakeCenter((hRc.left + hRc.right) / 2-500, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("�񷽺�������1L");
			ANIMATIONMANAGER->start("�񷽺�������1L");
			break;
		case MONSTER_DIRECTION_UP:
			_monsterImg = IMAGEMANAGER->findImage("�񷽺�������1");
			hRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			aRc = RectMakeCenter((hRc.left + hRc.right) / 2 - 500, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("�񷽺�������1U");
			ANIMATIONMANAGER->start("�񷽺�������1U");
			break;
		case MONSTER_DIRECTION_RIGHT:
			_monsterImg = IMAGEMANAGER->findImage("�񷽺�������1");
			hRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			aRc = RectMakeCenter((hRc.left + hRc.right) / 2 - 500, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("�񷽺�������1R");
			ANIMATIONMANAGER->start("�񷽺�������1R");
			break;
		case MONSTER_DIRECTION_DOWN:
			_monsterImg = IMAGEMANAGER->findImage("�񷽺�������1");
			hRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			aRc = RectMakeCenter((hRc.left + hRc.right) / 2 - 500, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("�񷽺�������1B");
			ANIMATIONMANAGER->start("�񷽺�������1B");
			break;
		}
		count = 0;
		return true;
	}

	return false;
}

void monster::golemSoldierMove()
{
	//if (monType == 0) {
	//count++;
	//���� ������ �ƴҶ� move
	//if (count == 300)
	//{
		_monState = MONSTER_STATE_MOVE;
		/*_x = cosf(getAngle(_x,
			_y,
			PLAYER->getPlayerX(),
			PLAYER->getPlayerY())) *2;
		_y = -sinf(getAngle(_x,
			_y,
			PLAYER->getPlayerX(),
			PLAYER->getPlayerY())) *2;*/
		if (_currentX < PLAYER->getPlayerX())_currentX += 1;
		if (_currentX > PLAYER->getPlayerX())_currentX -= 1;
		if (_currentY < PLAYER->getPlayerY())_currentY += 1;
		if (_currentY > PLAYER->getPlayerY())_currentY -= 1;
		hRc = RectMakeCenter(_currentX, _currentY, _monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
		_distance=getDistance(_currentX, _currentY, PLAYER->getPlayerX(), PLAYER->getPlayerY());
			if (_range >= _distance)count++;

			if (count > 30)
			{
				golemSoldierAtk(_monType, _monDirect);
			}
		//_rndFireCount = RND->getFromIntTo(1, 1000);
		//count = 0;
		//return true;
	//}
	//}
	//return false;
}

void monster::golemBossMove()
{
	if (_currentX < PLAYER->getPlayerX())_currentX += 1;
	if (_currentX > PLAYER->getPlayerX())_currentX -= 1;
	if (_currentY < PLAYER->getPlayerY())_currentY += 1;
	if (_currentY > PLAYER->getPlayerY())_currentY -= 1;
	hRc = RectMakeCenter(_currentX, _currentY, _monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
}

//ü�� �����ִ� �Լ�
void monster::viewProgressBar()
{
	_hpBar->setGauge(_currentHp, _hp);
	_hpBar->update();
}