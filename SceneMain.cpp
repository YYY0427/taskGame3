#include "DxLib.h"
#include <cassert>
#include "SceneMain.h"
#include "player.h"
#include "map.h"
#include "enemyUnchi.h"
#include "ShotNormal.h"
#include "ShotEnemyNormal.h"

SceneMain::SceneMain()
{
	for (auto& handle : m_hPlayerGraphic)
	{
		handle = -1;
	}
	for (auto& handle : m_hPlayerDamageGraphic)
	{
		handle = -1;
	}
	m_hShotGraphic = -1;
	m_hEnemyUnchiGraphic = -1;
	m_hMapGraphic = -1;
	m_hShotEnemyUnchiGraphic = -1;
	m_hEnemyUnchiDamageGraphic = -1;
	m_waitFrame = 0;
	m_waitFrame2 = 0;
	m_enemyDrawCounter = 0;
	m_playerDrawCounter = 0;
	m_enemyDamageFlag = false;
	m_playerDamageFlag = false;
}
SceneMain::~SceneMain()
{

}

//初期化
void SceneMain::init()
{
				/* ======= 画像のロード ========*/
	LoadDivGraph("playerImage/sasisuseso.png", Player::kGraphicDivNum,			//プレイヤーのロード
		Player::kGraphicDivX, Player::kGraphicDivY,	
		Player::kGraphicSizeX, Player::kGraphicSizeY, m_hPlayerGraphic);

	LoadDivGraph("playerImage/sasisusesodamage.png", Player::kGraphicDivNum,	//プレイヤーのダメージ表示のロード
		Player::kGraphicDivX, Player::kGraphicDivY,
		Player::kGraphicSizeX, Player::kGraphicSizeY, m_hPlayerDamageGraphic);
	m_hShotGraphic = LoadGraph("shotImage/13.png");								//弾のロード
	m_hMapGraphic = LoadGraph("mapImage/map3.png");								//マップのロード
	m_hEnemyUnchiGraphic = LoadGraph("enemyImage/enemy1.png");					//敵のロード
	m_hEnemyUnchiDamageGraphic = LoadGraph("enemyImage/enemy1damage.png");		//敵のダメージ表示のロード
	m_hShotEnemyUnchiGraphic = LoadGraph("enemyShotImage/enemy1.png");			//敵の弾のロード
	
				/* ======= ハンドルの設定 ======= */
	m_player.setMapHandle(m_hMapGraphic);
	m_enemyUnchi.setMapHandle(m_hMapGraphic);
	m_enemyUnchi.setHandle(m_hEnemyUnchiGraphic);
	m_enemyUnchi.setDamageHandle(m_hEnemyUnchiDamageGraphic);
	m_map.setHandle(m_hMapGraphic);

				/* ======= 画像のサイズの取得 ======= */
	GetGraphSizeF(m_hEnemyUnchiGraphic, &m_enemySize.x, &m_enemySize.y);
	GetGraphSizeF(m_hShotEnemyUnchiGraphic, &m_shotEnemySize.x, &m_shotEnemySize.y);
	GetGraphSizeF(m_hShotGraphic, &m_shotPlayerSize.x, &m_shotPlayerSize.y);

				/* ======= 初期化 ======= */
	for (int i = 0; i < Player::kGraphicDivNum; i++)
	{
		m_player.setHandle(i, m_hPlayerGraphic[i]);
		m_player.setDamageHandle(i, m_hPlayerDamageGraphic[i]);
	}
	m_playerDamageFlag = false;
	m_enemyDamageFlag = false;
	m_waitFrame = 0;
	m_enemyDrawCounter = 0;
	m_playerDrawCounter = 0;

	m_player.setMain(this);
	m_enemyUnchi.setMain(this);
	m_player.init();
	m_enemyUnchi.init();
	m_map.init();
	m_display.init();
}

// 終了処理
void SceneMain::end()
{
	//グラフィックアンロード
	for (auto& handle : m_hPlayerGraphic)
	{
		DeleteGraph(handle);
	}
	for (auto& handle : m_hPlayerDamageGraphic)
	{
		DeleteGraph(handle);
	}
	DeleteGraph(m_hShotGraphic);
	DeleteGraph(m_hMapGraphic);
	DeleteGraph(m_hEnemyUnchiGraphic);
	DeleteGraph(m_hShotEnemyUnchiGraphic);
	DeleteGraph(m_hEnemyUnchiDamageGraphic);

	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);

		delete pShot;
		pShot = nullptr;
	}
}

// 毎フレームの処理
void SceneMain::update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	std::vector<ShotBase*>::iterator it = m_pShotVt.begin();
	while (it != m_pShotVt.end())
	{
		auto& pShot = (*it);
		assert(pShot);
		pShot->update();
		if (!pShot->isExist())
		{
			delete pShot;
			pShot = nullptr;

			//vectorの要素削除
			it = m_pShotVt.erase(it);
			continue;
		}
		it++;
	}

	m_map.update();
	m_player.update();
	m_enemyUnchi.update();

	//敵とプレイヤーが当たった場合の無敵時間
	if (m_waitFrame > 0)
	{
		m_waitFrame--;
		if (m_waitFrame <= 0)
		{
			m_waitFrame = 0;
		}
	}
	//敵の弾とプレイヤーが当たった場合の無敵時間
	if (m_waitFrame2 > 0)
	{
		m_waitFrame2--;
		if (m_waitFrame2 <= 0)
		{
			m_waitFrame2 = 0;
		}
	}
	//敵とプレイヤーが当たった場合
	if (enemyPlayerCollision() && m_waitFrame == 0)
	{
		//プレイヤーのライフを減らす
		m_display.enemyPlayerCollision();
		m_playerDamageFlag = true;
		m_playerDrawCounter = 0;
		m_waitFrame = 70;
	}
	//敵の弾とプレイヤーが当たった場合
	if (enemyShotPlayerCollision() && m_waitFrame2 == 0)
	{
		m_display.enemyPlayerCollision();
		m_playerDamageFlag = true;
		m_playerDrawCounter = 0;
		m_waitFrame2 = 20;
	}
	//敵が存在している場合のみ実行する
	if (m_enemyUnchi.isExist())
	{
		//プレイヤーの弾と敵が当たった場合
		if (playerShotEnemyCollision())
		{
			m_display.defeatScore();
			m_enemyUnchi.enemyLife();
			m_enemyDamageFlag = true;
			m_enemyDrawCounter = 0;
		}
	}
}

// 毎フレームの描画
void SceneMain::draw()
{
	m_map.draw();
	m_display.draw();
	if (m_playerDamageFlag)
	{
		m_player.damageDraw();
		m_playerDrawCounter++;
		if (m_playerDrawCounter > 20)
		{
			m_playerDamageFlag = false;
		}
	}
	else
	{
		m_player.draw();
	}

	if (m_enemyDamageFlag)
	{
		m_enemyUnchi.drawDamage();
		m_enemyDrawCounter++;
		if (m_enemyDrawCounter > 20)
		{
			m_enemyDamageFlag = false;
		}
	}
	else
	{
		m_enemyUnchi.draw();
	}

	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);
		pShot->draw();
	}
}

//敵とプレイヤーの当たり判定
bool SceneMain::enemyPlayerCollision()
{
	float playerLeft = m_player.getPos().x;
	float playerRight = m_player.getPos().x + m_player.getSize().x / 2;
	float playerTop = m_player.getPos().y;
	float playerBottom = m_player.getPos().y + m_player.getSize().y;

	float enemyUnchiLeft = m_enemyUnchi.getPos().x;
	float enemyUnchiRight = m_enemyUnchi.getPos().x + m_enemyUnchi.getSize().x;
	float enemyUnchiTop = m_enemyUnchi.getPos().y;
	float enemyUnchiBottom = m_enemyUnchi.getPos().y + m_enemyUnchi.getSize().y;

	if (playerLeft > enemyUnchiRight)	return false;
	if (playerRight < enemyUnchiLeft)	return false;
	if (playerTop > enemyUnchiBottom)	return false;
	if (playerBottom < enemyUnchiTop)	return false;

	return true;
}

//プレイヤーの弾と敵の当たり判定
bool SceneMain::playerShotEnemyCollision()
{
	std::vector<ShotBase*>::iterator it = m_pShotVt.begin();
	while (it != m_pShotVt.end())
	{
		auto& pShot = (*it);
		assert(pShot);

		float shotLeft = pShot->getPos().x;
		float shotRight = pShot->getPos().x + m_shotPlayerSize.x;
		float shotTop = pShot->getPos().y + 20;
		float shotBottom = pShot->getPos().y + m_shotPlayerSize.y;

		float enemyLeft = m_enemyUnchi.getPos().x;
		float enemyRight = m_enemyUnchi.getPos().x + m_enemySize.x;
		float enemyTop = m_enemyUnchi.getPos().y;
		float enemyBottom = m_enemyUnchi.getPos().y + m_enemySize.y - 35;

		if (enemyLeft > shotRight)
		{
			it++;
			continue;
		}
		if (enemyRight < shotLeft)
		{
			it++;
			continue;
		}
		if (enemyTop > shotBottom)
		{
			it++;
			continue;
		}
		if (enemyBottom < shotTop)
		{
			it++;
			continue;
		}
		return true;
	}
	return false;
}

//敵の弾とプレイヤーの当たり判定
bool SceneMain::enemyShotPlayerCollision()
{
	std::vector<ShotBase*>::iterator it = m_pShotVt.begin();
	while (it != m_pShotVt.end())
	{
		auto& pShot = (*it);
		assert(pShot);

		float shotLeft = pShot->getPos().x;
		float shotRight = pShot->getPos().x + m_shotEnemySize.x;
		float shotTop = pShot->getPos().y;
		float shotBottom = pShot->getPos().y + m_shotEnemySize.y;

		float playerLeft = m_player.getPos().x;
		float playerRight = m_player.getPos().x + m_player.kGraphicSizeX;
		float playerTop = m_player.getPos().y + 35;
		float playerBottom = m_player.getPos().y + m_player.kGraphicSizeY;

		if (playerLeft > shotRight)
		{
			it++;
			continue;
		}
		if (playerRight < shotLeft)
		{
			it++;
			continue;
		}
		if (playerTop > shotBottom)
		{
			it++;
			continue;
		}
		if (playerBottom < shotTop)
		{
			it++;
			continue;
		}
		return true;
	}
	return false;
}

bool SceneMain::createShotNormal(Vec2 pos)
{
	ShotNormal* pShot = new ShotNormal;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);

	return true;
}

bool SceneMain::createShotEnemyNormal(Vec2 pos)
{
	ShotEnemyNormal* pShot = new ShotEnemyNormal;
	pShot->setHandle(m_hShotEnemyUnchiGraphic);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);

	return true;
}