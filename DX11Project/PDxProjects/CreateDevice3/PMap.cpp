#include "PMap.h"



bool PMap::Load(PMapDesc& md)
{
	PMapDesc map_desc_ = md;
	vertex_rows_ = md.vertex_rows;
	vertex_cols_ = md.vertex_cols;
	cell_rows_ = md.vertex_rows - 1;
	cell_cols_ = md.vertex_cols - 1;
	numberof_vertices_ = vertex_rows_ * vertex_cols_;
	numberof_faces_ = cell_rows_ * cell_cols_ * 2;
	cell_distance_ = md.cell_disatnce;


	
	if (md.vs_path == L"")
	{
		if (!Create(device_, immediate_context_, L"VertexShader.hlsl", "VS", L"PixelShader.hlsl", "PS", md.texture_name))
			assert(false);
	}
	else
	{
		if (!Create(device_, immediate_context_, md.vs_path, md.vs_func, md.ps_path, md.ps_func, md.texture_name))
			assert(false);
	}

	return true;

}

PMap::PMap()
{
}

PMap::~PMap()
{
}

HRESULT PMap::CreateVertexData()
{
	float half_cols = (vertex_cols_ - 1) / 2.0f;
	float half_rows = (vertex_rows_ - 1) / 2.0f;
	float tex_offset_u = 1.0f / (vertex_cols_ - 1);
	float tex_offset_v = 1.0f / (vertex_rows_ - 1);

	vertex_list_.resize(numberof_vertices_);

	for (int row = 0; row < vertex_rows_; row++)
	{
		for (int col = 0; col < vertex_cols_; col++)
		{
			int vert_index = row * vertex_cols_ + col;
			vertex_list_[vert_index].pos.x = (col - half_cols) * cell_distance_;
			vertex_list_[vert_index].pos.z = -((row - half_rows) * cell_distance_);
			vertex_list_[vert_index].pos.y = 0.0f;


			vertex_list_[vert_index].uv.x = col;
			vertex_list_[vert_index].uv.y = row;

			vertex_list_[vert_index].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex_list_[vert_index].color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

	return S_OK;
}

HRESULT PMap::CreateIndexData()
{
	index_list_.resize(numberof_faces_ * 3);

	int index = 0;

	for (int row = 0; row < cell_rows_; row++)
	{
		for (int col = 0; col < cell_cols_; col++)
		{
			int next_row = row + 1;
			int next_col = col + 1;

			index_list_[index + 0] = row * vertex_cols_ + col;
			index_list_[index + 1] = row * vertex_cols_ + next_col;
			index_list_[index + 2] = next_row * vertex_cols_ + col;

			index_list_[index + 3] = index_list_[index + 2];
			index_list_[index + 4] = index_list_[index + 1];
			index_list_[index + 5] = next_row * vertex_cols_ + next_col;

			index += 6;

		}
	}

	return S_OK;
}
