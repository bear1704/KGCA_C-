#pragma once
#include "PStd.h"

class PCollision : public PSingleton<PCollision>
{
private:
	PCollision();
public:
	~PCollision();

private:
	friend class PSingleton<PCollision>;


public:
	bool RectInRect(FLOAT_RECT collision_box1, FLOAT_RECT collision_box2);
	bool RectInRect(FLOAT_RECT collision_box1, FLOAT_RECT collision_box2, float& overlapping_ylength);

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;


};

