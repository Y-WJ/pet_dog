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
//WindowCondition WC;//ȫ�ֱ��������.cpp��Ҫ�õ����������staticֻ���ڵ�һ��include.h��Դ������

extern WindowCondition WC;




