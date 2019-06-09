#pragma once
#include "TBitmap.h"
class TBitmapManager : public TSingleton<TBitmapManager>
{
	friend class TSingleton<TBitmapManager>;
	typedef std::map<int, TBitmap*>::iterator ITOR;
	// 사전식 컨테이너 < 키, 값 >
	std::map<int, TBitmap*>   m_List;
	int			m_iNumSound;
public:
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	int         Load(T_STR pFilePath);
	TBitmap*	GetPtr(int iKey);
	bool		Delete(int iKey);
private:
	TBitmapManager();
public:
	~TBitmapManager();
};
#define I_BitmapMgr TBitmapManager::GetInstance()

