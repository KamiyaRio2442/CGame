#ifndef __GAME2_H__
#define __GAME2_H__

#include "Scene.h"
#include "Card.h"

// �N���X��`
class CEnemy;
class CGame2 : public CScene
{
private:
	bool m_bResult;

	// �J�������
	CCamera m_camera;
	// ���C�g���
	CLight m_light;
	// �v���C���[���
	CCard* m_pPlayer;
	int m_nBound;

public:
	CGame2();
	virtual ~CGame2();

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

#endif // !__GAME2_H__
