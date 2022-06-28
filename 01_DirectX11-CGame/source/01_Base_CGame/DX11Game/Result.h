#pragma once
#include "Scene.h"

// クラス定義
class CResult : public CScene
{
private:
	bool m_bStart;
	// リザルトテクスチャ情報
	ID3D11ShaderResourceView* m_pTexResult;
	// スタートテクスチャ情報
	ID3D11ShaderResourceView* m_pTexStart;
	// コメントテクスチャ情報
	ID3D11ShaderResourceView* m_pTexComment;
	// 背景色テクスチャ情報
	ID3D11ShaderResourceView* m_pTexBG;
	// 各カードテクスチャ情報
	ID3D11ShaderResourceView* m_pTexCard[4][4];

	// タイマー
	int m_nTimer;
	// Aマークの回転情報
	float thetaA[4];
	float m_plusangleA[4];
	// Jマークの回転情報
	float thetaJ[4];
	float m_plusangleJ[4];
	// Qマークの回転情報
	float thetaQ[4];
	float m_plusangleQ[4];
	// Kマークの回転情報
	float thetaK[4];
	float m_plusangleK[4];
	// 距離
	int dir;

public:
	CResult();
	virtual ~CResult();

	// 初期化
	virtual bool Init();
	// 終了
	virtual void Fin();
	// 更新
	virtual void Update();
	// 描画
	virtual void Draw();
};
