#pragma once

#include "ShotBase.h"

class ShotEnemyNormal : public ShotBase
{
public:
	ShotEnemyNormal()
	{

	}
	virtual ~ShotEnemyNormal()
	{

	}

	//ショット開始
	virtual void start(Vec2 pos);
	// 更新
	virtual void update();
	//表示
	virtual void draw();
};