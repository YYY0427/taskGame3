#include "DxLib.h"
#include "game.h"
#include "player.h"
#include "SceneMain.h"

namespace 
{
	//�L�����N�^�[�A�j���[�V�����P�R�}������̃t���[����
	constexpr int kAnimeChangeFrame = 8;
	//�L�����N�^�[�̈ړ����x
	constexpr int kSpeedX = 4;
	constexpr int kSpeedY = 4;
	//�V���b�g�̔��ˊԊu
	constexpr int  kShotInterval = 16;
}

Player::Player()
{
	//������
	for (auto& handle : m_handle)
	{
		handle = -1;
	}
	m_animeNo = 0;
	m_dirNo = 0;
	m_pMain = nullptr;
	m_shotInterval = 0;
	m_animeFrame = 0;
	m_mapHandle = -1;
	m_playerLife = 0;
}
Player::~Player()
{

}

void Player::init()
{
	//�v���C���[�̏����ʒu
	m_pos.x = 160;
	m_pos.y = 300;

	//������
	m_vec.x = 0.0f;
	m_vec.y = 0.0f;

	m_animeNo = 0;
	m_animeFrame = 0;
	m_dirNo = 0;
	m_shotInterval = 0;
	m_playerLife = 10;

	m_playerSize.x = kGraphicSizeX;
	m_playerSize.y = kGraphicSizeY;

	//�}�b�v�̉摜�̃T�C�Y�̎擾
	GetGraphSizeF(m_mapHandle, &m_mapSize.x, &m_mapSize.y);
}

void Player::update()
{
	// �p�b�h(�������̓L�[�{�[�h)����̓��͂��擾����
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	    /*�@==== �L�����N�^�[�̃A�j���[�V���� ==== */
	//������
	bool isKey = false;

	if (padState & PAD_INPUT_UP || CheckHitKey(KEY_INPUT_W))
	{
		m_dirNo = 3;
		isKey = true;
	}
	if (padState & PAD_INPUT_DOWN || CheckHitKey(KEY_INPUT_S))
	{
		m_dirNo = 0;
		isKey = true;
	}
	if (padState & PAD_INPUT_LEFT || CheckHitKey(KEY_INPUT_A))
	{
		m_dirNo = 1;
		isKey = true;
	}
	if (padState & PAD_INPUT_RIGHT || CheckHitKey(KEY_INPUT_D))
	{
		m_dirNo = 2;
		isKey = true;
	}

	//�L�[���͂��������ꍇ�t���[�����v���X
	if (isKey)	m_animeFrame++;

	if (m_animeFrame >= kGraphicDivX * kAnimeChangeFrame)
	{
		m_animeFrame = 0;
	}

	int tempAnimeNo = m_animeFrame / kAnimeChangeFrame;
	m_animeNo = m_dirNo * kGraphicDivX + tempAnimeNo;


	     /* ==== �V���b�g�������� ==== */
	m_shotInterval--;
	if (m_shotInterval < 0)m_shotInterval = 0;

	if (m_shotInterval <= 0)
	{
		if (padState & PAD_INPUT_1)
		{
			if (m_pMain->createShotNormal(getPos()))
			{
				m_shotInterval = kShotInterval;
			}
		}
	}

	          /* ==== �L�����N�^�[�̈ړ� ==== */
	if (padState & PAD_INPUT_UP || CheckHitKey(KEY_INPUT_W))
	{
		m_pos.y -= kSpeedY;
		//��ʊO�ɏo�����ȏꍇ�L�����N�^�[�̈ʒu���Ƃǂ߂�
		if (m_pos.y < 0) 
			m_pos.y = 0;
	}
	else if (padState & PAD_INPUT_DOWN || CheckHitKey(KEY_INPUT_S))
	{
		m_pos.y += kSpeedY;
		//��ʊO�ɏo�����ȏꍇ�L�����N�^�[�̈ʒu���Ƃǂ߂�
		if (m_pos.y > Game::kScreenHeight - kGraphicSizeY) 
			m_pos.y = Game::kScreenHeight - kGraphicSizeY;
	}
	else if (padState & PAD_INPUT_LEFT || CheckHitKey(KEY_INPUT_A))
	{
		m_pos.x -= kSpeedX;
		//��ʊO�ɏo�����ȏꍇ�L�����N�^�[�̈ʒu���Ƃǂ߂�
		if (m_pos.x < 0)
			m_pos.x = 0;
	}
	else if (padState & PAD_INPUT_RIGHT || CheckHitKey(KEY_INPUT_D))
	{
		m_pos.x += kSpeedX;
		//��ʊO�ɏo�����ȏꍇ�L�����N�^�[�̈ʒu���Ƃǂ߂�
		if (m_pos.x > m_mapSize.x - kGraphicSizeX)
				m_pos.x = m_mapSize.x - kGraphicSizeX;
	}
	else
	{

	}
}

void Player::draw()
{
	DrawGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_handle[m_animeNo], true);
}

void Player::damageDraw()
{
	DrawGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_damageHandle[m_animeNo], true);
}