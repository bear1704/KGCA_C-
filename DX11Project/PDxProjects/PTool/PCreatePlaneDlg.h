﻿#pragma once
#include "PTool.h"

// PCreatePlaneDlg 대화 상자

class PCreatePlaneDlg : public CDialogEx
{
	DECLARE_DYNAMIC(PCreatePlaneDlg)
public:
	CPToolApp* app;

public:
	PCreatePlaneDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~PCreatePlaneDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CreatePlane };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBtnClickedSelectTexture();
	afx_msg void OnBtnClickedSelectScript();
	afx_msg void OnBnClickedCancel();
	float m_PlaneHeight;
	float m_FrameInterval;
	float m_LifeTime;
	float m_SpriteXInit;
	float m_SpriteYInit;
	float m_XOffset;
	float m_YOffset;
	float m_PlaneWidth;
	CString m_PlaneName;
};
