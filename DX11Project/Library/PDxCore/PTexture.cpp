#include "PTexture.h"

PTexture::PTexture()
{
}

PTexture::~PTexture()
{

}

void PTexture::set_shader_res_view(ID3D11ShaderResourceView* view)
{
	shader_res_view_ = view;
}

void PTexture::Apply(ID3D11DeviceContext* device_context, UINT slot_num)
{
	device_context->PSSetShaderResources(slot_num, 1, &shader_res_view_);
}

void PTexture::set_uv_coord(std::vector<DX::PTex_uv> vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		uv_coord.u[i] = vec[i].u;
		uv_coord.v[i] = vec[i].v;
	}
	
}

void PTexture::SetImageSize(float width, float height)
{
	width_ = width;
	height_ = height;
}


ID3D11ShaderResourceView* PTexture::shader_res_view()
{
	return shader_res_view_;
}

ID3D11ShaderResourceView** PTexture::shader_res_view_double_ptr()
{
	return &shader_res_view_;
}

float PTexture::GetImageWidth()
{
	return width_;
}

float PTexture::GetImageHeight()
{
	return height_;
}

