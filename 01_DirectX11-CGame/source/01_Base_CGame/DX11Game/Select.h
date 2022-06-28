#pragma once
#include "Scene.h"

// �N���X��`
class CSelect : public CScene
{
private:
	bool m_bStart;
	// �I���e�N�X�`�����
	ID3D11ShaderResourceView* m_pTexSelect;
	// �X�^�[�g�e�N�X�`�����
	ID3D11ShaderResourceView* m_pTexStart;
	// �w�i�F�e�N�X�`�����
	ID3D11ShaderResourceView* m_pTexBG;
	// �^�C�}�[
	int m_nTimer;

public:
	CSelect();
	virtual ~CSelect();

	// ������
	virtual bool Init();
	// �I��
	virtual void Fin();
	// �X�V
	virtual void Update();
	// �`��
	virtual void Draw();
};
