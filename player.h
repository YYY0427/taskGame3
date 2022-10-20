#pragma once

#include "Vec2.h"

class SceneMain;

class Player
{
public:
	//�萔��`
	//�v���C���[�O���t�B�b�N������
	static constexpr int kGraphicDivX = 3;
	static constexpr int kGraphicDivY = 4;
	static constexpr int kGraphicDivNum = kGraphicDivX * kGraphicDivY;

	//�v���C���[�O���t�B�b�N�T�C�Y�@
	static constexpr int kGraphicSizeX = 40;
	static constexpr int kGraphicSizeY = 28;

public:
	Player();
	virtual ~Player();

	// �O���t�B�b�N�f�[�^�ݒ�
	void setHandle(int index, int handle) { m_handle[index] = handle; }
	void setMapHandle(int mapHandle) { m_mapHandle = mapHandle; }

	//SceneMain�N���X�̃|�C���^�ݒ�
	void setMain(SceneMain* pMain) { m_pMain = pMain; };

	// �v���C���[�̏�����
	void init();

	// ����
	void update();
	// �`��
	void draw();

	// ���̎擾
	Vec2 getPos() const { return m_pos; }
	Vec2 getSize() const { return m_playerSize; }

private:
	//�摜�̃n���h��
	int m_handle[kGraphicDivNum];
	int m_mapHandle;

	//SceneMain�̃|�C���^
	SceneMain* m_pMain;

	// �\���ʒu
	Vec2 m_pos;
	// �ړ�
	Vec2 m_vec;
	//�}�b�v�̉摜�T�C�Y
	Vec2 m_mapSize;

	Vec2 m_playerSize;

	int m_playerLife;

	//�L�����N�^�[�̃A�j���[�V����
	int m_animeNo;		//�\������ԍ�
	int m_animeFrame;
	int m_dirNo;		//�i�s����

	//�V���b�g
	int m_shotInterval;
};