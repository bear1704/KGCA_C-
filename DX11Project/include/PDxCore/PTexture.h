#pragma once
#include "PDevice.h"
#include "PDxHelper.h"

class PTexture
{
public:
	PTexture();
	~PTexture();
	
private:
	//std::vector<PTex_uv>	texture_buf_; //텍스쳐가 한 장에 여러 그림이 있는 경우를 ㄹ대비
	//int							texbuf_size_;
	ID3D11ShaderResourceView*	shader_res_view_;
	multibyte_string tex_name_;
	multibyte_string tex_path_;
	float width_, height_;
	DX::PTex_uv4 uv_coord;

public:
	//setter
	void set_shader_res_view(ID3D11ShaderResourceView* view);
	void Apply(ID3D11DeviceContext* device_context, UINT slot_num);
	void Draw(DX::PVertexAndUV vt_uv, float scale, bool is_reversal);
	void set_uv_coord(std::vector<DX::PTex_uv> vec);
	void SetImageSize(float width, float height);

	//getter
	ID3D11ShaderResourceView*	shader_res_view();
	ID3D11ShaderResourceView**	shader_res_view_double_ptr();
	float GetImageWidth();
	float GetImageHeight();


	

};

