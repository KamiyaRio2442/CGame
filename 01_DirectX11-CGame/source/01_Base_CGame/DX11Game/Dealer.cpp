#include "Dealer.h"
#include "Input.h"

// �R���X�g���N�^
CDealer::CDealer(CScene *pScene)
{
}
// �f�X�g���N�^
CDealer::~CDealer()
{
}

// ������
HRESULT CDealer::Init()
{
	// ���݂̎�D�̏�����
	for (int i = 0; i < EACH_HANDCARD_MAX; i++)
	{
		m_HandCard[i] = 0;
	}

	number = 0;
	m_AttachCardNo = 0;
	m_AttachPlayerNo = 0;
	m_eachcardNumber = 0;
	m_totalNo = 0;

	// �t���O�̏�����
	m_Attachflag = false;

	return S_OK;
}
// �I��
void CDealer::Fin()
{
}
// �X�V
void CDealer::Update()
{
	// �z��ɃJ�[�h�i���o�[���i�[����Ă�����z��̗v�f�����炷
	if (m_HandCard[number] != 0)
	{
		number++;
	}

	// �J�[�h�i���o�[�̊i�[
	if (m_HandCard[number] == 0)
	{
		if (m_Attachflag == true)
		{
			// �z��ꂽ�J�[�h�̐��l���i�[
			m_HandCard[number] = m_eachcardNumber;
			// �g�[�^�����l�̍X�V
			m_totalNo += m_HandCard[number];
			// �A�^�b�`�t���O�̖�����
			m_Attachflag = false;
			// �z��ꂽ�J�[�h�̐��l��������
			m_eachcardNumber = 0;
		}
	}
}