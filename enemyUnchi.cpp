#include "enemyUnchi.h"
#include "game.h"
#include "DxLib.h"
#include "SceneMain.h"

namespace
{
	//弾の移動
	constexpr float kEnemyShotX = 0.0f;
	constexpr float kEnemyShotY = 5.0f;
	//ショットの発射間隔
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
	//敵
	m_pos.x = 150;				//敵のx座標
	m_pos.y = -50;				//敵のy座標

	m_vec.x = 0.0f;				//敵のx座標の移動の大きさ
	m_vec.y = 3.0f;				//敵のy座標の移動の大きさ

	m_enemyLife = 100;			//敵のHP
	m_inCount = 120;			//敵が入ってくるまで何秒待つか(60で1秒待つ)
	m_randInterval = 180;		//敵の動きの間隔
	m_isExist = false;			//敵が存在しているか
	m_randMove = false;			//ランダムな動きをするか
	m_waitFrame = 8;
	m_randNum = GetRand(3);

	//弾
	m_shotTime = 120;			//敵が弾を発射するまで何秒待つか(60で1秒待つ)
	m_shotInterval = 0.0f;		//弾の発射間隔
	m_shotStart = false;		//弾の発射を開始

	//敵の画像のサイズの取得
	GetGraphSizeF(m_handle, &m_enemySize.x, &m_enemySize.y);
	GetGraphSizeF(m_mapHandle, &m_mapSize.x, &m_mapSize.y);
}

void enemyUnchi::update()
{
	//3秒待つ
	if (m_inCount > 0)
	{
		m_inCount--;
		return;
	}
	//3秒経った場合
	if (m_inCount == 0)
	{
		m_isExist = true;	//敵の存在を開始
		m_inCount--;		//このif分に次から入らないようにする
	}
	
	m_waitFrame--;
	if (m_waitFrame == 0)
	{
		m_randNum = GetRand(3);
		m_waitFrame = 8;
	}

	//敵が存在している場合
	if (m_isExist)
	{
		//画面の真ん中近くまで来たら動きを開始する
		if (m_pos.y > Game::kScreenHeight / 2 - 100)
		{
			m_randMove = true;
		}
		if (m_randMove)
		{
			//4分の1の確立で4方向に移動する
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
		//画面の半分までの到達するまでの間
		else
		{
			m_pos += m_vec;
		}

		//敵が画面内に存在していて指定した時間経った場合
		m_shotTime--;
		if (m_shotTime < 0)
		{
			m_shotStart = true;		//弾の発射を開始
		}

		//敵の弾のインターバル
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
	//falseなら実行しない
	if (!m_isExist)return;
	//敵の表示
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);	
}

void enemyUnchi::drawDamage()
{
	//falseなら実行しない
	if (!m_isExist)return;
	//敵の表示
	DrawGraphF(m_pos.x, m_pos.y, m_damageHandle, true);
}

void enemyUnchi::enemyLife()
{
	m_enemyLife--;
	//敵のHPが0以下になった場合
	if (m_enemyLife <= 0)
	{
		//敵の存在を消す
		m_isExist = false;
	}
}
