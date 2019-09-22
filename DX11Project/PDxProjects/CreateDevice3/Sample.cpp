#include "Sample.h"

Sample::Sample()
{
	
}

Sample::~Sample()
{

}


bool Sample::Init()
{
	/*cb_light_.g_AmbientMaterial = D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f);
	cb_light_.g_DiffuseMaterial = D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f);
	cb_light_.g_SpecularMaterial = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	cb_light_.g_AmbientColor = D3DXVECTOR4(1, 1, 1, 1);
	cb_light_.g_DiffuseColor = D3DXVECTOR4(1, 1, 1, 1);
	cb_light_.g_SpecularColor = D3DXVECTOR4(1, 1, 1, 1);

	constant_buffer_light_.Attach(DX::CreateConstantBuffer(device_, &cb_light_, 1, sizeof(LIGHT_CONSTANT_BUFFER), false));

*/


	screen_tex_object_.Init(device_, immediate_device_context_, L"VertexShader.hlsl", "VS", L"PixelShader.hlsl", "PS", L"blue");
	obj_.Init(device_, immediate_device_context_, L"VertexShader.hlsl", "VS", L"PixelShader.hlsl", "PS", L"blue");
	box_.Init(device_, immediate_device_context_, L"Terrain.hlsl", "VS", L"Terrain.hlsl", "PS", L"env");
	skybox_.Init(device_, immediate_device_context_, L"Skybox.hlsl", "VS", L"Skybox.hlsl", "PS");


	D3DXMatrixIdentity(&mat_obj_world_);
	D3DXMatrixIdentity(&mat_box_world_);

	free_camera_.Init();

	D3DXVECTOR3 eye(0.0f, 0.0f, -2.0f);
	D3DXVECTOR3 at(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);


	free_camera_.CreateTargetViewMatrix(eye, at, up);
	free_camera_.CreateProjectionMatrix();

	D3DXMatrixRotationY(&mat_box_world_, D3DX_PI / 2.5);
	D3DXMatrixScaling(&mat_box_world_, 4.0f, 4.0f, 10.0f);

	mat_obj_world_._42 = 1.0f;
	mat_box_world_._42 = 70.0f;
	

	main_camera_ = &free_camera_;

	map_.Init(device_, immediate_device_context_);
	map_.CreateHeightMap(device_, immediate_device_context_, L"data/texture/heightMap513.bmp");


	PMapDesc md;
	md.vertex_cols = map_.vertex_cols();
	md.vertex_rows = map_.vertex_rows();
	md.cell_disatnce = 1;
	md.vs_path = L"DiffuseLight.hlsl";
	md.vs_func = "VS";
	md.ps_path = L"DiffuseLight.hlsl";
	md.ps_func = "PS";
	md.texture_name = L"stone_wall";

	if (!map_.Load(md))
		assert(false);

	dx_rt_.Create(device_, 1024, 1024);
	dx_minimap_rt_.Create(device_, 1024, 1024);
	
	
	light_obj_.Init(D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f), D3DXVECTOR4(1, 1, 1, 1), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR4(1, 1, 1, 1),
		D3DXVECTOR4(3.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR4(1,1,1,1),device_, immediate_device_context_, main_camera_);
	
	return true;
}

bool Sample::Frame()
{

	light_obj_.Frame();
	//D3DXMATRIX light_world, translate, rotation;
	//D3DXMatrixTranslation(&light_world, 100.0f, 50.0f, 0.0f);
	//D3DXMatrixRotationY(&rotation, g_fGameTimer * D3DX_PI * 0.1f);
	//D3DXMatrixMultiply(&light_world, &translate, &rotation);


	//light_vector_.x = light_world._41;
	//light_vector_.y = light_world._42;
	//light_vector_.z = light_world._43;

	//D3DXVec3Normalize(&light_vector_, &light_vector_);
	//light_vector_ *= -1.0f;



#pragma region KEY
	if (g_InputActionMap.qKey == KEYSTAT::KEY_HOLD)
	{
		main_camera_->UpWard();
	}
	if (g_InputActionMap.eKey == KEYSTAT::KEY_HOLD)
	{
		main_camera_->DownWard();
	}
	if (g_InputActionMap.aKey == KEYSTAT::KEY_HOLD)
	{
		main_camera_->MoveLeft();
	}
	if (g_InputActionMap.dKey == KEYSTAT::KEY_HOLD)
	{
		main_camera_->MoveRight();
	}
	if (g_InputActionMap.wKey == KEYSTAT::KEY_HOLD)
	{
		main_camera_->MoveFoward();
	}
	if (g_InputActionMap.sKey == KEYSTAT::KEY_HOLD)
	{
		main_camera_->MoveBackward();
	}
	if (g_InputActionMap.middleClick == KEYSTAT::KEY_PUSH)
	{
		ToggleIsWireframeRender();
	}
	if (g_InputActionMap.leftArrowKey == KEYSTAT::KEY_HOLD)
		main_camera_->RotateLeft();
	if (g_InputActionMap.rightArrowKey == KEYSTAT::KEY_HOLD)
		main_camera_->RotateRight();
	if (g_InputActionMap.upArrowKey == KEYSTAT::KEY_HOLD)
		main_camera_->RotateUp();
	if (g_InputActionMap.downArrowKey == KEYSTAT::KEY_HOLD)
		main_camera_->RotateDown();

#pragma endregion

	main_camera_->Frame();
	obj_.Frame();
	box_.Frame();
	map_.Frame();
	return true;
}

bool Sample::Render()
{
	//light

	light_obj_.Render();

	//D3DXMATRIX matWorld, matScale;
	//D3DXMatrixScaling(&matScale, 100, 100, 100);
	//D3DXMatrixRotationY(&matWorld, g_fGameTimer);
	//D3DXMatrixMultiply(&matWorld, &matScale, &matWorld);
	//matWorld._42 = 200.0f; //공?

	//cb_light_.g_vLightDir.x = light_vector_.x;
	//cb_light_.g_vLightDir.y = light_vector_.y;
	//cb_light_.g_vLightDir.z = light_vector_.z;
	//cb_light_.g_vLightDir.w = 1;

	//cb_light_.g_vEyeDir.x = main_camera_->vec_look_.x;
	//cb_light_.g_vEyeDir.y = main_camera_->vec_look_.y;
	//cb_light_.g_vEyeDir.z = main_camera_->vec_look_.z;
	//cb_light_.g_vEyeDir.w = 20.0f; // 빛의 밝기 강도

	//cb_light_.g_vEyePos.x = main_camera_->camera_position_.x;
	//cb_light_.g_vEyePos.y = main_camera_->camera_position_.y;
	//cb_light_.g_vEyePos.z = main_camera_->camera_position_.z;
	//cb_light_.g_vEyePos.w = 50.0f;

	//D3DXMATRIX matInvWorld;
	//D3DXMatrixInverse(&matInvWorld, NULL, &matWorld);
	//D3DXMatrixTranspose(&matInvWorld, &matInvWorld);
	//D3DXMatrixTranspose(&cb_light_.g_matInvWorld, &matInvWorld);
	/*
	immediate_device_context_->UpdateSubresource(constant_buffer_light_.Get(), 0, NULL, &cb_light_, 0, 0);
	immediate_device_context_->VSSetConstantBuffers(1, 1, constant_buffer_light_.GetAddressOf());
	immediate_device_context_->PSSetConstantBuffers(1, 1, constant_buffer_light_.GetAddressOf());
	

	D3DXMatrixIdentity(&cb_light_.g_matInvWorld);
	immediate_device_context_->UpdateSubresource(constant_buffer_light_.Get(), 0, NULL, &cb_light_, 0, 0);*/



	//sky
	D3DXMATRIX mat_sky_world;
	D3DXMatrixScaling(&mat_sky_world, 10, 10, 10);
	D3DXMATRIX mat_sky_view = main_camera_->matView_;
	mat_sky_view._41 = 0.0f;
	mat_sky_view._42 = 0.0f;
	mat_sky_view._43 = 0.0f;


	dx_rt_.Begin(immediate_device_context_);
	{
		if(is_wireframe_render_) //마우스 휠 여부에 따라 와이어프레임, 솔리드를 가르는 코드
			DX::ApplyRasterizerState(immediate_device_context_, DX::PDxState::rs_state_wireframe_);
		else
			DX::ApplyRasterizerState(immediate_device_context_, DX::PDxState::rs_state_solidframe_);
		//sky

		DX::ApplyDepthStencilState(immediate_device_context_, DX::PDxState::depth_stencil_state_enable_);
		DX::ApplyBlendState(immediate_device_context_, DX::PDxState::blend_state_alphablend_);
		DX::ApplySamplerState(immediate_device_context_, DX::PDxState::sampler_state_wrap_point);
		
		skybox_.SetWVPMatrix(&mat_sky_world, &mat_sky_view, &main_camera_->matProj_);
		skybox_.Render();

		obj_.SetWVPMatrix(&mat_obj_world_, &main_camera_->matView_, &main_camera_->matProj_);
		obj_.Render();
		box_.SetWVPMatrix(&mat_box_world_, &main_camera_->matView_, &main_camera_->matProj_);
		box_.Render();
		map_.SetWVPMatrix(&main_camera_->matWorld_, &main_camera_->matView_, &main_camera_->matProj_);
		map_.Render();
		


		dx_rt_.End(immediate_device_context_);
	}

	D3DXMATRIX mat_top_view;
	D3DXMatrixLookAtLH(&mat_top_view,
		&D3DXVECTOR3(0, 70, 0),
		&D3DXVECTOR3(0, 0, 0.1),
		&D3DXVECTOR3(0, 1, 0));

	DX::ApplyRasterizerState(immediate_device_context_, DX::PDxState::rs_state_solidframe_);

	//dx_minimap_rt_.Begin(immediate_device_context_);
	//{		
	//	DX::ApplyDepthStencilState(immediate_device_context_, DX::PDxState::depth_stencil_state_enable_);
	//	DX::ApplySamplerState(immediate_device_context_, DX::PDxState::sampler_state_wrap_point);

	//	//skybox_.SetWVPMatrix(&mat_sky_world, &mat_sky_view, &main_camera_->matProj_);
	//	//skybox_.Render();


	//	obj_.SetWVPMatrix(&mat_obj_world_, &mat_top_view, &main_camera_->matProj_);
	//	obj_.Render();
	//	box_.SetWVPMatrix(&mat_box_world_, &mat_top_view, &main_camera_->matProj_);
	//	box_.Render();
	//	map_.SetWVPMatrix(nullptr, &mat_top_view, &main_camera_->matProj_);
	//	map_.Render();
	//	dx_minimap_rt_.End(immediate_device_context_);
	//}


	screen_tex_object_.vertex_list()[0].pos = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	screen_tex_object_.vertex_list()[1].pos = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	screen_tex_object_.vertex_list()[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	screen_tex_object_.vertex_list()[3].pos = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);

	screen_tex_object_.vertex_list()[0].uv = D3DXVECTOR2(0.0f, 0.0f);
	screen_tex_object_.vertex_list()[1].uv = D3DXVECTOR2(1.0f, 0.0f);
	screen_tex_object_.vertex_list()[2].uv = D3DXVECTOR2(1.0f, 1.0f);
	screen_tex_object_.vertex_list()[3].uv = D3DXVECTOR2(0.0f, 1.0f);
	

	DX::ApplyRasterizerState(immediate_device_context_, DX::PDxState::rs_state_solidframe_);

	//immediate_device_context_->UpdateSubresource(screen_tex_object_.dx_helper().vertex_buffer_.Get(),
	//	0, NULL, &screen_tex_object_.vertex_list().at(0), 0, 0);
	//screen_tex_object_.SetWVPMatrix(NULL, NULL, NULL);
	//screen_tex_object_.PreRender();
	//immediate_device_context_->PSSetShaderResources(0, 1, dx_minimap_rt_.shader_res_view_.GetAddressOf());
	//screen_tex_object_.PostRender();

	screen_tex_object_.vertex_list()[0].pos = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	screen_tex_object_.vertex_list()[1].pos = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	screen_tex_object_.vertex_list()[2].pos = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	screen_tex_object_.vertex_list()[3].pos = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);

	screen_tex_object_.vertex_list()[0].uv = D3DXVECTOR2(0.0f, 0.0f);
	screen_tex_object_.vertex_list()[1].uv = D3DXVECTOR2(1.0f, 0.0f);
	screen_tex_object_.vertex_list()[2].uv = D3DXVECTOR2(1.0f, 1.0f);
	screen_tex_object_.vertex_list()[3].uv = D3DXVECTOR2(0.0f, 1.0f);

	immediate_device_context_->UpdateSubresource(screen_tex_object_.dx_helper().vertex_buffer_.Get(),
		0, NULL, &screen_tex_object_.vertex_list().at(0), 0, 0);

	screen_tex_object_.SetWVPMatrix(NULL, NULL, NULL);
	screen_tex_object_.PreRender();
	immediate_device_context_->PSSetShaderResources(0, 1,
		dx_rt_.shader_res_view_.GetAddressOf());
	screen_tex_object_.PostRender();

	return true;
}

bool Sample::Release()
{
	obj_.Release();
	box_.Release();
	map_.Release();
	dx_rt_.Release();
	return true;
}

void Sample::MessageProc(MSG msg)
{
	PCore::MessageProc(msg);
	//PInput::GetInstance().MsgProc(msg);
	if (main_camera_ == nullptr) return;
	main_camera_->MessageProc(msg);
}
