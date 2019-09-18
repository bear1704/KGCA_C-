#pragma once
#include "PCore.h"
#include "PTexture.h"
#include "PShape.h"
#include "PDxState.h"
#include "PCamera.h"
#include "PMap.h"
#include "PFreeCamera.h"
#include "PDxRenderTarget.h"

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment (lib, "PDxCoreLib64_D.lib")
#else
#pragma comment (lib, "PDxCoreLib64_R.lib")
#endif

#pragma comment (lib, "fmod_vc.lib")
#pragma comment (lib, "winmm.lib")


PScene* g_current_scene_;


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
public:
	void MessageProc(MSG msg) override;

};
PCORE_RUN(L"planeobj", 0, 0, 800, 600);
