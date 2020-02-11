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
	hRc = RectMakeCenter(_x, _y, _monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
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
	if (PLAYER->getPlayerX() >= _currentX&&PLAYER->getPlayerY()>=_currentY)//4»çºÐ¸é
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
		if (_currentX-PLAYER->getPlayerX() >= _currentY-PLAYER->getPlayerY())
		{
			_monDirect = MONSTER_DIRECTION_LEFT;
		}
		else
		{
			_monDirect = MONSTER_DIRECTION_UP;
		}
	}
	//¾îÅÃ°ú ¹«ºùÀ» µ¿½Ã¿¡ ¾ÈµÇ°Ô ÇÏ°í½ÍÀºµ¥ ¾ÆÁ÷¸øÇÔ
	if (!attack(_monType, _monDirect))
	{
		move(_monType, _monDirect);
	}
	else if (!move(_monType, _monDirect))
	{
		attack(_monType, _monDirect);
	}
	//hp¹Ù À§Ä¡°»½Å
	_hpBar->setX(_currentX - 25);
	_hpBar->setY(_currentY - 70);
	//hp¹Ù Ãâ·Â
	viewProgressBar();
	
	
	
}

void monster::render()
{
	draw();
}

//ÇÁ·¹ÀÓÀÌ¹ÌÁö ±×·ÁÁÜ
void monster::draw()
{
	//¸ó½ºÅÍ ·»´õ
	_monsterImg->aniRender(getMemDC(), hRc.left, hRc.top, _ani);
	_hpBar->render();
	//¸ó½ºÅÍ ÇÇ°Ý¹üÀ§
	//RectangleMakeCenter(getMemDC(), (hRc.left+ hRc.right)/2, (hRc.top+ hRc.bottom)/2, _monsterImg->getFrameWidth()/2, _monsterImg->getFrameHeight()/2);
	//¸ó½ºÅÍ °ø°Ý¹üÀ§
	//RectangleMakeCenter(getMemDC(), (aRc.left + aRc.right) / 2, (aRc.top + aRc.bottom) / 2, aRc.right - aRc.left, aRc.bottom - aRc.top);
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
		golemBossAtk(monType, monDirect);
		break;
	}

	//°ñ·½ÅÍ·¿À» Á¦¿ÜÇÑ ¸ó½ºÅÍ´Â ¹üÀ§¿¡ ÇÃ·¹ÀÌ¾î°¡ ÀÖÀ»¶§ Ä«¿îÆ®°¡ ¿Ã¶ó°£´Ù.
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
	_monsterImg = IMAGEMANAGER->findImage("°ñ·½ÅÍ·¿");
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
	//if (monType == 0) {
	count++;
	//Ä«¿îÆ®°¡ 30ÀÏ¶§ °ø°Ý
	if (count == 100)
	{
		_monsterImg = IMAGEMANAGER->findImage("°ñ·½ÅÍ·¿");
		switch (monDirect) {
		case MONSTER_DIRECTION_LEFT:
			hRc = RectMakeH(hRc.left, hRc.bottom,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("°ñ·½ÅÍ·¿L");
			ANIMATIONMANAGER->start("°ñ·½ÅÍ·¿L");
			if (_monsterImg->getFrameX() == _monsterImg->getMaxFrameX())
			{
				_ani = ANIMATIONMANAGER->findAnimation("°ñ·½ÅÍ·¿L");
				ANIMATIONMANAGER->start("°ñ·½ÅÍ·¿L");
			}
			/*_x += cosf(getAngle(_monsterImg->getFrameX(), _monsterImg->getFrameY(),
				PLAYER->getPlayerX(), PLAYER->getPlayerY())*_speed);
			_y += -sinf(getAngle(_monsterImg->getFrameX(), _monsterImg->getFrameY(),
				PLAYER->getPlayerX(), PLAYER->getPlayerY())*_speed);*/
			break;
		case MONSTER_DIRECTION_UP:
			hRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight() - 50);
			_ani = ANIMATIONMANAGER->findAnimation("°ñ·½ÅÍ·¿U");
			ANIMATIONMANAGER->start("°ñ·½ÅÍ·¿U");
			break;
		case MONSTER_DIRECTION_RIGHT:
			hRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth() + 50, _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("°ñ·½ÅÍ·¿R");
			ANIMATIONMANAGER->start("°ñ·½ÅÍ·¿R");
			break;
		case MONSTER_DIRECTION_DOWN:
			hRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight() + 50);
			_ani = ANIMATIONMANAGER->findAnimation("°ñ·½ÅÍ·¿B");
			ANIMATIONMANAGER->start("°ñ·½ÅÍ·¿B");
			break;
		}
		//_rndFireCount = RND->getFromIntTo(1, 1000);
		count = 0;
		return true;
	}
	//}
	return false;
}

//°ñ·½¼ÖÁ®°ø°Ý
bool monster::golemSoldierAtk(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect)
{
	//if (monType == 0) {
	count++;
	//Ä«¿îÆ®°¡ 30ÀÏ¶§ °ø°Ý
	if (count == 300&&MONSTER_STATE_ATK)
	{
		_monsterImg = IMAGEMANAGER->findImage("°ñ·½¼ÖÀú°ø°Ý");
		switch (monDirect) {
		case MONSTER_DIRECTION_LEFT:
			
			hRc = RectMakeH(hRc.left, hRc.bottom,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			aRc = RectMakeCenter((hRc.left + hRc.right) / 2 - 200, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("°ñ·½¼ÖÀú°ø°ÝL");
			ANIMATIONMANAGER->start("°ñ·½¼ÖÀú°ø°ÝL");
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
			_ani = ANIMATIONMANAGER->findAnimation("°ñ·½¼ÖÀú°ø°ÝU");
			ANIMATIONMANAGER->start("°ñ·½¼ÖÀú°ø°ÝU");
			break;
		case MONSTER_DIRECTION_RIGHT:
			hRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth() + 50, _monsterImg->getFrameHeight());
			aRc = RectMakeCenter((hRc.left + hRc.right) / 2 + 200, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("°ñ·½¼ÖÀú°ø°ÝR");
			ANIMATIONMANAGER->start("°ñ·½¼ÖÀú°ø°ÝR");
			break;
		case MONSTER_DIRECTION_DOWN:
			hRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight() + 50);
			aRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2+200,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("°ñ·½¼ÖÀú°ø°ÝB");
			ANIMATIONMANAGER->start("°ñ·½¼ÖÀú°ø°ÝB");
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
	//Ä«¿îÆ®°¡ 30ÀÏ¶§ °ø°Ý
	if (count == 450)
	{
		_monsterImg = IMAGEMANAGER->findImage("½½¶óÀÓ°ÇÆ²·¿°ø°Ý");

		//_rndFireCount = RND->getFromIntTo(1, 1000);
		switch (monDirect) {
		case MONSTER_DIRECTION_LEFT:
			hRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			aRc = RectMakeCenter((hRc.left + hRc.right) / 2 - 200, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("½½¶óÀÓ°ÇÆ²·¿°ø°ÝL");
			ANIMATIONMANAGER->start("½½¶óÀÓ°ÇÆ²·¿°ø°ÝL");
			if (_monsterImg->getFrameX() == _monsterImg->getMaxFrameX())
			{
				_ani = ANIMATIONMANAGER->findAnimation("½½¶óÀÓ°ÇÆ²·¿L");
				ANIMATIONMANAGER->start("½½¶óÀÓ°ÇÆ²·¿L");
			}
			break;
		case MONSTER_DIRECTION_UP:
			hRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			aRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2-200,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("½½¶óÀÓ°ÇÆ²·¿°ø°ÝU");
			ANIMATIONMANAGER->start("½½¶óÀÓ°ÇÆ²·¿°ø°ÝU");
			break;
		case MONSTER_DIRECTION_RIGHT:
			hRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			aRc = RectMakeCenter((hRc.left + hRc.right) / 2-200, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("½½¶óÀÓ°ÇÆ²·¿°ø°ÝR");
			ANIMATIONMANAGER->start("½½¶óÀÓ°ÇÆ²·¿°ø°ÝR");
			break;
		case MONSTER_DIRECTION_DOWN:
			hRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight() + 50);
			aRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2 + 200,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("½½¶óÀÓ°ÇÆ²·¿°ø°ÝB");
			ANIMATIONMANAGER->start("½½¶óÀÓ°ÇÆ²·¿°ø°ÝB");
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
	//Ä«¿îÆ®°¡ 300ÀÏ¶§ °ø°Ý
	if (count == 300)
	{
		//_rndFireCount = RND->getFromIntTo(1, 1000);
		switch (monDirect) {
		case MONSTER_DIRECTION_LEFT:
			_monsterImg = IMAGEMANAGER->findImage("°ñ·½º¸½º°ø°Ý1");
			hRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			aRc = RectMakeCenter((hRc.left + hRc.right) / 2-500, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("°ñ·½º¸½º°ø°Ý1L");
			ANIMATIONMANAGER->start("°ñ·½º¸½º°ø°Ý1L");
			break;
		case MONSTER_DIRECTION_UP:
			_monsterImg = IMAGEMANAGER->findImage("°ñ·½º¸½º°ø°Ý1");
			hRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			aRc = RectMakeCenter((hRc.left + hRc.right) / 2 - 500, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("°ñ·½º¸½º°ø°Ý1U");
			ANIMATIONMANAGER->start("°ñ·½º¸½º°ø°Ý1U");
			break;
		case MONSTER_DIRECTION_RIGHT:
			_monsterImg = IMAGEMANAGER->findImage("°ñ·½º¸½º°ø°Ý1");
			hRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			aRc = RectMakeCenter((hRc.left + hRc.right) / 2 - 500, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("°ñ·½º¸½º°ø°Ý1R");
			ANIMATIONMANAGER->start("°ñ·½º¸½º°ø°Ý1R");
			break;
		case MONSTER_DIRECTION_DOWN:
			_monsterImg = IMAGEMANAGER->findImage("°ñ·½º¸½º°ø°Ý1");
			hRc = RectMakeCenter((hRc.left + hRc.right) / 2, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			aRc = RectMakeCenter((hRc.left + hRc.right) / 2 - 500, (hRc.top + hRc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("°ñ·½º¸½º°ø°Ý1B");
			ANIMATIONMANAGER->start("°ñ·½º¸½º°ø°Ý1B");
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
	//¸ó½ºÅÍ ¾îÅÃÀÌ ¾Æ´Ò¶§ move
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

//Ã¼·Â º¸¿©ÁÖ´Â ÇÔ¼ö
void monster::viewProgressBar()
{
	_hpBar->setGauge(_currentHp, _hp);
	_hpBar->update();
}