#pragma once
#include "Model.h"
#include "Card.h"

const int g_nEachHandCardMax = 12;

class CPlayer :public CModel
{
private:
	// ��D�̂��ꂼ��̔ԍ����i�[����z��
	int m_HandCard[EACH_HANDCARD_MAX];
	// �������ꎞ�ۑ����Ă����ϐ�
	int m_eachcardNumber;
	// ���̎莝���̍��v
	int m_totalNo;
	// ���ǂ̔z��̗v�f�܂Ő������i�[����Ă��邩
	int number;

	int m_AttachPlayerNo;
	int m_AttachCardNo;
	bool m_Attachflag;

public:
	CPlayer(CScene* pScene);
	~CPlayer();

	virtual HRESULT Init();	 // ������
	virtual void Fin();		 // �I������
	virtual void Update();	 // �X�V

	// �A�^�b�`�t���O�̐ݒ�A�擾
	void SetAttachFlag(bool vAttachFlag) { m_Attachflag = vAttachFlag; }
	bool& GetAttachFlag() { return m_Attachflag; }
	void SetAttachCardInfo(int vCardNo) { m_eachcardNumber = vCardNo; }
	int& GetAttachCardInfo() { return m_eachcardNumber; }
	void SetAttachNum(int vNo) { number = vNo; }
	int& GetAttachNum() { return number; }
	int GetTotalNo() { return m_totalNo; }

};
