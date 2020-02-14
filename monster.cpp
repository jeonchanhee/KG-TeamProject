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
	//ÇØ´ç ¸ó½ºÅÍÀÇ º¤ÅÍ °ª ³Ö±â
	_monsterImg = IMAGEMANAGER->findImage(imageName);
	_monType = monType;			//¸ó½ºÅÍ Á¾·ù
	_monState = monState;		//¸ó½ºÅÍ »óÅÂ
	_monDirect = monDirect;		//¸ó½ºÅÍ ¹æÇâ
	_x = x;
	_y = y;
	_currentX = x;
	_currentY = y;
	_atk = atk;
	_hp = hp;
	_range = range;
	_currentHp = currentHp;
	_speed = speed;
	_atkCount = atkCount;
	item = ITEMMANAGER->addItem("³ª¹µ°¡Áö");
	//ÀÌ¹ÌÁö ¹üÀ§
	iRc = RectMakeCenter(_x, _y, _monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
	//ÇÇ°Ý ¹üÀ§
	hRc = RectMakeCenter(_x, _y, _monsterImg->getFrameWidth() / 4, _monsterImg->getFrameHeight() / 4);
	//aRc = RectMakeCenter(_x, _y, _monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
	count = 0;					//Ä«¿îÆ®

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

	//ÇÃ·¹ÀÌ¾î À§Ä¡¿¡ µû¸¥ ¹æÇâÀüÈ¯
	if (PLAYER->getPlayerX() >= _currentX && PLAYER->getPlayerY() >= _currentY)//4»çºÐ¸é
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
	else if (PLAYER->getPlayerX() < _currentX&&PLAYER->getPlayerY() >= _currentY)//3»çºÐ¸é
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
	else if (PLAYER->getPlayerX() >= _currentX && PLAYER->getPlayerY() < _currentY)//1»çºÐ¸é
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
	else if (PLAYER->getPlayerX() < _currentX&&PLAYER->getPlayerY() < _currentY)//2»çºÐ¸é
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

	//hp¹Ù À§Ä¡°»½Å
	_hpBar->setX(_currentX - 25);
	_hpBar->setY(_currentY - 70);
	//hp¹Ù Ãâ·Â
	viewProgressBar();

	item.update();
	hit(_monType, _monDirect);
	die(_monType);
}

void monster::render()
{

	draw();
}

//ÇÁ·¹ÀÓÀÌ¹ÌÁö ±×·ÁÁÜ
void monster::draw()
{

	//¸ó½ºÅÍ °ø°Ý¹üÀ§
	//Rectangle(getMemDC(), aRc.left, aRc.top, aRc.right, aRc.bottom);
	if (KEYMANAGER->isToggleKey('P'))
	{

		//¸ó½ºÅÍ ÀÌ¹ÌÁö ¹üÀ§
		//Rectangle(getMemDC(), iRc.left, iRc.top, iRc.right, iRc.bottom);
		//¸ó½ºÅÍ ÇÇ°Ý¹üÀ§
		Rectangle(getMemDC(), hRc.left, hRc.top, hRc.right, hRc.bottom);
		//item.getItemInfo().image->render(getMemDC(), item.getRECT().left, item.getRECT().top);
	}
	//¸ó½ºÅÍ ·»´õ
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

//°ø°Ý
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
		//if (getDistance(_currentX, _currentY, PLAYER->getPlayerX(), PLAYER->getPlayerY()) < 400) {
		golemBossAtk1(monType, monDirect);
		//}
		//else {
		//	golemBossAtk2(monType, monDirect);
		//}
		break;
	}


	//°ñ·½ÅÍ·¿À» Á¦¿ÜÇÑ ¸ó½ºÅÍ´Â ¹üÀ§¿¡ ÇÃ·¹ÀÌ¾î°¡ ÀÖÀ»¶§ Ä«¿îÆ®°¡ ¿Ã¶ó°£´Ù.
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
	case MONSTER_TYPE_SLIMEGAUNTLET:
		slimeGauntletHit(monType, monDirect);
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
	case MONSTER_TYPE_GOLEMBOSS:
		golemBossMove();
		if (imgCount > 20) {
			golemBossDirectImg();
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
		case MONSTER_TYPE_SLIMEGAUNTLET:
			slimeGauntletDie(monType);
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

	//¹æÇâ°ªÀ¸·Î ¸Â´Â ¹æÇâ ÀÌ¹ÌÁö Ã£±â
	switch (_monDirect)
	{
	case 0:
		_ani = ANIMATIONMANAGER->findAnimation("°ñ·½ÅÍ·¿L");
		ANIMATIONMANAGER->start("°ñ·½ÅÍ·¿L");

		break;
	case 1:
		_ani = ANIMATIONMANAGER->findAnimation("°ñ·½ÅÍ·¿U");
		ANIMATIONMANAGER->start("°ñ·½ÅÍ·¿U");
		break;
	case 2:
		_ani = ANIMATIONMANAGER->findAnimation("°ñ·½ÅÍ·¿R");
		ANIMATIONMANAGER->start("°ñ·½ÅÍ·¿R");
		break;
	case 3:
		_ani = ANIMATIONMANAGER->findAnimation("°ñ·½ÅÍ·¿B");
		ANIMATIONMANAGER->start("°ñ·½ÅÍ·¿B");
		break;
	}
}

void monster::golemSoldierDirectImg()
{
	_monsterImg = IMAGEMANAGER->findImage("°ñ·½¼ÖÀú");
	//¹æÇâ°ªÀ¸·Î ¸Â´Â ¹æÇâ ÀÌ¹ÌÁö Ã£±â
	switch (_monDirect)
	{
	case 0:
		_ani = ANIMATIONMANAGER->findAnimation("°ñ·½¼ÖÀúL");
		ANIMATIONMANAGER->start("°ñ·½¼ÖÀúL");
		break;
	case 1:
		_ani = ANIMATIONMANAGER->findAnimation("°ñ·½¼ÖÀúU");
		ANIMATIONMANAGER->start("°ñ·½¼ÖÀúU");
		break;
	case 2:
		_ani = ANIMATIONMANAGER->findAnimation("°ñ·½¼ÖÀúR");
		ANIMATIONMANAGER->start("°ñ·½¼ÖÀúR");
		break;
	case 3:
		_ani = ANIMATIONMANAGER->findAnimation("°ñ·½¼ÖÀúB");
		ANIMATIONMANAGER->start("°ñ·½¼ÖÀúB");
		break;
	}
}

void monster::slimeGauntletDirectImg()
{
	_monsterImg = IMAGEMANAGER->findImage("½½¶óÀÓ°ÇÆ²·¿");
	//¹æÇâ°ªÀ¸·Î ¸Â´Â ¹æÇâ ÀÌ¹ÌÁö Ã£±â
	switch (_monDirect)
	{
	case 0:
		_ani = ANIMATIONMANAGER->findAnimation("½½¶óÀÓ°ÇÆ²·¿L");
		ANIMATIONMANAGER->start("½½¶óÀÓ°ÇÆ²·¿L");
		break;
	case 1:
		_ani = ANIMATIONMANAGER->findAnimation("½½¶óÀÓ°ÇÆ²·¿U");
		ANIMATIONMANAGER->start("½½¶óÀÓ°ÇÆ²·¿U");
		break;
	case 2:
		_ani = ANIMATIONMANAGER->findAnimation("½½¶óÀÓ°ÇÆ²·¿R");
		ANIMATIONMANAGER->start("½½¶óÀÓ°ÇÆ²·¿R");
		break;
	case 3:
		_ani = ANIMATIONMANAGER->findAnimation("½½¶óÀÓ°ÇÆ²·¿B");
		ANIMATIONMANAGER->start("½½¶óÀÓ°ÇÆ²·¿B");
		break;
	}
}

void monster::golemBossDirectImg()
{
	_monsterImg = IMAGEMANAGER->findImage("°ñ·½º¸½º");
	//¹æÇâ°ªÀ¸·Î ¸Â´Â ¹æÇâ ÀÌ¹ÌÁö Ã£±â
	switch (_monDirect)
	{
	case 0:
		_ani = ANIMATIONMANAGER->findAnimation("°ñ·½º¸½ºL");
		ANIMATIONMANAGER->start("°ñ·½º¸½ºL");
		break;
	case 1:
		_ani = ANIMATIONMANAGER->findAnimation("°ñ·½º¸½ºU");
		ANIMATIONMANAGER->start("°ñ·½º¸½ºU");
		break;
	case 2:
		_ani = ANIMATIONMANAGER->findAnimation("°ñ·½º¸½ºR");
		ANIMATIONMANAGER->start("°ñ·½º¸½ºR");
		break;
	case 3:
		_ani = ANIMATIONMANAGER->findAnimation("°ñ·½º¸½ºB");
		ANIMATIONMANAGER->start("°ñ·½º¸½ºB");
		break;
	}
}


//°ñ·½ÅÍ·¿°ø°Ý
bool monster::golemTurretAtk(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect)
{
	count++;
	//Ä«¿îÆ®°¡ 30ÀÏ¶§ °ø°Ý
	if (count == 100)
	{
		_monsterImg = IMAGEMANAGER->findImage("°ñ·½ÅÍ·¿");
		hRc = RectMakeCenter(_currentX, _currentY,
			_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
		switch (monDirect) {
		case MONSTER_DIRECTION_LEFT:
			_ani = ANIMATIONMANAGER->findAnimation("°ñ·½ÅÍ·¿L");
			ANIMATIONMANAGER->start("°ñ·½ÅÍ·¿L");

			/*_x += cosf(getAngle(_monsterImg->getFrameX(), _monsterImg->getFrameY(),
				PLAYER->getPlayerX(), PLAYER->getPlayerY())*_speed);
			_y += -sinf(getAngle(_monsterImg->getFrameX(), _monsterImg->getFrameY(),
				PLAYER->getPlayerX(), PLAYER->getPlayerY())*_speed);*/
			break;
		case MONSTER_DIRECTION_UP:

			_ani = ANIMATIONMANAGER->findAnimation("°ñ·½ÅÍ·¿U");
			ANIMATIONMANAGER->start("°ñ·½ÅÍ·¿U");
			break;
		case MONSTER_DIRECTION_RIGHT:

			_ani = ANIMATIONMANAGER->findAnimation("°ñ·½ÅÍ·¿R");
			ANIMATIONMANAGER->start("°ñ·½ÅÍ·¿R");
			break;
		case MONSTER_DIRECTION_DOWN:

			_ani = ANIMATIONMANAGER->findAnimation("°ñ·½ÅÍ·¿B");
			ANIMATIONMANAGER->start("°ñ·½ÅÍ·¿B");
			break;
		}

		count = 0;
		return true;
	}

	return false;
}

//°ñ·½¼ÖÁ®°ø°Ý
bool monster::golemSoldierAtk(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect)
{

	if (getDistance(_currentX, _currentY, PLAYER->getPlayerX(), PLAYER->getPlayerY()) < 100)
	{
		count--;
	}

	//Ä«¿îÆ®°¡ 0ÀÏ¶§ °ø°Ý
	if (count < 0)
	{
		_monState = MONSTER_STATE_ATK;
		_monsterImg = IMAGEMANAGER->findImage("°ñ·½¼ÖÀú°ø°Ý");
		switch (monDirect) {
		case MONSTER_DIRECTION_LEFT:

			aRc = RectMakeCenter((hRc.left + hRc.right) / 2 - 100, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth() / 2, _monsterImg->getFrameHeight() / 2);
			_ani = ANIMATIONMANAGER->findAnimation("°ñ·½¼ÖÀú°ø°ÝL");
			ANIMATIONMANAGER->start("°ñ·½¼ÖÀú°ø°ÝL");

			/*_x += cosf(getAngle(_monsterImg->getFrameX(), _monsterImg->getFrameY(),
				PLAYER->getPlayerX(), PLAYER->getPlayerY())*_speed);
			_y += -sinf(getAngle(_monsterImg->getFrameX(), _monsterImg->getFrameY(),
				PLAYER->getPlayerX(), PLAYER->getPlayerY())*_speed);*/
			break;
		case MONSTER_DIRECTION_UP:

			aRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2 - 100,
				_monsterImg->getFrameWidth() / 2, _monsterImg->getFrameHeight() / 2);
			_ani = ANIMATIONMANAGER->findAnimation("°ñ·½¼ÖÀú°ø°ÝU");
			ANIMATIONMANAGER->start("°ñ·½¼ÖÀú°ø°ÝU");
			break;
		case MONSTER_DIRECTION_RIGHT:

			aRc = RectMakeCenter((hRc.left + hRc.right) / 2 + 100, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth() / 2, _monsterImg->getFrameHeight() / 2);
			_ani = ANIMATIONMANAGER->findAnimation("°ñ·½¼ÖÀú°ø°ÝR");
			ANIMATIONMANAGER->start("°ñ·½¼ÖÀú°ø°ÝR");
			break;
		case MONSTER_DIRECTION_DOWN:

			aRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2 + 100,
				_monsterImg->getFrameWidth() / 2, _monsterImg->getFrameHeight() / 2);
			_ani = ANIMATIONMANAGER->findAnimation("°ñ·½¼ÖÀú°ø°ÝB");
			ANIMATIONMANAGER->start("°ñ·½¼ÖÀú°ø°ÝB");
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

bool monster::slimeGauntletAtk(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect)
{

	count++;
	//°ø°ÝÄ«¿îÆ®
	if (count >= 140)
	{
		_monsterImg = IMAGEMANAGER->findImage("½½¶óÀÓ°ÇÆ²·¿");

		hRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2,
			hRc.right - hRc.left, hRc.bottom - hRc.top);

		switch (monDirect) {
		case MONSTER_DIRECTION_LEFT:
			aRc = RectMakeCenter((hRc.left + hRc.right) / 2 - 100, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth() / 2, _monsterImg->getFrameHeight() / 2);
			_ani = ANIMATIONMANAGER->findAnimation("½½¶óÀÓ°ÇÆ²·¿°ø°ÝL");
			ANIMATIONMANAGER->start("½½¶óÀÓ°ÇÆ²·¿°ø°ÝL");
			break;
		case MONSTER_DIRECTION_UP:

			aRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2 - 100,
				_monsterImg->getFrameWidth() / 2, _monsterImg->getFrameHeight() / 2);
			_ani = ANIMATIONMANAGER->findAnimation("½½¶óÀÓ°ÇÆ²·¿°ø°ÝU");
			ANIMATIONMANAGER->start("½½¶óÀÓ°ÇÆ²·¿°ø°ÝU");
			break;
		case MONSTER_DIRECTION_RIGHT:

			aRc = RectMakeCenter((hRc.left + hRc.right) / 2 + 100, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth() / 2, _monsterImg->getFrameHeight() / 2);
			_ani = ANIMATIONMANAGER->findAnimation("½½¶óÀÓ°ÇÆ²·¿°ø°ÝR");
			ANIMATIONMANAGER->start("½½¶óÀÓ°ÇÆ²·¿°ø°ÝR");
			break;
		case MONSTER_DIRECTION_DOWN:

			aRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2 + 100,
				_monsterImg->getFrameWidth() / 2, _monsterImg->getFrameHeight() / 2);
			_ani = ANIMATIONMANAGER->findAnimation("½½¶óÀÓ°ÇÆ²·¿°ø°ÝB");
			ANIMATIONMANAGER->start("½½¶óÀÓ°ÇÆ²·¿°ø°ÝB");
			break;
		}
		_ani->setFPS(14.0f);

		count = 0;

		//¸ó½ºÅÍ°ø°ÝÃæµ¹
		RECT rc;
		if (IntersectRect(&rc, &aRc, &PLAYER->getPlayercollision()))
		{
			PLAYER->setHP(PLAYER->getHP() - _atk);
		}
		return true;
	}

	return false;
}

bool monster::golemBossAtk1(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect)
{

	count++;


	//Ä«¿îÆ®°¡ 0ÀÏ¶§ °ø°Ý
	if (count > 300)
	{
		_monState = MONSTER_STATE_ATK;
		if (getDistance(_currentX, _currentY, PLAYER->getPlayerX(), PLAYER->getPlayerY()) < 400) {
			_monsterImg = IMAGEMANAGER->findImage("°ñ·½º¸½º°ø°Ý1");
			iRc = RectMakeCenter((hRc.right + hRc.left) / 2 - 200, (hRc.bottom + hRc.top) / 2 - 200, hRc.right - hRc.left, hRc.bottom - hRc.top);
			switch (monDirect) {
			case MONSTER_DIRECTION_LEFT:

				aRc = RectMakeCenter((hRc.left + hRc.right) / 2 - 100, (hRc.top + hRc.bottom) / 2,
					_monsterImg->getFrameWidth() / 2, _monsterImg->getFrameHeight() / 2);
				_ani = ANIMATIONMANAGER->findAnimation("°ñ·½º¸½º°ø°Ý1L");
				ANIMATIONMANAGER->start("°ñ·½º¸½º°ø°Ý1L");

				break;
			case MONSTER_DIRECTION_UP:

				aRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2 - 100,
					_monsterImg->getFrameWidth() / 2, _monsterImg->getFrameHeight() / 2);
				_ani = ANIMATIONMANAGER->findAnimation("°ñ·½º¸½º°ø°Ý1U");
				ANIMATIONMANAGER->start("°ñ·½º¸½º°ø°Ý1U");
				break;
			case MONSTER_DIRECTION_RIGHT:

				aRc = RectMakeCenter((hRc.left + hRc.right) / 2 + 100, (hRc.top + hRc.bottom) / 2,
					_monsterImg->getFrameWidth() / 2, _monsterImg->getFrameHeight() / 2);
				_ani = ANIMATIONMANAGER->findAnimation("°ñ·½º¸½º°ø°Ý1R");
				ANIMATIONMANAGER->start("°ñ·½º¸½º°ø°Ý1R");
				break;
			case MONSTER_DIRECTION_DOWN:

				aRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2 + 100,
					_monsterImg->getFrameWidth() / 2, _monsterImg->getFrameHeight() / 2);
				_ani = ANIMATIONMANAGER->findAnimation("°ñ·½º¸½º°ø°Ý1B");
				ANIMATIONMANAGER->start("°ñ·½º¸½º°ø°Ý1B");
				break;
			}
		}
		else {
			_monsterImg = IMAGEMANAGER->findImage("°ñ·½º¸½º°ø°Ý2");
			iRc = RectMakeCenter((hRc.right + hRc.left) / 2 - 200, (hRc.bottom + hRc.top) / 2 - 200, hRc.right - hRc.left, hRc.bottom - hRc.top);
			switch (monDirect) {
			case MONSTER_DIRECTION_LEFT:

				aRc = RectMakeCenter((hRc.left + hRc.right) / 2 - 100, (hRc.top + hRc.bottom) / 2,
					_monsterImg->getFrameWidth() / 2, _monsterImg->getFrameHeight() / 2);
				_ani = ANIMATIONMANAGER->findAnimation("°ñ·½º¸½º°ø°Ý2L");
				ANIMATIONMANAGER->start("°ñ·½º¸½º°ø°Ý2L");

				break;
			case MONSTER_DIRECTION_UP:

				aRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2 - 100,
					_monsterImg->getFrameWidth() / 2, _monsterImg->getFrameHeight() / 2);
				_ani = ANIMATIONMANAGER->findAnimation("°ñ·½º¸½º°ø°Ý2U");
				ANIMATIONMANAGER->start("°ñ·½º¸½º°ø°Ý2U");
				break;
			case MONSTER_DIRECTION_RIGHT:

				aRc = RectMakeCenter((hRc.left + hRc.right) / 2 + 100, (hRc.top + hRc.bottom) / 2,
					_monsterImg->getFrameWidth() / 2, _monsterImg->getFrameHeight() / 2);
				_ani = ANIMATIONMANAGER->findAnimation("°ñ·½º¸½º°ø°Ý2R");
				ANIMATIONMANAGER->start("°ñ·½º¸½º°ø°Ý2R");
				break;
			case MONSTER_DIRECTION_DOWN:

				aRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2 + 100,
					_monsterImg->getFrameWidth() / 2, _monsterImg->getFrameHeight() / 2);
				_ani = ANIMATIONMANAGER->findAnimation("°ñ·½º¸½º°ø°Ý2B");
				ANIMATIONMANAGER->start("°ñ·½º¸½º°ø°Ý2B");
				break;
			}
		}
		count = 0;
		atkCount = 30;
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
		atkCount = 30;
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
	//ÇÇ°Ý¹üÀ§
	hRc = RectMakeCenter(_currentX, _currentY, _monsterImg->getFrameWidth() / 2, _monsterImg->getFrameHeight() / 2);
	//ÀÌ¹ÌÁö ¹üÀ§
	iRc = RectMakeCenter(_currentX, _currentY, _monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());

	return false;
}

bool monster::golemBossMove()
{

	if (_currentX < PLAYER->getPlayerX())_currentX += 1;
	if (_currentX > PLAYER->getPlayerX())_currentX -= 1;
	if (_currentY < PLAYER->getPlayerY())_currentY += 1;
	if (_currentY > PLAYER->getPlayerY())_currentY -= 1;

	//ÀÌ¹ÌÁö¹üÀ§
	iRc = RectMakeCenter(_currentX, _currentY, _monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
	//ÇÇ°Ý¹üÀ§
	hRc = RectMakeCenter(_currentX, _currentY, _monsterImg->getFrameWidth() / 2, _monsterImg->getFrameHeight() / 2);

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
	/*item.setRect(_currentX, _currentY);
	item.setMove(true);*/

	return false;
}

bool monster::golemSoldierDie(MONSTER_TYPE monType)
{

	return false;
}

bool monster::slimeGauntletDie(MONSTER_TYPE monType)
{
	return false;
}

bool monster::golemBossDie(MONSTER_TYPE monType)
{
	return false;
}

//Ã¼·Â º¸¿©ÁÖ´Â ÇÔ¼ö
void monster::viewProgressBar()
{
	_hpBar->setGauge(_currentHp, _hp);
	_hpBar->update();
}