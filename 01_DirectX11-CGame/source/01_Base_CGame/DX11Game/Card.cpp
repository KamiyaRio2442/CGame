// �v���C���[ [Player.cpp]
#include "Card.h"
#include "Input.h"
#include "DebugProc.h"
#include "Scene.h"
#include "Texture.h"
#include "Polygon.h"
#include "CardManeger.h"

// �萔
namespace {
	const float g_fSpeed = 15.0f;
	const float g_fRotSpd = 5.0f;
	const float g_fAccel = 0.1f;
	const float g_fBrake = 0.2f;
	const float g_fMaxSpeed = 10.0f;
}

// �R���X�g���N�^
CCard::CCard(CScene* pScene) : CModel(pScene)
{
	SetID(GOT_PLAYER);

	m_fSpeed = 0.0f;
	m_pLand = nullptr;
	m_pTexture = nullptr;

	m_nPat = 0;
}

// �f�X�g���N�^
CCard::~CCard()
{
}

// ������
HRESULT CCard::Init()
{
	// ���f���̕\�����J�[�h���[�h�ɐݒ�
	SetModel(MODEL_CARD);

	// �ϐ��̏�����
	mark = 0;
	number = 0;
	for (int i = 0; i < 2; i++)
	{
		mode[i] = 0;
	}

	// �n�ʃ��f���̐ݒ�
	m_pLand = (CLand*)m_pScene->Find(GOT_LAND);
	// �傫���ƈʒu�̏�����
	m_vScale = DirectX::XMFLOAT3(1.0f, 1.0f, 0.3f);
	m_vPos = DirectX::XMFLOAT3( 90.0f, 5.0f, -10.0f);
	m_fCollectPos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);

	// �t���O�̏�����
	m_bUseflag = false;
	m_bFinflag = false;

	// ���f���̏�����
	return CModel::Init();
}

// �I������
void CCard::Fin()
{
	CModel::Fin();
	m_pTexture = nullptr;
}

// �X�V
void CCard::Update()
{
	SetVisible(true);

	switch (m_nGameSceneNo)
	{
	// �I���ŃQ�[���P���I�΂ꂽ��
	case SCENE_GAME1:
		if (GetUseFlag() == true)
		{
			// �J�[�h�̈ʒu���v���C���[�̈ʒu��艜�̎�
			if (m_vPos.z >= m_fDestination.z)
			{
				// �ړ�����
				SetVelocity({ m_fDestination.x * 0.05f, m_fDestination.y * 0.05f, m_fDestination.z * 0.05f });
			}
			else
			{
				// �ړ��̒�~
				SetVelocity({ 0.0f,0.0f,0.0f });
				SetUseFlag(false);
			}
		}
		else if (GetFinFlag() == true)
		{
			// �J�[�h�̈ʒu���v���C���[�̈ʒu��艜�̎�
			if (m_vPos.z >= GetDestination().z)
			{
				// �ړ�����
				SetVelocity({ m_fDestination.x * -0.05f, m_fDestination.y * 0.05f, m_fDestination.z * 0.05f });
			}
			else
			{
				// �ړ��̒�~
				SetVelocity({ 0.0f,0.0f,0.0f });
				SetFinFlag(false);
			}
		}
		break;
	// �I���ŃQ�[���Q���I�΂ꂽ��
	case SCENE_GAME2:
		if (GetUseFlag() == true)
		{
			if (m_vPos.z >= m_fDestination.z)
			{
				// �ړ�����
				SetVelocity(m_fDestination);
			}
			else
			{
				// �ړ��̒�~
				SetVelocity({ 0.0f,0.0f,0.0f });
				SetUseFlag(false);
			}
		}
		break;
	default:
		break;
	}

	CModel::Update();
}

// �`��
void CCard::Draw()
{
	if (m_nPat < 0 || CARD_MAX <= m_nPat)
	{
		return;
	}

	// �}�e���A���̎擾
	TAssimpMaterial *pMat = GetModel()->GetMaterial();

	if (!pMat)
	{
		pMat = new TAssimpMaterial;
	}

	pMat->pTexture = m_pTexture;
	// �}�e���A���̐ݒ�
	GetModel()->SetMaterial(pMat);
	// ���f���̕`��
	CModel::Draw();
}

void CCard::SetPat(int n)
{
	// �\���e�N�X�`���̔ԍ��̐ݒ�
	m_nPat = n;
	m_pTexture = CCardManeger::GetTexture(m_nPat);
}
