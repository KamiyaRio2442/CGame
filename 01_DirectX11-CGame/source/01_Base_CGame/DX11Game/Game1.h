//=============================================================================
//
// �Q�[�� �N���X��` [Game.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#ifndef __GAME1_H__
#define __GAME1_H__

#include "Scene.h"
#include "Card.h"
#include "PlayerManager.h"

// �N���X��`
class CEnemy;
class CGame1 : public CScene
{
private:
	// ���U���g�t���O
	bool m_bResult;
	
	// �J�������
	CCamera m_camera;
	// ���C�g���
	CLight m_light;
	// �v���C���[���
	CCard* m_pPlayer;

	int m_nBound;
	// ���s�t���O
	bool m_continueflag;

public:
	CGame1();
	virtual ~CGame1();

	// ������
	virtual bool Init();
	// �I��
	virtual void Fin();
	// �X�V
	virtual void Update();
	// �`��
	virtual void Draw();

	int GetBound() { return m_nBound; }
};

#endif // !__GAME1_H__
