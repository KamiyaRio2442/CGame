//=============================================================================
//
// シーン クラス定義 [Scene.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#pragma once
#include "Camera.h"
#include "Light.h"

// 定数定義
enum EScene {
	SCENE_NONE = 0,		// (シーン無)
	SCENE_TITLE,		// タイトル画面
	SCENE_SELECT,		// セレクト画面
	SCENE_GAME1,		// ゲーム画面１
	SCENE_GAME2,		// ゲーム画面２
	SCENE_RESULT,		// リザルト画面

	MAX_SCENE
};

enum PlayerState
{
	NoState = 0,
	Hit,
	Stay,
	Bust,
	BlackJack,
	DealerStop,
	DealerWait,
};

enum WinLose
{
	NONE,
	WIN,
	LOSE,
	DRAW,
};

typedef struct
{
	WinLose player;
	WinLose dealer;
}BOTH_PLAYERS_WINLOSE;


// クラス定義
class CGameObj;
class CScene {
protected:
	EScene m_id;
	CGameObj* m_pObj;

private:
	static CScene* m_pScene;
	static CScene* m_pTop;
	CScene* m_pBack;
	CScene* m_pNext;

	CCamera* m_pCamera;
	CCamera m_camera;
	CLight* m_pLight;
	CLight m_lightOff;

public:
	CScene();
	virtual ~CScene();

	virtual bool Init();
	virtual void Fin();
	virtual void Update() = 0;
	virtual void Draw() = 0;

	static bool InitAll();
	static void FinAll();
	static void UpdateAll();
	static void DrawAll();

	static void Change(EScene scene);

	CGameObj* GetObj() { return m_pObj; }
	void SetObj(CGameObj* pObj) { m_pObj = pObj; }
	CGameObj* Find(int id = -1, CGameObj* pStart = nullptr);

	CLight* GetLight() { return m_pLight; }
	void SetLight(CLight* pLight);
	CCamera* GetCamera() { return m_pCamera; }
	void SetCamera(CCamera* pCamera);

	static CScene* GetCurrent() { return m_pScene; }
};
