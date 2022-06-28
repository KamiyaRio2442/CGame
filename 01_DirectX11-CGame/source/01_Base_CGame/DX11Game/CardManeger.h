#include "Card.h"
#include "Scene.h"
#include "PlayerManager.h"
#include "Dealer.h"

class CCardManeger : public CGameObj
{
private:
	DirectX::XMFLOAT3 m_EachCardPos[CARD_MAX];
	DirectX::XMFLOAT3 m_EachCardAngle[CARD_MAX];
	DirectX::XMFLOAT3 m_DifferencePos;

	// �e�v���C���[�̈ʒu
	DirectX::XMFLOAT3 m_EachPlayerPos[PLAYER_MAX] = { {DirectX::XMFLOAT3(- 30.0f, 5.0f, -45.0f)},		// �v���C���[�P�̈ʒu
													  {DirectX::XMFLOAT3(- 55.0f, 5.0f, -70.0f)},		// �v���C���[�Q�̈ʒu
													  {DirectX::XMFLOAT3(-102.5f, 5.0f, -80.0f)},		// �v���C���[�R�̈ʒu
													  {DirectX::XMFLOAT3(-150.0f, 5.0f, -70.0f)},		// �v���C���[�S�̈ʒu
													  {DirectX::XMFLOAT3(-202.5f, 5.0f, -45.0f)},		// �v���C���[�T�̈ʒu
													  {DirectX::XMFLOAT3(-130.0f, 5.0f, -30.0f)}, };	// �f�B�[���[�̈ʒu
	// �J�[�h���̈ʒu
	DirectX::XMFLOAT3 m_CradBasePos = DirectX::XMFLOAT3(90.0f, 5.0f, -10.0f);

	// �J�[�h���擾
	CCard *m_pCardList[CARD_MAX];
	// �V�[�����擾
	CScene *m_SceneNum;
	// �v���C���[�}�l�[�W�����擾
	CPlayerManager *m_pPlayerManager;
	// �f�B�[���[���擾
	CDealer *m_pDealer;
	// �v���C���[�̏�ԏ��̎擾
	PlayerState m_NowState[PLAYER_MAX];

	int m_pattern;
	// ���݂̔z�z�J�[�h����
	int m_currentCardNo;
	// ���݂̃v���C���[�̔ԍ�
	int m_PlayerNo;
	// �g�[�^�����l�̕ێ�
	int m_totalkeep[PLAYER_MAX];
	// �e�J�[�h�̃Y��
	int m_gap[PLAYER_MAX];
	// �����z�z�^�[���̉�
	int m_autocnt;
	// �I�[�g�t���O
	bool m_autoflag;
	// �f�B�[���[�^�[���t���O
	bool m_Dealerturnflag;
	// ���s���t���O
	bool m_NoPlay;
	// �z�z���t���O
	bool m_Distribute;

	// �v���C���[�A�f�B�[���[�̏��s���
	WinLose m_PlayerWinLose[PLAYER_MAX - 1];
	WinLose m_DealerWinLose[PLAYER_MAX - 1];
	// ��Ƀo�[�X�g�������̃t���O
	bool m_FirstPBust[PLAYER_MAX - 1];
	// �����Q�[���I���t���O
	bool m_oneGameFin;
	// �Q�[���̏I���t���O
	bool m_ThisGameFin;
	// �ҋ@�t���O
	bool m_Wait;
	// ���s�t���O
	bool m_tobecontinue;
	// �v���C���[�̃q�b�g�I���t���O
	bool m_FinFlag[PLAYER_MAX];
	// �Q�[���X�^�[�g�t���O
	bool m_StartFlag;
	// �Q�[���I���t���O
	int m_nAllFinCnt;

	// -------------------------------------------------------------------------------------------------------------------------------------------

	// �\���e�B�A�̕ϐ�
	// �R�D
	CCard *m_pWaitCards[CARD_MAX / 2 + 1];
	// ��D
	CCard *m_pPlaceCards[7][13];
	DirectX::XMFLOAT3 m_fPlacePos[7][13];
	// �g�D
	CCard *m_pSetCards[4][13];
	CCard *m_pDummyCards;
	int m_nSetNum;


public:
	CCardManeger(CScene* pScene);
	~CCardManeger();

	static ID3D11ShaderResourceView * m_pCardInfo[CARD_MAX];

	static HRESULT LoadAll();
	static void ReleaseAll();
	static ID3D11ShaderResourceView* GetTexture(int nPat);

	virtual HRESULT Init();	 // ������
	virtual void Fin();		 // �I������
	virtual void Update();	 // �X�V

	// ���s�t���O�̐ݒ�A�擾
	void SetContinueFlag(bool vContinueflag) { m_tobecontinue = vContinueflag; }
	bool& GetContinueFlag() { return m_tobecontinue; };

	int GetPattern() { return m_pattern; }
};