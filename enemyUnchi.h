#pragma once

#include "Vec2.h"

class SceneMain;

class enemyUnchi
{
public:
	enemyUnchi();
	virtual ~enemyUnchi();

	//初期化
	void init();
	//更新
	void update();
	//表示
	void draw();
	void drawDamage();
	//敵のHP処理
	void enemyLife();
	int  getEnemyLife()const { return m_enemyLife; }
	//SceneMainクラスのポインタ設定
	void setMain(SceneMain* pMain) { m_pMain = pMain; }
	//ハンドル設定
	void setHandle(int handle) { m_handle = handle; }
	void setMapHandle(int mapHandle) { m_mapHandle = mapHandle; }
	void setDamageHandle(int damageHandle) { m_damageHandle = damageHandle; }
	//存在するか
	bool isExist() const { return m_isExist; }
	//情報の取得
	Vec2 getPos() const { return m_pos; }
	//サイズの取得
	Vec2 getSize() const { return m_enemySize; }
	

private:
	SceneMain* m_pMain;		//SceneMainのポインタ
	Vec2 m_mapSize;			//マップのサイズ
	int m_randNum;			//ランダムな数字
	int m_mapHandle;		//マップのハンドル
	int m_damageHandle;

	//敵
	int m_handle;			// グラフィックハンドル
	int m_inCount;			//何秒で画面に入ってくるか
	int m_randInterval;		//動きの間隔
	int m_enemyLife;		//敵のHP
	int m_waitFrame;

	Vec2 m_pos;				//敵の表示位置
	Vec2 m_vec;				//敵の移動
	Vec2 m_enemySize;		//敵のサイズ

	bool m_isExist;			//存在するか
	bool m_randMove;		//ランダムな動き

	//弾
	int m_shotTime;			//弾の発射までの時間
	float m_shotInterval;	//弾の発射間隔
	bool m_shotStart;		//弾を発射するかしないか
};