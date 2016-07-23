#pragma once

class WindowCondition
{
public:
	bool LBUTTONDOWN;
	bool RBUTTONDOWN;
	POINT StartPoint;
	POINT CurPoint;
	POINT PrePoint;
	int Button_Select;
	int Button_Number;
	bool WC_LButtonDown(LPARAM);
	bool WC_MouseMove(LPARAM);
	bool WC_LButtonUp(LPARAM);
	bool CreatWindow(HWND,LPARAM);
	bool DrawItem(LPARAM);
};
//WindowCondition WC;//全局变量，多个.cpp中要用到，若定义成static只能在第一个include.h的源中引用

extern WindowCondition WC;




