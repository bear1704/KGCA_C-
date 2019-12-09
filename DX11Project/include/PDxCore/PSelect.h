#pragma once
#include "PShape.h"

struct PickingRay
{
	float extent;
	D3DXVECTOR3 origin;
	D3DXVECTOR3 direction;

	PickingRay()
	{
		extent = -1;
	}

};


class PSelect
{
public:
	PSelect();
	~PSelect();

public:
	PickingRay picking_ray_;
	D3DXMATRIX mat_world_;
	D3DXMATRIX mat_view_;
	D3DXMATRIX mat_proj_;
	D3DXVECTOR3 intersection_; //������ ���� -> ���������� ����(����ȭ�ȵ�)
public:
	//�������� ����� �������θ� �����ϰ� �������� ���� ��ǥ���� ��´�
	bool GetIntersection(OUT_ D3DXVECTOR3& intersection, 
		const D3DXVECTOR3& start, 
		const D3DXVECTOR3& end, 
		const D3DXVECTOR3& normal,
		const D3DXVECTOR3& v0);

	/*������(Triangle)�� ������,������ ������ �����Ѵ�.
	point : �˻��� ����    face_normal : ������ �ﰢ���� �븻����
	*/
	bool IsPointInTriPolygon(D3DXVECTOR3& point, 
		D3DXVECTOR3& face_normal,
		D3DXVECTOR3& v0,
		D3DXVECTOR3& v1, 
		D3DXVECTOR3& v2);

	void SetMatrix(D3DXMATRIX* world, D3DXMATRIX* view, D3DXMATRIX* proj);
	void RefreshPickingRay();
	//tbasis2 p.374
	bool CheckRaytoOBBCollision(P_BOX* box, PickingRay* ray = nullptr);

};

