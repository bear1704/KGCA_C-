#pragma once
#include "PDevice.h"

class PTexture
{
public:
	PTexture();
	~PTexture();

public:
	PTEXTURE_BUF*				texture_buf_;
	int							texbuf_size_;
	ID3D11ShaderResourceView**	shader_res_view_;
public:
	//setter
	void set_texture_buf(PTEXTURE_BUF* buf, int size);
	void set_shader_res_view(ID3D11ShaderResourceView** view);

	//getter
	PTEXTURE_BUF* texture_buf();
	ID3D11ShaderResourceView** shader_res_view();


};

