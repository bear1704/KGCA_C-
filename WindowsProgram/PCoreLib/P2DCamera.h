#pragma once
#include "PCollision.h"


class P2DCamera : public PSingleton<P2DCamera>
{
public:
	P2DCamera();
	~P2DCamera();

private:
	friend class PSingleton<P2DCamera>;
	DOUBLE_RECT center_rect_; //��ũ�� �ʿ����� ������ ���� ��� ��Ʈ
	DOUBLE_RECT camera_object_rect_; //ī�޶� ��ü. l,t�� ī�޶� ��ġ, r,b�� ī�޶� ũ��(Ŭ���̾�Ʈ ȭ�� ũ��)
	SizeXY world_size_; //(��ü �� ������) 
	Vector2 move_dir_vector_; //�̵�����(��ũ�� �� ȭ���̵������� ����)
	DOUBLE_RECT* character_collision_rect;
	PCollision collision_module;
	float camera_scroll_speed_;

public:
	pPoint WorldToGamescreen(pPoint world_pos);
	DOUBLE_RECT WorldToGamescreenRECT(DOUBLE_RECT world_rect);
	pPoint GamescreenToWorld(pPoint screen_pos);
	void MoveCamera();

	DOUBLE_RECT get_center_rect_();
	void set_center_rect(DOUBLE_RECT rect);
	DOUBLE_RECT get_camera_object_rect_();
	void set_camera_object_rect_(DOUBLE_RECT rect);
	Vector2 get_move_dir_vector_();
	void set_move_dir_vector_(Vector2 vec);
	void set_world_size_(SizeXY world_size);
	SizeXY get_world_size_();
	void set_character_collision_rect(DOUBLE_RECT* rect);
	void set_camera_position_(pPoint xy); //ī�޶� ��ǥ ����
	void add_camera_position_(pPoint xy); //ī�޶� ��ǥ�� ��,����
	pPoint get_camera_position();
	float get_camera_scroll_speed_();
	void camera_correction();

	bool Init();
	bool Frame();
	bool Render();
	bool Release();	
	
private:
	float center_rect_width = 150; //center_rect �ϵ��ڵ� ����
	float center_rect_height = 150;
	

};

