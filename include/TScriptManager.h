#pragma once
#include "TObject.h"
struct TSpriteData
{
	T_STR	m_szPath;
	T_STR	m_szName;
	int		m_iIndex;
	int     m_iBitmapID;
	int     m_iMaskBitmapID;
	std::vector<TObjectInfo>   m_SpliteListData;
};
class TScriptManager : public TSingleton<TScriptManager>
{
	friend class TSingleton<TScriptManager>;
	typedef std::map<int, TSpriteData>::iterator ITOR;
	std::map<int, TSpriteData>   m_list;
	int			m_iIndex;
public:
	int     Load(const TCHAR* pFileName);
	bool	GameDataLoad(T_STR name, TSpriteData& data);
	TSpriteData*  GetPtr(int iKey);
	bool    Init();
	bool    Frame();
	bool    Render();
	bool    Release();
private:
	TScriptManager();
public:
	virtual ~TScriptManager();
};
#define I_ScriptManager TScriptManager::GetInstance()
