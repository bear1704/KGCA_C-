#include "PCamera.h"

PCamera::PCamera()
{
	matWorld_.Identity();
	matView_.Identity();
	matProj_.Identity();

	camera_position_ = DX::Vector3(0.0f, 0.0f, -2.0f);
	vec_view_target_ = DX::Vector3(0.0f, 0.0f, 0.0f);
	vec_up_ = DX::Vector3(0.0f, 1.0f, 0.0f);
}

PCamera::~PCamera()
{
}

void PCamera::CreateTargetViewMatrix(DX::Vector3 mypos, DX::Vector3 target, DX::Vector3 up)
{
		
	matView_.ViewLookAt(mypos, target, up);

	vec_look_ = DX::Vector3(matView_._13, matView_._23, matView_._33);
	vec_up_ = DX::Vector3(matView_._12, matView_._22, matView_._32);
	vec_right_ = DX::Vector3(matView_._11, matView_._21, matView_._31);

	vec_look_.Normalize();
	vec_up_.Normalize();
	vec_right_.Normalize();
	

	
}

void PCamera::CreateProjectionMatrix()
{
	
	matProj_.PerspectiveFovLH(1.0f, 100.0f, D3DX_PI / 2, (float)g_rectangle_client.right / (float)g_rectangle_client.bottom);

}


//
//void PCamera::UpdateCameraVec(DX::Vector3 move)
//{
//	camera_position_ = camera_position_ + move * g_SecondPerFrame * 1.0f;
//	vec_look_ = vec_look_ + move * g_SecondPerFrame * 1.0f;
//	vec_up_ = vec_up_ + move * g_SecondPerFrame * 1.0f;
//	vec_right_ = vec_look_.Cross(vec_up_);
//	vec_look_.Normalize();
//	vec_up_.Normalize();
//	vec_right_.Normalize();
//
//	/*DX::PMatrix mat;
//	mat.Identity();
//*/
//	matView_._11 = vec_right_.x; matView_._12 = vec_up_.x; matView_._13 = vec_look_.x;
//	matView_._21 = vec_right_.y; matView_._22 = vec_up_.y; matView_._23 = vec_look_.y;
//	matView_._31 = vec_right_.z; matView_._32 = vec_up_.z; matView_._33 = vec_look_.z;
//	matView_ ._41 = -(camera_position_.Dot(vec_right_));
//	matView_ ._42 = -(camera_position_.Dot(vec_up_));
//	matView_ ._43 = -(camera_position_.Dot(vec_look_));
//
//	
//	//look-at이 없는 카메라 이동은 어떻게 하는가?
//}

void PCamera::Forward()
{
	//UpdateCameraVec(vec_up_);
	camera_position_ = camera_position_ + vec_look_ * g_SecondPerFrame * 10.0f;

}

void PCamera::BackWard()
{
	//UpdateCameraVec(vec_up_ * -1);
	camera_position_ = camera_position_ - vec_look_ * g_SecondPerFrame * 10.0f;
}

void PCamera::MoveLeft()
{
	//UpdateCameraVec(vec_right_ * -1);
	camera_position_ = camera_position_ - vec_right_ * g_SecondPerFrame * 10.0f;
}

void PCamera::MoveRight()
{
	//UpdateCameraVec(vec_right_);
	camera_position_ = camera_position_ + vec_right_ * g_SecondPerFrame * 10.0f;
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
