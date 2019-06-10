#include "PUIComponent.h"



PUIComponent::PUIComponent()
{
}


PUIComponent::~PUIComponent()
{
}

void PUIComponent::SetRect(int rect, PVertex start, 
	PVertex rightside_vertex, PVertex bottomside_vertex, 
	int bitmap_id, int mask_id)
{
	FLOAT_RECT rect_myobject = {start.my_pos.x, start.my_pos.y,
								rightside_vertex.my_pos.x - start.my_pos.x,
								bottomside_vertex.my_pos.y - start.my_pos.y};
	FLOAT_RECT rect_srcobject = {start.src_pos.x, start.src_pos.y, 
								rightside_vertex.src_pos.x - start.src_pos.x, 
								bottomside_vertex.src_pos.y - start.src_pos.y};
}
