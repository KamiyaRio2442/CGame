//=============================================================================
//
// オブジェクト クラス定義 [GameObj.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#pragma once
#include "main.h"
#include "Box.h"		// デバッグ表示用
#include "Sphere.h"		// デバッグ表示用

// 定数定義
enum EGameObjType {		// オブジェクト型
	GOT_GAMEOBJ = 0,	// 型無し
	GOT_PLAYER,			// プレイヤー
	GOT_LAND,			// 地面
	GOT_CHARACTER,			// 地面

	MAX_GAMEOBJTYPE
};

// クラス定義
class CScene;
class CGameObj
{
private:
	EGameObjType m_id;		// オブジェクト型

	CGameObj* m_pBack;		// 前のオブジェクト
	CGameObj* m_pNext;		// 次のオブジェクト

protected:
	CScene* m_pScene;		// 所属シーン

	XMFLOAT3 m_vPos;		// 座標
	XMFLOAT3 m_vVel;		// 速度
	XMFLOAT3 m_vAccel;		// 加速度
	XMFLOAT3 m_vAngle;		// 角度
	XMFLOAT3 m_vScale;		// 拡縮

	XMFLOAT4X4 m_mWorld;	// ワールド変換

	bool m_bVisible;		// 表示フラグ

	XMFLOAT3 m_vCenter;		// 境界ボックス(/球)中心座標
	XMFLOAT3 m_vBBox;		// 境界ボックス
	float m_fRadius;		// 境界球半径

	CBox* m_pBBox;			// 境界ボックス表示用メッシュ
	CSphere* m_pBSphere;	// 境界球表示用メッシュ
	bool m_bBBox;			// 境界ボックス表示用フラグ
	bool m_bBSphere;		// 境界球表示用フラグ

public:
	CGameObj(CScene* pScene);
	virtual ~CGameObj(void);

	virtual HRESULT Init();		// 初期化
	virtual void Update();		// 更新
	virtual void Draw();		// 不透明部分描画
	virtual void DrawAlpha();	// 半透明部分描画
	virtual void Fin();			// 終了処理

	static HRESULT InitAll(CGameObj* pTop);
	static void UpdateAll(CGameObj* pTop);
	static void DrawAll(CGameObj* pTop);
	static void FinAll(CGameObj* pTop);

	void SetPos(XMFLOAT3 vPos) { m_vPos = vPos; }
	XMFLOAT3& GetPos() { return m_vPos; }
	void SetAngle(XMFLOAT3 vAngle) { m_vAngle = vAngle; }
	XMFLOAT3& GetAngle() { return m_vAngle; }
	void SetScale(XMFLOAT3 vScale) { m_vScale = vScale; }
	XMFLOAT3& GetScale() { return m_vScale; }
	void SetVelocity(XMFLOAT3 vVel) { m_vVel = vVel; }
	XMFLOAT3& GetVelocity() { return m_vVel; }
	void SetWorld(XMFLOAT4X4& mWorld) { m_mWorld = mWorld; }
	XMFLOAT4X4& GetWorld() { return m_mWorld; }

	EGameObjType GetID() { return m_id; }
	void SetID(EGameObjType id) { m_id = id; }
	CGameObj* GetNext() { return m_pNext; }

	void SetVisible(bool bVisible = true) { m_bVisible = bVisible; }
	bool GetVisible() { return m_bVisible; }

	void SetCenter(XMFLOAT3 vCenter) { m_vCenter = vCenter; }
	XMFLOAT3& GetCenter() { return m_vCenter; }
	void SetBBox(XMFLOAT3 vBBox);
	XMFLOAT3& GetBBox() { return m_vBBox; }
	void SetRadius(float fRadius);
	float GetRadius() { return m_fRadius; }

	bool CollisionAABB(CGameObj* pOther);
	bool CollisionBS(CGameObj* pOther);

	void SetBBoxVisible(bool bVisible = true);
	void SetBSphereVisible(bool bVisible = true);
};
