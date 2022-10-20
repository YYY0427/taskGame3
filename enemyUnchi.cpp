#include "enemyUnchi.h"
#include "game.h"
#include "DxLib.h"
#include "SceneMain.h"

namespace
{
	//’e‚ÌˆÚ“®
	constexpr float kEnemyShotX = 0.0f;
	constexpr float kEnemyShotY = 5.0f;
	//ƒVƒ‡ƒbƒg‚Ì”­ËŠÔŠu
	constexpr float kShotInterval = 60;
}

enemyUnchi::enemyUnchi()
{
	m_inCount = 0;
	m_isExist = false;
	m_randMove = false;
	m_randInterval = 0;
	m_enemyLife = 0;

	m_shotTime = 0;
	m_shotInterval = 0.0f;
	m_shotStart = false;

	m_randNum = 0;
	m_handle = -1;
	m_mapHandle = -1;
	m_pMain = nullptr;
}

enemyUnchi::~enemyUnchi()
{

}

void enemyUnchi::init()
{
	m_randNum = 0;				//ƒ‰ƒ“ƒ_ƒ€‚È”š

	//“G
	m_pos.x = 150;				//“G‚ÌxÀ•W
	m_pos.y = -50;				//“G‚ÌyÀ•W

	m_vec.x = 0.0f;				//“G‚ÌxÀ•W‚ÌˆÚ“®‚Ì‘å‚«‚³
	m_vec.y = 3.0f;				//“G‚ÌyÀ•W‚ÌˆÚ“®‚Ì‘å‚«‚³

	m_enemyLife = 100;			//“G‚ÌHP
	m_inCount = 120;			//“G‚ª“ü‚Á‚Ä‚­‚é‚Ü‚Å‰½•b‘Ò‚Â‚©(60‚Å1•b‘Ò‚Â)
	m_randInterval = 180;		//“G‚Ì“®‚«‚ÌŠÔŠu
	m_isExist = false;			//“G‚ª‘¶İ‚µ‚Ä‚¢‚é‚©
	m_randMove = false;			//ƒ‰ƒ“ƒ_ƒ€‚È“®‚«‚ğ‚·‚é‚©

	//’e
	m_shotTime = 120;			//“G‚ª’e‚ğ”­Ë‚·‚é‚Ü‚Å‰½•b‘Ò‚Â‚©(60‚Å1•b‘Ò‚Â)
	m_shotInterval = 0.0f;		//’e‚Ì”­ËŠÔŠu
	m_shotStart = false;		//’e‚Ì”­Ë‚ğŠJn

	//“G‚Ì‰æ‘œ‚ÌƒTƒCƒY‚Ìæ“¾
	GetGraphSizeF(m_handle, &m_enemySize.x, &m_enemySize.y);
	GetGraphSizeF(m_mapHandle, &m_mapSize.x, &m_mapSize.y);
}

void enemyUnchi::update()
{
	//3•b‘Ò‚Â
	if (m_inCount > 0)
	{
		m_inCount--;
		return;
	}
	//3•bŒo‚Á‚½ê‡
	if (m_inCount == 0)
	{
		m_isExist = true;	//“G‚Ì‘¶İ‚ğŠJn
		m_inCount--;		//‚±‚Ìif•ª‚ÉŸ‚©‚ç“ü‚ç‚È‚¢‚æ‚¤‚É‚·‚é
	}
	
	//“G‚ª‘¶İ‚µ‚Ä‚¢‚éê‡
	if (m_isExist)
	{
		//‰æ–Ê‚Ì^‚ñ’†‹ß‚­‚Ü‚Å—ˆ‚½‚ç“®‚«‚ğŠJn‚·‚é
		if (m_pos.y > Game::kScreenHeight / 2 - 100)
		{
			m_randMove = true;
		}
		if (m_randMove)
		{
			//4•ª‚Ì1‚ÌŠm—§‚Å4•ûŒü‚ÉˆÚ“®‚·‚é
			m_randNum = GetRand(99);
			if (m_randNum < 25)
			{
				m_pos.x += 8;
				if (m_pos.x > m_mapSize.x - m_enemySize.x)
				{
					m_pos.x = m_mapSize.x - m_enemySize.x;
				}
			}
			else if (m_randNum < 25 + 25)
			{
				m_pos.x -= 8;
				if (m_pos.x < 0)
				{
					m_pos.x = 0;
				}
			}
			else if (m_randNum < 25 + 25 + 25)
			{
				m_pos.y += 8;
				if (m_pos.y > Game::kScreenHeight / 2 - 100 - m_enemySize.y)
				{
					m_pos.y = Game::kScreenHeight / 2 - 100 - m_enemySize.y;
				}
			}
			else
			{
				m_pos.y -= 8;
				if (m_pos.y < 0)
				{
					m_pos.y = 0;
				}
			}
		}
		//‰æ–Ê‚Ì”¼•ª‚Ü‚Å‚Ì“’B‚·‚é‚Ü‚Å‚ÌŠÔ
		else
		{
			m_pos += m_vec;
		}

		//“G‚ª‰æ–Ê“à‚É‘¶İ‚µ‚Ä‚¢‚Äw’è‚µ‚½ŠÔŒo‚Á‚½ê‡
		m_shotTime--;
		if (m_shotTime < 0)
		{
			m_shotStart = true;		//’e‚Ì”­Ë‚ğŠJn
		}

		//“G‚Ì’e‚ÌƒCƒ“ƒ^[ƒoƒ‹
		m_shotInterval--;
		if (m_shotInterval < 0) m_shotInterval = 0;

		if (m_shotInterval <= 0)
		{
			if (m_shotStart)
			{
				if (m_pMain->createShotEnemyNormal(getPos()))
				{
					m_shotInterval = kShotInterval;
				}
			}
		}
	}
}

void enemyUnchi::draw()
{
	//false‚È‚çÀs‚µ‚È‚¢
	if (!m_isExist)return;
	//“G‚Ì•\¦
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);	
}

void enemyUnchi::drawDamage()
{
	//false‚È‚çÀs‚µ‚È‚¢
	if (!m_isExist)return;
	//“G‚Ì•\¦
	DrawGraphF(m_pos.x, m_pos.y, m_damageHandle, true);
}

void enemyUnchi::enemyLife()
{
	m_enemyLife--;
	//“G‚ÌHP‚ª0ˆÈ‰º‚É‚È‚Á‚½ê‡
	if (m_enemyLife <= 0)
	{
		//“G‚Ì‘¶İ‚ğÁ‚·
		m_isExist = false;
	}
}
