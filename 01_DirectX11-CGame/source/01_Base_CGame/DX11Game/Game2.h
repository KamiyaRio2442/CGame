#ifndef __GAME2_H__
#define __GAME2_H__

#include "Scene.h"
#include "Card.h"

// クラス定義
class CEnemy;
class CGame2 : public CScene
{
private:
	bool m_bResult;

	// カメラ情報
	CCamera m_camera;
	// ライト情報
	CLight m_light;
	// プレイヤー情報
	CCard* m_pPlayer;
	int m_nBound;

public:
	CGame2();
	virtual ~CGame2();

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

#endif // !__GAME2_H__
