#pragma once
#include "PStd.h"


class P2DCamera : public PSingleton<P2DCamera>
{
public:
	P2DCamera();
	~P2DCamera();

private:
	friend class PSingleton<P2DCamera>;
	static RECT center_rect_;
	static RECT camera_object_rect_;
	static Vector2 move_dir_vector_;
	
public:
	static pPoint WorldToGamescreen(pPoint world_pos);
	static pPoint GamescreenToWorld(pPoint screen_pos);
	static void MoveCamera();

	static RECT get_center_rect_();
	static void set_center_rect(RECT rect);
	static RECT get_camera_object_rect_();
	static void set_camera_object_rect_(RECT rect);
	static Vector2 get_move_dir_vector_();
	static void set_move_dir_vector_(Vector2 vec);

	bool Init();
	bool Frame();
	bool Render();
	bool Release();	
	

};

