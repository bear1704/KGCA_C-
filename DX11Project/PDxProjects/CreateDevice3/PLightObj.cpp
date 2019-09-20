#include "PLightObj.h"

PLightObj::PLightObj()
{
	//ZeroMemory(&cb_light_, sizeof(LIGHT_CONSTANT_BUFFER));
	//ZeroMemory(&light_vector_, sizeof(D3DXVECTOR3));
	//ZeroMemory(&light_world_, sizeof(D3DXMATRIX));
	//ZeroMemory(&light_trs_, sizeof(D3DXMATRIX));
	//ZeroMemory(&light_world_, sizeof(D3DXMATRIX));
}

PLightObj::~PLightObj()
{
}

bool PLightObj::Init(D3DXVECTOR4 ambient_material, D3DXVECTOR4 ambient_color, D3DXVECTOR4 diffuse_material, 
	D3DXVECTOR4 diffuse_color, D3DXVECTOR3 light_init_pos, ID3D11Device* device, PCamera* camera)
{
	device_ = device;
	ZeroMemory(&cb_light_, sizeof(LIGHT_CONSTANT_BUFFER));
	ZeroMemory(&light_direction_, sizeof(D3DXVECTOR3));
	ZeroMemory(&light_trs_, sizeof(D3DXMATRIX));
	ZeroMemory(&light_world_, sizeof(D3DXMATRIX));
	light_trs_.light_trans_.y = 100;
	D3DXMatrixIdentity(&light_init_world_);
	D3DXMatrixIdentity(&light_world_);
	cb_light_.g_AmbientMaterial = ambient_material;
	cb_light_.g_AmbientColor = ambient_color;
	cb_light_.g_DiffuseMaterial = diffuse_material;
	cb_light_.g_DiffuseColor = diffuse_color;

	constant_buffer_light_.Attach(DX::CreateConstantBuffer(device_, &cb_light_, 1, sizeof(LIGHT_CONSTANT_BUFFER), false));



	return true;
}

bool PLightObj::Frame()
{
	D3DXMatrixTranslation(&light_init_world_, light_trs_.light_trans_.x, light_trs_.light_trans_.y , light_trs_.light_trans_.z);
	D3DXMATRIX mat_rotation;
	D3DXMatrixRotationYawPitchRoll(&mat_rotation, light_trs_.light_rot_.x, light_trs_.light_rot_.y, light_trs_.light_rot_.z);
	D3DXMatrixMultiply(&light_world_, &light_init_world_, &mat_rotation);

	light_position_.x = light_world_._41;
	light_position_.y = light_world_._42;
	light_position_.z = light_world_._43;

	D3DXVec3Normalize(&light_direction_, &light_position_);
	light_direction_ *= 1.0f;

	cb_light_.g_vLightDir.x = light_direction_.x;
	cb_light_.g_vLightDir.y = light_direction_.y;
	cb_light_.g_vLightDir.z = light_direction_.z;
	cb_light_.g_vLightDir.w = 1;

	cb_light_.g_vEyeDir.x = camera_->vec_look_.x;
	cb_light_.g_vEyeDir.y = camera_->vec_look_.y;
	cb_light_.g_vEyeDir.z = camera_->vec_look_.z;
	cb_light_.g_vEyeDir.w = 10.0f; // ºûÀÇ ¹à±â °­µµ

	return true;
}

bool PLightObj::Render()
{
	return false;
}

bool PLightObj::Release()
{
	return false;
}
