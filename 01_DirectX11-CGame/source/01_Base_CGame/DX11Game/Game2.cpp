//=============================================================================
//
// �Q�[�� �N���X���� [Game.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "Game2.h"
#include "Input.h"
#include "GameObj.h"
#include "Sound.h"
#include "Fade.h"
#include "Character.h"
#include "CardManeger.h"

CCardManeger *m_pCM2;

// �R���X�g���N�^
CGame2::CGame2() : CScene()
{
	m_id = SCENE_GAME2;

	m_pPlayer = nullptr;
	m_nBound = 0;
}

// �f�X�g���N�^
CGame2::~CGame2()
{
}

// ������
bool CGame2::Init()
{
	m_bResult = false;

	// �I�u�W�F�N�g����
	m_camera.Init();
	m_camera.SetSkyDome(CModel::GetAssimp(MODEL_SKY));
	SetCamera(&m_camera);

	m_light.Init();
	SetLight(&m_light);

	//new CCharacter(this);

	// �S�I�u�W�F�N�g������
	if (FAILED(CGameObj::InitAll(m_pObj))) {
		return false;
	}

	m_pCM2 = new CCardManeger(this);
	m_pCM2->SetID((EGameObjType)m_id);
	m_pCM2->Init();
	m_camera.SetPlayer(m_pPlayer);

	return true;
}

// �I������
void CGame2::Fin()
{
	// �S�I�u�W�F�N�g�I������
	CGameObj::FinAll(m_pObj);
}

// �X�V
void CGame2::Update()
{
	// �S�L�����X�V
	CGameObj::UpdateAll(m_pObj);

	if (!m_bResult) {
		if (CInput::GetKeyRelease(VK_RETURN)) {
			m_bResult = true;
			CFade::Out(SCENE_RESULT);
		}
	}
}

// �`��
void CGame2::Draw()
{
	// �S�L�����`��
	CGameObj::DrawAll(m_pObj);
}
