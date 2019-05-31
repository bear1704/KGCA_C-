#include "P2DCamera.h"


P2DCamera::P2DCamera()
{
	
}
RECT P2DCamera::center_rect_ = { 500,300,100 ,100};
RECT P2DCamera::camera_object_rect_ = { 400,300, g_rectangle_client.right, g_rectangle_client.bottom };
Vector2 P2DCamera::move_dir_vector_= { 0,0 };

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

bool P2DCamera::Init()
{
	return false;
}

bool P2DCamera::Frame()
{
	return false;
}

bool P2DCamera::Render()
{
	return false;
}

bool P2DCamera::Release()
{
	return false;
}
