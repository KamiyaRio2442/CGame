#pragma once
#include "Model.h"

class CCharacter : public CModel
{
private:
	ID3D11ShaderResourceView *m_pTexture;
	UINT m_nVertex;	// ���_��
	TAssimpVertex* m_pVertex;// ���_�z��
	UINT m_nIndex;	// �C���f�b�N�X��
	UINT* m_pIndex;	// �C���f�b�N�X�z��

	float m_fSpeed;			// ����
	int m_nPat;
	int m_gap;
	bool m_bUseflag;

public:
	CCharacter(CScene* pScene);	// �R���X�g���N�^
	virtual ~CCharacter();		// �f�X�g���N�^

	virtual HRESULT Init();	// ������
	virtual void Update();		// �I������
	virtual void Fin();		// �I������
	virtual void Draw();

	// ���C�Ƃ̓����蔻��
	bool Collision(XMFLOAT3 vP0, XMFLOAT3 vW, XMFLOAT3* pX = nullptr, XMFLOAT3* pN = nullptr);

};
