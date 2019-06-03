#pragma once
#include "PRectObject.h"

class PPlayer : public PRectObject
{
private:
	HDC handle_maskDC_;
	HDC handle_colorDC_;



public:
	PPlayer();
	~PPlayer();

public:
	bool AlphaBlendRender(int width, int height, HDC handle_offscreenDC, HDC handle_colorDC, HDC handle_maskDC, float alpha);
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;

};

