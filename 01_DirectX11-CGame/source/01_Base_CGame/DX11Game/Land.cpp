// �n�� [Land.cpp]
#include "Land.h"

// �R���X�g���N�^
CLand::CLand(CScene* pScene) : CModel(pScene)
{
	SetID(GOT_LAND);

	m_pVertex = nullptr;
	m_nVertex = 0;
	m_pIndex = nullptr;
	m_nIndex = 0;
}

// �f�X�g���N�^
CLand::~CLand()
{
}

// ������
HRESULT CLand::Init()
{
	SetModel(MODEL_LAND);

	// ���_�z��A�C���f�b�N�X�z����擾���Ă���
	CAssimpModel* pModel = GetAssimp(MODEL_LAND);
	pModel->GetVertexCount(&m_nVertex, &m_nIndex);
	m_pVertex = new TAssimpVertex[m_nVertex];
	m_pIndex = new UINT[m_nIndex];
	pModel->GetVertex(m_pVertex, m_pIndex);

	return CModel::Init();
}

// �I������
void CLand::Fin()
{
	CModel::Fin();

	// ���_�z��A�C���f�b�N�X�z��̉��
	SAFE_DELETE_ARRAY(m_pIndex);
	SAFE_DELETE_ARRAY(m_pVertex);
}

// ���C�Ƃ̓����蔻��
bool CLand::Collision(XMFLOAT3 vP0, XMFLOAT3 vW, XMFLOAT3* pX, XMFLOAT3* pN)
{
	// �S�Ă̎O�p�`�ɂ���
	for (UINT i = 0; i < m_nIndex; i += 3) {
		// �O�p�`�̒��_���W
		XMFLOAT3& V0 = m_pVertex[m_pIndex[i + 0]].vPos;
		XMFLOAT3& V1 = m_pVertex[m_pIndex[i + 1]].vPos;
		XMFLOAT3& V2 = m_pVertex[m_pIndex[i + 2]].vPos;
		// �ӂɑΉ�����x�N�g��
		XMFLOAT3 V0V1(V1.x - V0.x, V1.y - V0.y, V1.z - V0.z);
		XMFLOAT3 V1V2(V2.x - V1.x, V2.y - V1.y, V2.z - V1.z);
		XMFLOAT3 V2V0(V0.x - V2.x, V0.y - V2.y, V0.z - V2.z);
		// �O�p�`(=����)�̖@���x�N�g�������߂�
		XMVECTOR N = XMVector3Normalize(XMVector3Cross(XMLoadFloat3(&V0V1), XMLoadFloat3(&V1V2)));
		// t�̎�(t=(N�E(V0-P0))/(N�EW))�̕�������߂�
		float base;
		XMStoreFloat(&base, XMVector3Dot(N, XMLoadFloat3(&vW)));
		if (base == 0.0f)
			continue;	// �ʂƃ��C�����s
		// ���q�����߂�
		XMFLOAT3 P0V0(V0.x - vP0.x, V0.y - vP0.y, V0.z - vP0.z);
		float dot;
		XMStoreFloat(&dot, XMVector3Dot(N, XMLoadFloat3(&P0V0)));
		// t�����_�����߂�
		float t = dot / base;
		if (t < 0.0f)
			continue;	// ��_���n�_�̌��
		XMFLOAT3 X(vP0.x + t * vW.x, vP0.y + t * vW.y, vP0.z + t * vW.z);
		// ���O����
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
		// ������
		if (pX) *pX = X;
		if (pN) XMStoreFloat3(pN, N);
		return true;// �������Ă���
	}
	return false;	// �������Ă��Ȃ�
}
