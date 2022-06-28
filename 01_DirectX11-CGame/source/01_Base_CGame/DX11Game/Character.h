#pragma once
#include "Model.h"

class CCharacter : public CModel
{
private:
	ID3D11ShaderResourceView *m_pTexture;
	UINT m_nVertex;	// 頂点数
	TAssimpVertex* m_pVertex;// 頂点配列
	UINT m_nIndex;	// インデックス数
	UINT* m_pIndex;	// インデックス配列

	float m_fSpeed;			// 速さ
	int m_nPat;
	int m_gap;
	bool m_bUseflag;

public:
	CCharacter(CScene* pScene);	// コンストラクタ
	virtual ~CCharacter();		// デストラクタ

	virtual HRESULT Init();	// 初期化
	virtual void Update();		// 終了処理
	virtual void Fin();		// 終了処理
	virtual void Draw();

	// レイとの当たり判定
	bool Collision(XMFLOAT3 vP0, XMFLOAT3 vW, XMFLOAT3* pX = nullptr, XMFLOAT3* pN = nullptr);

};
