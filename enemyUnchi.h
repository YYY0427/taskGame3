#pragma once

#include "Vec2.h"

class SceneMain;

class enemyUnchi
{
public:
	enemyUnchi();
	virtual ~enemyUnchi();

	//������
	void init();
	//�X�V
	void update();
	//�\��
	void draw();
	void drawDamage();
	//�G��HP����
	void enemyLife();
	int  getEnemyLife()const { return m_enemyLife; }
	//SceneMain�N���X�̃|�C���^�ݒ�
	void setMain(SceneMain* pMain) { m_pMain = pMain; }
	//�n���h���ݒ�
	void setHandle(int handle) { m_handle = handle; }
	void setMapHandle(int mapHandle) { m_mapHandle = mapHandle; }
	void setDamageHandle(int damageHandle) { m_damageHandle = damageHandle; }
	//���݂��邩
	bool isExist() const { return m_isExist; }
	//���̎擾
	Vec2 getPos() const { return m_pos; }
	//�T�C�Y�̎擾
	Vec2 getSize() const { return m_enemySize; }
	

private:
	SceneMain* m_pMain;		//SceneMain�̃|�C���^
	Vec2 m_mapSize;			//�}�b�v�̃T�C�Y
	int m_randNum;			//�����_���Ȑ���
	int m_mapHandle;		//�}�b�v�̃n���h��
	int m_damageHandle;

	//�G
	int m_handle;			// �O���t�B�b�N�n���h��
	int m_inCount;			//���b�ŉ�ʂɓ����Ă��邩
	int m_randInterval;		//�����̊Ԋu
	int m_enemyLife;		//�G��HP
	int m_waitFrame;

	Vec2 m_pos;				//�G�̕\���ʒu
	Vec2 m_vec;				//�G�̈ړ�
	Vec2 m_enemySize;		//�G�̃T�C�Y

	bool m_isExist;			//���݂��邩
	bool m_randMove;		//�����_���ȓ���

	//�e
	int m_shotTime;			//�e�̔��˂܂ł̎���
	float m_shotInterval;	//�e�̔��ˊԊu
	bool m_shotStart;		//�e�𔭎˂��邩���Ȃ���
};