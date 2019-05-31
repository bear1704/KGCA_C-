#include "P2DCamera.h"


P2DCamera::P2DCamera()
{
	
}


P2DCamera::~P2DCamera()
{
}

pPoint P2DCamera::WorldToGamescreen(pPoint world_pos)
{
	pPoint game_screen_pos;
	game_screen_pos.x = world_pos.x - camera_object_rect_.left;
	game_screen_pos.y = world_pos.y - camera_object_rect_.top;
	return game_screen_pos;
}

pPoint P2DCamera::GamescreenToWorld(pPoint screen_pos)
{
	pPoint world_pos;
	world_pos.x = screen_pos.x + camera_object_rect_.left;
	world_pos.y = screen_pos.y + camera_object_rect_.top;
	return world_pos;
}

RECT P2DCamera::WorldToGamescreenRECT(RECT world_rect)
{
	RECT game_screen_rect;
	game_screen_rect.left = world_rect.left - camera_object_rect_.left;
	game_screen_rect.top = world_rect.top - camera_object_rect_.top;
	game_screen_rect.right = world_rect.right;
	game_screen_rect.bottom = world_rect.bottom;
	//right,bottom은 RECT에선 단순 width,height이므로 건드리면 안 됨!
	return game_screen_rect;
}

void P2DCamera::MoveCamera()
{
	center_rect_.left = camera_object_rect_.right / 2 - center_rect_.right/2;
	center_rect_.top = camera_object_rect_.bottom / 2;


	if (!collision_module.RectInRect(*character_collision_rect, center_rect_))
	{
		OutputDebugString(L"\n넘어감!!");
	}
}

RECT P2DCamera::get_center_rect_()
{
	return center_rect_;
}

void P2DCamera::set_center_rect(RECT rect)
{
	center_rect_ = rect;
}

RECT P2DCamera::get_camera_object_rect_()
{
	return camera_object_rect_;
}

void P2DCamera::set_camera_object_rect_(RECT rect)
{
	camera_object_rect_ = rect;
}



Vector2 P2DCamera::get_move_dir_vector_()
{
	return move_dir_vector_;
}

void P2DCamera::set_move_dir_vector_(Vector2 vec)
{
	move_dir_vector_ = vec;
}

pPoint P2DCamera::get_world_size_()
{
	return world_size_;
}

void P2DCamera::set_character_collision_rect(RECT * rect)
{
	character_collision_rect = rect;
}



bool P2DCamera::Init()
{
	center_rect_ = { -1,-1,center_rect_width ,center_rect_height};
	camera_object_rect_ = { 0,0, g_rectangle_client.right, g_rectangle_client.bottom };
	move_dir_vector_ = { 0,0 };
	world_size_ = { 1800,760 };
	return true;
}

bool P2DCamera::Frame()
{
	MoveCamera();
	return true;
}

bool P2DCamera::Render()
{
	return true;
}

bool P2DCamera::Release()
{
	return true;
}
