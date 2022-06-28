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

	// 各プレイヤーの位置
	DirectX::XMFLOAT3 m_EachPlayerPos[PLAYER_MAX] = { {DirectX::XMFLOAT3(- 30.0f, 5.0f, -45.0f)},		// プレイヤー１の位置
													  {DirectX::XMFLOAT3(- 55.0f, 5.0f, -70.0f)},		// プレイヤー２の位置
													  {DirectX::XMFLOAT3(-102.5f, 5.0f, -80.0f)},		// プレイヤー３の位置
													  {DirectX::XMFLOAT3(-150.0f, 5.0f, -70.0f)},		// プレイヤー４の位置
													  {DirectX::XMFLOAT3(-202.5f, 5.0f, -45.0f)},		// プレイヤー５の位置
													  {DirectX::XMFLOAT3(-130.0f, 5.0f, -30.0f)}, };	// ディーラーの位置
	// カード束の位置
	DirectX::XMFLOAT3 m_CradBasePos = DirectX::XMFLOAT3(90.0f, 5.0f, -10.0f);

	// カード情報取得
	CCard *m_pCardList[CARD_MAX];
	// シーン情報取得
	CScene *m_SceneNum;
	// プレイヤーマネージャ情報取得
	CPlayerManager *m_pPlayerManager;
	// ディーラー情報取得
	CDealer *m_pDealer;
	// プレイヤーの状態情報の取得
	PlayerState m_NowState[PLAYER_MAX];

	int m_pattern;
	// 現在の配布カード枚数
	int m_currentCardNo;
	// 現在のプレイヤーの番号
	int m_PlayerNo;
	// トータル数値の保持
	int m_totalkeep[PLAYER_MAX];
	// 各カードのズレ
	int m_gap[PLAYER_MAX];
	// 自動配布ターンの回数
	int m_autocnt;
	// オートフラグ
	bool m_autoflag;
	// ディーラーターンフラグ
	bool m_Dealerturnflag;
	// 実行時フラグ
	bool m_NoPlay;
	// 配布時フラグ
	bool m_Distribute;

	// プレイヤー、ディーラーの勝敗情報
	WinLose m_PlayerWinLose[PLAYER_MAX - 1];
	WinLose m_DealerWinLose[PLAYER_MAX - 1];
	// 先にバーストした時のフラグ
	bool m_FirstPBust[PLAYER_MAX - 1];
	// ワンゲーム終了フラグ
	bool m_oneGameFin;
	// ゲームの終了フラグ
	bool m_ThisGameFin;
	// 待機フラグ
	bool m_Wait;
	// 続行フラグ
	bool m_tobecontinue;
	// プレイヤーのヒット終了フラグ
	bool m_FinFlag[PLAYER_MAX];
	// ゲームスタートフラグ
	bool m_StartFlag;
	// ゲーム終了フラグ
	int m_nAllFinCnt;

	// -------------------------------------------------------------------------------------------------------------------------------------------

	// ソリティアの変数
	// 山札
	CCard *m_pWaitCards[CARD_MAX / 2 + 1];
	// 場札
	CCard *m_pPlaceCards[7][13];
	DirectX::XMFLOAT3 m_fPlacePos[7][13];
	// 組札
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

	virtual HRESULT Init();	 // 初期化
	virtual void Fin();		 // 終了処理
	virtual void Update();	 // 更新

	// 続行フラグの設定、取得
	void SetContinueFlag(bool vContinueflag) { m_tobecontinue = vContinueflag; }
	bool& GetContinueFlag() { return m_tobecontinue; };

	int GetPattern() { return m_pattern; }
};