#include "Player.h"
#include "Input.h"

CPlayer::CPlayer(CScene* pScene) : CModel(pScene)
{
}

CPlayer::~CPlayer()
{
}

HRESULT CPlayer::Init()
{
	// �ϐ��̏�����
	number = 0;

	// ��D���̏�����
	for (int i = 0; i < EACH_HANDCARD_MAX; i++)
	{
		m_HandCard[i] = 0;
	}

	m_eachcardNumber = 0;
	m_AttachCardNo = 0;
	m_AttachPlayerNo = 0;
	m_totalNo = 0;

	// �t���O�̏�����
	m_Attachflag = false;

	return S_OK;
}
void CPlayer::Fin()
{
}
void CPlayer::Update()
{
	// �z��ɃJ�[�h�i���o�[���i�[����Ă�����z��̗v�f�����炷
	if (m_HandCard[number] != 0)
	{
		number++;
	}
	// �J�[�h�i���o�[�̊i�[
	else if (m_HandCard[number] == 0)
	{
		m_HandCard[number] = m_eachcardNumber;
		m_totalNo += m_HandCard[number]; 
		m_eachcardNumber = 0;
	}
}