#pragma once
#include "Player.h"
#include "GameObj.h"

class CPlayerManager : public CGameObj
{
private:
	CPlayer *m_pPlayerList[PLAYER_MAX - 1];
	// フラグ
	bool m_flag;
	// アタッチフラグ
	bool m_attachflag;
	// 現在のカード数値
	int m_AttachCardNo;
	int m_AttachPlayerNo;
	// 数値保持
	int m_Nokeep[PLAYER_MAX - 1];

public:
	CPlayerManager(CScene* pScene);
	~CPlayerManager();

	virtual HRESULT Init();	 // 初期化
	virtual void Fin();		 // 終了処理
	virtual void Update();	 // 更新
	virtual void Draw();	 // 描画

	// 現在のプレイヤー番号の設定、取得
	void SetAttachPlayerNo(int vPNo) { m_AttachPlayerNo = vPNo; }
	int& GetAttachPlayerNo() { return m_AttachPlayerNo; }
	// 現在のカード数値の設定、取得
	void SetAttachCardNo(int vCNo) { m_AttachCardNo = vCNo; }
	int& GetAttachCardNo() { return m_AttachCardNo; }
	// 配布ナンバーの保持
	int& GetEachNoKeep(int vNo) { return m_Nokeep[vNo]; }

};