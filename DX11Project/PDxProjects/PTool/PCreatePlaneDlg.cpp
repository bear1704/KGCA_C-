// PCreatePlaneDlg.cpp: 구현 파일
//

#include "pch.h"
#include "PTool.h"
#include "PCreatePlaneDlg.h"
#include "afxdialogex.h"


// PCreatePlaneDlg 대화 상자

IMPLEMENT_DYNAMIC(PCreatePlaneDlg, CDialogEx)

PCreatePlaneDlg::PCreatePlaneDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CreatePlane, pParent)
	, m_PlaneHeight(0)
	, m_FrameInterval(0)
	, m_LifeTime(0)
	, m_SpriteXInit(0)
	, m_SpriteYInit(0)
	, m_XOffset(0)
	, m_YOffset(0)
	, m_PlaneWidth(0)
	, m_PlaneName(_T(""))
	, m_CurrentPlaneIsLoop(false)
	, m_XCount(0)
	, m_YCount(0)
	, m_TextureWidth(0)
	, m_TextureHeight(0)
{
	app = (CPToolApp*)AfxGetApp();
}

PCreatePlaneDlg::~PCreatePlaneDlg()
{
}

void PCreatePlaneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_PlaneHeight);
	DDV_MinMaxFloat(pDX, m_PlaneHeight, 0.01, FLT_MAX);
	DDX_Text(pDX, IDC_EDIT_FrameInterval, m_FrameInterval);
	DDV_MinMaxFloat(pDX, m_FrameInterval, 0.01, FLT_MAX);
	DDX_Text(pDX, IDC_EDIT_LifeTime, m_LifeTime);
	DDX_Text(pDX, IDC_EDIT_XInit, m_SpriteXInit);
	DDX_Text(pDX, IDC_EDIT_YInit, m_SpriteYInit);
	DDX_Text(pDX, IDC_EDIT_XOffset, m_XOffset);
	DDX_Text(pDX, IDC_EDIT_YOffset, m_YOffset);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_PlaneWidth);
	DDX_Text(pDX, IDC_EDIT_PlaneName, m_PlaneName);
	DDV_MaxChars(pDX, m_PlaneName, 30);
	DDX_Check(pDX, IDC_CHECK_IsLoop, m_CurrentPlaneIsLoop);
	DDX_Text(pDX, IDC_EDIT1_XCount, m_XCount);
	DDX_Text(pDX, IDC_EDIT_YCount, m_YCount);
	DDX_Text(pDX, IDC_EDIT_TextureWidth, m_TextureWidth);
	DDX_Text(pDX, IDC_EDIT_TextureHeight, m_TextureHeight);
}


BEGIN_MESSAGE_MAP(PCreatePlaneDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &PCreatePlaneDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_Btn_SelectTexture, &PCreatePlaneDlg::OnBtnClickedSelectTexture)
	ON_BN_CLICKED(IDC_Btn_SelectScript, &PCreatePlaneDlg::OnBtnClickedSelectScript)
	ON_BN_CLICKED(IDCANCEL, &PCreatePlaneDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// PCreatePlaneDlg 메시지 처리기



void PCreatePlaneDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
	UpdateData(TRUE);
	std::wstring plane_and_sprite_name = m_PlaneName;


	// > 1  이면 다중텍스쳐 스프라이트
	if (tex_list.size() > 1)
	{
		SpriteDataInfo sp_info;
		sp_info.max_frame = tex_list.size();
		sp_info.once_playtime = m_FrameInterval * tex_list.size();
		sp_info.posX = 100.0f;
		sp_info.posY = 100.0f;
		sp_info.texture_list = tex_list;
		std::wstring plane_and_sprite_name = m_PlaneName;
		sp_info.texture_name = plane_and_sprite_name;

		if (m_CurrentPlaneIsLoop == TRUE)
			sp_info.lifetime = kLoopLifetime;
		else
			sp_info.lifetime = m_LifeTime;

		PSpriteManager::GetInstance().LoadSpriteDataWithoutScript(plane_and_sprite_name, tex_list, sp_info);
		PPlaneObject pp;
		pp.CreatePlane(app->m_tool.device(), app->m_tool.immediate_device_context(), m_PlaneWidth, m_PlaneHeight, plane_and_sprite_name);
		app->m_tool.plane_list_.push_back(pp);

		tex_list.clear();
	}
	else
	{
		SpriteDataInfo sp_info;
		sp_info.max_frame = m_XCount * m_YCount;
		sp_info.once_playtime = m_FrameInterval * sp_info.max_frame;
		sp_info.posX = 100.0f;
		sp_info.posY = 100.0f;
		std::wstring plane_and_sprite_name = m_PlaneName;
		sp_info.texture_name = tex_list[0]->tex_name();

		if (m_CurrentPlaneIsLoop == TRUE)
			sp_info.lifetime = kLoopLifetime;
		else
			sp_info.lifetime = m_LifeTime;


		float xOrigin = m_SpriteXInit;
		float yOrigin = m_SpriteYInit;

		for (int ii = 0; ii < m_YCount; ii++)
		{
			for (int jj = 0; jj < m_XCount; jj++)
			{
				float current_xOrigin = xOrigin + m_XOffset * jj;
				float current_yOrigin = yOrigin + m_YOffset * ii;

				DX::PTex_uv4 uv;
				uv.u[0] = current_xOrigin / m_TextureWidth;
				uv.u[1] = (current_xOrigin + m_XOffset) / m_TextureWidth;
				uv.u[2] = (current_xOrigin + m_XOffset) / m_TextureWidth;
				uv.u[3] = current_xOrigin / m_TextureWidth;
				uv.v[0] = current_yOrigin / m_TextureHeight;
				uv.v[1] = current_yOrigin / m_TextureHeight;
				uv.v[2] = (current_yOrigin + m_YOffset) / m_TextureHeight;
				uv.v[3] = (current_yOrigin + m_YOffset) / m_TextureHeight;

				sp_info.tex_boundary_list.push_back(uv);
			}
		}
		

		PSpriteManager::GetInstance().LoadSpriteDataWithoutScript(plane_and_sprite_name, tex_list, sp_info);

		PPlaneObject pp;
		pp.CreatePlane(app->m_tool.device(), app->m_tool.immediate_device_context(), m_PlaneWidth, m_PlaneHeight, plane_and_sprite_name);
		app->m_tool.plane_list_.push_back(pp);

	}
}


void PCreatePlaneDlg::OnBtnClickedSelectTexture()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString selFileName;
	CFileDialog dlg(
		TRUE, L"bmp", NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_ALLOWMULTISELECT,
		L"img Files(*.이믜지)|*.png;*.dds;*.bmp;*.jpg;*.jpeg|All Files(*.*)|*.*||", this
	);
	CString file_path;
	char str_file[4096];
	dlg.m_ofn.lpstrFile = file_path.GetBuffer(4096);
	dlg.m_ofn.nMaxFile = sizeof(str_file);



	if (dlg.DoModal() == IDOK)
	{
		UpdateData(TRUE);
		
		for (POSITION ii = dlg.GetStartPosition(); ii != NULL;)
		{
			CString path = dlg.GetNextPathName(ii);
			TextureInfo info;
			info.tex_path = path;
			PTexture* tex = PTextureManager::GetInstance().LoadTextureWithoutScript(info, app->m_tool.device());
			if (tex == nullptr)
			{
				TCHAR Drive[MAX_PATH] = { 0, };
				TCHAR Dir[MAX_PATH] = { 0, };
				TCHAR Name[MAX_PATH] = { 0, };
				TCHAR Ext[MAX_PATH] = { 0, };

				_tsplitpath_s(info.tex_path.c_str(), Drive, Dir, Name, Ext);
				tex = PTextureManager::GetInstance().GetTextureFromMap(Name);
			}

			tex_list.push_back(tex);
		}
 		
		

	}


}


void PCreatePlaneDlg::OnBtnClickedSelectScript()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void PCreatePlaneDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


