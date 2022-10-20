#pragma once

class Display
{
public:
	Display();
	virtual ~Display();

	void init();
	void draw();
	void enemyPlayerCollision();
	void defeatScore();

private:
	int playerLife;
	int score;
};