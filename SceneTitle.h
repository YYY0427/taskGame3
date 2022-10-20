#pragma once
#include "SceneBase.h"
#include "selectMenu.h"

class SceneTitle : public SceneBase
{
public:
	SceneTitle()
	{
		m_textPosY = 0;
		m_textVecY = 0;
		m_isGameStart = false;
		m_isGameEnd = false;
	}
	virtual ~SceneTitle() {}


	virtual void init();
	virtual void end();

	virtual void update();
	virtual void draw();


	virtual bool isGameStart() { return m_isGameStart; }
	virtual bool getisGameEnd() { return m_isGameEnd; }


private:
	// テキスト表示位置変更
	int m_textPosY;
	int m_textVecY;

	SelectMenu m_menu;

	bool m_isGameStart;
	bool m_isGameEnd;
};