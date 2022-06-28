//=============================================================================
//
// �^�C�g����ʃN���X��` [Title.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#pragma once
#include "Scene.h"

// �N���X��`
class CTitle : public CScene
{
private:
	bool m_bStart;
	// �^�C�g���e�N�X�`�����
	ID3D11ShaderResourceView* m_pTexTitle;
	// �I���e�N�X�`�����
	ID3D11ShaderResourceView* m_pTexSelect[4];
	// �X�^�[�g�e�N�X�`�����
	ID3D11ShaderResourceView* m_pTexStart;
	// �w�i�F�e�N�X�`�����
	ID3D11ShaderResourceView* m_pTexBG;
	// �I���Q�[���֊s�e�N�X�`�����
	ID3D11ShaderResourceView* m_pTexAlpha;
	// �������e�N�X�`�����
	ID3D11ShaderResourceView* m_pTexUnimple;
	// �^�C�}�[
	int m_nTimer;
	// �I���Q�[���ԍ�
	int m_select;
	// ��]
	int m_roll;
	XMFLOAT2 m_selectpos;
	float m_changeangle;
	// �Q�[���P�I��
	float m_changeangleA;
	// �Q�[���Q�I��
	float m_changeangleB;
	bool m_caA;
	bool m_caB;

	// �������t���O
	bool m_Unimplementedflag;

	// �I���Q�[���֊s�J���[
	XMFLOAT4 m_backcardcolor;

public:
	CTitle();
	virtual ~CTitle();

	// ������
	virtual bool Init();
	// �I��
	virtual void Fin();
	// �X�V
	virtual void Update();
	// �`��
	virtual void Draw();

};
