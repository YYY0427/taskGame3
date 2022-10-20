#include "SceneTitle.h"
#include "DxLib.h"
#include "Pad.h"

void SceneTitle::init()
{
	m_textPosY = 0;
	m_textVecY = 4;

	m_isGameStart = false;
	m_isGameEnd = false;
	
	m_menu.init();
	m_menu.addItem("�Q�[���X�^�[�g");
	m_menu.addItem("�Q�[���I��");
	m_menu.setPos(256, 256);

	m_menu.setCursor();
}

void SceneTitle::end()
{
	m_menu.end();
}

void SceneTitle::update()
{
	// �����̈ړ�
	m_textPosY += m_textVecY;
	if (m_textPosY < 0)
	{
		m_textPosY = 0;
		m_textVecY = 4;
	}
	if (m_textPosY > 200)
	{
		m_textPosY = 200;
		m_textVecY = -4;
	}

	m_menu.update();

	m_isGameStart = m_menu.getisGameStart();

	m_isGameEnd = m_menu.getisGameEnd();
}

void SceneTitle::draw()
{
	//DrawString(0, m_textPosY,"�^�C�g�����",GetColor(255,255,255));

	m_menu.draw();
}