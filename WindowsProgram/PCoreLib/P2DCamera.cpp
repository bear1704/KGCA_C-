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
	pPoint center_rect_center = pPoint(center_rect_.left + center_rect_.right / 2, center_rect_.top + center_rect_.bottom / 2);
	pPoint character_rect_center = pPoint(character_collision_rect->left + character_collision_rect->right / 2,
		character_collision_rect->top + character_collision_rect->bottom / 2);

	camera_object_rect_.left = center_rect_center.x - camera_object_rect_.right/2;
	camera_object_rect_.top = center_rect_center.y - camera_object_rect_.bottom/2;

	if (!collision_module.RectInRect(*character_collision_rect, center_rect_))
	{
		
		float vector_size = std::sqrt(std::pow(character_rect_center.x - center_rect_center.x, 2)
			+ std::pow(character_rect_center.y - center_rect_center.y, 2));
		
		move_dir_vector_ = pPoint((character_rect_center.x - center_rect_center.x) / vector_size, 
			(character_rect_center.y - center_rect_center.y) / vector_size); //Normalized 방향벡터


		std::string str = "[ vec : " + std::to_string(move_dir_vector_.x) + " , " +  std::to_string(move_dir_vector_.y) + "]\n";
		std::wstring wstr = std::wstring(str.begin(), str.end());
		//OutputDebugString(wstr.c_str());

		
		std::wstring spf = std::to_wstring(center_rect_.left);
		spf += L" --> 센터렉트 left \n";
		std::wstring spf1 = std::to_wstring(move_dir_vector_.x);
		spf1 += L" --> 이동방향벡터 x \n";
		std::wstring spf1_1 = std::to_wstring(move_dir_vector_.y);
		spf1_1 += L" --> 이동방향벡터 y \n";
		std::wstring spf2 = std::to_wstring(g_SecondPerFrame);
		spf2 += L" SecondPerFrame \n";
		
		std::wstring spf3 = spf + spf1 + spf1_1 + spf2;


		OutputDebugString(spf3.c_str());



  		center_rect_.left += move_dir_vector_.x * camera_scroll_speed_ * g_SecondPerFrame; //센터렉트에 방향벡터만큼 더해준다.
		center_rect_.top += move_dir_vector_.y * camera_scroll_speed_ * g_SecondPerFrame;


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

void P2DCamera::set_world_size_(SizeXY world_size)
{
	world_size_ = world_size;
}

pPoint P2DCamera::get_world_size_()
{
	return world_size_;
}

void P2DCamera::set_character_collision_rect(RECT * rect)
{
	character_collision_rect = rect;
}

void P2DCamera::set_camera_position_(pPoint xy)
{
	camera_object_rect_.left = xy.x;
	camera_object_rect_.top = xy.y;
}

void P2DCamera::add_camera_position_(pPoint xy)
{
	camera_object_rect_.left += xy.x;
	camera_object_rect_.top += xy.y;
}

pPoint P2DCamera::get_camera_position()
{
	return pPoint(camera_object_rect_.left, camera_object_rect_.top);
}

float P2DCamera::get_camera_scroll_speed_()
{
	return camera_scroll_speed_;
}

void P2DCamera::camera_correction()
{
	if (camera_object_rect_.left < 0)
		camera_object_rect_.left = 0;
	if(camera_object_rect_.top < 0)
		camera_object_rect_.top = 0;
	if(camera_object_rect_.left + camera_object_rect_.right > get_world_size_().x)
		camera_object_rect_.left = get_world_size_().x - camera_object_rect_.right;
	if(camera_object_rect_.top + camera_object_rect_.bottom > get_world_size_().y)
		camera_object_rect_.top = get_world_size_().y - camera_object_rect_.bottom;
}



bool P2DCamera::Init()
{

	center_rect_ = { 400,400,center_rect_width ,center_rect_height};
	camera_object_rect_ = { center_rect_.left,center_rect_.top , g_rectangle_client.right, g_rectangle_client.bottom };
	move_dir_vector_ = { 0,0 };
	world_size_ = { 1499,895 }; //749
	//world_size_ = { 5000,5000}; //749
	camera_scroll_speed_ = 360.0f;
	return true;
}

bool P2DCamera::Frame()  
{
	MoveCamera();
	//camera_correction();
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
