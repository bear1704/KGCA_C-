#include "PWindow.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}


bool PWindow::InitWindow(HINSTANCE hInstance, LPCWSTR titleName, int X, int Y, int width, int height)
{

	this->hInstance = hInstance;

	if (!MyRegisterClass())
		return false;

	hWnd = CreateWindow(className, titleName, WS_OVERLAPPEDWINDOW, 
		X, Y, width, height, NULL, NULL, this->hInstance, NULL);

	if (hWnd == NULL) return 0;

	ShowWindow(hWnd, SW_SHOW);
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




PWindow::PWindow(LPCWSTR className)
{
	this->className = className;
}

PWindow::PWindow()
{
	this->className = L"KGCA";
}



PWindow::~PWindow()
{
}


