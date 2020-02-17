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
	switch (_monType) {
	case 0:item = ITEMMANAGER->addItem("�̻���"); break;
	case 1:item = ITEMMANAGER->addItem("����"); break;
	case 2:item = ITEMMANAGER->addItem("�踷���"); break;
	case 3:item = ITEMMANAGER->addItem("��������"); break;
	case 4:item = ITEMMANAGER->addItem("õ"); break;
	case 5:item = ITEMMANAGER->addItem("����ȭ �� ������"); break;
	}
	//�̹��� ����
	iRc = RectMakeCenter(_x, _y, _monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
	//�ǰ� ����
	hRc = RectMakeCenter(_x, _y, _monsterImg->getFrameWidth() / 4, _monsterImg->getFrameHeight() / 4);
	//aRc = RectMakeCenter(_x, _y, _monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
	count = 0;					//ī��Ʈ

	_hpBar = new monsterProgressBar;
	_hpBar->init("ü�¹پ�", "ü�¹ٵ�", 0, 0, 50, 10);
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
		flyingGolemDirectImg();
		break;
	case MONSTER_TYPE_SLIME:
		slimeDirectImg();
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
	if (PLAYER->getPlayerX() >= _currentX && PLAYER->getPlayerY() >= _currentY)//4��и�
	{
		if (PLAYER->getPlayerX() - _currentX >= PLAYER->getPlayerY() - _currentY)
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
		if (_currentX - PLAYER->getPlayerX() >= _currentY - PLAYER->getPlayerY())
		{
			_monDirect = MONSTER_DIRECTION_LEFT;
		}
		else
		{
			_monDirect = MONSTER_DIRECTION_UP;
		}
	}
	atkCount--;
	if (_monState == MONSTER_STATE_MOVE)
	{
		move(_monType);
	}
	else if (atkCount <= 0) {
		attack(_monType, _monDirect);
		//atkCount = _atkCount;
	}

	//hp�� ��ġ����
	_hpBar->setX(_currentX - 25);
	_hpBar->setY(_currentY - 70);
	//hp�� ���
	viewProgressBar();

	item.update();
	hit(_monType, _monDirect);
	die(_monType);
}

void monster::render()
{

	draw();
}

//�������̹��� �׷���
void monster::draw()
{


	if (KEYMANAGER->isToggleKey('P'))
	{
		//���� ���ݹ���
		Rectangle(getMemDC(), aRc.left, aRc.top, aRc.right, aRc.bottom);
		//���� �̹��� ����
		//Rectangle(getMemDC(), iRc.left, iRc.top, iRc.right, iRc.bottom);
		//���� �ǰݹ���
		//Rectangle(getMemDC(), hRc.left, hRc.top, hRc.right, hRc.bottom);
		//item.getItemInfo().image->render(getMemDC(), item.getRECT().left, item.getRECT().top);
	}
	//���� ����
	_monsterImg->aniRender(getMemDC(), iRc.left, iRc.top, _ani);

	_hpBar->render();
	item.render();
	char str[128];
	sprintf_s(str, "%d", _currentHp);
	TextOut(getMemDC(), _x, _y, str, strlen(str));
	char str1[128];
	sprintf_s(str1, "%d", _monState);
	TextOut(getMemDC(), _x, _y + 50, str1, strlen(str1));

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
	case MONSTER_TYPE_FLYINGGOLEM:
		flyingGolemAtk(monType, monDirect);
		break;
	case MONSTER_TYPE_SLIMEGAUNTLET:
		slimeGauntletAtk(monType, monDirect);
		break;
	case MONSTER_TYPE_SLIME:
		slimeAtk(monType, monDirect);
		break;
	case MONSTER_TYPE_GOLEMBOSS:
		golemBossAtk(monType, monDirect);
		break;
	}


	//���ͷ��� ������ ���ʹ� ������ �÷��̾ ������ ī��Ʈ�� �ö󰣴�.
	return false;
}

bool monster::hit(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect)
{
	switch (monType) {
	case MONSTER_TYPE_GOLEMTURRET:
		golemTurretHit(monType, monDirect);
		break;
	case MONSTER_TYPE_GOLEMSOLDIER:
		golemSoldierHit(monType, monDirect);
		break;
	case MONSTER_TYPE_FLYINGGOLEM:
		flyginGolemHit(monType, monDirect);
		break;
	case MONSTER_TYPE_SLIMEGAUNTLET:
		slimeGauntletHit(monType, monDirect);
		break;
	case MONSTER_TYPE_SLIME:
		slimeHit(monType, monDirect);
		break;
	case MONSTER_TYPE_GOLEMBOSS:
		golemBossHit(monType, monDirect);
		break;
	}
	return false;
}

bool monster::move(MONSTER_TYPE monType)
{
	imgCount++;

	switch (_monType) {
	case MONSTER_TYPE_GOLEMSOLDIER:
		golemSoldierMove();
		if (imgCount > 20) {
			golemSoldierDirectImg();
			imgCount = 0;
		}
		break;
	case MONSTER_TYPE_FLYINGGOLEM:
		flyingGolemMove();
		if (imgCount > 20) {
			flyingGolemDirectImg();
			imgCount = 0;
		}
		break;
	case MONSTER_TYPE_GOLEMBOSS:
		golemBossMove();
		if (imgCount > 20) {
			golemBossDirectImg();
			imgCount = 0;
		}
		break;
	case MONSTER_TYPE_SLIME:
		slimeMove();
		if (imgCount > 10) {
			slimeDirectImg();
			imgCount = 0;
		}
		break;
	}

	return false;
}

bool monster::die(MONSTER_TYPE monType)
{
	if (_currentHp <= 0) {
		switch (monType) {
		case MONSTER_TYPE_GOLEMTURRET:
			golemTurretDie(monType);
			break;
		case MONSTER_TYPE_GOLEMSOLDIER:
			golemSoldierDie(monType);
			break;
		case MONSTER_TYPE_FLYINGGOLEM:
			flyingGolemDie(monType);
			break;
		case MONSTER_TYPE_SLIMEGAUNTLET:
			slimeGauntletDie(monType);
			break;
		case MONSTER_TYPE_SLIME:
			slimeDie(monType);
			break;
		case MONSTER_TYPE_GOLEMBOSS:
			golemBossDie(monType);
			break;
		}
		return true;
	}
	return false;
}

void monster::golemTurretDirectImg()
{

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

void monster::flyingGolemDirectImg()
{
	_monsterImg = IMAGEMANAGER->findImage("�ö��װ�");
	_ani = ANIMATIONMANAGER->findAnimation("�ö��װ��̵�");
	ANIMATIONMANAGER->start("�ö��װ��̵�");
}

void monster::slimeDirectImg()
{
	_monsterImg = IMAGEMANAGER->findImage("������");
	_ani = ANIMATIONMANAGER->findAnimation("�������̵�");
	ANIMATIONMANAGER->start("�������̵�");
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
	count++;
	//ī��Ʈ�� 30�϶� ����
	if (count == 100)
	{
		_monsterImg = IMAGEMANAGER->findImage("���ͷ�");
		hRc = RectMakeCenter(_currentX, _currentY,
			_monsterImg->getFrameWidth() / 2, _monsterImg->getFrameHeight() / 2);
		switch (monDirect) {
		case MONSTER_DIRECTION_LEFT:
			_ani = ANIMATIONMANAGER->findAnimation("���ͷ�L");
			ANIMATIONMANAGER->start("���ͷ�L");

			/*_x += cosf(getAngle(_monsterImg->getFrameX(), _monsterImg->getFrameY(),
				PLAYER->getPlayerX(), PLAYER->getPlayerY())*_speed);
			_y += -sinf(getAngle(_monsterImg->getFrameX(), _monsterImg->getFrameY(),
				PLAYER->getPlayerX(), PLAYER->getPlayerY())*_speed);*/
			break;
		case MONSTER_DIRECTION_UP:

			_ani = ANIMATIONMANAGER->findAnimation("���ͷ�U");
			ANIMATIONMANAGER->start("���ͷ�U");
			break;
		case MONSTER_DIRECTION_RIGHT:

			_ani = ANIMATIONMANAGER->findAnimation("���ͷ�R");
			ANIMATIONMANAGER->start("���ͷ�R");
			break;
		case MONSTER_DIRECTION_DOWN:

			_ani = ANIMATIONMANAGER->findAnimation("���ͷ�B");
			ANIMATIONMANAGER->start("���ͷ�B");
			break;
		}

		count = 0;
		return true;
	}

	return false;
}

//�񷽼�������
bool monster::golemSoldierAtk(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect)
{

	if (getDistance(_currentX, _currentY, PLAYER->getPlayerX(), PLAYER->getPlayerY()) < 100)
	{
		count--;
	}

	//ī��Ʈ�� 0�϶� ����
	if (count < 0)
	{
		_monState = MONSTER_STATE_ATK;
		_monsterImg = IMAGEMANAGER->findImage("�񷽼�������");
		switch (monDirect) {
		case MONSTER_DIRECTION_LEFT:

			aRc = RectMakeCenter((hRc.left + hRc.right) / 2 - 100, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth() / 2, _monsterImg->getFrameHeight() / 2);
			_ani = ANIMATIONMANAGER->findAnimation("�񷽼�������L");
			ANIMATIONMANAGER->start("�񷽼�������L");

			/*_x += cosf(getAngle(_monsterImg->getFrameX(), _monsterImg->getFrameY(),
				PLAYER->getPlayerX(), PLAYER->getPlayerY())*_speed);
			_y += -sinf(getAngle(_monsterImg->getFrameX(), _monsterImg->getFrameY(),
				PLAYER->getPlayerX(), PLAYER->getPlayerY())*_speed);*/
			break;
		case MONSTER_DIRECTION_UP:

			aRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2 - 100,
				_monsterImg->getFrameWidth() / 2, _monsterImg->getFrameHeight() / 2);
			_ani = ANIMATIONMANAGER->findAnimation("�񷽼�������U");
			ANIMATIONMANAGER->start("�񷽼�������U");
			break;
		case MONSTER_DIRECTION_RIGHT:

			aRc = RectMakeCenter((hRc.left + hRc.right) / 2 + 100, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth() / 2, _monsterImg->getFrameHeight() / 2);
			_ani = ANIMATIONMANAGER->findAnimation("�񷽼�������R");
			ANIMATIONMANAGER->start("�񷽼�������R");
			break;
		case MONSTER_DIRECTION_DOWN:

			aRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2 + 100,
				_monsterImg->getFrameWidth() / 2, _monsterImg->getFrameHeight() / 2);
			_ani = ANIMATIONMANAGER->findAnimation("�񷽼�������B");
			ANIMATIONMANAGER->start("�񷽼�������B");
			break;
		}

		count = 120;
		atkCount = 150;
		RECT rc;
		if (IntersectRect(&rc, &aRc, &PLAYER->getPlayercollision()))
		{
			PLAYER->setHP(PLAYER->getHP() - _atk);
		}
		return true;
	}
	atkCount--;
	if (atkCount < 0)
	{
		_monState = MONSTER_STATE_MOVE;
		atkCount = 250;
	}

	return false;
}

bool monster::flyingGolemAtk(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect)
{
	if (getDistance(_currentX, _currentY, PLAYER->getPlayerX(), PLAYER->getPlayerY()) < 100)
	{
		count--;
	}

	//ī��Ʈ�� 0�϶� ����
	if (count < 0)
	{
		_monState = MONSTER_STATE_ATK;
		_monsterImg = IMAGEMANAGER->findImage("�ö��װ�");
		aRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2,
			_monsterImg->getFrameWidth() / 2, _monsterImg->getFrameHeight() / 2);
		_ani = ANIMATIONMANAGER->findAnimation("�ö��װ񷽰���");
		ANIMATIONMANAGER->start("�ö��װ񷽰���");

		count = 120;
		atkCount = 150;
		RECT rc;
		if (IntersectRect(&rc, &aRc, &PLAYER->getPlayercollision()))
		{
			PLAYER->setHP(PLAYER->getHP() - _atk);
		}
		return true;
	}
	atkCount--;
	if (atkCount < 0)
	{
		_monState = MONSTER_STATE_MOVE;
		atkCount = 150;
	}


	return false;
}
bool monster::slimeAtk(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect)
{
	if (getDistance(_currentX, _currentY, PLAYER->getPlayerX(), PLAYER->getPlayerY()) < 50)
	{
		count--;
	}

	//ī��Ʈ�� 0�϶� ����
	if (count < 0)
	{
		_monState = MONSTER_STATE_ATK;
		_monsterImg = IMAGEMANAGER->findImage("������");
		aRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2,
			_monsterImg->getFrameWidth() / 2, _monsterImg->getFrameHeight() / 2);
		_ani = ANIMATIONMANAGER->findAnimation("�����Ӱ���");
		ANIMATIONMANAGER->start("�����Ӱ���");

		count = 120;
		atkCount = 150;
		RECT rc;
		if (IntersectRect(&rc, &aRc, &PLAYER->getPlayercollision()))
		{
			PLAYER->setHP(PLAYER->getHP() - _atk);
		}
		return true;
	}
	atkCount--;
	if (atkCount < 0)
	{
		_monState = MONSTER_STATE_MOVE;
		atkCount = 150;
	}


	return false;
}

bool monster::slimeGauntletAtk(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect)
{

	count++;
	//����ī��Ʈ
	if (count >= 200)
	{
		_monsterImg = IMAGEMANAGER->findImage("�����Ӱ�Ʋ��");

		hRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2,
			hRc.right - hRc.left, hRc.bottom - hRc.top);

		switch (monDirect) {
		case MONSTER_DIRECTION_LEFT:
			aRc = RectMakeCenter((hRc.left + hRc.right) / 2 - 100, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth() / 2, _monsterImg->getFrameHeight() / 4);
			_ani = ANIMATIONMANAGER->findAnimation("�����Ӱ�Ʋ������L");
			ANIMATIONMANAGER->start("�����Ӱ�Ʋ������L");
			break;
		case MONSTER_DIRECTION_UP:

			aRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2 - 100,
				_monsterImg->getFrameWidth() / 4, _monsterImg->getFrameHeight() / 2);
			_ani = ANIMATIONMANAGER->findAnimation("�����Ӱ�Ʋ������U");
			ANIMATIONMANAGER->start("�����Ӱ�Ʋ������U");
			break;
		case MONSTER_DIRECTION_RIGHT:

			aRc = RectMakeCenter((hRc.left + hRc.right) / 2 + 100, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth() / 2, _monsterImg->getFrameHeight() / 4);
			_ani = ANIMATIONMANAGER->findAnimation("�����Ӱ�Ʋ������R");
			ANIMATIONMANAGER->start("�����Ӱ�Ʋ������R");
			break;
		case MONSTER_DIRECTION_DOWN:

			aRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2 + 100,
				_monsterImg->getFrameWidth() / 4, _monsterImg->getFrameHeight() / 2);
			_ani = ANIMATIONMANAGER->findAnimation("�����Ӱ�Ʋ������B");
			ANIMATIONMANAGER->start("�����Ӱ�Ʋ������B");
			break;
		}

		count = 0;

		//���Ͱ����浹
		RECT rc;
		if (IntersectRect(&rc, &aRc, &PLAYER->getPlayercollision()))
		{
			PLAYER->setHP(PLAYER->getHP() - _atk);
		}
		return true;
	}

	return false;
}

bool monster::golemBossAtk(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect)
{

	count++;


	//ī��Ʈ�� 0�϶� ����
	if (count > 300)
	{
		_monState = MONSTER_STATE_ATK;
		if (getDistance(_currentX, _currentY, PLAYER->getPlayerX(), PLAYER->getPlayerY()) < 400) {

			switch (monDirect) {
			case MONSTER_DIRECTION_LEFT:\
				aRc = RectMakeCenter((hRc.left + hRc.right) / 2 - 100, (hRc.top + hRc.bottom) / 2 + 100,
					_monsterImg->getFrameWidth() / 4, _monsterImg->getFrameHeight() / 4);
				_ani = ANIMATIONMANAGER->findAnimation("�񷽺�������1L");
				ANIMATIONMANAGER->start("�񷽺�������1L");

				break;
			case MONSTER_DIRECTION_UP:\
				aRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2,
					_monsterImg->getFrameWidth() / 4, _monsterImg->getFrameHeight() / 4);
				_ani = ANIMATIONMANAGER->findAnimation("�񷽺�������1U");
				ANIMATIONMANAGER->start("�񷽺�������1U");
				break;
			case MONSTER_DIRECTION_RIGHT:\
				aRc = RectMakeCenter((hRc.left + hRc.right) / 2 + 100, (hRc.top + hRc.bottom) / 2 + 100,
					_monsterImg->getFrameWidth() / 4, _monsterImg->getFrameHeight() / 4);
				_ani = ANIMATIONMANAGER->findAnimation("�񷽺�������1R");
				ANIMATIONMANAGER->start("�񷽺�������1R");
				break;
			case MONSTER_DIRECTION_DOWN:
				//iRc = RectMakeCenter((hRc.right + hRc.left) / 2 - 200, (hRc.bottom + hRc.top) / 2 - 200, hRc.right - hRc.left, hRc.bottom - hRc.top);
				aRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2 + 100,
					_monsterImg->getFrameWidth() / 4, _monsterImg->getFrameHeight() / 4);
				_ani = ANIMATIONMANAGER->findAnimation("�񷽺�������1B");
				ANIMATIONMANAGER->start("�񷽺�������1B");
				break;
			}
		}
		else {
			//iRc = RectMakeCenter((iRc.right + iRc.left) / 2, (iRc.bottom + iRc.top) / 2 +100, _monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			switch (monDirect) {
			case MONSTER_DIRECTION_LEFT:
				aRc = RectMakeCenter((hRc.left + hRc.right) / 2 - 200, (hRc.top + hRc.bottom) / 2 + 100,
					_monsterImg->getFrameWidth() / 2, _monsterImg->getFrameHeight() / 2);
				_ani = ANIMATIONMANAGER->findAnimation("�񷽺�������2L");
				ANIMATIONMANAGER->start("�񷽺�������2L");

				break;
			case MONSTER_DIRECTION_UP:
				aRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2,
					_monsterImg->getFrameWidth() / 2, _monsterImg->getFrameHeight() / 2);
				_ani = ANIMATIONMANAGER->findAnimation("�񷽺�������2U");
				ANIMATIONMANAGER->start("�񷽺�������2U");
				break;
			case MONSTER_DIRECTION_RIGHT:
				aRc = RectMakeCenter((hRc.left + hRc.right) / 2 + 100, (hRc.top + hRc.bottom) / 2 + 100,
					_monsterImg->getFrameWidth() / 2, _monsterImg->getFrameHeight() / 2);
				_ani = ANIMATIONMANAGER->findAnimation("�񷽺�������2R");
				ANIMATIONMANAGER->start("�񷽺�������2R");
				break;
			case MONSTER_DIRECTION_DOWN:
				aRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2 + 200,
					_monsterImg->getFrameWidth() / 2, _monsterImg->getFrameHeight() / 2);
				_ani = ANIMATIONMANAGER->findAnimation("�񷽺�������2B");
				ANIMATIONMANAGER->start("�񷽺�������2B");
				break;
			}
		}
		count = 0;
		atkCount = 50;
		RECT rc;
		if (IntersectRect(&rc, &aRc, &PLAYER->getPlayercollision()))
		{
			PLAYER->setHP(PLAYER->getHP() - _atk);
		}
		return true;
	}
	atkCount--;
	if (atkCount == 0)
	{
		_monState = MONSTER_STATE_MOVE;
		atkCount = 50;
	}

	return false;
}

bool monster::golemSoldierMove()
{

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
	//�ǰݹ���
	hRc = RectMakeCenter(_currentX, _currentY, _monsterImg->getFrameWidth() / 2, _monsterImg->getFrameHeight() / 2);
	//�̹��� ����
	iRc = RectMakeCenter(_currentX, _currentY, _monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());

	return false;
}

bool monster::slimeMove()
{
	if (_currentX < PLAYER->getPlayerX())_currentX += 2;
	if (_currentX > PLAYER->getPlayerX())_currentX -= 2;
	if (_currentY < PLAYER->getPlayerY())_currentY += 2;
	if (_currentY > PLAYER->getPlayerY())_currentY -= 2;

	//�̹�������
	iRc = RectMakeCenter(_currentX, _currentY, _monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
	//�ǰݹ���
	hRc = RectMakeCenter(_currentX, _currentY, _monsterImg->getFrameWidth() / 4, _monsterImg->getFrameHeight() / 4);

	return false;
}

bool monster::flyingGolemMove()
{
	if (_currentX < PLAYER->getPlayerX())_currentX += 1;
	if (_currentX > PLAYER->getPlayerX())_currentX -= 1;
	if (_currentY < PLAYER->getPlayerY())_currentY += 1;
	if (_currentY > PLAYER->getPlayerY())_currentY -= 1;

	//�̹�������
	iRc = RectMakeCenter(_currentX, _currentY, _monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
	//�ǰݹ���
	hRc = RectMakeCenter(_currentX, _currentY, _monsterImg->getFrameWidth() / 2, _monsterImg->getFrameHeight() / 2);

	return false;
}

bool monster::golemBossMove()
{

	if (_currentX < PLAYER->getPlayerX())_currentX += 1;
	if (_currentX > PLAYER->getPlayerX())_currentX -= 1;
	if (_currentY < PLAYER->getPlayerY())_currentY += 1;
	if (_currentY > PLAYER->getPlayerY())_currentY -= 1;

	//�̹�������
	iRc = RectMakeCenter(_currentX, _currentY, _monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
	//�ǰݹ���
	hRc = RectMakeCenter(_currentX, _currentY, _monsterImg->getFrameWidth() / 4, _monsterImg->getFrameHeight() / 4);

	return false;
}

bool monster::golemTurretHit(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect)
{

	hitCount++;
	if (hitCount > 20)
	{
		RECT temp;

		if (IntersectRect(&temp, &hRc, &PLAYER->getPlayercollision()))
		{
			_currentHp = _currentHp - 10;
		}
		hitCount = 0;
	}
	return false;
}

bool monster::golemSoldierHit(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect)
{

	hitCount++;
	if (hitCount > 20)
	{
		RECT temp;

		if (IntersectRect(&temp, &hRc, &PLAYER->getPlayercollision()))
		{
			_currentHp = _currentHp - 10;
		}
		hitCount = 0;
	}

	return false;
}

bool monster::flyginGolemHit(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect)
{
	hitCount++;
	if (hitCount > 20)
	{
		RECT temp;

		if (IntersectRect(&temp, &hRc, &PLAYER->getPlayercollision()))
		{
			_currentHp = _currentHp - 10;
		}
		hitCount = 0;
	}
	return false;
}

bool monster::slimeHit(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect)
{
	hitCount++;
	if (hitCount > 20)
	{
		RECT temp;

		if (IntersectRect(&temp, &hRc, &PLAYER->getPlayercollision()))
		{
			_currentHp = _currentHp - 10;
		}
		hitCount = 0;
	}
	return false;
}

bool monster::slimeGauntletHit(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect)
{
	hitCount++;
	if (hitCount > 20)
	{
		RECT temp;

		if (IntersectRect(&temp, &hRc, &PLAYER->getPlayercollision()))
		{
			_currentHp = _currentHp - 10;
		}
		hitCount = 0;
	}
	return false;
}

bool monster::golemBossHit(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect)
{
	hitCount++;
	if (hitCount > 20)
	{
		RECT temp;

		if (IntersectRect(&temp, &hRc, &PLAYER->getPlayercollision()))
		{
			_currentHp = _currentHp - 10;
		}
		hitCount = 0;
	}
	return false;
}

bool monster::golemTurretDie(MONSTER_TYPE monType)
{
	if (deadCount == 0) {
		iRc = RectMakeCenter(iRc.left - 50, iRc.top - 50, iRc.right - iRc.left, iRc.bottom - iRc.top);
		_monsterImg = IMAGEMANAGER->findImage("��������");
		_ani = ANIMATIONMANAGER->findAnimation("�����ֱ�");
		_ani->start();
	}
	deadCount++;
	//item.setRect(iRc);
	//iRc = item.getRECT();
	if (deadCount >= 10) {
		_monState = MONSTER_STATE_DEAD;
	}
	/*item.setRect(_currentX, _currentY);
	item.setMove(true);*/
	return false;
}

bool monster::golemSoldierDie(MONSTER_TYPE monType)
{
	if (deadCount == 0) {
		_monsterImg = IMAGEMANAGER->findImage("��������");
		_ani = ANIMATIONMANAGER->findAnimation("�����ֱ�");
		_ani->start();
	}
	deadCount++;
	if (deadCount >= 10) {
		_monState = MONSTER_STATE_DEAD;
	}
	return false;
}

bool monster::flyingGolemDie(MONSTER_TYPE monType)
{
	if (deadCount == 0) {
		iRc = RectMakeCenter(iRc.left, iRc.top, iRc.right - iRc.left, iRc.bottom - iRc.top);
		_monsterImg = IMAGEMANAGER->findImage("��������");
		_ani = ANIMATIONMANAGER->findAnimation("�����ֱ�");
		_ani->start();
	}
	deadCount++;
	if (deadCount >= 10) {
		_monState = MONSTER_STATE_DEAD;
	}
	return false;
}

bool monster::slimeDie(MONSTER_TYPE monType)
{
	if (deadCount == 0) {
		iRc = RectMakeCenter(iRc.left, iRc.top, iRc.right - iRc.left, iRc.bottom - iRc.top);

		_monsterImg = IMAGEMANAGER->findImage("��������");
		_ani = ANIMATIONMANAGER->findAnimation("�����ֱ�");
		_ani->start();
	}
	deadCount++;
	if (deadCount >= 10) {
		_monState = MONSTER_STATE_DEAD;
	}
	return false;
}

bool monster::slimeGauntletDie(MONSTER_TYPE monType)
{
	if (deadCount == 0) {
		iRc = RectMakeCenter(iRc.left + 280, iRc.top + 280, iRc.right - iRc.left, iRc.bottom - iRc.top);
		_monsterImg = IMAGEMANAGER->findImage("��������");
		_ani = ANIMATIONMANAGER->findAnimation("�����ֱ�");
		_ani->start();
	}
	deadCount++;
	if (deadCount >= 10) {
		_monState = MONSTER_STATE_DEAD;
	}
	return false;
}

bool monster::golemBossDie(MONSTER_TYPE monType)
{
	if (deadCount == 0) {
		_monsterImg = IMAGEMANAGER->findImage("��������");
		_ani = ANIMATIONMANAGER->findAnimation("�����ֱ�");
		_ani->start();
	}
	deadCount++;
	if (deadCount >= 10) {
		_monState = MONSTER_STATE_DEAD;
	}
	return false;
}

//ü�� �����ִ� �Լ�
void monster::viewProgressBar()
{
	_hpBar->setGauge(_currentHp, _hp);
	_hpBar->update();
}