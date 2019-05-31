#pragma once
#include "PCollision.h"


class P2DCamera : public PSingleton<P2DCamera>
{
public:
	P2DCamera();
	~P2DCamera();

private:
	friend class PSingleton<P2DCamera>;
	RECT center_rect_;
	RECT camera_object_rect_;
	pPoint world_size_;
	Vector2 move_dir_vector_;
	RECT* character_collision_rect;
	PCollision collision_module;
public:
	pPoint WorldToGamescreen(pPoint world_pos);
	pPoint GamescreenToWorld(pPoint screen_pos);
	RECT WorldToGamescreenRECT(RECT world_rect);
	void MoveCamera();

	RECT get_center_rect_();
	void set_center_rect(RECT rect);
	RECT get_camera_object_rect_();
	void set_camera_object_rect_(RECT rect);
	Vector2 get_move_dir_vector_();
	void set_move_dir_vector_(Vector2 vec);
	pPoint get_world_size_();
	void set_character_collision_rect(RECT* rect);
	

	bool Init();
	bool Frame();
	bool Render();
	bool Release();	
	
private:
	int center_rect_width = 350;
	int center_rect_height = 350;
	

};

