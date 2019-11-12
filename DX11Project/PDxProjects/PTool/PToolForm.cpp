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
}

BEGIN_MESSAGE_MAP(PToolForm, CFormView)
	ON_BN_CLICKED(IDC_BTN_CREATEPLANE, &PToolForm::OnBnClickedBtnCreateplane)
	ON_WM_CREATE()
	ON_CBN_SELCHANGE(IDC_COMBO_BLEND_SRC, &PToolForm::OnCbnSelchangeComboBlendSrc)
	ON_CBN_SELCHANGE(IDC_COMBO_BLEND_DEST, &PToolForm::OnCbnSelchangeComboBlendDest)
	ON_BN_CLICKED(IDC_Btn_Save, &PToolForm::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_Btn_Load, &PToolForm::OnBnClickedBtnLoad)
	ON_BN_CLICKED(IDC_CHECK_BLEND, &PToolForm::OnBnClickedCheckBlend)
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
	UpdateData(TRUE);

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
	}



	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void PToolForm::OnCbnSelchangeComboBlendDest()
{

	UpdateData(TRUE);

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
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
		std::vector<PPlaneObject> plane_list = app->m_tool.plane_list_;

		for (auto plane : plane_list)
		{
			PSprite* sprite = &plane.sprite_;

			parse.Push("data", "plane");

			if(sprite->get_is_multitexture())
				parse.Push("type", "MULTI");
			else
			{
				parse.Push("type", "OFFSET");
				parse.Push("xInit", std::to_string(sprite->get_effect_info().x_init));
				parse.Push("yInit", std::to_string(sprite->get_effect_info().y_init));
				parse.Push("xCount", std::to_string(sprite->get_effect_info().x_count));
				parse.Push("yCount", std::to_string(sprite->get_effect_info().x_count));
				parse.Push("xOffset", std::to_string(sprite->get_effect_info().x_offset));
				parse.Push("yOffset", std::to_string(sprite->get_effect_info().y_offset));
				parse.Push("tex_width", std::to_string(sprite->get_effect_info().tex_width));
				parse.Push("tex_height", std::to_string(sprite->get_effect_info().tex_height));
			}
			std::string sname;
			
			sname.assign(plane.name.begin(), plane.name.end());
			parse.Push("name", sname);
			
			if (m_IsAlphaBlend == TRUE)
				parse.Push("blend", "TRUE");
			else
				parse.Push("blend", "FALSE");

			parse.Push("lifetime", std::to_string(sprite->get_lifetime_()));
			parse.Push("each_sprite_playtime", std::to_string(sprite->get_allocatetime_for_onesprite()));
			
			std::string str = std::to_string(plane.matWorld_._11) + "," + std::to_string(plane.matWorld_._12) + "," +
				std::to_string(plane.matWorld_._13) + "," + std::to_string(plane.matWorld_._14);
			parse.Push("MAT1col", str);
			str = std::to_string(plane.matWorld_._21) + "," + std::to_string(plane.matWorld_._22) + "," +
				std::to_string(plane.matWorld_._23) + "," + std::to_string(plane.matWorld_._24);
			parse.Push("MAT2col", str);
			str = std::to_string(plane.matWorld_._31) + "," + std::to_string(plane.matWorld_._32) + "," +
				std::to_string(plane.matWorld_._33) + "," + std::to_string(plane.matWorld_._34);
			parse.Push("MAT3col", str);
			str = std::to_string(plane.matWorld_._41) + "," + std::to_string(plane.matWorld_._42) + "," +
				std::to_string(plane.matWorld_._43) + "," + std::to_string(plane.matWorld_._44);
			parse.Push("MAT4col", str);

			parse.Push("PlaneWidth", std::to_string(plane.width_));
			parse.Push("PlaneHeight", std::to_string(plane.height_));

			int tex_list_size = sprite->get_texture_list_ptr()->size();
			for (int ii = 0 ; ii < tex_list_size; ii++)
			{
				PTexture* tex = sprite->get_texture_list_ptr()->at(ii);
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
		PPlaneObject pp;
		SpriteDataInfo info;
		std::vector<PTexture*> tex_list;
		int frame_count = 0;
		float each_sprite_playtime = 0.0f;
		info.effect_info.is_effect_sprite = true;

		if (iter->second == "plane")
		{
			while (true)
			{
				iter++;
				if (iter->first == "type")
				{
					if (iter->second == "MULTI")
						info.effect_info.is_multi_texture = true;
					else
						info.effect_info.is_multi_texture = false;
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
					pp.matWorld_._11 = std::stof(col1[0]); pp.matWorld_._12 = std::stof(col1[1]);
					pp.matWorld_._13 = std::stof(col1[2]); pp.matWorld_._14 = std::stof(col1[3]);
				}
				else if (iter->first == "MAT2col")
				{
					std::vector<string> col2 = parse.SplitString(iter->second, ',');
					pp.matWorld_._21 = std::stof(col2[0]); pp.matWorld_._22 = std::stof(col2[1]);
					pp.matWorld_._23 = std::stof(col2[2]); pp.matWorld_._24 = std::stof(col2[3]);
				}
				else if (iter->first == "MAT3col")
				{
					std::vector<string> col3 = parse.SplitString(iter->second, ',');
					pp.matWorld_._31 = std::stof(col3[0]); pp.matWorld_._32 = std::stof(col3[1]);
					pp.matWorld_._33 = std::stof(col3[2]); pp.matWorld_._34 = std::stof(col3[3]);
				}
				else if (iter->first == "MAT4col")
				{
					std::vector<string> col4 = parse.SplitString(iter->second, ',');
					pp.matWorld_._41 = std::stof(col4[0]); pp.matWorld_._42 = std::stof(col4[1]);
					pp.matWorld_._43 = std::stof(col4[2]); pp.matWorld_._44 = std::stof(col4[3]);
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
					info.effect_info.x_init = std::stof(iter->second);
				else if (iter->first == "yInit")
					info.effect_info.y_init = std::stof(iter->second);
				else if (iter->first == "xCount")
					info.effect_info.x_count = std::stof(iter->second);
				else if (iter->first == "yCount")
					info.effect_info.y_count = std::stof(iter->second);
				else if (iter->first == "xOffset")
					info.effect_info.x_offset = std::stof(iter->second);
				else if (iter->first == "yOffset")
					info.effect_info.y_offset = std::stof(iter->second);
				else if (iter->first == "tex_width")
					info.effect_info.tex_width = std::stof(iter->second);
				else if (iter->first == "tex_height")
					info.effect_info.tex_height = std::stof(iter->second);
				else if (iter->first == "PlaneWidth")
					pp.width_ = std::stof(iter->second);
				else if (iter->first == "PlaneHeight")
					pp.height_ = std::stof(iter->second);
				else if (iter->first == "END")
				{
					//offset sprite일 경우 프레임 갯수를 다르게 세어야 한다.
					if (info.effect_info.is_multi_texture == false)
					{
						frame_count = info.effect_info.x_count * info.effect_info.y_count;
					}
						info.once_playtime = each_sprite_playtime * frame_count;
						info.max_frame = frame_count;


					std::wstring wstr_name;
					StringToWstring(info.sprite_name, wstr_name);
					
					PSpriteManager::GetInstance().LoadSpriteDataWithoutScript(wstr_name, tex_list, info);
					break;
				}

			}
			std::wstring wstr_spname;
			StringToWstring(info.sprite_name, wstr_spname);
			pp.CreatePlane(app->m_tool.device(), app->m_tool.immediate_device_context(), pp.width_, pp.height_, wstr_spname);
			app->m_tool.plane_list_.push_back(pp);

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

	int index = m_CtlBlendSrc.GetCurSel();
	app->m_tool.blend_desc_.RenderTarget[0].SrcBlend = (D3D11_BLEND)(index + 1);

	index = m_CtlBlendDest.GetCurSel();
	app->m_tool.blend_desc_.RenderTarget[0].DestBlend = (D3D11_BLEND)(index + 1);
	
	HRESULT hr;
	if (FAILED(hr = device->CreateBlendState(
		&app->m_tool.blend_desc_, &app->m_tool.blend_state_)))
	{
		return;
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
