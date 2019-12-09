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
	
	//t�� 0~1 ���̿� �����ؾ� �Ѵ�.(������/������ ���� �������� ��������->������ġ���� �̵��ϸ�, �̵����� ����ũ�� * t �̴�)
	if (t < 0.0f || t > 1.0f)
		return false;

	intersection = start + ray_direction * t;

	return true;
	
}

bool PSelect::IsPointInTriPolygon(D3DXVECTOR3& point, D3DXVECTOR3& face_normal, D3DXVECTOR3& v0, D3DXVECTOR3& v1, D3DXVECTOR3& v2)
{
	//tbasis 2��  p.357

	D3DXVECTOR3 e0, e1, e2, vi, cross_prod;
	e0 = v1 - v0;
	e1 = v2 - v1;
	e2 = v0 - v2;

	vi = point - v0;

	D3DXVec3Cross(&cross_prod, &e0, &vi);
	D3DXVec3Normalize(&cross_prod, &cross_prod);
	float dot = D3DXVec3Dot(&face_normal, &cross_prod);

	//�������� 0���� �۴ٸ� �ﰢ�� ������ �ۿ� �ִ� ���̴�.
	if (dot < 0.0f) return false;


	vi = point - v1;
	D3DXVec3Cross(&cross_prod, &e1, &vi);
	D3DXVec3Normalize(&cross_prod, &cross_prod);
	dot = D3DXVec3Dot(&face_normal, &cross_prod);

	//�������� 0���� �۴ٸ� �ﰢ�� ������ �ۿ� �ִ� ���̴�.
	if (dot < 0.0f) return false;

	vi = point - v2;
	D3DXVec3Cross(&cross_prod, &e2, &vi);
	D3DXVec3Normalize(&cross_prod, &cross_prod);
	dot = D3DXVec3Dot(&face_normal, &cross_prod);

	//�������� 0���� �۴ٸ� �ﰢ�� ������ �ۿ� �ִ� ���̴�.
	if (dot < 0.0f) return false;

	return true;
}

void PSelect::SetMatrix(D3DXMATRIX* world, D3DXMATRIX* view, D3DXMATRIX* proj)
{
	if (world != nullptr)
	{
		mat_world_ = *world;

	}
	if (view != nullptr)
	{
		mat_view_ = *view;
	}
	if (proj != nullptr)
	{
		mat_proj_ = *proj;
	}

	RefreshPickingRay();
}

void PSelect::RefreshPickingRay()
{
	if (g_InputActionMap.leftClick == KEYSTAT::KEY_PUSH || g_InputActionMap.leftClick == KEYSTAT::KEY_HOLD)
	{
		POINT cursor;
		GetCursorPos(&cursor);
		ScreenToClient(g_hWnd, &cursor);

		D3DXVECTOR3 view_coord_point;
		D3DXVECTOR3& v = view_coord_point;

		//��ũ�� ��ǥ->�� ��ǥ�� ��ȯ Tbasis 2�� p.354
		v.x = (((2.0f * cursor.x) / g_rectangle_client.right) - 1) / mat_proj_._11;
		v.y = -(((2.0f * cursor.y) / g_rectangle_client.bottom) - 1) / mat_proj_._22;
		v.z = 1.0f;
		
		D3DXMATRIX mat_world_view = mat_world_ * mat_view_;
		D3DXMATRIX m;
		D3DXMatrixInverse(&m, NULL, &mat_world_view);

		picking_ray_.origin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		picking_ray_.direction = D3DXVECTOR3(v.x, v.y, v.z);
		D3DXVec3TransformCoord(&picking_ray_.origin, &picking_ray_.origin, &m);
		D3DXVec3TransformNormal(&picking_ray_.direction, &picking_ray_.direction, &m);
		D3DXVec3Normalize(&picking_ray_.direction, &picking_ray_.direction);
	}
}

bool PSelect::CheckRaytoOBBCollision(P_BOX* box, PickingRay* ray)
{
	if (ray == nullptr) ray = &picking_ray_;


	//s -> OBBcenter�� ray�� origin�� �մ� ���Ϳ� �и����� ���� ���  sa -> s�� ���밪(Vec R->)
 	//f -> ray�� ray-box�������� ����˻�(p.376)�� ���� ��(vec x dot vec d)   fa -> f�� ���밪
	float f[3], s[3], fa[3], sa[3];
	float t_min = -999999.0f;
	float t_max = 999999.0f;

	D3DXVECTOR3 box_to_rayorigin = ray->origin - box->center;

	//v = axis x,y,z
	for (int v = 0; v < 3; v++)
	{
		f[v] = D3DXVec3Dot(&box->obb_axis[v], &ray->direction);
		s[v] = D3DXVec3Dot(&box->obb_axis[v], &box_to_rayorigin);
		fa[v] = std::fabs(f[v]);
		sa[v] = std::fabs(s[v]);

		//p.376 ������ ����˻� / p.375 �и��� ���� �Ÿ� �˻� 
		if (sa[v] * f[v] >= 0.0f && sa[v] > box->obb_extents[v])
			return false;

		//AABB üũ
		float t1 = (-s[v] - box->obb_extents[v]) / f[v];
		float t2 = (-s[v] + box->obb_extents[v]) / f[v];

		if (t1 > t2)
			swap(t1, t2);

		t_min = max(t_min, t1);
		t_max = min(t_max, t2);

		if (t_min > t_max)
		{
			assert(false); //aabb ��Ұ� �ȵ��������� ����
			return false;
		}
			
		
	}

	//fw = p.375�� OBB����(f) fx, fy, fz
		//sn_cross = p/376 �и��࿡���� vec R = vec O - vec C ���� sx, sy, sz
	float sn_cross[3], fw;
	D3DXVECTOR3 d_cross_R;

	//d_cross_R = rayorigin-boxcenter ������ ����, ray_direction���� ����. �� vec d cross vec R(p 375 �ϴ�)
	D3DXVec3Cross(&d_cross_R, &ray->direction, &box_to_rayorigin);

	//�и��� d cross axis x(vec w)
	sn_cross[0] = fabs(D3DXVec3Dot(&d_cross_R, &box->obb_axis[0])); //Sx = abs(d cross x dot R)
	float fx_1 = box->obb_extents[1] * fa[2];//d dot z * e[1]
	float fx_2 = box->obb_extents[2] * fa[1];//d dot y * e[2]
	fw = fx_1 + fx_2;

	if (sn_cross[0] > fw)
	{
		//m_vDxR = vDxR;
		return false;
	}
	//�и��� d cross axis y(vec w)
	sn_cross[1] = fabs(D3DXVec3Dot(&d_cross_R, &box->obb_axis[1])); //Sy = abs(d cross y dot R)
	float fy_1 = box->obb_extents[0] * fa[2]; //d dot z * e[0]
	float fy_2 = box->obb_extents[2] * fa[0]; //d dot x * e[2]
	fw = fy_1 + fy_2;

	if (sn_cross[1] > fw)
	{
		return false;
	}

	//�и��� d cross axis z(vec w)
	sn_cross[2] = fabs(D3DXVec3Dot(&d_cross_R, &box->obb_axis[2])); //Sy = abs(d cross y dot R)
	float fz_1 = box->obb_extents[0] * fa[1]; //d dot z * e[0]
	float fz_2 = box->obb_extents[1] * fa[0]; //d dot x * e[2]
	fw = fz_1 + fz_2;

	if (sn_cross[2] > fw)
	{
		return false;
	}

	intersection_ = ray->origin + ray->direction * t_min;
	return true;

}
