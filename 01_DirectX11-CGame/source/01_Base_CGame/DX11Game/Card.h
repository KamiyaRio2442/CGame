// プレイヤー [Player.h]
#pragma once
#include "Model.h"
#include "Land.h"

constexpr int CARD_MAX = 52;
constexpr int PLAYER_MAX = 6;
const int EACH_HANDCARD_MAX = 12;

class CCard : public CModel
{
private:
	ID3D11ShaderResourceView *m_pTexture;
	CLand *m_pLand;			// 地面
	DirectX::XMFLOAT3 m_fDestination;
	DirectX::XMFLOAT3 m_fCollectPos;

	CCard *m_pDummyData;

	float m_fSpeed;			// 速さ
	int m_nPat;
	int m_gap;
	int m_nGameSceneNo;
	bool m_bUseflag;
	bool m_bFinflag;

public:
	CCard(CScene* pScene); // コンストラクタ
	virtual ~CCard();		 // デストラクタ

	virtual HRESULT Init();	 // 初期化
	virtual void Fin();		 // 終了処理
	virtual void Update();	 // 更新
	virtual void Draw();

	void SetPat(int n);
	void SetDestination(XMFLOAT3 vFinPos) { m_fDestination = vFinPos; }
	XMFLOAT3& GetDestination() { return m_fDestination; }
	// カード間のズレの設定、取得
	void SetGap(int vGap) { m_gap = vGap; }
	int& GetGap() { return m_gap; }
	// 使用フラグの設定、取得
	void SetUseFlag(bool vUseflag) { m_bUseflag = vUseflag; }
	bool& GetUseFlag() { return m_bUseflag; }
	// 終了フラグの設定、取得
	void SetFinFlag(bool vFinflag) { m_bFinflag = vFinflag; }
	bool& GetFinFlag() { return m_bFinflag; }

	// シーン番号の設定
	void SetNowGameSceneNo(int vSceneNo) { m_nGameSceneNo = vSceneNo; }

public:
	// マーク
	int mark;
	// ナンバー
	int number;
	// 数値のモード
	int mode[2];
};
