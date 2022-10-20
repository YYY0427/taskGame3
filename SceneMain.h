#pragma once

#include <vector>
#include "map.h"
#include "player.h"
#include "ShotBase.h"
#include "enemyUnchi.h"
#include "SceneBase.h"

class SceneMain : public SceneBase 
{
public:
	SceneMain();
	virtual ~SceneMain();

	//初期化
	void init();
	// 終了処理
	void end();
	// 毎フレームの処理
	void update();
	// 毎フレームの描画
	void draw();
	//弾の生成
	bool createShotNormal(Vec2 pos);
	bool createShotEnemyNormal(Vec2 pos);

	/* ==== 当たり判定 ==== */
	//敵とプレイヤーの当たり判定
	bool enemyPlayerCollision();
	//敵の弾とプレイヤーの当たり判定
	bool enemyShotPlayerCollision();
	//プレイヤーの弾と敵の当たり判定
	bool playerShotEnemyCollision();
private:
	int m_playerLife;
	int m_enemyDrawCounter;
	int m_playerDrawCounter;
	bool m_enemyDamageFlag;
	bool m_playerDamageFlag;
	//ハンドル
	int m_hPlayerGraphic[Player::kGraphicDivNum];		//プレイヤーのグラフィックハンドル
	int m_hPlayerDamageGraphic[Player::kGraphicDivNum];	//プレイヤーのダメージのグラフィックハンドル
	int m_hShotGraphic;									//プレイヤーの弾のハンドル
	int m_hMapGraphic;									//マップのハンドル
	int m_hEnemyUnchiGraphic;							//敵のハンドル
	int m_hEnemyUnchiDamageGraphic;						//敵のダメージのハンドル
	int m_hShotEnemyUnchiGraphic;						//敵の弾のハンドル
	//無敵時間
	int m_waitFrame;									//敵とプレイヤーが当たった場合の無敵時間
	int m_waitFrame2;									//敵の弾とプレイヤーが当たった場合の無敵時間					
	//サイズ
	Vec2 m_shotEnemySize;								//敵の弾の画像サイズ
	Vec2 m_shotPlayerSize;								//プレイヤーの弾の画像のサイズ
	Vec2 m_enemySize;									//敵の画像サイズ
	//クラスの設定
	Player m_player;								
	Map m_map;
	enemyUnchi m_enemyUnchi;
	//vectorの設定
	std::vector<ShotBase*> m_pShotVt;
};