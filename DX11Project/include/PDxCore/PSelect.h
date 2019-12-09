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
	//반직선과 평면의 교차여부를 판정하고 반직선의 교점 좌표값을 얻는다
	bool GetIntersection(OUT_ D3DXVECTOR3& intersection, 
		const D3DXVECTOR3& start, 
		const D3DXVECTOR3& end, 
		const D3DXVECTOR3& normal,
		const D3DXVECTOR3& v0);

	/*폴리곤(Triangle)과 반직선,선분의 교차를 판정한다.
	point : 검사할 교점    face_normal : 폴리곤 삼각형의 노말벡터
	*/
	bool IsPointInTriPolygon(D3DXVECTOR3& point, 
		D3DXVECTOR3& face_normal,
		D3DXVECTOR3& v0,
		D3DXVECTOR3& v1, 
		D3DXVECTOR3& v2);
};

