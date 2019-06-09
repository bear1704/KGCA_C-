#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <tchar.h>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <assert.h>
#include <memory>

using namespace std;

#pragma comment( lib, "TCoreLib.lib")
#pragma comment( lib, "msimg32")

#define TCORE_START int APIENTRY wWinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPWSTR    lpCmdLine,_In_ int       nCmdShow){
#define TCORE_MAIN(s,x,y,w,h) {Sample  sample;sample.InitWindow(hInstance,L#s,x,y,w,h);sample.Run();}
#define TCORE_END }

#define TCORE_RUN(s,x,y,w,h) TCORE_START; TCORE_MAIN(s,x,y,w,h); TCORE_END;


typedef std::basic_string<TCHAR> T_STR;
typedef std::basic_string<char>  C_STR; // std::string
typedef std::basic_string<WCHAR> W_STR; // std::wstring
//using T_STR = std::basic_string<TCHAR>;

static std::wstring mtw(std::string str)
{
	std::wstring ret = std::wstring( str.begin(), str.end());
	return ret;
}
static std::string wtm(std::wstring str)
{
	std::string ret = std::string(str.begin(), str.end());
	return ret;
}
static char*  GetWtM(WCHAR* src)
{
	char retData[1024] = { 0, };
	int iLength = WideCharToMultiByte(CP_ACP, 0, 
		src, -1, 0, 0, NULL, NULL);

	int iRet = WideCharToMultiByte(CP_ACP, 0,
		src, -1, retData, iLength, NULL, NULL);
	if (iRet == 0) return nullptr;
	return retData;
}
static bool  GetWtM(WCHAR* src, char* pDest)
{
	int iLength = WideCharToMultiByte(CP_ACP, 0,
		src, -1, 0, 0, NULL, NULL);

	int iRet = WideCharToMultiByte(CP_ACP, 0,
		src, -1, pDest, iLength, NULL, NULL);
	if (iRet == 0) return false;
	return true;
}
static WCHAR*  GetMtW(CHAR* src)
{
	WCHAR retData[1024] = { 0, };
	int iLength = MultiByteToWideChar(CP_ACP, 0,src, -1, 0, 0);

	int iRet = MultiByteToWideChar(CP_ACP, 0,
		src, -1, retData, iLength);
	if (iRet == 0) return nullptr;
	return retData;
}
static bool  GetMtW(CHAR* src, WCHAR* pDest)
{
	int iLength = MultiByteToWideChar(CP_ACP, 0,
		src, -1, 0, 0);
	int iRet = MultiByteToWideChar(CP_ACP, 0,
		src, -1, pDest, iLength);
	if (iRet == 0) return false;
	return true;
}
struct TInputActionMap
{
	DWORD   bWKey;
	DWORD   bSKey;
	DWORD   bAKey;
	DWORD   bDKey;
	DWORD   bLeftClick;
	DWORD   bRightClick;
	DWORD   bMiddleClick;
	DWORD   bExit;
	DWORD   bSpace; // left mouse, A key
};
enum { KEY_FREE, KEY_PUSH, KEY_HOLD, KEY_UP };
extern TInputActionMap  g_ActionInput;
extern HWND  g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_MousePos;
extern float g_fGameTimer;
extern float g_fSecPerFrame;
extern HDC	 g_hOffScreenDC;
extern HDC   g_hScreenDC;
extern RECT  g_rtClient;
template <class T> 
class TSingleton
{
public:
	static T& GetInstance()
	{
		static T singleton;
		return singleton;
	}
};

struct tPoint
{
	float  x;
	float  y;
	tPoint() {};
	tPoint(float fx, float fy) { x = fx; y = fy; }
} ;
struct TRect
{
	float    left;
	float    top;
	float    right;
	float    bottom;
	TRect() {};
	TRect(float a, float b, float c, float d) { 
		left = a;
		top = b;
		right =c;
		bottom =d;
	}
};
struct TSphere
{
	tPoint vCenter;
	float  fRadius;
};
struct TVertex
{
	tPoint   p; // client pos
	tPoint   t; // bitmap pos
	TVertex() {}
	TVertex(tPoint a, tPoint b)
	{
		p = a;
		t = b;
	}
	TVertex(float px, float py, float tx, float ty)
	{
		p.x = px; p.y = py;
		t.x = tx; t.y = ty;
	}
};