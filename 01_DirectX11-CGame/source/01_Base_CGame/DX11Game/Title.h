//=============================================================================
//
// タイトル画面クラス定義 [Title.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#pragma once
#include "Scene.h"

// クラス定義
class CTitle : public CScene
{
private:
	bool m_bStart;
	// タイトルテクスチャ情報
	ID3D11ShaderResourceView* m_pTexTitle;
	// 選択テクスチャ情報
	ID3D11ShaderResourceView* m_pTexSelect[4];
	// スタートテクスチャ情報
	ID3D11ShaderResourceView* m_pTexStart;
	// 背景色テクスチャ情報
	ID3D11ShaderResourceView* m_pTexBG;
	// 選択ゲーム輪郭テクスチャ情報
	ID3D11ShaderResourceView* m_pTexAlpha;
	// 未実装テクスチャ情報
	ID3D11ShaderResourceView* m_pTexUnimple;
	// タイマー
	int m_nTimer;
	// 選択ゲーム番号
	int m_select;
	// 回転
	int m_roll;
	XMFLOAT2 m_selectpos;
	float m_changeangle;
	// ゲーム１選択
	float m_changeangleA;
	// ゲーム２選択
	float m_changeangleB;
	bool m_caA;
	bool m_caB;

	// 未実装フラグ
	bool m_Unimplementedflag;

	// 選択ゲーム輪郭カラー
	XMFLOAT4 m_backcardcolor;

public:
	CTitle();
	virtual ~CTitle();

	// 初期化
	virtual bool Init();
	// 終了
	virtual void Fin();
	// 更新
	virtual void Update();
	// 描画
	virtual void Draw();

};
