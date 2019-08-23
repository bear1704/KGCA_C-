#pragma once
#include "PObject.h"


class PPlaneObject : public PObject
{
public:
	PPlaneObject();
	~PPlaneObject();

public:
	bool Init() override;
	bool DXInit(ID3D11Device* device, ID3D11DeviceContext* context) override;
	bool Frame() override;
	bool Render(ID3D11DeviceContext* context) override;
	bool Release() override;

	



};

