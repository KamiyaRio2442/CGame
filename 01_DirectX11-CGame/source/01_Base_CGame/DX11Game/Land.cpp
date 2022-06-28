// 地面 [Land.cpp]
#include "Land.h"

// コンストラクタ
CLand::CLand(CScene* pScene) : CModel(pScene)
{
	SetID(GOT_LAND);

	m_pVertex = nullptr;
	m_nVertex = 0;
	m_pIndex = nullptr;
	m_nIndex = 0;
}

// デストラクタ
CLand::~CLand()
{
}

// 初期化
HRESULT CLand::Init()
{
	SetModel(MODEL_LAND);

	// 頂点配列、インデックス配列を取得しておく
	CAssimpModel* pModel = GetAssimp(MODEL_LAND);
	pModel->GetVertexCount(&m_nVertex, &m_nIndex);
	m_pVertex = new TAssimpVertex[m_nVertex];
	m_pIndex = new UINT[m_nIndex];
	pModel->GetVertex(m_pVertex, m_pIndex);

	return CModel::Init();
}

// 終了処理
void CLand::Fin()
{
	CModel::Fin();

	// 頂点配列、インデックス配列の解放
	SAFE_DELETE_ARRAY(m_pIndex);
	SAFE_DELETE_ARRAY(m_pVertex);
}

// レイとの当たり判定
bool CLand::Collision(XMFLOAT3 vP0, XMFLOAT3 vW, XMFLOAT3* pX, XMFLOAT3* pN)
{
	// 全ての三角形について
	for (UINT i = 0; i < m_nIndex; i += 3) {
		// 三角形の頂点座標
		XMFLOAT3& V0 = m_pVertex[m_pIndex[i + 0]].vPos;
		XMFLOAT3& V1 = m_pVertex[m_pIndex[i + 1]].vPos;
		XMFLOAT3& V2 = m_pVertex[m_pIndex[i + 2]].vPos;
		// 辺に対応するベクトル
		XMFLOAT3 V0V1(V1.x - V0.x, V1.y - V0.y, V1.z - V0.z);
		XMFLOAT3 V1V2(V2.x - V1.x, V2.y - V1.y, V2.z - V1.z);
		XMFLOAT3 V2V0(V0.x - V2.x, V0.y - V2.y, V0.z - V2.z);
		// 三角形(=平面)の法線ベクトルを求める
		XMVECTOR N = XMVector3Normalize(XMVector3Cross(XMLoadFloat3(&V0V1), XMLoadFloat3(&V1V2)));
		// tの式(t=(N・(V0-P0))/(N・W))の分母を求める
		float base;
		XMStoreFloat(&base, XMVector3Dot(N, XMLoadFloat3(&vW)));
		if (base == 0.0f)
			continue;	// 面とレイが平行
		// 分子を求める
		XMFLOAT3 P0V0(V0.x - vP0.x, V0.y - vP0.y, V0.z - vP0.z);
		float dot;
		XMStoreFloat(&dot, XMVector3Dot(N, XMLoadFloat3(&P0V0)));
		// tから交点を求める
		float t = dot / base;
		if (t < 0.0f)
			continue;	// 交点が始点の後ろ
		XMFLOAT3 X(vP0.x + t * vW.x, vP0.y + t * vW.y, vP0.z + t * vW.z);
		// 内外判定
		XMFLOAT3 V0X(X.x - V0.x, X.y - V0.y, X.z - V0.z);
		XMStoreFloat(&dot, XMVector3Dot(N, XMVector3Cross(XMLoadFloat3(&V0V1), XMLoadFloat3(&V0X))));
		if (dot < 0.0f)
			continue;
		XMFLOAT3 V1X(X.x - V1.x, X.y - V1.y, X.z - V1.z);
		XMStoreFloat(&dot, XMVector3Dot(N, XMVector3Cross(XMLoadFloat3(&V1V2), XMLoadFloat3(&V1X))));
		if (dot < 0.0f)
			continue;
		XMFLOAT3 V2X(X.x - V2.x, X.y - V2.y, X.z - V2.z);
		XMStoreFloat(&dot, XMVector3Dot(N, XMVector3Cross(XMLoadFloat3(&V2V0), XMLoadFloat3(&V2X))));
		if (dot < 0.0f)
			continue;
		// 当たり
		if (pX) *pX = X;
		if (pN) XMStoreFloat3(pN, N);
		return true;// 当たっている
	}
	return false;	// 当たっていない
}
