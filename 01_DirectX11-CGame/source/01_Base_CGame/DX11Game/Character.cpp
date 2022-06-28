// �v���C���[ [Player.cpp]
#include "Character.h"
#include "Input.h"
#include "DebugProc.h"
#include "Scene.h"
#include "Texture.h"
#include "Polygon.h"

// �萔
namespace {
	const float g_fSpeed = 15.0f;
	const float g_fRotSpd = 5.0f;
	const float g_fAccel = 0.1f;
	const float g_fBrake = 0.2f;
	const float g_fMaxSpeed = 10.0f;
}

// �R���X�g���N�^
CCharacter::CCharacter(CScene* pScene) : CModel(pScene)
{
	SetID(GOT_PLAYER);

	m_fSpeed = 0.0f;
	m_pTexture = nullptr;
	m_bUseflag = false;

	m_nPat = 0;
}

// �f�X�g���N�^
CCharacter::~CCharacter()
{
}

// ������
HRESULT CCharacter::Init()
{
	// ���f���̕\�����L�����N�^�[���[�h�ɐݒ�
	SetModel(MODEL_CHARACTER);

	// �J�[�h�̃Y���̏�����
	m_gap = 0;

	// �傫���A�ʒu�A�p�x�̐ݒ�
	m_vScale = DirectX::XMFLOAT3(0.5f, 0.5f, 0.5f);
	m_vPos = DirectX::XMFLOAT3(0.0f, 60.0f, -50.0f);		// �f�B�[���[�̈ʒu
	m_vAngle = DirectX::XMFLOAT3(180.0f, 180.0f, 0.0f);

	// ���f���̏�����
	return CModel::Init();
}

// �I������
void CCharacter::Fin()
{
	CModel::Fin();
	m_pTexture = nullptr;
}

// �X�V
void CCharacter::Update()
{
	SetVisible(true);

	// ���L�[�������ꂽ��
	if (CInput::GetKeyRelease(VK_UP))
	{
		m_vPos.y += 0.5f;
	}
	// ���L�[�������ꂽ��
	if (CInput::GetKeyRelease(VK_DOWN))
	{
		m_vPos.y -= 0.5f;
	}
	// ���L�[�������ꂽ��
	if (CInput::GetKeyRelease(VK_RIGHT))
	{
		m_vPos.z += 0.5f;
	}
	// ���L�[�������ꂽ��
	if (CInput::GetKeyRelease(VK_LEFT))
	{
		m_vPos.z -= 0.5f;
	}

	// Q�L�[�������ꂽ��
	if (CInput::GetKeyRelease(VK_Q))
	{
		m_vAngle.x += 2.0f;
	}
	// E�L�[�������ꂽ��
	if (CInput::GetKeyRelease(VK_E))
	{
		m_vAngle.x -= 2.0f;
	}
	// W�L�[�������ꂽ��
	if (CInput::GetKeyRelease(VK_W))
	{
		m_vAngle.y += 2.0f;
	}
	// S�L�[�������ꂽ��
	if (CInput::GetKeyRelease(VK_S))
	{
		m_vAngle.y -= 2.0f;
	}
	// D�L�[�������ꂽ��
	if (CInput::GetKeyRelease(VK_D))
	{
		m_vAngle.z += 2.0f;
	}
	// A�L�[�������ꂽ��
	if (CInput::GetKeyRelease(VK_A))
	{
		m_vAngle.z -= 2.0f;
	}
	// ���݂̈ʒu���A�p�x�̐ݒ�
	SetPos(m_vPos);
	SetAngle(m_vAngle);

	// ���f���̍X�V
	CModel::Update();
}

// �`��
void CCharacter::Draw()
{
	TAssimpMaterial *pMat = GetModel()->GetMaterial();

	if (!pMat)
	{
		pMat = new TAssimpMaterial;
	}

	pMat->pTexture = m_pTexture;
	GetModel()->SetMaterial(pMat);
	CModel::Draw();
}
