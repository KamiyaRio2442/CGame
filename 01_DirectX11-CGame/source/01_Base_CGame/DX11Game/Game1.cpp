#include "Game1.h"
#include "Input.h"
#include "GameObj.h"
#include "Sound.h"
#include "Fade.h"
#include "Land.h"
#include "CardManeger.h"

CCardManeger *m_pCM1;

// �R���X�g���N�^
CGame1::CGame1() : CScene()
{
	m_id = SCENE_GAME1;

	m_pPlayer = nullptr;
	m_nBound = 0;
}

// �f�X�g���N�^
CGame1::~CGame1()
{
}

// ������
bool CGame1::Init()
{
	m_bResult = false;
	m_continueflag = false;

	// �I�u�W�F�N�g����
	m_camera.Init();
	m_camera.SetSkyDome(CModel::GetAssimp(MODEL_SKY));
	SetCamera(&m_camera);

	m_light.Init();
	SetLight(&m_light);

	new CLand(this);

	// �S�I�u�W�F�N�g������
	if (FAILED(CGameObj::InitAll(m_pObj))) {
		return false;
	}

	m_pCM1 = new CCardManeger(this);
	m_pCM1->SetID((EGameObjType)m_id);
	m_pCM1->Init();

	m_camera.SetPlayer(m_pPlayer);

	return true;
}

// �I������
void CGame1::Fin()
{
	// �S�I�u�W�F�N�g�I������
	CGameObj::FinAll(m_pObj);
}

// �X�V
void CGame1::Update()
{
	// �S�L�����X�V
	CGameObj::UpdateAll(m_pObj);
	m_continueflag = m_pCM1->GetContinueFlag();

	if (!m_bResult) {
		if (CInput::GetKeyRelease(VK_RETURN)) {
			m_bResult = true;
			CFade::Out(SCENE_RESULT);
		}
		if (m_continueflag == true && CInput::GetKeyRelease(VK_C))
		{
			m_bResult = true;
			CFade::Out(SCENE_GAME1);
		}
	}
}

// �`��
void CGame1::Draw()
{
	// �S�L�����`��
	CGameObj::DrawAll(m_pObj);
}
