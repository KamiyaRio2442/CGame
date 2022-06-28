// �v���C���[ [Player.h]
#pragma once
#include "Model.h"
#include "Land.h"

constexpr int CARD_MAX = 52;
constexpr int PLAYER_MAX = 6;
const int EACH_HANDCARD_MAX = 12;

class CCard : public CModel
{
private:
	ID3D11ShaderResourceView *m_pTexture;
	CLand *m_pLand;			// �n��
	DirectX::XMFLOAT3 m_fDestination;
	DirectX::XMFLOAT3 m_fCollectPos;

	CCard *m_pDummyData;

	float m_fSpeed;			// ����
	int m_nPat;
	int m_gap;
	int m_nGameSceneNo;
	bool m_bUseflag;
	bool m_bFinflag;

public:
	CCard(CScene* pScene); // �R���X�g���N�^
	virtual ~CCard();		 // �f�X�g���N�^

	virtual HRESULT Init();	 // ������
	virtual void Fin();		 // �I������
	virtual void Update();	 // �X�V
	virtual void Draw();

	void SetPat(int n);
	void SetDestination(XMFLOAT3 vFinPos) { m_fDestination = vFinPos; }
	XMFLOAT3& GetDestination() { return m_fDestination; }
	// �J�[�h�Ԃ̃Y���̐ݒ�A�擾
	void SetGap(int vGap) { m_gap = vGap; }
	int& GetGap() { return m_gap; }
	// �g�p�t���O�̐ݒ�A�擾
	void SetUseFlag(bool vUseflag) { m_bUseflag = vUseflag; }
	bool& GetUseFlag() { return m_bUseflag; }
	// �I���t���O�̐ݒ�A�擾
	void SetFinFlag(bool vFinflag) { m_bFinflag = vFinflag; }
	bool& GetFinFlag() { return m_bFinflag; }

	// �V�[���ԍ��̐ݒ�
	void SetNowGameSceneNo(int vSceneNo) { m_nGameSceneNo = vSceneNo; }

public:
	// �}�[�N
	int mark;
	// �i���o�[
	int number;
	// ���l�̃��[�h
	int mode[2];
};
