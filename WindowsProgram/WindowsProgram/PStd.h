#pragma once
#include <Windows.h>
#include <tchar.h>

#define PCORE_RUN(title,x,y,w,h) \
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)\
{\
 Sample sample;\
 sample.InitWindow(hInstance, title,x, y, w, h);\
 sample.Run();\
}



enum class KEYSTAT
{
	KEY_FREE,
	KEY_PUSH,
	KEY_HOLD,
	KEY_UP
};

struct PInputActionMap
{
	KEYSTAT wKey;
	KEYSTAT sKey;
	KEYSTAT aKey;
	KEYSTAT dKey;
	KEYSTAT leftClick;
	KEYSTAT rightClick;
	KEYSTAT middleClick;
	KEYSTAT exitKey;
	KEYSTAT jumpKey;

};


extern HWND g_hWnd;
extern POINT g_MousePos;
extern float g_fGameTimer;
extern float g_SecondPerFrame;
extern PInputActionMap g_InputActionMap;

template <typename T>
class PSingleton
{
public:
	static T& GetInstance()
	{
		static T singleton;
		return singleton;
	}
public:
	virtual bool Init() = 0;
	virtual bool Frame() = 0;
	virtual bool Render() = 0;
	virtual bool Release() = 0;

};