//=============================================================================
//
// ゲーム クラス実装 [Game.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "Game2.h"
#include "Input.h"
#include "GameObj.h"
#include "Sound.h"
#include "Fade.h"
#include "Character.h"
#include "CardManeger.h"

CCardManeger *m_pCM2;

// コンストラクタ
CGame2::CGame2() : CScene()
{
	m_id = SCENE_GAME2;

	m_pPlayer = nullptr;
	m_nBound = 0;
}

// デストラクタ
CGame2::~CGame2()
{
}

// 初期化
bool CGame2::Init()
{
	m_bResult = false;

	// オブジェクト生成
	m_camera.Init();
	m_camera.SetSkyDome(CModel::GetAssimp(MODEL_SKY));
	SetCamera(&m_camera);

	m_light.Init();
	SetLight(&m_light);

	//new CCharacter(this);

	// 全オブジェクト初期化
	if (FAILED(CGameObj::InitAll(m_pObj))) {
		return false;
	}

	m_pCM2 = new CCardManeger(this);
	m_pCM2->SetID((EGameObjType)m_id);
	m_pCM2->Init();
	m_camera.SetPlayer(m_pPlayer);

	return true;
}

// 終了処理
void CGame2::Fin()
{
	// 全オブジェクト終了処理
	CGameObj::FinAll(m_pObj);
}

// 更新
void CGame2::Update()
{
	// 全キャラ更新
	CGameObj::UpdateAll(m_pObj);

	if (!m_bResult) {
		if (CInput::GetKeyRelease(VK_RETURN)) {
			m_bResult = true;
			CFade::Out(SCENE_RESULT);
		}
	}
}

// 描画
void CGame2::Draw()
{
	// 全キャラ描画
	CGameObj::DrawAll(m_pObj);
}
