#include "Result.h"
#include "Texture.h"
#include "Sound.h"
#include "Input.h"
#include "Polygon.h"
#include "Fade.h"

// 定数定義
namespace {

	// カードのサイズの設定
	const XMFLOAT2 g_fTexCard = { 180.0f, 200.0f };
	// コメントのサイズの設定
	const XMFLOAT2 g_fTexComment = { 800.0f, 200.0f };
	// スタートのサイズの設定
	const XMFLOAT2 g_fTexStart = { 480.0f, 120.0f };

	// リザルト画面に表示するテクスチャの設定
	const LPCWSTR g_pszPathCard[4][4] = {  {L"data/texture/Heart/1.png", L"data/texture/Spade/1.png", L"data/texture/Clover/1.png", L"data/texture/Diamond/1.png" },
										   {L"data/texture/Heart/11.png",L"data/texture/Spade/11.png",L"data/texture/Clover/11.png",L"data/texture/Diamond/11.png"},
										   {L"data/texture/Heart/12.png",L"data/texture/Spade/12.png",L"data/texture/Clover/12.png",L"data/texture/Diamond/12.png"},
										   {L"data/texture/Heart/13.png",L"data/texture/Spade/13.png",L"data/texture/Clover/13.png",L"data/texture/Diamond/13.png"} };

	const LPCWSTR g_pszPathTexComment = L"data/texture/ThankYouForPlaying.png";
	const float g_fTexCommentY = SCREEN_HEIGHT / 10.0f;

	const LPCWSTR g_pszPathTexStart = L"data/texture/PushEnterTex.png";
	const float g_fTexStartY = SCREEN_HEIGHT / -5.0f;

	const LPCWSTR g_pszPathTexBG = L"data/model/color/Black.tif";
}

// コンストラクタ
CResult::CResult() : CScene()
{
	m_id = SCENE_RESULT;

	m_bStart = false;
	m_pTexResult = nullptr;
	m_pTexStart = nullptr;
	m_pTexBG = nullptr;
	m_nTimer = 0;
	dir = 1;

	for (int i = 0; i < 4; i++)
	{
		// 初期位置の基準の設定
		thetaA[i] = (i * DirectX::XM_PIDIV2);
		m_plusangleA[i] = 0.0f;
		thetaJ[i] = (i * DirectX::XM_PIDIV2) - (DirectX::XM_PIDIV2 / 4 * 1);
		m_plusangleJ[i] = -22.5f;
		thetaQ[i] = (i * DirectX::XM_PIDIV2) - (DirectX::XM_PIDIV2 / 4 * 2);
		m_plusangleQ[i] = -45.0f;
		thetaK[i] = (i * DirectX::XM_PIDIV2) - (DirectX::XM_PIDIV2 / 4 * 3);
		m_plusangleK[i] = -67.5f;
	}
}

// デストラクタ
CResult::~CResult()
{
}

// 初期化
bool CResult::Init()
{
	if (!CScene::Init()) {
		return false;
	}

	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();

	m_bStart = false;
	// テクスチャの読み込み
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			hr = CreateTextureFromFile(pDevice, g_pszPathCard[i][j], &m_pTexCard[i][j]);
			if (FAILED(hr))
			{
				Fin();
				return false;
			}
		}
	}
	// コメントテクスチャの読み込み
	hr = CreateTextureFromFile(pDevice, g_pszPathTexComment, &m_pTexComment);
	if (FAILED(hr)) {
		Fin();
		return false;
	}
	// スタートのテクスチャの読み込み
	hr = CreateTextureFromFile(pDevice, g_pszPathTexStart, &m_pTexStart);
	if (FAILED(hr)) {
		Fin();
		return false;
	}
	// 背景色のテクスチャの読み込み
	hr = CreateTextureFromFile(pDevice, g_pszPathTexBG, &m_pTexBG);
	if (FAILED(hr)) {
		Fin();
		return false;
	}

	m_nTimer = 0;

	//// BGM再生開始
	//CSound::Play(BGM_TITLE);

	return true;
}

// 終了処理
void CResult::Fin()
{
	//// BGM再生停止
	//CSound::Stop(BGM_TITLE);

	SAFE_RELEASE(m_pTexBG);
	SAFE_RELEASE(m_pTexComment);
	SAFE_RELEASE(m_pTexStart);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			SAFE_RELEASE(m_pTexCard[i][j]);
		}
	}

	CScene::Fin();
}

// 更新
void CResult::Update()
{
	++m_nTimer;
	if (m_nTimer > 120) {
		m_nTimer = 0;
	}

	// 回転時の位置情報の計算
	for (int i = 0; i < 4; i++)
	{
		thetaA[i] -= (5 / 60.0f) * DirectX::XM_PI / 180.0f * dir;
		m_plusangleA[i] -= (50.0f / 60.0f) * 0.1f * dir;
		thetaJ[i] -= (5 / 60.0f) * DirectX::XM_PI / 180.0f * dir;
		m_plusangleJ[i] -= (50.0f / 60.0f) * 0.1f * dir;
		thetaQ[i] -= (5 / 60.0f) * DirectX::XM_PI / 180.0f * dir;
		m_plusangleQ[i] -= (50.0f / 60.0f) * 0.1f * dir;
		thetaK[i] -= (5 / 60.0f) * DirectX::XM_PI / 180.0f * dir;
		m_plusangleK[i] -= (50.0f / 60.0f) * 0.1f * dir;
	}

	//// 回転（正方向）
	//if (thetaA >= DirectX::XM_PI)
	//{
	//	dir = 1;
	//}
	//// 回転（負方向）
	//else if (thetaA <= DirectX::XM_PIDIV2)
	//{
	//	dir = -1;
	//}

	if (!m_bStart) {
		if (CInput::GetKeyRelease(VK_RETURN)) {
			m_bStart = true;
			CFade::Out(SCENE_TITLE);
		}
	}
}

// 描画
void CResult::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	SetZBuffer(false);
	SetBlendState(BS_ALPHABLEND);

	CPolygon::SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	CPolygon::SetUV(0.0f, 0.0f);
	CPolygon::SetFrameSize(1.0f, 1.0f);
	CPolygon::TextureDraw(m_pTexBG, { 0.0f, 0.0f }, 0.0f, { SCREEN_WIDTH, SCREEN_HEIGHT }, pDC);

	// 各テクスチャの描画位置の設定
	for (int i = 0; i < 4; i++)
	{
		// ハート札
		CPolygon::SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		CPolygon::TextureDraw(m_pTexCard[i][0], { cosf(thetaA[i]) * (SCREEN_HEIGHT - 120) + (SCREEN_W_HALF * 1.125f), sinf(thetaA[i]) * (SCREEN_HEIGHT - 120) - SCREEN_H_HALF },
			m_plusangleA[i] + (90.0f * (i - 1)), { g_fTexCard.x, g_fTexCard.y }, pDC);
		CPolygon::TextureDraw(m_pTexCard[i][0], { -cosf(thetaA[i] + 3.14) * (SCREEN_HEIGHT - 120) - (SCREEN_W_HALF * 1.125f), sinf(thetaA[i] + 3.14) * (SCREEN_HEIGHT - 120) - SCREEN_H_HALF },
			-90.0f - m_plusangleA[i] + (90.0f * (4 - i)), { g_fTexCard.x, g_fTexCard.y }, pDC);

		// スペード札
		CPolygon::TextureDraw(m_pTexCard[i][1], { cosf(thetaJ[i]) * (SCREEN_HEIGHT - 120) + (SCREEN_W_HALF * 1.125f), sinf(thetaJ[i]) * (SCREEN_HEIGHT - 120) - SCREEN_H_HALF },
			m_plusangleJ[i] + (90.0f * (i - 1)), { g_fTexCard.x, g_fTexCard.y }, pDC);
		CPolygon::TextureDraw(m_pTexCard[i][1], { -cosf(thetaJ[i] + 3.14) * (SCREEN_HEIGHT - 120) - (SCREEN_W_HALF * 1.125f), sinf(thetaJ[i] + 3.14) * (SCREEN_HEIGHT - 120) - SCREEN_H_HALF },
			-90.0f - m_plusangleJ[i] + (90.0f * (4 - i)), { g_fTexCard.x, g_fTexCard.y }, pDC);

		// クローバー札
		CPolygon::TextureDraw(m_pTexCard[i][2], { cosf(thetaQ[i]) * (SCREEN_HEIGHT - 120) + (SCREEN_W_HALF * 1.125f), sinf(thetaQ[i]) * (SCREEN_HEIGHT - 120) - SCREEN_H_HALF },
			m_plusangleQ[i] + (90.0f * (i - 1)), { g_fTexCard.x, g_fTexCard.y }, pDC);
		CPolygon::TextureDraw(m_pTexCard[i][2], { -cosf(thetaQ[i] + 3.14) * (SCREEN_HEIGHT - 120) - (SCREEN_W_HALF * 1.125f), sinf(thetaQ[i] + 3.14) * (SCREEN_HEIGHT - 120) - SCREEN_H_HALF },
			-90.0f - m_plusangleQ[i] + (90.0f * (4 - i)), { g_fTexCard.x, g_fTexCard.y }, pDC);

		// ダイアモンド札
		CPolygon::TextureDraw(m_pTexCard[i][3], { cosf(thetaK[i]) * (SCREEN_HEIGHT - 120) + (SCREEN_W_HALF * 1.125f), sinf(thetaK[i]) * (SCREEN_HEIGHT - 120) - SCREEN_H_HALF },
			m_plusangleK[i] + (90.0f * (i - 1)), { g_fTexCard.x, g_fTexCard.y }, pDC);
		CPolygon::TextureDraw(m_pTexCard[i][3], { -cosf(thetaK[i] + 3.14) * (SCREEN_HEIGHT - 120) - (SCREEN_W_HALF * 1.125f), sinf(thetaK[i] + 3.14) * (SCREEN_HEIGHT - 120) - SCREEN_H_HALF },
			-90.0f - m_plusangleK[i] + (90.0f * (4 - i)), { g_fTexCard.x, g_fTexCard.y }, pDC);

		//CPolygon::SetAngle(90.0f - m_plusangleK[i] + (90.0f * (4 - i)));
		//CPolygon::SetPos(
		//	-cosf(thetaK[i]) * (SCREEN_HEIGHT - 120) - (SCREEN_WIDTH / 2),
		//	sinf(thetaK[i]) * (SCREEN_HEIGHT - 120) - (SCREEN_HEIGHT / 2));
		//CPolygon::Draw(pDC);
	}

	CPolygon::SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	CPolygon::TextureDraw(m_pTexComment, { 0.0f, g_fTexCommentY }, 0.0f, { g_fTexComment.x, g_fTexComment.y }, pDC);

	CPolygon::SetColor(1.0f, 1.0f, 1.0f, (m_nTimer <= 60) ? m_nTimer / 60.0f : (120 - m_nTimer) / 60.0f);
	CPolygon::TextureDraw(m_pTexStart, { 0.0f, g_fTexStartY }, 0.0f, { g_fTexStart.x, g_fTexStart.y }, pDC);
}