#pragma once

#include "SceneTitle.h"
#include "SceneMain.h"

class SceneManager
{
public:
	// ƒV[ƒ“‚Ìí—Ş’è‹`
	typedef enum SceneKind
	{
		kSceneKindTitle,
		kSceneKindMain,

		kSceneKindNum
	}SceneKind;

public:
	SceneManager();
	virtual ~SceneManager();

	void init(SceneKind kind = kSceneKindTitle);
	void end();

	void update();
	void draw();

	bool getisGameEnd() { return m_isGameEnd; }

private:
	SceneKind	m_kind;

	SceneTitle	m_title;
	SceneMain	m_main;

	bool m_isGameEnd;
};