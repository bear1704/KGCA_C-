#pragma once
#include "PStd.h"
#include <D3DX11.h>
#include <D3DX10math.h>

class PCamera
{
public:
	D3DXVECTOR3 vec_look_;
	D3DXVECTOR3 vec_up_;
	D3DXVECTOR3 vec_right_;
	D3DXVECTOR3 camera_position_;
	D3DXVECTOR3 vec_view_target_;

	float pitch_angle_;
	float yaw_angle_;
	float turn_speed_;


	D3DXMATRIX matWorld_;
	D3DXMATRIX matView_;
	D3DXMATRIX matProj_;
public:
	PCamera();
	~PCamera();



public:
	void CreateTargetViewMatrix(D3DXVECTOR3 mypos, D3DXVECTOR3 target, D3DXVECTOR3 up);
	void CreateProjectionMatrix();
	void UpdateCameraVec(D3DXVECTOR3 move = D3DXVECTOR3(0,0,0));

	void Forward();
	void BackWard();
	void MoveLeft();
	void MoveRight();
	void RotateLeft();
	void RotateRight();
	void RotateUp();
	void RotateDown();

public:
	bool Init();
	bool Frame();


};

