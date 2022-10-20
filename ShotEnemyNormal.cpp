#include "ShotEnemyNormal.h"
#include "game.h"
#include "DxLib.h"

namespace
{
	constexpr float kShotSpeed = 8.0f;
}

void ShotEnemyNormal::start(Vec2 pos)
{
	ShotBase::start(pos);

	m_vec.x = 0.0f;
	m_vec.y = kShotSpeed;
}

void ShotEnemyNormal::update()
{
	if (!m_isExist)return;
	m_pos += m_vec;

	if (m_pos.x > Game::kScreenWidth)
	{
		m_isExist = false;
	}
}

// •\Ž¦
void ShotEnemyNormal::draw()
{
	if (!m_isExist)return;
	DrawGraphF(m_pos.x - 10, m_pos.y + 35, m_handle, true);
}