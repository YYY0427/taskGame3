#include "DxLib.h"
#include "game.h"
#include "player.h"
#include "SceneMain.h"

namespace 
{
	//キャラクターアニメーション１コマ当たりのフレーム数
	constexpr int kAnimeChangeFrame = 8;
	//キャラクターの移動速度
	constexpr int kSpeedX = 4;
	constexpr int kSpeedY = 4;
	//ショットの発射間隔
	constexpr int  kShotInterval = 16;
}

Player::Player()
{
	//初期化
	for (auto& handle : m_handle)
	{
		handle = -1;
	}
	m_animeNo = 0;
	m_dirNo = 0;
	m_pMain = nullptr;
	m_shotInterval = 0;
	m_animeFrame = 0;
	m_mapHandle = -1;
	m_playerLife = 0;
}
Player::~Player()
{

}

void Player::init()
{
	//プレイヤーの初期位置
	m_pos.x = 160;
	m_pos.y = 300;

	//初期化
	m_vec.x = 0.0f;
	m_vec.y = 0.0f;

	m_animeNo = 0;
	m_animeFrame = 0;
	m_dirNo = 0;
	m_shotInterval = 0;
	m_playerLife = 10;

	m_playerSize.x = kGraphicSizeX;
	m_playerSize.y = kGraphicSizeY;

	//マップの画像のサイズの取得
	GetGraphSizeF(m_mapHandle, &m_mapSize.x, &m_mapSize.y);
}

void Player::update()
{
	// パッド(もしくはキーボード)からの入力を取得する
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	    /*　==== キャラクターのアニメーション ==== */
	//初期化
	bool isKey = false;

	if (padState & PAD_INPUT_UP || CheckHitKey(KEY_INPUT_W))
	{
		m_dirNo = 3;
		isKey = true;
	}
	if (padState & PAD_INPUT_DOWN || CheckHitKey(KEY_INPUT_S))
	{
		m_dirNo = 0;
		isKey = true;
	}
	if (padState & PAD_INPUT_LEFT || CheckHitKey(KEY_INPUT_A))
	{
		m_dirNo = 1;
		isKey = true;
	}
	if (padState & PAD_INPUT_RIGHT || CheckHitKey(KEY_INPUT_D))
	{
		m_dirNo = 2;
		isKey = true;
	}

	//キー入力があった場合フレームをプラス
	if (isKey)	m_animeFrame++;

	if (m_animeFrame >= kGraphicDivX * kAnimeChangeFrame)
	{
		m_animeFrame = 0;
	}

	int tempAnimeNo = m_animeFrame / kAnimeChangeFrame;
	m_animeNo = m_dirNo * kGraphicDivX + tempAnimeNo;


	     /* ==== ショットを撃つ処理 ==== */
	m_shotInterval--;
	if (m_shotInterval < 0)m_shotInterval = 0;

	if (m_shotInterval <= 0)
	{
		if (padState & PAD_INPUT_1)
		{
			if (m_pMain->createShotNormal(getPos()))
			{
				m_shotInterval = kShotInterval;
			}
		}
	}

	          /* ==== キャラクターの移動 ==== */
	if (padState & PAD_INPUT_UP || CheckHitKey(KEY_INPUT_W))
	{
		m_pos.y -= kSpeedY;
		//画面外に出そうな場合キャラクターの位置をとどめる
		if (m_pos.y < 0) 
			m_pos.y = 0;
	}
	else if (padState & PAD_INPUT_DOWN || CheckHitKey(KEY_INPUT_S))
	{
		m_pos.y += kSpeedY;
		//画面外に出そうな場合キャラクターの位置をとどめる
		if (m_pos.y > Game::kScreenHeight - kGraphicSizeY) 
			m_pos.y = Game::kScreenHeight - kGraphicSizeY;
	}
	else if (padState & PAD_INPUT_LEFT || CheckHitKey(KEY_INPUT_A))
	{
		m_pos.x -= kSpeedX;
		//画面外に出そうな場合キャラクターの位置をとどめる
		if (m_pos.x < 0)
			m_pos.x = 0;
	}
	else if (padState & PAD_INPUT_RIGHT || CheckHitKey(KEY_INPUT_D))
	{
		m_pos.x += kSpeedX;
		//画面外に出そうな場合キャラクターの位置をとどめる
		if (m_pos.x > m_mapSize.x - kGraphicSizeX)
				m_pos.x = m_mapSize.x - kGraphicSizeX;
	}
	else
	{

	}
}

void Player::draw()
{
	DrawGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_handle[m_animeNo], true);
}

void Player::damageDraw()
{
	DrawGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_damageHandle[m_animeNo], true);
}