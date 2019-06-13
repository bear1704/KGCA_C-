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
using strkey = std::wstring;

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
	KEYSTAT aKey;
	KEYSTAT sKey;
	KEYSTAT dKey;
	KEYSTAT fKey;
	KEYSTAT qKey;
	KEYSTAT wKey;
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


}pPoint, Vector2, SizeXY;

struct FLOAT_RECT
{
	float left;
	float top;
	float right;
	float bottom;
};

struct PVertex
{
	pPoint my_pos;
	pPoint src_pos;

	PVertex() {}

	PVertex(float my_x, float my_y, float src_x, float src_y)
	{
		my_pos.x = my_x; my_pos.y = my_y;
		src_pos.x = src_x; src_pos.y = src_y;
	}
	PVertex(pPoint my, pPoint src)
	{
		my_pos = my;
		src_pos = src;
	}

};


extern HWND g_hWnd;
extern POINT g_MousePos;
extern float g_fGameTimer;
extern float g_SecondPerFrame;
extern PInputActionMap g_InputActionMap;
extern HDC g_handle_off_screenDC;
extern HDC g_handle_screenDC;
extern HINSTANCE g_hInstance;
extern FLOAT_RECT g_rectangle_client;


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