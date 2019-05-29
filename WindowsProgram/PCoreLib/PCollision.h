#pragma once
#include "PStd.h"

class PCollision
{
public:
	PCollision();
	~PCollision();
public:
	static bool RectInRect(RECT rect1, RECT rect2)
	{
		POINT rect1_center;
		POINT rect2_center;
		rect1_center.x = (rect1.right + rect1.left) / 2;
		rect1_center.y = (rect1.bottom + rect1.top) / 2;
		rect2_center.x = (rect2.right+ rect2.left) / 2;
		rect2_center.y = (rect2.bottom + rect2.top) / 2;

		POINT rect1_radius;
		POINT rect2_radius;
		rect1_radius.x = rect1.right - rect1_center.x;
		rect1_radius.y = rect1.bottom - rect1_center.y;
		rect2_radius.x = rect2.right - rect2_center.x;
		rect2_radius.y = rect2.bottom - rect2_center.y;

		POINT between_rect_distance;
		between_rect_distance.x = abs(rect2_center.x - rect1_center.x);
		between_rect_distance.y = abs(rect2_center.y - rect1_center.y);


		if (between_rect_distance.x <= (rect1_radius.x + rect2_radius.x) &&
			between_rect_distance.y <= (rect1_radius.y + rect2_radius.y))
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

