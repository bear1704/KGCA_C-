#pragma once
#include "PCollision.h"


class P2DCamera : public PSingleton<P2DCamera>
{
public:
	P2DCamera();
	~P2DCamera();

private:
	friend class PSingleton<P2DCamera>;
	DOUBLE_RECT center_rect_; //스크롤 필요유무 구분을 위한 가운데 렉트
	DOUBLE_RECT camera_object_rect_; //카메라 객체. l,t은 카메라 위치, r,b는 카메라 크기(클라이언트 화면 크기)
	SizeXY world_size_; //(전체 맵 사이즈) 
	Vector2 move_dir_vector_; //이동방향(스크롤 시 화면이동방향을 정의)
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
	void set_camera_position_(pPoint xy); //카메라 좌표 설정
	void add_camera_position_(pPoint xy); //카메라 좌표값 가,감산
	pPoint get_camera_position();
	float get_camera_scroll_speed_();
	void camera_correction();

	bool Init();
	bool Frame();
	bool Render();
	bool Release();	
	
private:
	float center_rect_width = 150; //center_rect 하드코드 설정
	float center_rect_height = 150;
	

};

