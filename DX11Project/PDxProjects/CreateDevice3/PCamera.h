#pragma once
#include "PStd.h"
#include "PMatrix.h"
#include <D3DX11.h>
#include <D3DX10math.h>

class PCamera
{
public:
	DX::Vector3 vec_look_;
	DX::Vector3 vec_up_;
	DX::Vector3 vec_right_;
	DX::Vector3 camera_position_;
	DX::Vector3 vec_view_target_;

	DX::PMatrix matWorld_;
	DX::PMatrix matView_;
	DX::PMatrix matProj_;
public:
	PCamera();
	~PCamera();



public:
	void CreateTargetViewMatrix(DX::Vector3 mypos, DX::Vector3 target, DX::Vector3 up);
	void CreateProjectionMatrix();
	//void UpdateCameraVec(DX::Vector3 move);

	void Forward();
	void BackWard();
	void MoveLeft();
	void MoveRight();

public:
	bool Init();
	bool Frame();


};

