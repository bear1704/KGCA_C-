#pragma once
// ../../FMOD/inc      fmod.hpp
// ../../FMOD/lib/x64  fmod_vc.lib
// fmod.dll  ���� ���� �� �������� ��ġ

#include "TSound.h"

const int g_iMaxSound = 10;

class TSoundMgr : public TSingleton<TSoundMgr>
{
	friend class TSingleton<TSoundMgr>;
	typedef std::map<int, TSound*>::iterator ITOR;
	// ������ �����̳� < Ű, �� >
	std::map<int, TSound*>   m_List;
public:
	FMOD::System*		m_pSystem;
	float				m_fVolume;
	int					m_iNumSound;
public:
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	int         Load(T_STR pFilePath);
	TSound*		GetPtr(int iKey);
	bool		Delete(int iKey);
	void		Play(int dwKey);
private:
	TSoundMgr();
public:
	~TSoundMgr();
};
#define I_SoundMgr TSoundMgr::GetInstance()
