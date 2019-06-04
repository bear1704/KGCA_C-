#pragma once
#include "PStd.h"

class PCollision
{
public:
	PCollision();
	~PCollision();
public:
	static bool RectInRect(RECT collision_box1, RECT collision_box2)
	{
		POINT collision_box1_center;
		POINT collision_box2_center;
		collision_box1_center.x = (collision_box1.right/2 + collision_box1.left);
		collision_box1_center.y = (collision_box1.bottom/2 + collision_box1.top);
		collision_box2_center.x = (collision_box2.right/2 + collision_box2.left);
		collision_box2_center.y = (collision_box2.bottom/2 + collision_box2.top);

		POINT collision_box1_radius;
		POINT collision_box2_radius;
		collision_box1_radius.x = collision_box1.right/2;
		collision_box1_radius.y = collision_box1.bottom/2;
		collision_box2_radius.x = collision_box2.right/2;
		collision_box2_radius.y = collision_box2.bottom/2;

		POINT between_rect_distance;
		between_rect_distance.x = abs(collision_box2_center.x - collision_box1_center.x);
		between_rect_distance.y = abs(collision_box2_center.y - collision_box1_center.y);


		if (between_rect_distance.x <= (collision_box1_radius.x + collision_box2_radius.x) &&
			between_rect_distance.y <= (collision_box1_radius.y + collision_box2_radius.y))
		{
			return true;
		}

		return false;

	}


	static bool RectUnderSegment()
	{
		return false;
	}

};

