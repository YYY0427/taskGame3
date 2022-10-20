#pragma once

#include "Vec2.h"

class SceneMain;

class Player
{
public:
	//定数定義
	//プレイヤーグラフィック分割数
	static constexpr int kGraphicDivX = 3;
	static constexpr int kGraphicDivY = 4;
	static constexpr int kGraphicDivNum = kGraphicDivX * kGraphicDivY;

	//プレイヤーグラフィックサイズ　
	static constexpr int kGraphicSizeX = 40;
	static constexpr int kGraphicSizeY = 28;

public:
	Player();
	virtual ~Player();

	// グラフィックデータ設定
	void setHandle(int index, int handle) { m_handle[index] = handle; }
	void setMapHandle(int mapHandle) { m_mapHandle = mapHandle; }

	//SceneMainクラスのポインタ設定
	void setMain(SceneMain* pMain) { m_pMain = pMain; };

	// プレイヤーの初期化
	void init();

	// 処理
	void update();
	// 描画
	void draw();

	// 情報の取得
	Vec2 getPos() const { return m_pos; }
	Vec2 getSize() const { return m_playerSize; }

private:
	//画像のハンドル
	int m_handle[kGraphicDivNum];
	int m_mapHandle;

	//SceneMainのポインタ
	SceneMain* m_pMain;

	// 表示位置
	Vec2 m_pos;
	// 移動
	Vec2 m_vec;
	//マップの画像サイズ
	Vec2 m_mapSize;

	Vec2 m_playerSize;

	int m_playerLife;

	//キャラクターのアニメーション
	int m_animeNo;		//表示する番号
	int m_animeFrame;
	int m_dirNo;		//進行方向

	//ショット
	int m_shotInterval;
};