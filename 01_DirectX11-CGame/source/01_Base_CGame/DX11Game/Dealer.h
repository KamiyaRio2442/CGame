#pragma once
#include "Card.h"

class CDealer
{
private:
	// ��D
	int m_HandCard[EACH_HANDCARD_MAX];
	// ���݂̔z�z�J�[�h�̐��l
	int m_eachcardNumber;
	int m_AttachPlayerNo;
	// ��D�J�[�h�̊D��
	int m_AttachCardNo;
	// �g�[�^�����l
	int m_totalNo;
	// �A�^�b�`�t���O
	bool m_Attachflag;

public:
	CDealer(CScene *pScene);
	~CDealer();

	virtual HRESULT Init();	 // ������
	virtual void Fin();		 // �I������
	virtual void Update();	 // �X�V

	// �A�^�b�`�t���O�̐ݒ�A�擾
	void SetAttachFlag(bool vAttachFlag) { m_Attachflag = vAttachFlag; }
	bool& GetAttachFlag() { return m_Attachflag; }
	// ���݂̃J�[�h���l�̐ݒ�A�擾
	void SetAttachCardInfo(int vCardNo) { m_eachcardNumber = vCardNo; }
	int& GetAttachCardInfo() { return m_eachcardNumber; }
	// �g�[�^�����l�̎擾
	int& GetTotalNo() { return m_totalNo; }

public:
	// �i���o�[
	int number;

};
