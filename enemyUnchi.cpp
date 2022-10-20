#include "enemyUnchi.h"
#include "game.h"
#include "DxLib.h"
#include "SceneMain.h"

namespace
{
	//�e�̈ړ�
	constexpr float kEnemyShotX = 0.0f;
	constexpr float kEnemyShotY = 5.0f;
	//�V���b�g�̔��ˊԊu
	constexpr float kShotInterval = 60;
}

enemyUnchi::enemyUnchi()
{
	m_inCount = 0;
	m_isExist = false;
	m_randMove = false;
	m_randInterval = 0;
	m_enemyLife = 0;

	m_shotTime = 0;
	m_shotInterval = 0.0f;
	m_shotStart = false;

	m_randNum = 0;
	m_handle = -1;
	m_mapHandle = -1;
	m_pMain = nullptr;
}

enemyUnchi::~enemyUnchi()
{

}

void enemyUnchi::init()
{
	m_randNum = 0;				//�����_���Ȑ���

	//�G
	m_pos.x = 150;				//�G��x���W
	m_pos.y = -50;				//�G��y���W

	m_vec.x = 0.0f;				//�G��x���W�̈ړ��̑傫��
	m_vec.y = 3.0f;				//�G��y���W�̈ړ��̑傫��

	m_enemyLife = 100;			//�G��HP
	m_inCount = 120;			//�G�������Ă���܂ŉ��b�҂�(60��1�b�҂�)
	m_randInterval = 180;		//�G�̓����̊Ԋu
	m_isExist = false;			//�G�����݂��Ă��邩
	m_randMove = false;			//�����_���ȓ��������邩

	//�e
	m_shotTime = 120;			//�G���e�𔭎˂���܂ŉ��b�҂�(60��1�b�҂�)
	m_shotInterval = 0.0f;		//�e�̔��ˊԊu
	m_shotStart = false;		//�e�̔��˂��J�n

	//�G�̉摜�̃T�C�Y�̎擾
	GetGraphSizeF(m_handle, &m_enemySize.x, &m_enemySize.y);
	GetGraphSizeF(m_mapHandle, &m_mapSize.x, &m_mapSize.y);
}

void enemyUnchi::update()
{
	//3�b�҂�
	if (m_inCount > 0)
	{
		m_inCount--;
		return;
	}
	//3�b�o�����ꍇ
	if (m_inCount == 0)
	{
		m_isExist = true;	//�G�̑��݂��J�n
		m_inCount--;		//����if���Ɏ��������Ȃ��悤�ɂ���
	}
	
	//�G�����݂��Ă���ꍇ
	if (m_isExist)
	{
		//��ʂ̐^�񒆋߂��܂ŗ����瓮�����J�n����
		if (m_pos.y > Game::kScreenHeight / 2 - 100)
		{
			m_randMove = true;
		}
		if (m_randMove)
		{
			//4����1�̊m����4�����Ɉړ�����
			m_randNum = GetRand(99);
			if (m_randNum < 25)
			{
				m_pos.x += 8;
				if (m_pos.x > m_mapSize.x - m_enemySize.x)
				{
					m_pos.x = m_mapSize.x - m_enemySize.x;
				}
			}
			else if (m_randNum < 25 + 25)
			{
				m_pos.x -= 8;
				if (m_pos.x < 0)
				{
					m_pos.x = 0;
				}
			}
			else if (m_randNum < 25 + 25 + 25)
			{
				m_pos.y += 8;
				if (m_pos.y > Game::kScreenHeight / 2 - 100 - m_enemySize.y)
				{
					m_pos.y = Game::kScreenHeight / 2 - 100 - m_enemySize.y;
				}
			}
			else
			{
				m_pos.y -= 8;
				if (m_pos.y < 0)
				{
					m_pos.y = 0;
				}
			}
		}
		//��ʂ̔����܂ł̓��B����܂ł̊�
		else
		{
			m_pos += m_vec;
		}

		//�G����ʓ��ɑ��݂��Ă��Ďw�肵�����Ԍo�����ꍇ
		m_shotTime--;
		if (m_shotTime < 0)
		{
			m_shotStart = true;		//�e�̔��˂��J�n
		}

		//�G�̒e�̃C���^�[�o��
		m_shotInterval--;
		if (m_shotInterval < 0) m_shotInterval = 0;

		if (m_shotInterval <= 0)
		{
			if (m_shotStart)
			{
				if (m_pMain->createShotEnemyNormal(getPos()))
				{
					m_shotInterval = kShotInterval;
				}
			}
		}
	}
}

void enemyUnchi::draw()
{
	//false�Ȃ���s���Ȃ�
	if (!m_isExist)return;
	//�G�̕\��
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);	
}

void enemyUnchi::drawDamage()
{
	//false�Ȃ���s���Ȃ�
	if (!m_isExist)return;
	//�G�̕\��
	DrawGraphF(m_pos.x, m_pos.y, m_damageHandle, true);
}

void enemyUnchi::enemyLife()
{
	m_enemyLife--;
	//�G��HP��0�ȉ��ɂȂ����ꍇ
	if (m_enemyLife <= 0)
	{
		//�G�̑��݂�����
		m_isExist = false;
	}
}
