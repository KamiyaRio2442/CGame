#include "Select.h"
#include "Texture.h"
#include "Sound.h"
#include "Input.h"
#include "Polygon.h"
#include "Fade.h"

// 定数定義
namespace {
	const LPCWSTR g_pszPathTexTitle = L"data/texture/OC1_Green.png";
	const float g_fTexTitleWidth = 800.0f;
	const float g_fTexTitleHeight = 320.0f;

	const LPCWSTR g_pszPathTexStart = L"data/texture/press_enter.png";
	const float g_fTexStartWidth = 480.0f;
	const float g_fTexStartHeight = 120.0f;
	const float g_fTexStartY = SCREEN_HEIGHT / -3.0f;

	const LPCWSTR g_pszPathTexBG = L"data/model/color/Blue.tif";
}

// コンストラクタ
CSelect::CSelect() : CScene()
{
	m_id = SCENE_SELECT;

	m_bStart = false;
	m_pTexSelect = nullptr;
	m_pTexStart = nullptr;
	m_pTexBG = nullptr;
	m_nTimer = 0;
}

// デストラクタ
CSelect::~CSelect()
{
}

// 初期化
bool CSelect::Init()
{
	if (!CScene::Init()) {
		return false;
	}

	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();

	m_bStart = false;
	// テクスチャの読み込み
	hr = CreateTextureFromFile(pDevice, g_pszPathTexTitle, &m_pTexSelect);
	if (FAILED(hr)) {
		return false;
	}
	hr = CreateTextureFromFile(pDevice, g_pszPathTexStart, &m_pTexStart);
	if (FAILED(hr)) {
		Fin();
		return false;
	}
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
void CSelect::Fin()
{
	//// BGM再生停止
	//CSound::Stop(BGM_TITLE);

	SAFE_RELEASE(m_pTexBG);
	SAFE_RELEASE(m_pTexStart);
	SAFE_RELEASE(m_pTexSelect);

	CScene::Fin();
}

// 更新
void CSelect::Update()
{
	++m_nTimer;
	if (m_nTimer > 120) {
		m_nTimer = 0;
	}

	if (!m_bStart) {
		if (CInput::GetKeyRelease(VK_RETURN)) {
			m_bStart = true;
			CFade::Out(SCENE_GAME1);
		}

		if (CInput::GetKeyRelease(VK_SPACE))
		{
			m_bStart = true;
			CFade::Out(SCENE_GAME2);
		}
	}
}

// 描画
void CSelect::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	SetZBuffer(false);
	SetBlendState(BS_ALPHABLEND);

	CPolygon::SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	CPolygon::SetTexture(m_pTexBG);
	CPolygon::SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	CPolygon::SetUV(0.0f, 0.0f);
	CPolygon::SetFrameSize(1.0f, 1.0f);
	CPolygon::SetPos(0.0f, 0.0f);
	CPolygon::Draw(pDC);

	CPolygon::SetTexture(m_pTexSelect);
	CPolygon::SetSize(g_fTexTitleWidth, g_fTexTitleHeight);
	CPolygon::SetPos(0.0f, 100.0f);
	CPolygon::Draw(pDC);

	CPolygon::SetAlpha((m_nTimer <= 60) ? m_nTimer / 60.0f : (120 - m_nTimer) / 60.0f);
	CPolygon::SetTexture(m_pTexStart);
	CPolygon::SetSize(g_fTexStartWidth, g_fTexStartHeight);
	CPolygon::SetPos(0.0f, g_fTexStartY);
	CPolygon::Draw(pDC);
}
