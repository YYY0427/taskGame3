#include "ShotNormal.h"
#include "game.h"
#include "DxLib.h"

namespace
{
	constexpr float kShotSpeed = 8.0f;
}

void ShotNormal::start(Vec2 pos)
{
	ShotBase::start(pos);

	m_vec.x = 0.0f;
	m_vec.y = kShotSpeed;
}

void ShotNormal::update()
{
	if (!m_isExist)return;
	m_pos -= m_vec;

	if (m_pos.x > Game::kScreenWidth)
	{
		m_isExist = false;
	}
}

// •\Ž¦
void ShotNormal::draw()
{
	if (!m_isExist)return;
	DrawGraphF(m_pos.x + 10, m_pos.y - 30, m_handle, true);
}