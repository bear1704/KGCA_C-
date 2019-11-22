// PToolForm.cpp: 구현 파일
//

#include "pch.h"
#include "PTool.h"
#include "PToolForm.h"

const TCHAR* tD3D11_BLEND[] =
{
	_T("D3D11_BLEND_ZERO"),
	_T("D3D11_BLEND_ONE"),
	_T("D3D11_BLEND_SRC_COLOR"),
	_T("D3D11_BLEND_INV_SRC_COLOR"),
	_T("D3D11_BLEND_SRC_ALPHA"),
	_T("D3D11_BLEND_INV_SRC_ALPHA"),
	_T("D3D11_BLEND_DEST_ALPHA"),
	_T("D3D11_BLEND_INV_DEST_ALPHA"),
	_T("D3D11_BLEND_DEST_COLOR"),
	_T("D3D11_BLEND_INV_DEST_COLOR"),
	_T("D3D11_BLEND_SRC_ALPHA_SAT"),//10
	_T("D3D11_BLEND_BLEND_FACTOR"),
	_T("D3D11_BLEND_INV_BLEND_FACTOR"),
	_T("D3D11_BLEND_SRC1_COLOR"),
	_T("D3D11_BLEND_INV_SRC1_COLOR"),
	_T("D3D11_BLEND_SRC1_ALPHA"),
	_T("D3D11_BLEND_INV_SRC1_ALPHA"),
};

// PToolForm

IMPLEMENT_DYNCREATE(PToolForm, CFormView)

PToolForm::PToolForm()
	: CFormView(IDD_EffToolForm)
	, m_IsAlphaBlend(FALSE)
	, m_FadeInNum(0)
	, m_FadeOutNum(0)
	, m_VeloX(0)
	, m_VeloY(0)
	, m_Gravity(0)
	, m_VeloZ(0)
	, m_LaunchTime(0)
	, m_LifeTIme(0)
{

}

PToolForm::~PToolForm()
{
}

PToolForm* PToolForm::CreateOne(CWnd* pParent)
{
	PToolForm* pForm = new PToolForm;
	pForm->Create(NULL, NULL, WS_CHILD | WS_VISIBLE,
		CRect(0, 0, 500, 500), pParent, 0, NULL);

	return pForm;
}

void PToolForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_CREATEPLANE, m_BtnCreatePlane);
	DDX_Control(pDX, IDC_COMBO_BLEND_SRC, m_CtlBlendSrc);
	DDX_Check(pDX, IDC_CHECK_BLEND, m_IsAlphaBlend);
	DDX_Control(pDX, IDC_COMBO_BLEND_DEST, m_CtlBlendDest);
	DDX_Text(pDX, IDC_EDIT_FadeIn, m_FadeInNum);
	DDX_Text(pDX, IDC_EDIT_FadeOut, m_FadeOutNum);
	DDX_Control(pDX, IDC_COMBO_PlaneList, m_CtlPlaneList);
	DDX_Text(pDX, IDC_EDIT_VeloX, m_VeloX);
	DDX_Text(pDX, IDC_EDIT_VeloY, m_VeloY);
	DDX_Text(pDX, IDC_EDIT_Gravity, m_Gravity);
	DDX_Text(pDX, IDC_EDIT_VeloZ, m_VeloZ);
	DDX_Text(pDX, IDC_EDIT_LaunchTime, m_LaunchTime);
	DDX_Text(pDX, IDC_EDIT_LifeTime, m_LifeTIme);
}

BEGIN_MESSAGE_MAP(PToolForm, CFormView)
	ON_BN_CLICKED(IDC_BTN_CREATEPLANE, &PToolForm::OnBnClickedBtnCreateplane)
	ON_WM_CREATE()
	ON_CBN_SELCHANGE(IDC_COMBO_BLEND_SRC, &PToolForm::OnCbnSelchangeComboBlendSrc)
	ON_CBN_SELCHANGE(IDC_COMBO_BLEND_DEST, &PToolForm::OnCbnSelchangeComboBlendDest)
	ON_BN_CLICKED(IDC_Btn_Save, &PToolForm::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_Btn_Load, &PToolForm::OnBnClickedBtnLoad)
	ON_BN_CLICKED(IDC_CHECK_BLEND, &PToolForm::OnBnClickedCheckBlend)
	ON_BN_CLICKED(IDC_Btn_EffectApply, &PToolForm::OnBnClickedBtnEffectapply)
	ON_BN_CLICKED(IDC_Btn_Refresh, &PToolForm::OnBnClickedBtnRefresh)
	ON_CBN_SELCHANGE(IDC_COMBO_PlaneList, &PToolForm::OnCbnSelchangeComboPlanelist)
END_MESSAGE_MAP()


// PToolForm 진단

#ifdef _DEBUG
void PToolForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void PToolForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// PToolForm 메시지 처리기


void PToolForm::OnBnClickedBtnCreateplane()
{
	if (m_DlgPlane.GetSafeHwnd() == NULL)
	{
		m_DlgPlane.Create(IDD_CreatePlane);
	}

	m_DlgPlane.ShowWindow(SW_SHOW);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}



int PToolForm::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	app = (CPToolApp*)AfxGetApp();

	return 0;
}


void PToolForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	int blend_arr_size = _countof(tD3D11_BLEND);
	for (int ii = 0; ii < blend_arr_size; ii++)
	{
		m_CtlBlendSrc.AddString(tD3D11_BLEND[ii]);
		m_CtlBlendDest.AddString(tD3D11_BLEND[ii]);
	}
	m_CtlBlendSrc.SetCurSel(0);
	m_CtlBlendDest.SetCurSel(0);
}


void PToolForm::OnCbnSelchangeComboBlendSrc()
{
	/*UpdateData(TRUE);

	ID3D11DeviceContext* context = app->m_tool.immediate_device_context();
	ID3D11Device* device = app->m_tool.device();

	if (m_IsAlphaBlend == FALSE)
	{
		app->m_tool.blend_desc_.RenderTarget[0].BlendEnable = false;
	}
	else
	{
		int index = m_CtlBlendSrc.GetCurSel();
		app->m_tool.blend_desc_.RenderTarget[0].BlendEnable = true;
		app->m_tool.blend_desc_.RenderTarget[0].SrcBlend = (D3D11_BLEND)(index + 1);
	}
	HRESULT hr;
	if (FAILED(hr = device->CreateBlendState(
		&app->m_tool.blend_desc_, &app->m_tool.blend_state_)))
	{
		return;
	}*/



	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void PToolForm::OnCbnSelchangeComboBlendDest()
{

	/*UpdateData(TRUE);

	ID3D11DeviceContext* context = app->m_tool.immediate_device_context();
	ID3D11Device* device = app->m_tool.device();

	if (m_IsAlphaBlend == FALSE)
	{
		app->m_tool.blend_desc_.RenderTarget[0].BlendEnable = false;
	}
	else 
	{
		int index = m_CtlBlendDest.GetCurSel();
		app->m_tool.blend_desc_.RenderTarget[0].BlendEnable = true;
		app->m_tool.blend_desc_.RenderTarget[0].DestBlend = (D3D11_BLEND)(index + 1);
	}
	HRESULT hr;
	if (FAILED(hr = device->CreateBlendState(
		&app->m_tool.blend_desc_, &app->m_tool.blend_state_)))
	{
		return;
	}*/

}



void PToolForm::OnBnClickedBtnSave()
{

	CFileDialog dlg(
		FALSE, L"EffSceNE", NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
		L"effect scene files(*.이펙t)|*.EffSceNE|All Files(*.*)|*.*||", this
	);
	CString file_path;
	char str_file[4096];
	ZeroMemory(&str_file, sizeof(str_file));
	dlg.m_ofn.lpstrFile = file_path.GetBuffer(4096);
	dlg.m_ofn.nMaxFile = sizeof(str_file);

	if (dlg.DoModal() == IDOK)
	{
		CString path_name = dlg.GetPathName();
		multibyte_string wstr(path_name);

		_tfopen_s(&fp, wstr.c_str(), L"wb");
		
		SaveData();

		fclose(fp);

	}


	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void PToolForm::OnBnClickedBtnLoad()
{
	CFileDialog dlg(
		FALSE, L"EffSceNE", NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
		L"effect scene files(*.이펙t)|*.EffSceNE|All Files(*.*)|*.*||", this
	);
	CString file_path;
	char str_file[4096];
	ZeroMemory(&str_file, sizeof(str_file));
	dlg.m_ofn.lpstrFile = file_path.GetBuffer(4096);
	dlg.m_ofn.nMaxFile = sizeof(str_file);

	
	if (dlg.DoModal() == IDOK)
	{
		CString cstr = dlg.GetPathName();
		std::string str = CT2CA(cstr);
		LoadData(str);
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void PToolForm::SaveData()
{
	parse.ClearOutVec();


		std::vector<PSprite*> sprite_list = PSpriteManager::GetInstance().GetSpriteListFromMap();
		std::vector<PEffectObject*> effect_list = app->m_tool.effect_plane_.eff_list_;

		for (auto plane : effect_list)
		{
			PParticle* ori_particle = plane->original_particle_;

			parse.Push("data", "effect");

			if(ori_particle->effect_info.is_multi_texture == true)
				parse.Push("type", "MULTI");
			else
			{
				parse.Push("type", "OFFSET");
				parse.Push("xInit", std::to_string(ori_particle->effect_info.x_init));
				parse.Push("yInit", std::to_string(ori_particle->effect_info.y_init));
				parse.Push("xCount", std::to_string(ori_particle->effect_info.x_count));
				parse.Push("yCount", std::to_string(ori_particle->effect_info.x_count));
				parse.Push("xOffset", std::to_string(ori_particle->effect_info.x_offset));
				parse.Push("yOffset", std::to_string(ori_particle->effect_info.y_offset));
				parse.Push("tex_width", std::to_string(ori_particle->effect_info.tex_width));
				parse.Push("tex_height", std::to_string(ori_particle->effect_info.tex_height));
			}
			std::string sname;
			
			sname.assign(plane->name.begin(), plane->name.end());
			parse.Push("name", sname);
			
			if (m_IsAlphaBlend == TRUE)
				parse.Push("blend", "TRUE");
			else
				parse.Push("blend", "FALSE");

			if(ori_particle->get_lifetime_() > 999999999.0f)
				parse.Push("lifetime", std::to_string(777.0f));
			else
				parse.Push("lifetime", std::to_string(ori_particle->get_lifetime_()));

			parse.Push("each_sprite_playtime", std::to_string(ori_particle->get_allocatetime_for_onesprite()));
			
			std::string str = std::to_string(plane->matWorld_._11) + "," + std::to_string(plane->matWorld_._12) + "," +
				std::to_string(plane->matWorld_._13) + "," + std::to_string(plane->matWorld_._14);
			parse.Push("MAT1col", str);
			str = std::to_string(plane->matWorld_._21) + "," + std::to_string(plane->matWorld_._22) + "," +
				std::to_string(plane->matWorld_._23) + "," + std::to_string(plane->matWorld_._24);
			parse.Push("MAT2col", str);
			str = std::to_string(plane->matWorld_._31) + "," + std::to_string(plane->matWorld_._32) + "," +
				std::to_string(plane->matWorld_._33) + "," + std::to_string(plane->matWorld_._34);
			parse.Push("MAT3col", str);
			str = std::to_string(plane->matWorld_._41) + "," + std::to_string(plane->matWorld_._42) + "," +
				std::to_string(plane->matWorld_._43) + "," + std::to_string(plane->matWorld_._44);
			parse.Push("MAT4col", str);

			parse.Push("PlaneWidth", std::to_string(plane->width_));
			parse.Push("PlaneHeight", std::to_string(plane->height_));

			parse.Push("Particle_fadein", std::to_string(ori_particle->effect_info.fadein_time));
			parse.Push("Particle_fadeout", std::to_string(ori_particle->effect_info.fadeout_time));
			parse.Push("Particle_launch_time", std::to_string(plane->launch_time));
			str = std::to_string(ori_particle->position.x) + "," + std::to_string(ori_particle->position.y) + "," + std::to_string(ori_particle->position.z);
			parse.Push("Particle_position", str);
			str = std::to_string(ori_particle->scale.x) + "," + std::to_string(ori_particle->scale.y) + "," + std::to_string(ori_particle->scale.z);
			parse.Push("Particle_scale", str);
			str = std::to_string(ori_particle->velocity.x) + "," + std::to_string(ori_particle->velocity.y) + "," + std::to_string(ori_particle->velocity.z);
			parse.Push("Particle_Velocity", str);
			parse.Push("Particle_Gravity", std::to_string(ori_particle->gravity.y));
			str = std::to_string(ori_particle->external_force.x) + "," + std::to_string(ori_particle->external_force.y) + "," + std::to_string(ori_particle->external_force.z);
			parse.Push("Particle_ExternalForce",str);
			parse.Push("BlendSrc", std::to_string(plane->src_blend_));
			parse.Push("BlendDest", std::to_string(plane->dest_blend_));

			int tex_list_size = ori_particle->get_texture_list_ptr()->size();
			for (int ii = 0 ; ii < tex_list_size; ii++)
			{
				PTexture* tex = ori_particle->get_texture_list_ptr()->at(ii);
				std::wstring wstr = tex->tex_path();
				str.clear();
				str.assign(wstr.begin(), wstr.end());
				parse.Push("tex_path", str);
			}
			
			//OFFSET
			parse.Commit();
		}

		int ovec_size = parse.out_vec().size();
		for (int ii = 0; ii < ovec_size; ii++)
		{
			for (int jj = 0; jj < parse.out_vec().at(ii).size(); jj++)
			{
				std::string& str = parse.out_vec().at(ii).at(jj);
				multibyte_string tstr;
				tstr.assign(str.begin(), str.end());
				_ftprintf(fp, _T("%s\n"), (TCHAR*)tstr.c_str());
			}
		}

}

void PToolForm::LoadData(std::string path)
{
	PairVec vec;
	parse.XmlParse(path, &vec, true);

	auto iter = vec.begin();
		
	while (iter != vec.end())
	{
		PEffectObject* pp = new PEffectObject();
		SpriteDataInfo info;
		EffectInfo eff_info;
		std::vector<PTexture*> tex_list;
		int frame_count = 0;
		float each_sprite_playtime = 0.0f;

		D3DXVECTOR3 particle_pos;
		D3DXVECTOR3 particle_scale;
		D3DXVECTOR3 particle_velocity;
		D3DXVECTOR3 particle_gravity;
		D3DXVECTOR3 particle_external_force;
		

		if (iter->second == "effect")
		{
			while (true)
			{
				iter++;
				if (iter->first == "type")
				{
					if (iter->second == "MULTI")
						eff_info.is_multi_texture = true;
					else
						eff_info.is_multi_texture = false;
				}
				else if (iter->first == "name")
				{
					info.sprite_name = iter->second;
				}
				else if (iter->first == "lifetime")
					info.lifetime = std::stof(iter->second);
				else if (iter->first == "each_sprite_playtime")
					each_sprite_playtime = std::stof(iter->second);
				else if (iter->first == "MAT1col")
				{
					std::vector<string> col1 = parse.SplitString(iter->second, ',');
					pp->matWorld_._11 = std::stof(col1[0]); pp->matWorld_._12 = std::stof(col1[1]);
					pp->matWorld_._13 = std::stof(col1[2]); pp->matWorld_._14 = std::stof(col1[3]);
				}
				else if (iter->first == "MAT2col")
				{
					std::vector<string> col2 = parse.SplitString(iter->second, ',');
					pp->matWorld_._21 = std::stof(col2[0]); pp->matWorld_._22 = std::stof(col2[1]);
					pp->matWorld_._23 = std::stof(col2[2]); pp->matWorld_._24 = std::stof(col2[3]);
				}
				else if (iter->first == "MAT3col")
				{
					std::vector<string> col3 = parse.SplitString(iter->second, ',');
					pp->matWorld_._31 = std::stof(col3[0]); pp->matWorld_._32 = std::stof(col3[1]);
					pp->matWorld_._33 = std::stof(col3[2]); pp->matWorld_._34 = std::stof(col3[3]);
				}
				else if (iter->first == "MAT4col")
				{
					std::vector<string> col4 = parse.SplitString(iter->second, ',');
					pp->matWorld_._41 = std::stof(col4[0]); pp->matWorld_._42 = std::stof(col4[1]);
					pp->matWorld_._43 = std::stof(col4[2]); pp->matWorld_._44 = std::stof(col4[3]);
				}
				else if (iter->first == "Particle_fadein")
				{
					eff_info.fadein_time = std::stof(iter->second);
					eff_info.current_fadein_time = std::stof(iter->second);
				}
				else if (iter->first == "Particle_fadeout")
				{
					eff_info.fadeout_time = std::stof(iter->second);
					eff_info.current_fadeout_time= std::stof(iter->second);
				}
				else if (iter->first == "Particle_launch_time")
				{
					pp->launch_time = std::stof(iter->second);
				}
				else if (iter->first == "Particle_position")
				{
					std::vector<string> split = parse.SplitString(iter->second, ',');
					particle_pos = D3DXVECTOR3(std::stof(split[0]), std::stof(split[1]), std::stof(split[2]));
				}
				else if (iter->first == "Particle_scale")
				{
					std::vector<string> split = parse.SplitString(iter->second, ',');
					particle_scale = D3DXVECTOR3(std::stof(split[0]), std::stof(split[1]), std::stof(split[2]));
				}
				else if (iter->first == "Particle_Velocity")
				{
					std::vector<string> split = parse.SplitString(iter->second, ',');
					particle_velocity = D3DXVECTOR3(std::stof(split[0]), std::stof(split[1]), std::stof(split[2]));
				}
				else if (iter->first == "Particle_Gravity")
				{
					particle_gravity = D3DXVECTOR3(0.0f, std::stof(iter->second), 0.0f);
				}
				else if (iter->first == "Particle_ExternalForce")
				{
					std::vector<string> split = parse.SplitString(iter->second, ',');
					particle_external_force = D3DXVECTOR3(std::stof(split[0]), std::stof(split[1]), std::stof(split[2]));
				}
				else if (iter->first == "BlendSrc")
				{
					pp->src_blend_ = (D3D11_BLEND) std::stoi(iter->second);
				}
				else if (iter->first == "BlendDest")
				{
					pp->dest_blend_ = (D3D11_BLEND)std::stoi(iter->second);
				}
				else if (iter->first == "tex_path")
				{
					TextureInfo info;
					std::wstring path_wstr;
					StringToWstring(iter->second, path_wstr);
					info.tex_path = path_wstr;
					PTexture* tex = PTextureManager::GetInstance().LoadTextureWithoutScript(info, app->m_tool.device());

					if (tex)
						tex_list.push_back(tex);
					frame_count++;
				}
				else if (iter->first == "xInit")
					eff_info.x_init = std::stof(iter->second);
				else if (iter->first == "yInit")
					eff_info.y_init = std::stof(iter->second);
				else if (iter->first == "xCount")
					eff_info.x_count = std::stof(iter->second);
				else if (iter->first == "yCount")
					eff_info.y_count = std::stof(iter->second);
				else if (iter->first == "xOffset")
					eff_info.x_offset = std::stof(iter->second);
				else if (iter->first == "yOffset")
					eff_info.y_offset = std::stof(iter->second);
				else if (iter->first == "tex_width")
					eff_info.tex_width = std::stof(iter->second);
				else if (iter->first == "tex_height")
					eff_info.tex_height = std::stof(iter->second);
				else if (iter->first == "PlaneWidth")
					pp->width_ = std::stof(iter->second);
				else if (iter->first == "PlaneHeight")
					pp->height_ = std::stof(iter->second);
				else if (iter->first == "END")
				{
					//offset sprite일 경우 프레임 갯수를 다르게 세어야 한다.
					if (eff_info.is_multi_texture == false)
					{
						frame_count = eff_info.x_count * eff_info.y_count;
					}
						info.once_playtime = each_sprite_playtime * frame_count;
						info.max_frame = frame_count;
					
					break;
				}

			}


			//OFFSET 이펙트일 시의 텍스쳐 바운더리 추가 작업
			if (eff_info.is_multi_texture == false)
			{
				float xOrigin = eff_info.x_init;
				float yOrigin = eff_info.y_init;

				for (int ii = 0; ii < eff_info.y_count; ii++)
				{
					for (int jj = 0; jj < eff_info.x_count; jj++)
					{
						float current_xOrigin = xOrigin + eff_info.x_offset * jj;
						float current_yOrigin = yOrigin + eff_info.y_offset * ii;

						DX::PTex_uv4 uv;
						uv.u[0] = current_xOrigin / eff_info.tex_width;
						uv.u[1] = (current_xOrigin + eff_info.x_offset) / eff_info.tex_width;
						uv.u[2] = (current_xOrigin + eff_info.x_offset) / eff_info.tex_width;
						uv.u[3] = current_xOrigin / eff_info.tex_width;
						uv.v[0] = current_yOrigin / eff_info.tex_height;
						uv.v[1] = current_yOrigin / eff_info.tex_height;
						uv.v[2] = (current_yOrigin + eff_info.y_offset) / eff_info.tex_height;
						uv.v[3] = (current_yOrigin + eff_info.y_offset) / eff_info.tex_height;

						info.tex_boundary_list.push_back(uv);
					}
				}
			}

			//sprite_info(info) 스프라이트 추가과정
			std::wstring wstr_spname;
			StringToWstring(info.sprite_name, wstr_spname);
			PSpriteManager::GetInstance().LoadSpriteDataWithoutScript(wstr_spname, tex_list, info);

			//이펙트 생성(sprite가 미리 생성되어 매니져에 들어가 있어야 한다)
			pp->CreateEffect(app->m_tool.device(), app->m_tool.immediate_device_context(), pp->width_, pp->height_, wstr_spname, eff_info);
			pp->original_particle_->position	= particle_pos;
			pp->original_particle_->scale		= particle_scale;
			pp->original_particle_->velocity	= particle_velocity;
			pp->original_particle_->gravity		= particle_gravity;
			pp->original_particle_->external_force		= particle_external_force;
			
			
			D3DXVECTOR3 v_scale; D3DXVECTOR3 v_pos; D3DXQUATERNION q_rot; D3DXMATRIX mat_rot;
			D3DXMatrixDecompose(&v_scale, &q_rot, &v_pos, &pp->matWorld_);
			D3DXMatrixRotationQuaternion(&mat_rot, &q_rot);
			pp->plane_rot_matrix_ = mat_rot;

			app->m_tool.effect_plane_.eff_list_.push_back(pp);

			iter++;
		}

	}

	
}


void PToolForm::OnBnClickedCheckBlend()
{

	UpdateData(TRUE);

	ID3D11DeviceContext* context = app->m_tool.immediate_device_context();
	ID3D11Device* device = app->m_tool.device();

	if (m_IsAlphaBlend == TRUE)
		app->m_tool.blend_desc_.RenderTarget[0].BlendEnable = true;
	else
		app->m_tool.blend_desc_.RenderTarget[0].BlendEnable = false;

	//int index = m_CtlBlendSrc.GetCurSel();
	//app->m_tool.blend_desc_.RenderTarget[0].SrcBlend = (D3D11_BLEND)(index + 1);

	//index = m_CtlBlendDest.GetCurSel();
	//app->m_tool.blend_desc_.RenderTarget[0].DestBlend = (D3D11_BLEND)(index + 1);
	//
	//HRESULT hr;
	//if (FAILED(hr = device->CreateBlendState(
	//	&app->m_tool.blend_desc_, &app->m_tool.blend_state_)))
	//{
	//	return;
	//}
}

/*
적용 버튼을 누르면 현재 이펙트의 정보가 적용된다.
*/
void PToolForm::OnBnClickedBtnEffectapply()
{
	UpdateData(TRUE);

	m_pCurrentEffObj->original_particle_->effect_info.fadeout_time = m_FadeOutNum;
	m_pCurrentEffObj->original_particle_->effect_info.current_fadeout_time = m_FadeOutNum;
	m_pCurrentEffObj->original_particle_->effect_info.fadein_time = m_FadeInNum;
	m_pCurrentEffObj->original_particle_->effect_info.current_fadein_time = m_FadeInNum;
	m_pCurrentEffObj->original_particle_->set_lifetime(m_LifeTIme);
	m_pCurrentEffObj->original_particle_->set_remain_lifetime(m_LifeTIme);
	

	m_pCurrentEffObj->original_particle_->gravity.y = m_Gravity;
	m_pCurrentEffObj->original_particle_->velocity.x = m_VeloX;
	m_pCurrentEffObj->original_particle_->velocity.y = m_VeloY;
	m_pCurrentEffObj->original_particle_->velocity.z = m_VeloZ;
	
	m_pCurrentEffObj->launch_time = m_LaunchTime;
	
	int index = m_CtlBlendSrc.GetCurSel();
	m_pCurrentEffObj->src_blend_ = (D3D11_BLEND)(index + 1);
	index = m_CtlBlendDest.GetCurSel();
	m_pCurrentEffObj->dest_blend_ = (D3D11_BLEND)(index + 1);

	//external force 들어갈 자리
}

/*
이펙트 오브젝트 리스트를 최신화
*/
void PToolForm::OnBnClickedBtnRefresh()
{
	UpdateData(TRUE);
	m_CtlPlaneList.ResetContent();

	std::vector<PEffectObject*> object_list = app->m_tool.effect_plane_.eff_list_;
	
	for (PEffectObject* sp : object_list)
	{
		multibyte_string mstr = string_to_multibyte(sp->original_particle_->get_name());
		m_CtlPlaneList.AddString(mstr.c_str());
	}

}


void PToolForm::OnCbnSelchangeComboPlanelist()
{
	

	int index = m_CtlPlaneList.GetCurSel();
	CString cstr;
	m_CtlPlaneList.GetLBText(index, cstr);

	std::string str = CT2CA(cstr);

	auto list = app->m_tool.effect_plane_.eff_list_;

	for (int ii = 0; ii < list.size(); ii++)
	{
		if (list[ii]->original_particle_->get_name() == str)
		{
			m_pCurrentEffObj = list[ii];
			m_FadeOutNum = m_pCurrentEffObj->original_particle_->effect_info.fadeout_time;
			m_FadeOutNum = m_pCurrentEffObj->original_particle_->effect_info.current_fadeout_time;
			m_FadeInNum = m_pCurrentEffObj->original_particle_->effect_info.fadein_time;
			m_FadeInNum = m_pCurrentEffObj->original_particle_->effect_info.current_fadein_time;

			m_Gravity = m_pCurrentEffObj->original_particle_->gravity.y;
			m_VeloX = m_pCurrentEffObj->original_particle_->velocity.x;
			m_VeloY = m_pCurrentEffObj->original_particle_->velocity.y;
			m_VeloZ = m_pCurrentEffObj->original_particle_->velocity.z;
			m_LaunchTime = m_pCurrentEffObj->launch_time;
			m_LifeTIme = m_pCurrentEffObj->original_particle_->get_lifetime_();

			m_CtlBlendSrc.SetCurSel(m_pCurrentEffObj->src_blend_ - 1);
			m_CtlBlendDest.SetCurSel(m_pCurrentEffObj->dest_blend_ - 1);

			UpdateData(FALSE);
			break;
		}
	}
}
