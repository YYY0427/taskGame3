#pragma once

#include "Vec2.h"

class Map
{
public:
	Map();
	virtual ~Map();

	// グラフィックデータ設定
	void setHandle(int handle) { m_handle = handle; }
	// マップの初期化
	void init();
	// 処理
	void update();
	// 描画
	void draw();

private:
	//画像のハンドル
	int m_handle;
	//画像のサイズ
	Vec2 m_mapSize;
	// 表示位置
	Vec2 m_pos;
};