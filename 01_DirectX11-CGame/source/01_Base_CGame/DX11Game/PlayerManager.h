#pragma once
#include "Player.h"
#include "GameObj.h"

class CPlayerManager : public CGameObj
{
private:
	CPlayer *m_pPlayerList[PLAYER_MAX - 1];
	// �t���O
	bool m_flag;
	// �A�^�b�`�t���O
	bool m_attachflag;
	// ���݂̃J�[�h���l
	int m_AttachCardNo;
	int m_AttachPlayerNo;
	// ���l�ێ�
	int m_Nokeep[PLAYER_MAX - 1];

public:
	CPlayerManager(CScene* pScene);
	~CPlayerManager();

	virtual HRESULT Init();	 // ������
	virtual void Fin();		 // �I������
	virtual void Update();	 // �X�V
	virtual void Draw();	 // �`��

	// ���݂̃v���C���[�ԍ��̐ݒ�A�擾
	void SetAttachPlayerNo(int vPNo) { m_AttachPlayerNo = vPNo; }
	int& GetAttachPlayerNo() { return m_AttachPlayerNo; }
	// ���݂̃J�[�h���l�̐ݒ�A�擾
	void SetAttachCardNo(int vCNo) { m_AttachCardNo = vCNo; }
	int& GetAttachCardNo() { return m_AttachCardNo; }
	// �z�z�i���o�[�̕ێ�
	int& GetEachNoKeep(int vNo) { return m_Nokeep[vNo]; }

};