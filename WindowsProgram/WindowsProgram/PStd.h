#pragma once
#include <Windows.h>

#define PCORE_RUN(title,x,y,w,h) \
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)\
{\
 Sample sample;\
 sample.InitWindow(hInstance, title,x, y, w, h);\
 sample.Run();\
}