#pragma once
#include "Scene.h"

// クラス定義
class CSelect : public CScene
{
private:
	bool m_bStart;
	// 選択テクスチャ情報
	ID3D11ShaderResourceView* m_pTexSelect;
	// スタートテクスチャ情報
	ID3D11ShaderResourceView* m_pTexStart;
	// 背景色テクスチャ情報
	ID3D11ShaderResourceView* m_pTexBG;
	// タイマー
	int m_nTimer;

public:
	CSelect();
	virtual ~CSelect();

	// 初期化
	virtual bool Init();
	// 終了
	virtual void Fin();
	// 更新
	virtual void Update();
	// 描画
	virtual void Draw();
};
