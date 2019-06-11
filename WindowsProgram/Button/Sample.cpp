#include "Sample.h"



Sample::Sample()
{
}


Sample::~Sample()
{
}

bool Sample::Init()
{
	PButtonControl* button2 = new PButtonControl();
	button2->Set(L"D:/SC/C_C++/Git/WindowsProgram/Button/data/UI/UI_data.txt", L"optionbutton", pPoint(500, 500));
	PUIComponent* button = (PButtonControl*) button2->Clone();

	button1 = (PButtonControl*) button;


	return true;
}
bool Sample::Frame()
{
	return true;
}

bool Sample::Render()
{
	button1->Draw();
	draw_test_rect(button1->get_collision_rect_());
	return true;
}

bool Sample::Release()
{
	return true;
}

void Sample::draw_test_rect(FLOAT_RECT rect)
{

	SetROP2(g_handle_off_screenDC, R2_NOTXORPEN);
	FLOAT_RECT arect = P2DCamera::GetInstance().WorldToGamescreenRECT(rect);
	int prevMode2 = Rectangle(g_handle_off_screenDC, arect.left, arect.top,
		arect.left + arect.right, arect.top + arect.bottom);
	SetROP2(handle_off_screenDC, prevMode2);
}