#pragma once
#include "Scene.h"

// �N���X��`
class CResult : public CScene
{
private:
	bool m_bStart;
	// ���U���g�e�N�X�`�����
	ID3D11ShaderResourceView* m_pTexResult;
	// �X�^�[�g�e�N�X�`�����
	ID3D11ShaderResourceView* m_pTexStart;
	// �R�����g�e�N�X�`�����
	ID3D11ShaderResourceView* m_pTexComment;
	// �w�i�F�e�N�X�`�����
	ID3D11ShaderResourceView* m_pTexBG;
	// �e�J�[�h�e�N�X�`�����
	ID3D11ShaderResourceView* m_pTexCard[4][4];

	// �^�C�}�[
	int m_nTimer;
	// A�}�[�N�̉�]���
	float thetaA[4];
	float m_plusangleA[4];
	// J�}�[�N�̉�]���
	float thetaJ[4];
	float m_plusangleJ[4];
	// Q�}�[�N�̉�]���
	float thetaQ[4];
	float m_plusangleQ[4];
	// K�}�[�N�̉�]���
	float thetaK[4];
	float m_plusangleK[4];
	// ����
	int dir;

public:
	CResult();
	virtual ~CResult();

	// ������
	virtual bool Init();
	// �I��
	virtual void Fin();
	// �X�V
	virtual void Update();
	// �`��
	virtual void Draw();
};
