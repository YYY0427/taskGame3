#include "map.h"
#include "DxLib.h"
#include "game.h"
#include "SceneMain.h"

Map::Map()
{
	//������
	m_handle = -1;
}

Map::~Map()
{

}

void Map::init()
{ 
	//�摜�̃T�C�Y�̎擾
	GetGraphSizeF(m_handle, &m_mapSize.x, &m_mapSize.y);

	//�摜�̈ʒu�̏�����
	m_pos.x = 0.0f;
	m_pos.y = 0.0f;
}

void Map::update()
{
	//�w�i�̈ړ�
	m_pos.y += 1.0f;

	//�摜�̈ʒu��m_mapSize.y�܂œ��B������摜�̈ʒu��߂�
	if (m_pos.y == m_mapSize.y)
		m_pos.y = 0.0f;
}

void Map::draw()
{
	//1���ڂ̕\��
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
	//2���ڂ̕\��
	DrawGraphF(m_pos.x, m_pos.y - m_mapSize.y, m_handle, true);
}