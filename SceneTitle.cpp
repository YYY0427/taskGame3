#include "SceneTitle.h"
#include "DxLib.h"
#include "SceneTest.h"
#include "SceneMain.h"

void SceneTitle::init()
{
	m_isEnd = false;
	m_handle = LoadGraph("data/Title.jpg");
	x = 0;
	y = 0;
}

SceneBase* SceneTitle::update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	//ゲームスタート
	if (padState & PAD_INPUT_1)
	{
		return(new SceneMain);
	}
	//ルール説明
	else if (padState & PAD_INPUT_8)
	{
		return(new SceneTest);
	}
	return this;
}

void SceneTitle::draw()
{
	DrawGraph(x, y, m_handle, false);
	DrawString(0, m_textPosY, "タイトル", GetColor(255, 255, 255));
	DrawString(0, m_textPosY + 20, "ゲームスタート->Aボタン", GetColor(255, 255, 255));
	DrawString(0, m_textPosY + 40, "オプション->STARTボタン", GetColor(255, 255, 255));
}