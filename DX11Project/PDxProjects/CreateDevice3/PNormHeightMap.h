#pragma once
#include "PMap.h"
#include "PNormalMapHelper.h"

class PNormHeightMap :
	public PHeightMap
{
public:
	PNormHeightMap();
	~PNormHeightMap();

protected:
	std::vector<D3DXVECTOR3>			 tangent_list_;
	Microsoft::WRL::ComPtr<ID3D11Buffer> tangent_space_vbuffer_;
	PNormalMapHelper					 helper_normalmap_;
	D3DXMATRIX							 mat_normal_; //??
	PTexture* normal_texture_;

public:
	bool Render() override;
	bool UpdataBuffer();
	HRESULT SetInputLayout();
	HRESULT CreateVertexBuffer() override;
	HRESULT CreateResource();
	HRESULT LoadTextures(std::wstring tex_name = nullptr) override;
	void SetWVPMatrix(D3DXMATRIX* world = nullptr, D3DXMATRIX* view = nullptr, D3DXMATRIX* proj = nullptr) override;




};

