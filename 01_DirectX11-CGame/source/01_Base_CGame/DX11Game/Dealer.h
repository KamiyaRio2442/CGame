#pragma once
#include "Card.h"

class CDealer
{
private:
	// 手札
	int m_HandCard[EACH_HANDCARD_MAX];
	// 現在の配布カードの数値
	int m_eachcardNumber;
	int m_AttachPlayerNo;
	// 手札カードの灰数
	int m_AttachCardNo;
	// トータル数値
	int m_totalNo;
	// アタッチフラグ
	bool m_Attachflag;

public:
	CDealer(CScene *pScene);
	~CDealer();

	virtual HRESULT Init();	 // 初期化
	virtual void Fin();		 // 終了処理
	virtual void Update();	 // 更新

	// アタッチフラグの設定、取得
	void SetAttachFlag(bool vAttachFlag) { m_Attachflag = vAttachFlag; }
	bool& GetAttachFlag() { return m_Attachflag; }
	// 現在のカード数値の設定、取得
	void SetAttachCardInfo(int vCardNo) { m_eachcardNumber = vCardNo; }
	int& GetAttachCardInfo() { return m_eachcardNumber; }
	// トータル数値の取得
	int& GetTotalNo() { return m_totalNo; }

public:
	// ナンバー
	int number;

};
