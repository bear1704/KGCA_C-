#pragma once
#include "PStd.h"
#include <D3DX11.h>
#include <D3DX10math.h>
#include "PArcBall.h"

class PCamera
{
public:

	PArcBall arcball_view_;
	PArcBall arcball_world_;
	D3DXVECTOR3 vec_look_;
	D3DXVECTOR3 vec_up_;
	D3DXVECTOR3 vec_right_;
	D3DXVECTOR3 camera_position_;
	D3DXVECTOR3 vec_view_target_;
	D3DXVECTOR4 vec_value_;
	float radius_;

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
	//ī�޶��� �ܼ������̵��� ����
	void MoveCameraVec(D3DXVECTOR3 move = D3DXVECTOR3(0,0,0)); 
	void UpdateVector();

	void UpWard();
	void DownWard();
	void MoveLeft();
	void MoveRight();
	void MoveFoward();
	void MoveBackward();
	void RotateLeft();
	void RotateRight();
	void RotateUp();
	void RotateDown();

	void MessageProc(MSG msg);


public:
	virtual bool Init();
	virtual bool Frame();


};
