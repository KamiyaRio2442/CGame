#include "PlayerManager.h"

// �R���X�g���N�^
CPlayerManager::CPlayerManager(CScene* pScene) : CGameObj(pScene)
{
}
// �f�X�g���N�^
CPlayerManager::~CPlayerManager()
{
}

// ������
HRESULT CPlayerManager::Init()
{	
	// �t���O�̏�����
	m_flag = false;
	m_attachflag = false;

	// �ϐ��̏�����
	m_AttachPlayerNo = -1;
	// �e�v���C���[�̏������̐ݒ�
	for (int i = 0; i < PLAYER_MAX - 1; i++)
	{
		CPlayer *pPlayerL = new CPlayer(m_pScene);
		pPlayerL->Init();
		pPlayerL->SetAttachFlag(false);
		pPlayerL->SetAttachCardInfo(0);
		m_pPlayerList[i] = pPlayerL;

		m_Nokeep[i] = 0;
	}

	return S_OK;
}

// �I��
void CPlayerManager::Fin()
{

}

// �X�V
void CPlayerManager::Update()
{
	m_attachflag = false;

	// ���ݑI������Ă���v���C���[��-1�ɂȂ��Ă��Ȃ���
	if (m_AttachPlayerNo != -1 && m_flag == false && m_attachflag == false)
	{
		// �t���O�̗L����
		m_flag = true;
	}

	// �t���O���L���ɂȂ��Ă�����
	if (m_flag == true)
	{
		// ���݂̃v���C���[��
		m_pPlayerList[m_AttachPlayerNo]->SetAttachFlag(true);
		m_pPlayerList[m_AttachPlayerNo]->SetAttachCardInfo(m_AttachCardNo);
		m_pPlayerList[m_AttachPlayerNo]->Update();
		m_flag = false;
	}

	// ���ݑI������Ă���v���C���[��-1�ɂȂ��Ă��Ȃ���
	if (m_AttachPlayerNo != -1)
	{
		for (int i = 0; i < PLAYER_MAX - 1; i++)
		{
			// �e�v���C���[��
			m_Nokeep[i] = m_pPlayerList[i]->GetTotalNo();
		}

		m_AttachPlayerNo = -1;
	}
}

// �`��
void CPlayerManager::Draw()
{

}
