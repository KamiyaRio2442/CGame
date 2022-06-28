#include "Dealer.h"
#include "Input.h"

// コンストラクタ
CDealer::CDealer(CScene *pScene)
{
}
// デストラクタ
CDealer::~CDealer()
{
}

// 初期化
HRESULT CDealer::Init()
{
	// 現在の手札の初期化
	for (int i = 0; i < EACH_HANDCARD_MAX; i++)
	{
		m_HandCard[i] = 0;
	}

	number = 0;
	m_AttachCardNo = 0;
	m_AttachPlayerNo = 0;
	m_eachcardNumber = 0;
	m_totalNo = 0;

	// フラグの初期化
	m_Attachflag = false;

	return S_OK;
}
// 終了
void CDealer::Fin()
{
}
// 更新
void CDealer::Update()
{
	// 配列にカードナンバーが格納されていたら配列の要素をずらす
	if (m_HandCard[number] != 0)
	{
		number++;
	}

	// カードナンバーの格納
	if (m_HandCard[number] == 0)
	{
		if (m_Attachflag == true)
		{
			// 配られたカードの数値を格納
			m_HandCard[number] = m_eachcardNumber;
			// トータル数値の更新
			m_totalNo += m_HandCard[number];
			// アタッチフラグの無効化
			m_Attachflag = false;
			// 配られたカードの数値を初期化
			m_eachcardNumber = 0;
		}
	}
}