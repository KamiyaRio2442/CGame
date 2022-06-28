#include "PlayerManager.h"

// コンストラクタ
CPlayerManager::CPlayerManager(CScene* pScene) : CGameObj(pScene)
{
}
// デストラクタ
CPlayerManager::~CPlayerManager()
{
}

// 初期化
HRESULT CPlayerManager::Init()
{	
	// フラグの初期化
	m_flag = false;
	m_attachflag = false;

	// 変数の初期化
	m_AttachPlayerNo = -1;
	// 各プレイヤーの初期情報の設定
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

// 終了
void CPlayerManager::Fin()
{

}

// 更新
void CPlayerManager::Update()
{
	m_attachflag = false;

	// 現在選択されているプレイヤーが-1になっていないか
	if (m_AttachPlayerNo != -1 && m_flag == false && m_attachflag == false)
	{
		// フラグの有効化
		m_flag = true;
	}

	// フラグが有効になっていた時
	if (m_flag == true)
	{
		// 現在のプレイヤーの
		m_pPlayerList[m_AttachPlayerNo]->SetAttachFlag(true);
		m_pPlayerList[m_AttachPlayerNo]->SetAttachCardInfo(m_AttachCardNo);
		m_pPlayerList[m_AttachPlayerNo]->Update();
		m_flag = false;
	}

	// 現在選択されているプレイヤーが-1になっていないか
	if (m_AttachPlayerNo != -1)
	{
		for (int i = 0; i < PLAYER_MAX - 1; i++)
		{
			// 各プレイヤーの
			m_Nokeep[i] = m_pPlayerList[i]->GetTotalNo();
		}

		m_AttachPlayerNo = -1;
	}
}

// 描画
void CPlayerManager::Draw()
{

}
