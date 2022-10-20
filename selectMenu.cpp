#include "selectMenu.h"
#include "DxLib.h"
#include "Pad.h"

namespace
{
	//メニュー項目の問題
	constexpr int kMenuItemInterval = 32;
}

SelectMenu::Item::Item()
{
	m_text = nullptr;
}

SelectMenu::Item::~Item()
{

}
void SelectMenu::Item::draw(int x, int y)
{
	DrawString(x, y, m_text, GetColor(255, 255, 255));
}

void SelectMenu::Item::setText(const char* text)
{
	m_text = text;
}
int SelectMenu::Item::getTextWidth()
{
	return GetDrawStringWidth(m_text, strlen(m_text));
}

//======================================================
//Cursor
//======================================================

SelectMenu::Cursor::Cursor()
{
	m_selectIndex = 0;
	m_repeatUp = 0;
	m_repeatDown = 0;
}

SelectMenu::Cursor::~Cursor()
{

}

void SelectMenu::Cursor::update()
{
	if (Pad::isPress(PAD_INPUT_UP))
	{
		if (m_repeatUp <= 0)
		{
			m_selectIndex--;
			m_repeatUp = 8;
			//上下ループ
			if (m_selectIndex < 0)
			{
				if (Pad::isTrigger(PAD_INPUT_UP))
				{
					m_selectIndex = m_itemNum - 1;
				}
				else
				{
					m_selectIndex = 0;
				}
			}
		}
		else
		{
			m_repeatUp--;
		}
	}
	else
	{
		m_repeatUp = 0;
	}
	if (Pad::isPress(PAD_INPUT_DOWN))
	{
		if (m_repeatDown <= 0)
		{
			m_selectIndex++;
			m_repeatDown = 8;
			if (m_selectIndex > m_itemNum - 1)
			{
				if (Pad::isTrigger(PAD_INPUT_DOWN))
				{
					m_selectIndex = 0;
				}
				else
				{
					m_selectIndex = m_itemNum - 1;
				}
			}
		}
		else
		{
			m_repeatDown--;
		}
	}
	else
	{
		m_repeatDown = 0;
	}

	if (Pad::isTrigger(PAD_INPUT_1)) {

		if (m_selectIndex == 0) {
			m_isGameStart = true;
		}

		if (m_selectIndex == 1) {
			m_isGameEnd = true;
		}

	}
}

void SelectMenu::Cursor::draw()
{
	int posX = m_menuPos.x;
	int posY = m_menuPos.y + kMenuItemInterval * m_selectIndex;

	DrawBox(posX, posY, posX + m_size.x, posY + m_size.y, GetColor(255, 0, 0), false);
}

//=======================================================
//SelectMenu
//=======================================================

SelectMenu::SelectMenu()
{

}

SelectMenu::~SelectMenu()
{

}

void SelectMenu::init()
{

}

void SelectMenu::end()
{
	for (auto& pItem : m_pItem)
	{
		delete pItem;
	}
	m_pItem.clear();
}

void SelectMenu::update()
{
	m_cursor.update();
}

void SelectMenu::draw()
{
	int width = getWindowWidth();
	int height = getWindowHeight();

	DrawBox(m_pos.x, m_pos.y, m_pos.x + width, m_pos.y + height, GetColor(64, 64, 64), true);
	for (int i = 0; i < m_pItem.size(); i++)
	{
		m_pItem[i]->draw(m_pos.x, m_pos.y + i * 32);
	}
	m_cursor.draw();
}

void SelectMenu::setCursor()
{
	m_cursor.setMenuPos(m_pos);
	m_cursor.setSize(Vec2(getWindowWidth(), kMenuItemInterval));
	m_cursor.setItemNum(m_pItem.size());
}

void SelectMenu::setPos(float x, float y)
{
	setPos(Vec2(x, y));
}

void SelectMenu::setPos(Vec2 pos)
{
	m_pos = pos;
}

void SelectMenu::addItem(const char* text)
{
	Item* pItem = new Item;
	pItem->setText(text);

	m_pItem.push_back(pItem);
}

int SelectMenu::getWindowWidth()
{
	int width = 0;
	//一番広いメニュー項目の幅をウィンドウサイズにする
	for (auto& pItem : m_pItem)
	{
		if (width < pItem->getTextWidth())
		{
			width = pItem->getTextWidth();
		}
	}
	return width;
}

int SelectMenu::getWindowHeight()
{
	return kMenuItemInterval * m_pItem.size();
}
