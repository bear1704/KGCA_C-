#pragma once
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

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment (lib, "PDxCoreLib64_D.lib")
#else
#pragma comment (lib, "PDxCoreLib64_R.lib")
#endif

#pragma comment (lib, "fmod_vc.lib")
#pragma comment (lib, "winmm.lib")


PScene* g_current_scene_;

//
//struct LIGHT_CONSTANT_BUFFER
//{
//	D3DXMATRIX g_matInvWorld;
//
//	D3DXVECTOR4 g_AmbientMaterial;
//	D3DXVECTOR4 g_DiffuseMaterial;
//	D3DXVECTOR4 g_SpecularMaterial;
//	D3DXVECTOR4 g_EmissionMaterial;
//
//	//Light
//	D3DXVECTOR4			g_AmbientColor;
//	D3DXVECTOR4			g_DiffuseColor;
//	D3DXVECTOR4			g_SpecularColor;
//	D3DXVECTOR4			g_vLightDir; // w = light damping(attenuation) : °¨¼è
//	D3DXVECTOR4			g_vLightPos; // w = light radius
//	D3DXVECTOR4			g_vEyeDir;// w = light intensity : °­µµ
//	D3DXVECTOR4			g_vEyePos;// w = light radius	
//
//};

class Sample : public PCore
{
public:
	Sample();
	~Sample();

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
	PHeightMap map_;

	PPlaneObject screen_tex_object_;

	PSkyBox skybox_;

	//LIGHT_CONSTANT_BUFFER cb_light_;
	//Microsoft::WRL::ComPtr<ID3D11Buffer> constant_buffer_light_;
	//D3DXVECTOR3 light_vector_;
	
	PLightObj light_obj_;
public:
	void MessageProc(MSG msg) override;

};
PCORE_RUN(L"planeobj", 0, 0, 800, 600);
