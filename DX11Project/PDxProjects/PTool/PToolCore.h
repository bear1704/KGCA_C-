#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "PCore.h"
#include "PCore.h"
#include "PTexture.h"
#include "PShape.h"
#include "PDxState.h"
#include "PCamera.h"
#include "PMap.h"
#include "PFreeCamera.h"
#include "PDxRenderTarget.h"
#include "PSkyBox.h"
#include "PLightObj.h"
#include "PNormHeightMap.h"

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment (lib, "PDxCoreLib64_D.lib")
#else
#pragma comment (lib, "PDxCoreLib64_R.lib")
#endif

#pragma comment (lib, "fmod_vc.lib")
#pragma comment (lib, "winmm.lib")




class PToolCore : public PCore
{
public:
	PToolCore();
	~PToolCore();

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;


public:
	D3DXMATRIX mat_obj_world_;
	D3DXMATRIX mat_box_world_;

	PCamera* main_camera_;
	PCamera  backview_camera_;
	PFreeCamera free_camera_;

	PDxRenderTarget dx_rt_;
	PDxRenderTarget dx_minimap_rt_;

	PPlaneObject obj_;
	PBoxObject box_;

	PPlaneObject screen_tex_object_;

	PSkyBox skybox_;

	//LIGHT_CONSTANT_BUFFER cb_light_;
	//Microsoft::WRL::ComPtr<ID3D11Buffer> constant_buffer_light_;
	//D3DXVECTOR3 light_vector_;

	PLightObj light_obj_;
	PNormHeightMap map_;
	//PHeightMap map_;
	PImportObject ship_;


	Microsoft::WRL::ComPtr<ID3D11Buffer> constant_buffer_changes_everyframe_;
	CB_VS_NearlyNotChange cb_nearly_not_changes_;
	Microsoft::WRL::ComPtr<ID3D11Buffer> constant_buffer_nearly_not_changes_;




public:
	void MessageProc(MSG msg) override;
	HRESULT CreateConstantBuffer();

};