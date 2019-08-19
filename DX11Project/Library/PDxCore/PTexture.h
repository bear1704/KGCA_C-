#pragma once
#include "PDevice.h"

class PTexture
{
public:
	PTexture();
	~PTexture();

private:
	std::vector<PTEXTURE_BUF>	texture_buf_; //�ؽ��İ� �� �忡 ���� �׸��� �ִ� ��츦 �����
	int							texbuf_size_;
	ID3D11ShaderResourceView*	shader_res_view_;
public:
	//setter
	void set_texture_buf(PTEXTURE_BUF* buf, int size);
	void set_texture_buf(std::vector<PTEXTURE_BUF>& buf);
	void set_texture_buf(std::vector<PTEXTURE_BUF>&& buf);
	void set_shader_res_view(ID3D11ShaderResourceView* view);
	void set_texbuf_size(int size);

	//getter
	std::vector<PTEXTURE_BUF>&	texture_buf();
	ID3D11ShaderResourceView*	shader_res_view();
	int							texbuf_size();

};

