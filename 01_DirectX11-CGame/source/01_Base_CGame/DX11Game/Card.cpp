// プレイヤー [Player.cpp]
#include "Card.h"
#include "Input.h"
#include "DebugProc.h"
#include "Scene.h"
#include "Texture.h"
#include "Polygon.h"
#include "CardManeger.h"

// 定数
namespace {
	const float g_fSpeed = 15.0f;
	const float g_fRotSpd = 5.0f;
	const float g_fAccel = 0.1f;
	const float g_fBrake = 0.2f;
	const float g_fMaxSpeed = 10.0f;
}

// コンストラクタ
CCard::CCard(CScene* pScene) : CModel(pScene)
{
	SetID(GOT_PLAYER);

	m_fSpeed = 0.0f;
	m_pLand = nullptr;
	m_pTexture = nullptr;

	m_nPat = 0;
}

// デストラクタ
CCard::~CCard()
{
}

// 初期化
HRESULT CCard::Init()
{
	// モデルの表示をカードモードに設定
	SetModel(MODEL_CARD);

	// 変数の初期化
	mark = 0;
	number = 0;
	for (int i = 0; i < 2; i++)
	{
		mode[i] = 0;
	}

	// 地面モデルの設定
	m_pLand = (CLand*)m_pScene->Find(GOT_LAND);
	// 大きさと位置の初期化
	m_vScale = DirectX::XMFLOAT3(1.0f, 1.0f, 0.3f);
	m_vPos = DirectX::XMFLOAT3( 90.0f, 5.0f, -10.0f);
	m_fCollectPos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);

	// フラグの初期化
	m_bUseflag = false;
	m_bFinflag = false;

	// モデルの初期化
	return CModel::Init();
}

// 終了処理
void CCard::Fin()
{
	CModel::Fin();
	m_pTexture = nullptr;
}

// 更新
void CCard::Update()
{
	SetVisible(true);

	switch (m_nGameSceneNo)
	{
	// 選択でゲーム１が選ばれた時
	case SCENE_GAME1:
		if (GetUseFlag() == true)
		{
			// カードの位置がプレイヤーの位置より奥の時
			if (m_vPos.z >= m_fDestination.z)
			{
				// 移動処理
				SetVelocity({ m_fDestination.x * 0.05f, m_fDestination.y * 0.05f, m_fDestination.z * 0.05f });
			}
			else
			{
				// 移動の停止
				SetVelocity({ 0.0f,0.0f,0.0f });
				SetUseFlag(false);
			}
		}
		else if (GetFinFlag() == true)
		{
			// カードの位置がプレイヤーの位置より奥の時
			if (m_vPos.z >= GetDestination().z)
			{
				// 移動処理
				SetVelocity({ m_fDestination.x * -0.05f, m_fDestination.y * 0.05f, m_fDestination.z * 0.05f });
			}
			else
			{
				// 移動の停止
				SetVelocity({ 0.0f,0.0f,0.0f });
				SetFinFlag(false);
			}
		}
		break;
	// 選択でゲーム２が選ばれた時
	case SCENE_GAME2:
		if (GetUseFlag() == true)
		{
			if (m_vPos.z >= m_fDestination.z)
			{
				// 移動処理
				SetVelocity(m_fDestination);
			}
			else
			{
				// 移動の停止
				SetVelocity({ 0.0f,0.0f,0.0f });
				SetUseFlag(false);
			}
		}
		break;
	default:
		break;
	}

	CModel::Update();
}

// 描画
void CCard::Draw()
{
	if (m_nPat < 0 || CARD_MAX <= m_nPat)
	{
		return;
	}

	// マテリアルの取得
	TAssimpMaterial *pMat = GetModel()->GetMaterial();

	if (!pMat)
	{
		pMat = new TAssimpMaterial;
	}

	pMat->pTexture = m_pTexture;
	// マテリアルの設定
	GetModel()->SetMaterial(pMat);
	// モデルの描画
	CModel::Draw();
}

void CCard::SetPat(int n)
{
	// 表示テクスチャの番号の設定
	m_nPat = n;
	m_pTexture = CCardManeger::GetTexture(m_nPat);
}
