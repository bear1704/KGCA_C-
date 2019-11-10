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

		
		CFileException e;
		if (!fp.Open(path_name, CFile::modeWrite | CFile::modeCreate, &e))
		{
			e.ReportError();
			return;
		}

		/*CString str = _T("dsfsadf");
		CArchive ar(&fp, CArchive::store);
		ar << str;*/
		SaveData();


	}

	fp.Close();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void PToolForm::OnBnClickedBtnLoad()
{


	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void PToolForm::SaveData()
{
	parse.ClearOutVec();

	CString str = _T("qqqq");
	CArchive ar(&fp, CArchive::store);
	ar << str;



	//멀티텍스쳐
	if (m_DlgPlane.m_IsMultiTexture == TRUE)
	{
		std::vector<PSprite*> sprite_list = PSpriteManager::GetInstance().GetSpriteListFromMap();
		std::vector<PPlaneObject> plane_list = app->m_tool.plane_list_;
		int plane_count = 0;

		for (auto sprite : sprite_list)
		{
			if (sprite->get_is_effect() == false)
				continue;

			parse.Push("type", "MULTI");
			//parse.Push("name", std::string(CT2CA(m_DlgPlane.m_PlaneName)));
			//parse.Push("name", sprite.get));
			if (m_IsAlphaBlend == TRUE)
				parse.Push("blend", "TRUE");
			else
				parse.Push("blend", "FALSE");

			parse.Push("lifetime", std::to_string(sprite->get_lifetime_()));
			parse.Push("each_sprite_playtime", std::to_string(sprite->get_allocatetime_for_onesprite()));
			
			std::string str = std::to_string(plane_list[plane_count].matWorld_._11) + " " + std::to_string(plane_list[plane_count].matWorld_._12) + " " +
				std::to_string(plane_list[plane_count].matWorld_._13) + " " + std::to_string(plane_list[plane_count].matWorld_._14);
			parse.Push("MAT1col", str);
			str = std::to_string(plane_list[plane_count].matWorld_._21) + " " + std::to_string(plane_list[plane_count].matWorld_._22) + " " +
				std::to_string(plane_list[plane_count].matWorld_._23) + " " + std::to_string(plane_list[plane_count].matWorld_._24);
			parse.Push("MAT2col", str);
			str = std::to_string(plane_list[plane_count].matWorld_._31) + " " + std::to_string(plane_list[plane_count].matWorld_._32) + " " +
				std::to_string(plane_list[plane_count].matWorld_._33) + " " + std::to_string(plane_list[plane_count].matWorld_._34);
			parse.Push("MAT3col", str);
			str = std::to_string(plane_list[plane_count].matWorld_._41) + " " + std::to_string(plane_list[plane_count].matWorld_._42) + " " +
				std::to_string(plane_list[plane_count].matWorld_._43) + " " + std::to_string(plane_list[plane_count].matWorld_._44);
			parse.Push("MAT4col", str);

			int tex_list_size = sprite->get_texture_list_ptr()->size();
			for (int ii = 0 ; ii < tex_list_size; ii++)
			{
				PTexture* tex = sprite->get_texture_list_ptr()->at(ii);
				std::wstring wstr = tex->tex_path();
				str.clear();
				str.assign(wstr.begin(), wstr.end());
				parse.Push("tex_path", str);
			}
			plane_count++;
			
			parse.Commit();
		}


	}
	


}
