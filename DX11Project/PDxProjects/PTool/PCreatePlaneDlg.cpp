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
{

}

PCreatePlaneDlg::~PCreatePlaneDlg()
{
}

void PCreatePlaneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PCreatePlaneDlg, CDialogEx)
END_MESSAGE_MAP()


// PCreatePlaneDlg 메시지 처리기
