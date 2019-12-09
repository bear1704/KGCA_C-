#pragma once
#include "PShape.h"

struct PickingRay
{


};


class PSelect
{
public:
	PSelect();
	~PSelect();


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
};

