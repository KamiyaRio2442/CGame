#pragma once
#include "Model.h"
#include "Card.h"

const int g_nEachHandCardMax = 12;

class CPlayer :public CModel
{
private:
	// 手札のそれぞれの番号を格納する配列
	int m_HandCard[EACH_HANDCARD_MAX];
	// 数字を一時保存しておく変数
	int m_eachcardNumber;
	// 今の手持ちの合計
	int m_totalNo;
	// 今どの配列の要素まで数字が格納されているか
	int number;

	int m_AttachPlayerNo;
	int m_AttachCardNo;
	bool m_Attachflag;

public:
	CPlayer(CScene* pScene);
	~CPlayer();

	virtual HRESULT Init();	 // 初期化
	virtual void Fin();		 // 終了処理
	virtual void Update();	 // 更新

	// アタッチフラグの設定、取得
	void SetAttachFlag(bool vAttachFlag) { m_Attachflag = vAttachFlag; }
	bool& GetAttachFlag() { return m_Attachflag; }
	void SetAttachCardInfo(int vCardNo) { m_eachcardNumber = vCardNo; }
	int& GetAttachCardInfo() { return m_eachcardNumber; }
	void SetAttachNum(int vNo) { number = vNo; }
	int& GetAttachNum() { return number; }
	int GetTotalNo() { return m_totalNo; }

};
