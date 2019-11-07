// PToolForm.cpp: 구현 파일
//

#include "pch.h"
#include "PTool.h"
#include "PToolForm.h"


// PToolForm

IMPLEMENT_DYNCREATE(PToolForm, CFormView)

PToolForm::PToolForm()
	: CFormView(IDD_EffToolForm)
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
}

BEGIN_MESSAGE_MAP(PToolForm, CFormView)
	ON_BN_CLICKED(IDC_BTN_CREATEPLANE, &PToolForm::OnBnClickedBtnCreateplane)
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
