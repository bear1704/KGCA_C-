#include "PWindow.h"

PWindow* myWindow = nullptr;
HWND g_hWnd;
HINSTANCE g_hInstance;
RECT g_rectangle_client;
//FLOAT_RECT g_world_rect;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	if (myWindow != nullptr)
	{
		myWindow->MsgProc(hWnd, msg, wParam, lParam);
	}

	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


LRESULT PWindow::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) { return 1; }


bool PWindow::InitWindow(HINSTANCE hInstance, LPCWSTR titleName, int X, int Y, int width, int height)
{

	this->hInstance = hInstance;
	g_hInstance = hInstance;

	if (!MyRegisterClass())
		return false;

	hWnd = CreateWindow(className, titleName, WS_OVERLAPPEDWINDOW, 
		X, Y, width, height, NULL, NULL, this->hInstance, NULL);

	if (hWnd == NULL) return 0;

	ShowWindow(hWnd, SW_SHOW);
	CenterWindow();
	GetClientRect(hWnd, &rectangle_client);
	g_rectangle_client = rectangle_client;


	return true;
}

bool PWindow::MyRegisterClass()
{
	WNDCLASSEXW wcex;
	wcex.lpfnWndProc = WndProc;
	wcex.lpszClassName = className;
	wcex.hInstance = hInstance;
	
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wcex.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(nullptr, IDC_WAIT);
	
	wcex.lpszMenuName = NULL;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;

	if (!RegisterClassExW(&wcex))
		return false;
	
	return true;

	return RegisterClassEx(&wcex);
	
}

void PWindow::CenterWindow()
{
	RECT rtWindow;
	GetWindowRect(hWnd, &rtWindow);

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	int x = (screenWidth - (rtWindow.right - rtWindow.left)) / 2;
	int y = (screenHeight - (rtWindow.bottom - rtWindow.top)) / 2;
	MoveWindow(hWnd, x, y, rtWindow.right - rtWindow.left, rtWindow.bottom - rtWindow.top, true);
}






PWindow::PWindow(LPCWSTR className)
{
	this->className = className;
}

PWindow::PWindow()
{
	this->className = L"KGCA";
	myWindow = this;
}



PWindow::~PWindow()
{
}


