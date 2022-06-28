//=============================================================================
//
// �^�C�g����ʃN���X���� [Title.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "Title.h"
#include "Texture.h"
#include "Sound.h"
#include "Input.h"
#include "Polygon.h"
#include "Fade.h"

// �萔��`
namespace 
{
	const LPCWSTR g_pszPathTexBG = L"data/model/color/Black.tif";
	const LPCWSTR g_pszPathTexTitle = L"data/texture/Title.png";

	// �e�}�[�N�̃J�[�h�̃e�N�X�`���ݒ�
	const LPCWSTR g_pszPathTexSelect[4] = { L"data/texture/Heart/1.png",
											L"data/texture/Spade/1.png",
											L"data/texture/Clover/1.png",
											L"data/texture/Diamond/1.png" };

	const LPCWSTR g_pszPathTexStart = L"data/texture/PushEnterTex.png";
	
	const LPCWSTR g_pszPathTexUnimple = L"data/texture/Unimplemented.png";
	
	// �I���Q�[���̗֊s�\���̃T�C�Y�̐ݒ�
	const XMFLOAT2 g_fTexAlpha = { 170.0f, 190.0f };
	// �I���Q�[���̃T�C�Y�̐ݒ�
	const XMFLOAT2 g_fTexSelect = { 160.0f, 180.0f };
	// �I���Q�[���̃T�C�Y�̐ݒ�
	const XMFLOAT2 g_fTexUnimple = {250.0f,100.0f };
	// Enter�e�N�X�`���̃T�C�Y�̐ݒ�
	const XMFLOAT2 g_fTexStart = { 480.0f, 120.0f };
	const float g_fTexStartY = SCREEN_HEIGHT / -3.5f;
}

// �R���X�g���N�^
CTitle::CTitle() : CScene()
{
	m_id = SCENE_TITLE;

	// �ϐ��̏�����
	m_bStart = false;
	for (int i = 0; i < 4; i++)
	{
		m_pTexSelect[i] = nullptr;
	}
	m_pTexStart = nullptr;
	m_pTexBG = nullptr;
	m_nTimer = 0;
	m_select = 0;
	m_roll = 20;
	m_selectpos = { -300.0f, -100.0f };
	m_changeangleA = 20.0f;
	m_changeangleB = 0.0f;
	m_changeangle = m_changeangleA;
	// �t���O�̏�����
	m_caA = true;
	m_caB = false;
	m_Unimplementedflag = false;
	m_backcardcolor = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
}

// �f�X�g���N�^
CTitle::~CTitle()
{
}

// ������
bool CTitle::Init()
{
	if (!CScene::Init()) 
	{
		return false;
	}

	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();

	m_bStart = false;
	// �e�N�X�`���̓ǂݍ���
	hr = CreateTextureFromFile(pDevice, g_pszPathTexTitle, &m_pTexTitle);
	if (FAILED(hr))
	{
		Fin();
		return false;
	}
	// �I���e�N�X�`���̓ǂݍ���
	for (int i = 0; i < 4; i++)
	{
		hr = CreateTextureFromFile(pDevice, g_pszPathTexSelect[i], &m_pTexSelect[i]);
		if (FAILED(hr))
		{
			Fin();
			return false;
		}
	}
	// �X�^�[�g�e�N�X�`���̓ǂݍ���
	hr = CreateTextureFromFile(pDevice, g_pszPathTexStart, &m_pTexStart);
	if (FAILED(hr)) 
	{
		Fin();
		return false;
	}
	// �w�i�F�e�N�X�`���̓ǂݍ���
	hr = CreateTextureFromFile(pDevice, g_pszPathTexBG, &m_pTexBG);
	if (FAILED(hr)) 
	{
		Fin();
		return false;
	}
	// �������e�N�X�`���̓ǂݍ���
	hr = CreateTextureFromFile(pDevice, g_pszPathTexUnimple, &m_pTexUnimple);
	if (FAILED(hr))
	{
		Fin();
		return false;
	}

	m_nTimer = 0;

	//// BGM�Đ��J�n
	//CSound::Play(BGM_TITLE);

	return true;
}

// �I������
void CTitle::Fin()
{
	//// BGM�Đ���~
	//CSound::Stop(BGM_TITLE);

	SAFE_RELEASE(m_pTexBG);
	SAFE_RELEASE(m_pTexStart);
	for (int i = 0; i < 4; i++)
	{
		SAFE_RELEASE(m_pTexSelect[i]);
	}

	CScene::Fin();
}

// �X�V
void CTitle::Update()
{
	++m_nTimer;
	if (m_nTimer > 120) 
	{
		m_nTimer = 0;
	}

	// ���L�[�������ꂽ��
	if (CInput::GetKeyRelease(VK_RIGHT))
	{
		if (m_roll >= 20)
		{
			m_roll = 0;
		}

		m_select = 1;
		m_selectpos = { 300.0f, -100.0f };
		m_changeangleA = 0.0f;
		m_caA = false;
		m_caB = true;
	}
	// ���L�[�������ꂽ��
	if (CInput::GetKeyRelease(VK_LEFT))
	{
		if (m_roll >= 20)
		{
			m_roll = 0;
		}
		m_select = 0;
		m_selectpos = { -300.0f,-100.0f };
		m_changeangleB = 0.0f;
		m_caA = true;
		m_caB = false;
	}

	// �A�j���[�V�����̐ݒ�
	if (m_caA == true && m_roll < 20)
	{
		m_Unimplementedflag = false;
		m_changeangleA = 1.0f * m_roll;
		m_changeangle = m_changeangleA;
		m_roll++;
	}
	if (m_caB == true && m_roll < 20)
	{
		m_changeangleB = 1.0f * m_roll;
		m_changeangle = m_changeangleB;
		m_roll++;
	}

	if (!m_bStart) 
	{
		// �Q�[���P���I�����ꂽ��
		if (CInput::GetKeyRelease(VK_RETURN) && m_select == 0) 
		{
			m_bStart = true;
			CFade::Out(SCENE_GAME1);
			m_Unimplementedflag = false;
		}
		// �Q�[���Q���I�����ꂽ��
		else if (CInput::GetKeyRelease(VK_RETURN) && m_select == 1)
		{
			//m_bStart = true;
			//CFade::Out(SCENE_GAME2);
			m_Unimplementedflag = true;
		}
	}
}

// �`��
void CTitle::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	SetZBuffer(false);
	SetBlendState(BS_ALPHABLEND);

	// �e�e�N�X�`���̕`��ʒu�̐ݒ�
	CPolygon::SetUV(0.0f, 0.0f);
	CPolygon::SetFrameSize(1.0f, 1.0f);
	CPolygon::SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	CPolygon::TextureDraw(m_pTexBG, { 0.0f,0.0f }, 0.0f, { SCREEN_WIDTH, SCREEN_HEIGHT }, pDC);

	CPolygon::TextureDraw(m_pTexTitle, { 0.0, SCREEN_HEIGHT / 4 }, 0.0f,
							{ SCREEN_WIDTH / 2 * 1.5f, SCREEN_HEIGHT / 4 * 1.5f }, pDC);

	CPolygon::SetColor(m_backcardcolor);
	CPolygon::TextureDraw(m_pTexSelect[0], { m_selectpos.x - (m_changeangle * 0.65f),
							m_selectpos.y + (m_changeangle * 0.025f) }, m_changeangle, { g_fTexAlpha.x, g_fTexAlpha.y }, pDC);

	CPolygon::SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	CPolygon::TextureDraw(m_pTexSelect[2], { 300.0f - (m_changeangleB * 0.65f), -100.0f },
							m_changeangleB, { g_fTexSelect.x, g_fTexSelect.y }, pDC);

	CPolygon::TextureDraw(m_pTexSelect[3], { -300.0f - (m_changeangleA * 0.65f), -100.0f },
							m_changeangleA, { g_fTexSelect.x, g_fTexSelect.y }, pDC);

	CPolygon::SetColor(m_backcardcolor);
	CPolygon::TextureDraw(m_pTexSelect[0], { m_selectpos.x + (m_changeangle * 0.65f),
							m_selectpos.y + (m_changeangle * 0.025f) }, -m_changeangle, { g_fTexAlpha.x, g_fTexAlpha.y }, pDC);

	CPolygon::SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	CPolygon::TextureDraw(m_pTexSelect[1], { 300.0f + (m_changeangleB * 0.65f), -100.0f },
							-m_changeangleB, { g_fTexSelect.x, g_fTexSelect.y }, pDC);

	CPolygon::TextureDraw(m_pTexSelect[0], { -300.0f + (m_changeangleA * 0.65f), -100.0f },
							-m_changeangleA, { g_fTexSelect.x, g_fTexSelect.y }, pDC);

	if (m_Unimplementedflag == true)
	{
		CPolygon::SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		CPolygon::TextureDraw(m_pTexUnimple, { 310.0f - (m_changeangleB * 0.65f), -100.0f },
			0.0f, { g_fTexUnimple.x, g_fTexUnimple.y }, pDC);
	}
	else
	{
		CPolygon::SetColor(1.0f, 1.0f, 1.0f, 0.0f);
		CPolygon::TextureDraw(m_pTexUnimple, { 310.0f - (m_changeangleB * 0.65f), -100.0f },
			0.0f, { g_fTexUnimple.x, g_fTexUnimple.y }, pDC);
	}

	CPolygon::SetColor(1.0f, 1.0f, 1.0f, (m_nTimer <= 60) ? m_nTimer / 60.0f : (120 - m_nTimer) / 60.0f);
	CPolygon::TextureDraw(m_pTexStart, { 0.0f, g_fTexStartY }, 0.0f, { g_fTexStart.x, g_fTexStart.y }, pDC);
}