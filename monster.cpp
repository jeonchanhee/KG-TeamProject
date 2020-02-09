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
	MONSTER_TYPE monType,	//Å¸ÀÔ
	MONSTER_STATE monState,	//»óÅÂ
	MONSTER_DIRECTION monDirect,//¹æÇâ
	int x,
	int y		//ÃÊ±âÁÂÇ¥
)
{




	//¸ó½ºÅÍ Å¸ÀÔ¿¡ µû¸¥ º¤ÅÍ°ª ³Ö±â
	switch (monType)
	{
	case MONSTER_TYPE_GOLEMTURRET://°ñ·½ÅÍ·¿
		_monsterImg = IMAGEMANAGER->findImage("°ñ·½ÅÍ·¿");
		//¹æÇâ°ªÀ¸·Î ¸Â´Â ¹æÇâ ÀÌ¹ÌÁö Ã£±â
		golemTurretDirectImg(monDirect);//ÀÌ¹ÌÁö¹æÇâ

		//¸ó½ºÅÍ ÇÇ°İ¹üÀ§
		rc = RectMakeCenter(x, y,
			_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
		atk = 10;					//°ø°İ·Â
		maxHp = 100;				//Ã¼·Â
		currentHp = 100;			//ÇöÀçÃ¼·Â
		speed = 0;					//ÀÌµ¿¼Óµµ
		_x = x;						//ÃÊ±âÁÂÇ¥
		_y = y;
		dropItemNum1 = 0;			//µå¶ø°¡´ÉÇÑ ¾ÆÀÌÅÛ ¹øÈ£
		dropItemNum2 = 1;			//µå¶ø°¡´ÉÇÑ ¾ÆÀÌÅÛ ¹øÈ£
		dropItemNum3 = 2;			//µå¶ø°¡´ÉÇÑ ¾ÆÀÌÅÛ ¹øÈ£
		break;
	case MONSTER_TYPE_GOLEMSOLDIER://°ñ·½¼ÖÁ®
		_monsterImg = IMAGEMANAGER->findImage("°ñ·½¼ÖÀú");
		//¹æÇâ°ªÀ¸·Î ¸Â´Â ¹æÇâ ÀÌ¹ÌÁö Ã£±â
		golemSoldierDirectImg(monDirect);//ÀÌ¹ÌÁö¹æÇâ
		//¸ó½ºÅÍ ÇÇ°İ¹üÀ§
		rc = RectMakeCenter(x, y,
			_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
		atk = 15;					//°ø°İ·Â
		maxHp = 100;				//Ã¼·Â
		currentHp = 100;				//ÇöÀçÃ¼·Â
		speed = 5;					//ÀÌµ¿¼Óµµ
		_x = x;						//ÃÊ±âÁÂÇ¥
		_y = y;
		dropItemNum1 = 1;			//µå¶ø°¡´ÉÇÑ ¾ÆÀÌÅÛ ¹øÈ£
		dropItemNum2 = 3;			//µå¶ø°¡´ÉÇÑ ¾ÆÀÌÅÛ ¹øÈ£
		dropItemNum3 = 2;			//µå¶ø°¡´ÉÇÑ ¾ÆÀÌÅÛ ¹øÈ£
		break;
	case MONSTER_TYPE_SLIMEGAUNTLET:
		_monsterImg = IMAGEMANAGER->findImage("½½¶óÀÓ°ÇÆ²·¿");
		//¹æÇâ°ªÀ¸·Î ¸Â´Â ¹æÇâ ÀÌ¹ÌÁö Ã£±â
		slimeGauntletDirectImg(monDirect);//ÀÌ¹ÌÁö¹æÇâ
		//¸ó½ºÅÍ ÇÇ°İ¹üÀ§
		rc = RectMakeCenter(x, y,
			_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
		atk = 15;					//°ø°İ·Â
		maxHp = 100;				//Ã¼·Â
		currentHp = 100;				//ÇöÀçÃ¼·Â
		speed = 0;					//ÀÌµ¿¼Óµµ
		_x = x;						//ÃÊ±âÁÂÇ¥
		_y = y;
		dropItemNum1 = 1;			//µå¶ø°¡´ÉÇÑ ¾ÆÀÌÅÛ ¹øÈ£
		dropItemNum2 = 3;			//µå¶ø°¡´ÉÇÑ ¾ÆÀÌÅÛ ¹øÈ£
		dropItemNum3 = 2;			//µå¶ø°¡´ÉÇÑ ¾ÆÀÌÅÛ ¹øÈ£
		break;
	case MONSTER_TYPE_GOLEMBOSS:
		_monsterImg = IMAGEMANAGER->findImage("°ñ·½º¸½º");
		//¹æÇâ°ªÀ¸·Î ¸Â´Â ¹æÇâ ÀÌ¹ÌÁö Ã£±â
		golemBossDirectImg(monDirect);//ÀÌ¹ÌÁö¹æÇâ
		//¸ó½ºÅÍ ÇÇ°İ¹üÀ§
		rc = RectMakeCenter(x, y,
			_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
		atk = 15;					//°ø°İ·Â
		maxHp = 100;				//Ã¼·Â
		currentHp = 100;				//ÇöÀçÃ¼·Â
		speed = 0;					//ÀÌµ¿¼Óµµ
		_x = x;						//ÃÊ±âÁÂÇ¥
		_y = y;
		dropItemNum1 = 1;			//µå¶ø°¡´ÉÇÑ ¾ÆÀÌÅÛ ¹øÈ£
		dropItemNum2 = 3;			//µå¶ø°¡´ÉÇÑ ¾ÆÀÌÅÛ ¹øÈ£
		dropItemNum3 = 2;			//µå¶ø°¡´ÉÇÑ ¾ÆÀÌÅÛ ¹øÈ£
		break;
	}

	//ÇØ´ç ¸ó½ºÅÍÀÇ º¤ÅÍ °ª ³Ö±â
	_monType = monType;			//¸ó½ºÅÍ Á¾·ù
	_monState = monState;		//¸ó½ºÅÍ »óÅÂ
	_monDirect = monDirect;		//¸ó½ºÅÍ ¹æÇâ
	count = 0;					//Ä«¿îÆ®
	_hpBar = new monsterProgressBar;
	_hpBar->init("images/monster/progressBarFront.bmp", "images/monster/progressBarBack.bmp", 0, 0, 50, 10);
	_hpBar->setGauge(currentHp, maxHp);
	_hpBar->setX(x - 25);
	_hpBar->setY(y - 70);
	return S_OK;
}

void monster::release()
{
}

void monster::update()
{
	viewProgressBar();
	animation();
}

void monster::render()
{
	draw();
}
//ÇÁ·¹ÀÓÀÌ¹ÌÁö ±×·ÁÁÜ
void monster::draw()
{
	//°ñ·½ÅÍ·¿ ·»´õ
	_monsterImg->aniRender(getMemDC(), rc.left, rc.top, _ani);
	_hpBar->render();
	//¸ó½ºÅÍ ÇÇ°İ¹üÀ§
	//RectangleMakeCenter(getMemDC(), (rc.left+rc.right)/2, (rc.top+rc.bottom)/2, _monsterImg->getFrameWidth()/2, _monsterImg->getFrameHeight()/2);
}

void monster::animation()
{

}
//°ø°İ
bool monster::attack(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect)
{
	switch (monType) {
	case MONSTER_TYPE_GOLEMTURRET:
		golemTurretAtk();
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

void monster::golemTurretDirectImg(MONSTER_DIRECTION monDirect)
{
	_monsterImg = IMAGEMANAGER->findImage("°ñ·½ÅÍ·¿");
	//¹æÇâ°ªÀ¸·Î ¸Â´Â ¹æÇâ ÀÌ¹ÌÁö Ã£±â
	switch (monDirect)
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

void monster::golemSoldierDirectImg(MONSTER_DIRECTION monDirect)
{
	_monsterImg = IMAGEMANAGER->findImage("°ñ·½¼ÖÀú");
	//¹æÇâ°ªÀ¸·Î ¸Â´Â ¹æÇâ ÀÌ¹ÌÁö Ã£±â
	switch (monDirect)
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

void monster::slimeGauntletDirectImg(MONSTER_DIRECTION monDirect)
{
	_monsterImg = IMAGEMANAGER->findImage("½½¶óÀÓ°ÇÆ²·¿");
	//¹æÇâ°ªÀ¸·Î ¸Â´Â ¹æÇâ ÀÌ¹ÌÁö Ã£±â
	switch (monDirect)
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

void monster::golemBossDirectImg(MONSTER_DIRECTION monDirect)
{
	_monsterImg = IMAGEMANAGER->findImage("°ñ·½º¸½º");
	//¹æÇâ°ªÀ¸·Î ¸Â´Â ¹æÇâ ÀÌ¹ÌÁö Ã£±â
	switch (monDirect)
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


//°ñ·½ÅÍ·¿°ø°İ
bool monster::golemTurretAtk()
{
	//if (monType == 0) {
	count++;
	//Ä«¿îÆ®°¡ 30ÀÏ¶§ °ø°İ
	if (count == 30)
	{
		//_rndFireCount = RND->getFromIntTo(1, 1000);
		count = 0;
		return true;
	}
	//}
	return false;
}

//°ñ·½¼ÖÁ®°ø°İ
bool monster::golemSoldierAtk(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect)
{
	//if (monType == 0) {
	count++;
	//Ä«¿îÆ®°¡ 30ÀÏ¶§ °ø°İ
	if (count == 300)
	{
		_monState = MONSTER_STATE_ATK;
		switch (monDirect) {
		case MONSTER_DIRECTION_LEFT:
			_monsterImg = IMAGEMANAGER->findImage("°ñ·½¼ÖÀú°ø°İ");
			rc = RectMakeH(rc.left, rc.bottom,
				_monsterImg->getFrameWidth() - 50, _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("°ñ·½¼ÖÀú°ø°İL");
			ANIMATIONMANAGER->start("°ñ·½¼ÖÀú°ø°İL");
			if (_monsterImg->getFrameX() == _monsterImg->getMaxFrameX())
			{
				_ani = ANIMATIONMANAGER->findAnimation("°ñ·½¼ÖÀú°ø°İL");
				ANIMATIONMANAGER->start("°ñ·½¼ÖÀú°ø°İL");
			}
			break;
		case MONSTER_DIRECTION_UP:
			_monsterImg = IMAGEMANAGER->findImage("°ñ·½¼ÖÀú°ø°İ");
			rc = RectMakeCenter((rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight() - 50);
			_ani = ANIMATIONMANAGER->findAnimation("°ñ·½¼ÖÀú°ø°İU");
			ANIMATIONMANAGER->start("°ñ·½¼ÖÀú°ø°İU");
			break;
		case MONSTER_DIRECTION_RIGHT:
			_monsterImg = IMAGEMANAGER->findImage("°ñ·½¼ÖÀú°ø°İ");
			rc = RectMakeCenter((rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2,
				_monsterImg->getFrameWidth() + 50, _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("°ñ·½¼ÖÀú°ø°İR");
			ANIMATIONMANAGER->start("°ñ·½¼ÖÀú°ø°İR");
			break;
		case MONSTER_DIRECTION_DOWN:
			_monsterImg = IMAGEMANAGER->findImage("°ñ·½¼ÖÀú°ø°İ");
			rc = RectMakeCenter((rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight() + 50);
			_ani = ANIMATIONMANAGER->findAnimation("°ñ·½¼ÖÀú°ø°İB");
			ANIMATIONMANAGER->start("°ñ·½¼ÖÀú°ø°İB");
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
	//Ä«¿îÆ®°¡ 30ÀÏ¶§ °ø°İ
	if (count == 300)
	{
		_monState = MONSTER_STATE_ATK;
		//_rndFireCount = RND->getFromIntTo(1, 1000);
		switch (monDirect) {
		case MONSTER_DIRECTION_LEFT:
			_monsterImg = IMAGEMANAGER->findImage("½½¶óÀÓ°ÇÆ²·¿°ø°İ");
			rc = RectMakeCenter((rc.left + rc.right) / 2 + 10, (rc.top + rc.bottom) / 2 + 35,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("½½¶óÀÓ°ÇÆ²·¿°ø°İL");
			ANIMATIONMANAGER->start("½½¶óÀÓ°ÇÆ²·¿°ø°İL");
			if (_monsterImg->getFrameX() == _monsterImg->getMaxFrameX())
			{
				_ani = ANIMATIONMANAGER->findAnimation("½½¶óÀÓ°ÇÆ²·¿L");
				ANIMATIONMANAGER->start("½½¶óÀÓ°ÇÆ²·¿L");
			}
			break;
		case MONSTER_DIRECTION_UP:
			_monsterImg = IMAGEMANAGER->findImage("½½¶óÀÓ°ÇÆ²·¿°ø°İ");
			rc = RectMakeCenter((rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2 + 40,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("½½¶óÀÓ°ÇÆ²·¿°ø°İU");
			ANIMATIONMANAGER->start("½½¶óÀÓ°ÇÆ²·¿°ø°İU");
			break;
		case MONSTER_DIRECTION_RIGHT:
			_monsterImg = IMAGEMANAGER->findImage("½½¶óÀÓ°ÇÆ²·¿°ø°İ");
			rc = RectMakeCenter((rc.left + rc.right) / 2 + 15, (rc.top + rc.bottom) / 2 + 25,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("½½¶óÀÓ°ÇÆ²·¿°ø°İR");
			ANIMATIONMANAGER->start("½½¶óÀÓ°ÇÆ²·¿°ø°İR");
			break;
		case MONSTER_DIRECTION_DOWN:
			_monsterImg = IMAGEMANAGER->findImage("½½¶óÀÓ°ÇÆ²·¿°ø°İ");
			rc = RectMakeCenter((rc.left + rc.right) / 2 + 10, (rc.top + rc.bottom) / 2 + 35,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight() + 50);
			_ani = ANIMATIONMANAGER->findAnimation("½½¶óÀÓ°ÇÆ²·¿°ø°İB");
			ANIMATIONMANAGER->start("½½¶óÀÓ°ÇÆ²·¿°ø°İB");
			break;
		}
		count = 0;
		return true;
	}
	//}
	return false;
}

bool monster::golemBossAtk(MONSTER_TYPE monType, MONSTER_DIRECTION monDirect)
{
	//if (monType == 0) {
	count++;
	//Ä«¿îÆ®°¡ 30ÀÏ¶§ °ø°İ
	if (count == 300)
	{
		_monState = MONSTER_STATE_ATK;
		//_rndFireCount = RND->getFromIntTo(1, 1000);
		switch (monDirect) {
		case MONSTER_DIRECTION_LEFT:
			_monsterImg = IMAGEMANAGER->findImage("°ñ·½º¸½º°ø°İ2");
			rc = RectMakeCenter((rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("°ñ·½º¸½º°ø°İ2L");
			ANIMATIONMANAGER->start("°ñ·½º¸½º°ø°İ2L");
			if (_monsterImg->getFrameX() == _monsterImg->getMaxFrameX())
			{
				_ani = ANIMATIONMANAGER->findAnimation("°ñ·½º¸½ºL");
				ANIMATIONMANAGER->start("°ñ·½º¸½ºL");
			}
			break;
		case MONSTER_DIRECTION_UP:
			_monsterImg = IMAGEMANAGER->findImage("°ñ·½º¸½º°ø°İ2");
			rc = RectMakeCenter((rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight() - 50);
			_ani = ANIMATIONMANAGER->findAnimation("°ñ·½º¸½º°ø°İ2U");
			ANIMATIONMANAGER->start("°ñ·½º¸½º°ø°İ2U");
			break;
		case MONSTER_DIRECTION_RIGHT:
			_monsterImg = IMAGEMANAGER->findImage("°ñ·½º¸½º°ø°İ2");
			rc = RectMakeCenter((rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2,
				_monsterImg->getFrameWidth() + 50, _monsterImg->getFrameHeight());
			_ani = ANIMATIONMANAGER->findAnimation("°ñ·½º¸½º°ø°İ2R");
			ANIMATIONMANAGER->start("°ñ·½º¸½º°ø°İ2R");
			break;
		case MONSTER_DIRECTION_DOWN:
			_monsterImg = IMAGEMANAGER->findImage("°ñ·½º¸½º°ø°İ2");
			rc = RectMakeCenter((rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2,
				_monsterImg->getFrameWidth(), _monsterImg->getFrameHeight() + 50);
			_ani = ANIMATIONMANAGER->findAnimation("°ñ·½º¸½º°ø°İ2B");
			ANIMATIONMANAGER->start("°ñ·½º¸½º°ø°İ2B");
			break;
		}
		count = 0;
		return true;
	}
	//}
	return false;
}

//Ã¼·Â º¸¿©ÁÖ´Â ÇÔ¼ö
void monster::viewProgressBar()
{
	_hpBar->setGauge(currentHp, maxHp);
	_hpBar->update();
}