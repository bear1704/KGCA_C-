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
	DDX_Text(pDX, IDC_EDIT1, m_PlaneName);
	DDV_MaxChars(pDX, m_PlaneName, 30);
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
	

}


void PCreatePlaneDlg::OnBtnClickedSelectTexture()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString selFileName;
	CFileDialog dlg(
		TRUE, L"jpg", NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_ALLOWMULTISELECT,
		L"img Files(*.png)|*.jpg|*.jpeg|*.bmp|*.dds|All Files(*.*)|*.*|", this
	);
	CString file_path;
	char str_file[4096];
	dlg.m_ofn.lpstrFile = file_path.GetBuffer(4096);
	dlg.m_ofn.nMaxFile = sizeof(str_file);



	if (dlg.DoModal() == IDOK)
	{
		UpdateData(TRUE);
		std::vector<PTexture*> tex_list;
		for (POSITION ii = dlg.GetStartPosition(); ii != NULL;)
		{
			CString path = dlg.GetNextPathName(ii);
			TextureInfo info;
			info.tex_path = path;
			PTexture* tex = PTextureManager::GetInstance().LoadTextureWithoutScript(info, app->m_tool.device());
			tex_list.push_back(tex);
		}
 		SpriteDataInfo sp_info;
		sp_info.lifetime = m_LifeTime;
		sp_info.max_frame = tex_list.size();
		sp_info.once_playtime = m_FrameInterval;
		sp_info.posX = 100.0f;
		sp_info.posY = 100.0f;
		sp_info.texture_list = tex_list;
		std::wstring plane_and_sprite_name = m_PlaneName;
		sp_info.texture_name = plane_and_sprite_name;
		PSpriteManager::GetInstance().LoadSpriteDataWithoutScript(plane_and_sprite_name, tex_list, sp_info);
		app->m_tool.plane_.CreatePlane(app->m_tool.device(), app->m_tool.immediate_device_context(), 100.0f, 100.0f, plane_and_sprite_name);

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


