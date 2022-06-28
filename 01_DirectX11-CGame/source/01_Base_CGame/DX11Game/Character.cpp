// プレイヤー [Player.cpp]
#include "Character.h"
#include "Input.h"
#include "DebugProc.h"
#include "Scene.h"
#include "Texture.h"
#include "Polygon.h"

// 定数
namespace {
	const float g_fSpeed = 15.0f;
	const float g_fRotSpd = 5.0f;
	const float g_fAccel = 0.1f;
	const float g_fBrake = 0.2f;
	const float g_fMaxSpeed = 10.0f;
}

// コンストラクタ
CCharacter::CCharacter(CScene* pScene) : CModel(pScene)
{
	SetID(GOT_PLAYER);

	m_fSpeed = 0.0f;
	m_pTexture = nullptr;
	m_bUseflag = false;

	m_nPat = 0;
}

// デストラクタ
CCharacter::~CCharacter()
{
}

// 初期化
HRESULT CCharacter::Init()
{
	// モデルの表示をキャラクターモードに設定
	SetModel(MODEL_CHARACTER);

	// カードのズレの初期化
	m_gap = 0;

	// 大きさ、位置、角度の設定
	m_vScale = DirectX::XMFLOAT3(0.5f, 0.5f, 0.5f);
	m_vPos = DirectX::XMFLOAT3(0.0f, 60.0f, -50.0f);		// ディーラーの位置
	m_vAngle = DirectX::XMFLOAT3(180.0f, 180.0f, 0.0f);

	// モデルの初期化
	return CModel::Init();
}

// 終了処理
void CCharacter::Fin()
{
	CModel::Fin();
	m_pTexture = nullptr;
}

// 更新
void CCharacter::Update()
{
	SetVisible(true);

	// ↑キーが押された時
	if (CInput::GetKeyRelease(VK_UP))
	{
		m_vPos.y += 0.5f;
	}
	// ↓キーが押された時
	if (CInput::GetKeyRelease(VK_DOWN))
	{
		m_vPos.y -= 0.5f;
	}
	// →キーが押された時
	if (CInput::GetKeyRelease(VK_RIGHT))
	{
		m_vPos.z += 0.5f;
	}
	// ←キーが押された時
	if (CInput::GetKeyRelease(VK_LEFT))
	{
		m_vPos.z -= 0.5f;
	}

	// Qキーが押された時
	if (CInput::GetKeyRelease(VK_Q))
	{
		m_vAngle.x += 2.0f;
	}
	// Eキーが押された時
	if (CInput::GetKeyRelease(VK_E))
	{
		m_vAngle.x -= 2.0f;
	}
	// Wキーが押された時
	if (CInput::GetKeyRelease(VK_W))
	{
		m_vAngle.y += 2.0f;
	}
	// Sキーが押された時
	if (CInput::GetKeyRelease(VK_S))
	{
		m_vAngle.y -= 2.0f;
	}
	// Dキーが押された時
	if (CInput::GetKeyRelease(VK_D))
	{
		m_vAngle.z += 2.0f;
	}
	// Aキーが押された時
	if (CInput::GetKeyRelease(VK_A))
	{
		m_vAngle.z -= 2.0f;
	}
	// 現在の位置情報、角度の設定
	SetPos(m_vPos);
	SetAngle(m_vAngle);

	// モデルの更新
	CModel::Update();
}

// 描画
void CCharacter::Draw()
{
	TAssimpMaterial *pMat = GetModel()->GetMaterial();

	if (!pMat)
	{
		pMat = new TAssimpMaterial;
	}

	pMat->pTexture = m_pTexture;
	GetModel()->SetMaterial(pMat);
	CModel::Draw();
}
