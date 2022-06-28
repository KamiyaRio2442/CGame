#pragma once
#include "main.h"

class CAssimpModel;
class CCard;
class CCamera
{
private:
	DirectX::XMFLOAT3 m_vPos;		// ���_
	DirectX::XMFLOAT3 m_vTarget;	// �����_
	DirectX::XMFLOAT3 m_vUp;		// ����x�N�g��

	float m_fAspectRatio;			// �c����
	float m_fFovY;					// ����p(Degree)
	float m_fNearZ;					// �O���N���b�v����
	float m_fFarZ;					// ����N���b�v����

	DirectX::XMFLOAT4X4 m_mtxWorld;	// ���[���h �}�g���b�N�X
	DirectX::XMFLOAT4X4 m_mtxView;	// �r���[ �}�g���b�N�X
	DirectX::XMFLOAT4X4 m_mtxProj;	// �v���W�F�N�V���� �}�g���b�N�X

	//DirectX::XMFLOAT3 m_vAngle;		// �J�����̊p�x
	//float m_fLengthInterval;		// �J�����̎��_�ƒ����_�̋���

	CAssimpModel* m_pSky;			// �X�J�C �h�[��

	float m_fRadius;				// ���a

	CCard* m_pPlayer;				// ���@
	int m_nMode;					// �J�������[�h
	float m_fAngle;					// �J�����A���O��

	DirectX::XMFLOAT4 m_frus[6];	// ������
	DirectX::XMFLOAT4 m_frusw[6];	// ������(���[���h���)

public:
	CCamera();

	virtual void Init();
	virtual void Update();
	virtual void Clear();

	void SetPos(DirectX::XMFLOAT3& vPos) { m_vPos = vPos; }
	DirectX::XMFLOAT3& GetPos() { return m_vPos; }
	void SetPos(float x, float y, float z) { m_vPos.x = x, m_vPos.y = y, m_vPos.z = z; }
	void SetTarget(DirectX::XMFLOAT3& vTarget) { m_vTarget = vTarget; }
	void SetTarget(float x, float y, float z) { m_vTarget.x = x, m_vTarget.y = y, m_vTarget.z = z; }
	void SetUpVector(DirectX::XMFLOAT3& vUp) { m_vUp = vUp; }
	void SetUpVector(float x, float y, float z) { m_vUp.x = x, m_vUp.y = y, m_vUp.z = z; }
	void SetWorldMatrix(DirectX::XMFLOAT4X4& mtxWorld);
	DirectX::XMFLOAT4X4& GetWorldMatrix() { return m_mtxWorld; }
	DirectX::XMFLOAT4X4& CalcWorldMatrix();
	void SetFovY(float fFovY);
	void SetAspectRatio(float fAspect);
	void SetRangeZ(float fNearZ, float fFarZ);
	void UpdateMatrix();
	DirectX::XMFLOAT4X4& GetViewMatrix() { return m_mtxView; }
	DirectX::XMFLOAT4X4& GetProjMatrix() { return m_mtxProj; }
	//DirectX::XMFLOAT3& GetAngle() { return m_vAngle; }
	void SetSkyDome(CAssimpModel* pSky) { m_pSky = pSky; }
	CAssimpModel* GetSkyDome() { return m_pSky; }
	void SetRadius(float fRadius) { m_fRadius = fRadius; }
	void SetPlayer(CCard* pPlayer);
	int CollisionViewFrustum(XMFLOAT3 vCenter,
float fRadius);//������(0:��\��,-1:����, 1:�\��)

private:
	void CreateViewFrustum();
	void UpdateViewFrustum();
};