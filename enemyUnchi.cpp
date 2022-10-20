#include "enemyUnchi.h"
#include "game.h"
#include "DxLib.h"
#include "SceneMain.h"

namespace
{
	//íeÇÃà⁄ìÆ
	constexpr float kEnemyShotX = 0.0f;
	constexpr float kEnemyShotY = 5.0f;
	//ÉVÉáÉbÉgÇÃî≠éÀä‘äu
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
	//ìG
	m_pos.x = 150;				//ìGÇÃxç¿ïW
	m_pos.y = -50;				//ìGÇÃyç¿ïW

	m_vec.x = 0.0f;				//ìGÇÃxç¿ïWÇÃà⁄ìÆÇÃëÂÇ´Ç≥
	m_vec.y = 3.0f;				//ìGÇÃyç¿ïWÇÃà⁄ìÆÇÃëÂÇ´Ç≥

	m_enemyLife = 100;			//ìGÇÃHP
	m_inCount = 120;			//ìGÇ™ì¸Ç¡ÇƒÇ≠ÇÈÇ‹Ç≈âΩïbë“Ç¬Ç©(60Ç≈1ïbë“Ç¬)
	m_randInterval = 180;		//ìGÇÃìÆÇ´ÇÃä‘äu
	m_isExist = false;			//ìGÇ™ë∂ç›ÇµÇƒÇ¢ÇÈÇ©
	m_randMove = false;			//ÉâÉìÉ_ÉÄÇ»ìÆÇ´ÇÇ∑ÇÈÇ©
	m_waitFrame = 8;
	m_randNum = GetRand(3);

	//íe
	m_shotTime = 120;			//ìGÇ™íeÇî≠éÀÇ∑ÇÈÇ‹Ç≈âΩïbë“Ç¬Ç©(60Ç≈1ïbë“Ç¬)
	m_shotInterval = 0.0f;		//íeÇÃî≠éÀä‘äu
	m_shotStart = false;		//íeÇÃî≠éÀÇäJén

	//ìGÇÃâÊëúÇÃÉTÉCÉYÇÃéÊìæ
	GetGraphSizeF(m_handle, &m_enemySize.x, &m_enemySize.y);
	GetGraphSizeF(m_mapHandle, &m_mapSize.x, &m_mapSize.y);
}

void enemyUnchi::update()
{
	//3ïbë“Ç¬
	if (m_inCount > 0)
	{
		m_inCount--;
		return;
	}
	//3ïbåoÇ¡ÇΩèÍçá
	if (m_inCount == 0)
	{
		m_isExist = true;	//ìGÇÃë∂ç›ÇäJén
		m_inCount--;		//Ç±ÇÃifï™Ç…éüÇ©ÇÁì¸ÇÁÇ»Ç¢ÇÊÇ§Ç…Ç∑ÇÈ
	}
	
	m_waitFrame--;
	if (m_waitFrame == 0)
	{
		m_randNum = GetRand(3);
		m_waitFrame = 8;
	}

	//ìGÇ™ë∂ç›ÇµÇƒÇ¢ÇÈèÍçá
	if (m_isExist)
	{
		//âÊñ ÇÃê^ÇÒíÜãﬂÇ≠Ç‹Ç≈óàÇΩÇÁìÆÇ´ÇäJénÇ∑ÇÈ
		if (m_pos.y > Game::kScreenHeight / 2 - 100)
		{
			m_randMove = true;
		}
		if (m_randMove)
		{
			//4ï™ÇÃ1ÇÃämóßÇ≈4ï˚å¸Ç…à⁄ìÆÇ∑ÇÈ
			if (m_randNum == 0)
			{
				m_pos.x += 4;
				if (m_pos.x > m_mapSize.x - m_enemySize.x)
				{
					m_pos.x = m_mapSize.x - m_enemySize.x;
				}
			}
			else if (m_randNum == 1)
			{
				m_pos.x -= 4;
				if (m_pos.x < 0)
				{
					m_pos.x = 0;
				}
			}
			else if (m_randNum == 2)
			{
				m_pos.y += 4;
				if (m_pos.y > Game::kScreenHeight / 2 - 100 - m_enemySize.y)
				{
					m_pos.y = Game::kScreenHeight / 2 - 100 - m_enemySize.y;
				}
			}
			else
			{
				m_pos.y -= 4;
				if (m_pos.y < 0)
				{
					m_pos.y = 0;
				}
			}
		}
		//âÊñ ÇÃîºï™Ç‹Ç≈ÇÃìûíBÇ∑ÇÈÇ‹Ç≈ÇÃä‘
		else
		{
			m_pos += m_vec;
		}

		//ìGÇ™âÊñ ì‡Ç…ë∂ç›ÇµÇƒÇ¢ÇƒéwíËÇµÇΩéûä‘åoÇ¡ÇΩèÍçá
		m_shotTime--;
		if (m_shotTime < 0)
		{
			m_shotStart = true;		//íeÇÃî≠éÀÇäJén
		}

		//ìGÇÃíeÇÃÉCÉìÉ^Å[ÉoÉã
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
	//falseÇ»ÇÁé¿çsÇµÇ»Ç¢
	if (!m_isExist)return;
	//ìGÇÃï\é¶
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);	
}

void enemyUnchi::drawDamage()
{
	//falseÇ»ÇÁé¿çsÇµÇ»Ç¢
	if (!m_isExist)return;
	//ìGÇÃï\é¶
	DrawGraphF(m_pos.x, m_pos.y, m_damageHandle, true);
}

void enemyUnchi::enemyLife()
{
	m_enemyLife--;
	//ìGÇÃHPÇ™0à»â∫Ç…Ç»Ç¡ÇΩèÍçá
	if (m_enemyLife <= 0)
	{
		//ìGÇÃë∂ç›Çè¡Ç∑
		m_isExist = false;
	}
}
