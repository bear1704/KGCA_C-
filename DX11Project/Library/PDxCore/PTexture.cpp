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

//
//void PTexture::set_texture_buf(PTex_uv* buf, int size)
//{
//	texture_buf_.resize(size);
//	for (int i = 0; i < size; i++)
//	{
//		texture_buf_[i].u = buf[i].u;
//		texture_buf_[i].v = buf[i].v;
//	}
//	//memcpy(texture_buf_, buf, sizeof(PTex_uv) * size);  //왜안되지
//	
//	texbuf_size_ = size;
//}
//
//void PTexture::set_texture_buf(std::vector<PTex_uv>& buf)
//{
//	//std::copy(buf.begin(), buf.end(), texture_buf_);
//	//error1!1 error   error!!!!!
//}
//
//void PTexture::set_texture_buf(std::vector<PTex_uv>&& buf)
//{
//	texture_buf_ = buf;
//}
//
//
//void PTexture::set_texbuf_size(int size)
//{
//	texbuf_size_ = size;
//}
//
//
//std::vector<PTex_uv>& PTexture::texture_buf()
//{
//	return texture_buf_;
//}

ID3D11ShaderResourceView* PTexture::shader_res_view()
{
	return shader_res_view_;
}

ID3D11ShaderResourceView** PTexture::shader_res_view_double_ptr()
{
	return &shader_res_view_;
}

//int PTexture::texbuf_size()
//{
//	return texbuf_size_;
//}
//
