#pragma once

#include <vector>
#include "map.h"
#include "player.h"
#include "ShotBase.h"
#include "enemyUnchi.h"
#include "SceneBase.h"

class SceneMain : public SceneBase 
{
public:
	SceneMain();
	virtual ~SceneMain();

	//������
	void init();
	// �I������
	void end();
	// ���t���[���̏���
	void update();
	// ���t���[���̕`��
	void draw();
	//�e�̐���
	bool createShotNormal(Vec2 pos);
	bool createShotEnemyNormal(Vec2 pos);

	/* ==== �����蔻�� ==== */
	//�G�ƃv���C���[�̓����蔻��
	bool enemyPlayerCollision();
	//�G�̒e�ƃv���C���[�̓����蔻��
	bool enemyShotPlayerCollision();
	//�v���C���[�̒e�ƓG�̓����蔻��
	bool playerShotEnemyCollision();
private:
	int m_playerLife;
	int m_enemyDrawCounter;
	int m_playerDrawCounter;
	bool m_enemyDamageFlag;
	bool m_playerDamageFlag;
	//�n���h��
	int m_hPlayerGraphic[Player::kGraphicDivNum];		//�v���C���[�̃O���t�B�b�N�n���h��
	int m_hPlayerDamageGraphic[Player::kGraphicDivNum];	//�v���C���[�̃_���[�W�̃O���t�B�b�N�n���h��
	int m_hShotGraphic;									//�v���C���[�̒e�̃n���h��
	int m_hMapGraphic;									//�}�b�v�̃n���h��
	int m_hEnemyUnchiGraphic;							//�G�̃n���h��
	int m_hEnemyUnchiDamageGraphic;						//�G�̃_���[�W�̃n���h��
	int m_hShotEnemyUnchiGraphic;						//�G�̒e�̃n���h��
	//���G����
	int m_waitFrame;									//�G�ƃv���C���[�����������ꍇ�̖��G����
	int m_waitFrame2;									//�G�̒e�ƃv���C���[�����������ꍇ�̖��G����					
	//�T�C�Y
	Vec2 m_shotEnemySize;								//�G�̒e�̉摜�T�C�Y
	Vec2 m_shotPlayerSize;								//�v���C���[�̒e�̉摜�̃T�C�Y
	Vec2 m_enemySize;									//�G�̉摜�T�C�Y
	//�N���X�̐ݒ�
	Player m_player;								
	Map m_map;
	enemyUnchi m_enemyUnchi;
	//vector�̐ݒ�
	std::vector<ShotBase*> m_pShotVt;
};