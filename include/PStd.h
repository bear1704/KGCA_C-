#pragma once
#include <Windows.h>
#include <tchar.h>
#include <string>
#include <map>
#include <vector>

using namespace std;

#pragma comment(lib, "PCoreLib.lib")
#pragma comment(lib, "msimg32")

#define PCORE_RUN(title,x,y,w,h) \
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)\
{\
 Sample sample;\
 sample.InitWindow(hInstance, title,x, y, w, h);\
 sample.Run();\
}

typedef std::wstring unicode_string;
typedef std::basic_string<TCHAR> multibyte_string;

static std::wstring multibyte_to_unicode_str(std::string str)
{
	std::wstring ret = std::wstring(str.begin(), str.end());
	return ret;
}
static std::string unicode_to_multibyte_str(std::wstring str)
{
	std::string ret = std::string(str.begin(), str.end());
	return ret;
}

enum class KEYSTAT
{
	KEY_FREE,
	KEY_PUSH,
	KEY_HOLD,
	KEY_UP
};

enum class PLoadMode
{
	BITMAP,
	BITMAPMASK,
};

enum class PXY
{
	X,
	Y,

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
	KEYSTAT leftArrowKey;
	KEYSTAT rightArrowKey;
	KEYSTAT upArrowKey;
	KEYSTAT downArrowKey;
	


};




typedef struct pPoint_
{

	float x;
	float y;
	pPoint_() {};
	pPoint_(float fx, float fy) { x = fx; y = fy; }

}pPoint;


extern HWND g_hWnd;
extern POINT g_MousePos;
extern float g_fGameTimer;
extern float g_SecondPerFrame;
extern PInputActionMap g_InputActionMap;
extern HDC g_handle_off_screenDC;
extern HDC g_handle_screenDC;
extern HINSTANCE g_hInstance;


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