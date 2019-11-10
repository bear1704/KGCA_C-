#pragma once
#include "PCreatePlaneDlg.h"


// PToolForm 폼 보기

class PToolForm : public CFormView
{
	DECLARE_DYNCREATE(PToolForm)

protected:
	PToolForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~PToolForm();

public:
	static PToolForm* CreateOne(CWnd* pParent);
	CPToolApp* app;

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EffToolForm };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	PCreatePlaneDlg m_DlgPlane;
	CButton m_BtnCreatePlane;

	afx_msg void OnBnClickedBtnCreateplane();
	CComboBox m_CtlBlendSrc;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnInitialUpdate();
	afx_msg void OnCbnSelchangeComboBlendSrc();
	BOOL m_IsAlphaBlend;
	afx_msg void OnCbnSelchangeComboBlendDest();
	CComboBox m_CtlBlendDest;
};


