#include "Display.h"
#include "DxLib.h"

Display::Display()
{
	playerLife = 0;
	score = 0;
}

void Display::init()
{
	playerLife = 10;
	score = 0;
}

Display::~Display()
{

}

//敵とプレイヤーが当たった場合
void Display::enemyPlayerCollision()
{
	playerLife--;
}

void Display::defeatScore()
{
	score++;
}

void Display::draw()
{
	DrawFormatString(400, 50, GetColor(255, 255, 255),"LIFE  %d", playerLife);
	DrawFormatString(400, 100, GetColor(255, 255, 255), "SCORE  %d", score);
}