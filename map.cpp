#include "map.h"
#include "DxLib.h"
#include "game.h"
#include "SceneMain.h"

Map::Map()
{
	//初期化
	m_handle = -1;
}

Map::~Map()
{

}

void Map::init()
{ 
	//画像のサイズの取得
	GetGraphSizeF(m_handle, &m_mapSize.x, &m_mapSize.y);

	//画像の位置の初期化
	m_pos.x = 0.0f;
	m_pos.y = 0.0f;
}

void Map::update()
{
	//背景の移動
	m_pos.y += 1.0f;

	//画像の位置がm_mapSize.yまで到達したら画像の位置を戻す
	if (m_pos.y == m_mapSize.y)
		m_pos.y = 0.0f;
}

void Map::draw()
{
	//1枚目の表示
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
	//2枚目の表示
	DrawGraphF(m_pos.x, m_pos.y - m_mapSize.y, m_handle, true);
}