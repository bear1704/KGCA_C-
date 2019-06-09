#pragma once
#include "TBitmap.h"
#include "TCollision.h"

struct TObjectInfo
{
	tPoint InitPos;
	int   iNumFrame;
	float fTime;
	float fLifeTime;
	int   iBitmapID;
	int   iMaskID;
	bool  bLoop;
	RECT   rtClient;
	float  fSpeed;
	std::vector<RECT> rtList;
	TObjectInfo() {
		iBitmapID = -1;
		iMaskID = -1;
		bLoop = false;
	}
	TObjectInfo(tPoint p, RECT r, float f)
	{
		InitPos = p;
		rtClient = r;
		fSpeed = f;
		iBitmapID = -1;
		iMaskID = -1;
		bLoop = false;
	}
};

class TObject
{
protected:
	TBitmap*   m_pBitmap;
	TBitmap*   m_pBitmapMask;
	tPoint    m_Pos;
	float    m_fSpeed;	
	RECT     m_rtDraw;
	float    m_fAlpha;
public:	
	RECT     GetDrawRect() { return m_rtDraw; }
	tPoint   GetPos() { return m_Pos; }
	RECT     m_rtObj;
	RECT     m_rtColl;
	TSphere  m_Sphere;
	TBitmap* GetBitmap() { return m_pBitmap; }
	void     SetPos(POINT pos);
	void     SetPos(tPoint pos);
	void     SetPos(float x, float y);
	void	 Move(tPoint pos);
public:
	virtual bool	Init();
	virtual void	SetDrawRect(tPoint p, RECT rt);
	virtual void	SetColliRect(tPoint p, RECT rt);
	virtual void	Set(tPoint pos, RECT rt, float fSpeed = 100.0f);
	virtual void	Set(TObjectInfo info);
	virtual bool    Load(std::wstring filename);
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();
public:
	TObject();
	virtual ~TObject();
};

