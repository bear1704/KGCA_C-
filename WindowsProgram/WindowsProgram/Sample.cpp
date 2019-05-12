#include "Sample.h"


Sample::Sample()
{
	
}


Sample::~Sample()
{
}

bool Sample::Init()
{
	PSoundMgr::GetInstance().Load("../../a.wav");
	PSoundMgr::GetInstance().Load("../../a.wav");
	PSoundMgr::GetInstance().Load("../../a.wav");
	return true;
}

bool Sample::Frame()
{
	
	PSound* pSound = PSoundMgr::GetInstance().GetPtr(0);
	PSound* pSoundEffect1 = PSoundMgr::GetInstance().GetPtr(1);
	PSound* pSoundEffect2 = PSoundMgr::GetInstance().GetPtr(2);
	if (g_InputActionMap.wKey == KEYSTAT::KEY_PUSH)
	{
		//I_SoundMgr.Play(0);		
		pSound->Play();
	}
	if (g_InputActionMap.sKey == KEYSTAT::KEY_PUSH)
	{
		pSound->Stop();
	}
	if (g_InputActionMap.aKey == KEYSTAT::KEY_PUSH)
	{
		pSound->Paused();
	}

	if (g_InputActionMap.leftClick > KEYSTAT::KEY_FREE)
	{
		pSound->Volume(0.1f, true);
	}
	if (g_InputActionMap.rightClick > KEYSTAT::KEY_FREE)
	{
		pSound->Volume(0.1f, false);
	}

	if (g_InputActionMap.dKey == KEYSTAT::KEY_PUSH)
	{
		pSoundEffect1->PlayEffect();
	}
	if (g_InputActionMap.middleClick == KEYSTAT::KEY_PUSH)
	{
		pSoundEffect2->PlayEffect();
	}
	return true;

}

PCORE_RUN(L"Sampleaaaaaaa",100, 100, 1024, 768);