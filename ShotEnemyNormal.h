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

	//�V���b�g�J�n
	virtual void start(Vec2 pos);
	// �X�V
	virtual void update();
	//�\��
	virtual void draw();
};