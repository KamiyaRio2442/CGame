//=============================================================================
//
// ゲーム クラス定義 [Game.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#ifndef __GAME1_H__
#define __GAME1_H__

#include "Scene.h"
#include "Card.h"
#include "PlayerManager.h"

// クラス定義
class CEnemy;
class CGame1 : public CScene
{
private:
	// リザルトフラグ
	bool m_bResult;
	
	// カメラ情報
	CCamera m_camera;
	// ライト情報
	CLight m_light;
	// プレイヤー情報
	CCard* m_pPlayer;

	int m_nBound;
	// 続行フラグ
	bool m_continueflag;

public:
	CGame1();
	virtual ~CGame1();

	// 初期化
	virtual bool Init();
	// 終了
	virtual void Fin();
	// 更新
	virtual void Update();
	// 描画
	virtual void Draw();

	int GetBound() { return m_nBound; }
};

#endif // !__GAME1_H__
