#include "Player.h"
#include "Input.h"

CPlayer::CPlayer(CScene* pScene) : CModel(pScene)
{
}

CPlayer::~CPlayer()
{
}

HRESULT CPlayer::Init()
{
	// 変数の初期化
	number = 0;

	// 手札情報の初期化
	for (int i = 0; i < EACH_HANDCARD_MAX; i++)
	{
		m_HandCard[i] = 0;
	}

	m_eachcardNumber = 0;
	m_AttachCardNo = 0;
	m_AttachPlayerNo = 0;
	m_totalNo = 0;

	// フラグの初期化
	m_Attachflag = false;

	return S_OK;
}
void CPlayer::Fin()
{
}
void CPlayer::Update()
{
	// 配列にカードナンバーが格納されていたら配列の要素をずらす
	if (m_HandCard[number] != 0)
	{
		number++;
	}
	// カードナンバーの格納
	else if (m_HandCard[number] == 0)
	{
		m_HandCard[number] = m_eachcardNumber;
		m_totalNo += m_HandCard[number]; 
		m_eachcardNumber = 0;
	}
}