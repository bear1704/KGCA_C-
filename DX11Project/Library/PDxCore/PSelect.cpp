#include "PSelect.h"

PSelect::PSelect()
{
}

PSelect::~PSelect()
{
}

bool PSelect::GetIntersection(OUT_ D3DXVECTOR3& intersection,
	const D3DXVECTOR3& start,
	const D3DXVECTOR3& end,
	const D3DXVECTOR3& normal,
	const D3DXVECTOR3& v0)
{
	//Tbasis 2  p.338
	D3DXVECTOR3 ray_direction = end - start;
	float dist_b = D3DXVec3Dot(&normal, &ray_direction);
	float dist_a = D3DXVec3Dot(&normal, &(v0 - start));
	
	float t = dist_a / dist_b;
	
	//t는 0~1 사이에 존재해야 한다.(반직선/선분의 벡터 방향으로 원점에서->교점위치까지 이동하며, 이동량은 선분크기 * t 이다)
	if (t < 0.0f || t > 1.0f)
		return false;

	intersection = start + ray_direction * t;

	return true;
	
}

bool PSelect::IsPointInTriPolygon(D3DXVECTOR3& point, D3DXVECTOR3& face_normal, D3DXVECTOR3& v0, D3DXVECTOR3& v1, D3DXVECTOR3& v2)
{
	//tbasis 2권  p.357

	D3DXVECTOR3 e0, e1, e2, vi, cross_prod;
	e0 = v1 - v0;
	e1 = v2 - v1;
	e2 = v0 - v2;

	vi = point - v0;

	D3DXVec3Cross(&cross_prod, &e0, &vi);
	D3DXVec3Normalize(&cross_prod, &cross_prod);
	float dot = D3DXVec3Dot(&face_normal, &cross_prod);

	//내적값이 0보다 작다면 삼각형 폴리곤 밖에 있는 것이다.
	if (dot < 0.0f) return false;


	vi = point - v1;
	D3DXVec3Cross(&cross_prod, &e1, &vi);
	D3DXVec3Normalize(&cross_prod, &cross_prod);
	dot = D3DXVec3Dot(&face_normal, &cross_prod);

	//내적값이 0보다 작다면 삼각형 폴리곤 밖에 있는 것이다.
	if (dot < 0.0f) return false;

	vi = point - v2;
	D3DXVec3Cross(&cross_prod, &e2, &vi);
	D3DXVec3Normalize(&cross_prod, &cross_prod);
	dot = D3DXVec3Dot(&face_normal, &cross_prod);

	//내적값이 0보다 작다면 삼각형 폴리곤 밖에 있는 것이다.
	if (dot < 0.0f) return false;

	return true;
}
