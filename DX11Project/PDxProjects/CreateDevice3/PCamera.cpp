#include "PCamera.h"

PCamera::PCamera()
{

	D3DXMatrixIdentity(&matWorld_);
	D3DXMatrixIdentity(&matView_);
	D3DXMatrixIdentity(&matProj_);


	turn_speed_ = 30.0f;

	camera_position_ = D3DXVECTOR3(0.0f, 0.0f, -2.0f);
	vec_view_target_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vec_up_ = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}

PCamera::~PCamera()
{
	
}

void PCamera::CreateTargetViewMatrix(D3DXVECTOR3 mypos, D3DXVECTOR3 target, D3DXVECTOR3 up)
{
		
	D3DXMatrixLookAtLH(&matView_, &mypos, &target, &up);

	vec_look_ = D3DXVECTOR3(matView_._13, matView_._23, matView_._33);
	vec_up_ = D3DXVECTOR3(matView_._12, matView_._22, matView_._32);
	vec_right_ = D3DXVECTOR3(matView_._11, matView_._21, matView_._31);

	D3DXVec3Normalize(&vec_look_, &vec_look_);
	D3DXVec3Normalize(&vec_up_, &vec_up_);
	D3DXVec3Normalize(&vec_right_, &vec_right_);

	
}

void PCamera::CreateProjectionMatrix()
{
	D3DXMatrixPerspectiveFovLH(&matProj_, D3DX_PI / 2, (float)g_rectangle_client.right / (float)g_rectangle_client.bottom,
	0.0001f, 3000.0f);
}



void PCamera::UpdateCameraVec(D3DXVECTOR3 move)
{
	camera_position_ = camera_position_ + move * g_SecondPerFrame * 1.0f;

	float pitch = DEGREE_TO_RADIAN(pitch_angle_);
	float yaw = DEGREE_TO_RADIAN(yaw_angle_);


	vec_view_target_ = camera_position_ + vec_look_;

	D3DXVec3Normalize(&vec_look_, &vec_look_);
	D3DXVec3Normalize(&vec_up_, &vec_up_);
	D3DXVec3Normalize(&vec_right_, &vec_right_);

	matView_._11 = vec_right_.x; matView_._12 = vec_up_.x; matView_._13 = vec_look_.x;
	matView_._21 = vec_right_.y; matView_._22 = vec_up_.y; matView_._23 = vec_look_.y;
	matView_._31 = vec_right_.z; matView_._32 = vec_up_.z; matView_._33 = vec_look_.z;
	
	matView_ ._41 = -(D3DXVec3Dot(&camera_position_, &vec_right_));
	matView_ ._41 = -(D3DXVec3Dot(&camera_position_, &vec_up_));
	matView_ ._41 = -(D3DXVec3Dot(&camera_position_, &vec_look_));

}

void PCamera::Forward()
{
	UpdateCameraVec(vec_up_);

}

void PCamera::BackWard()
{
	UpdateCameraVec(vec_up_ * -1);
}

void PCamera::MoveLeft()
{
	UpdateCameraVec(vec_right_ * -1);
}

void PCamera::MoveRight()
{
	UpdateCameraVec(vec_right_);
}

void PCamera::RotateUp()
{
	pitch_angle_ += turn_speed_ * g_SecondPerFrame;
	UpdateCameraVec();
}

void PCamera::RotateDown()
{
	pitch_angle_ += turn_speed_ * g_SecondPerFrame;
	UpdateCameraVec();
}

void PCamera::RotateLeft()
{
	yaw_angle_ -= turn_speed_ * g_SecondPerFrame;
	UpdateCameraVec();
}

void PCamera::RotateRight()
{
	yaw_angle_ += turn_speed_ * g_SecondPerFrame;
	UpdateCameraVec();
}



bool PCamera::Init()
{
	return false;
}

bool PCamera::Frame()
{
	CreateTargetViewMatrix(camera_position_, vec_view_target_, vec_up_);
	
	return true;
}
