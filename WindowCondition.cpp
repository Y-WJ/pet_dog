#include"stdafx.h"
#include "WindowCondition.h"

static struct
{
	int ButtonStyle;
	TCHAR *ButtonText;
	int x;
	int y;
	int w;
	int h;
}

ButtonList[]=
{ /*BS_OWNERDRAW*/																//ButtonID
	SS_ETCHEDHORZ,		TEXT(""),		0,	0,	1500,	25,						//	0
	BS_DEFPUSHBUTTON,	TEXT("D"),		1,	1,	20,	22,							//	1
	BS_DEFPUSHBUTTON,	TEXT("P"),		27,	1,	20,	22,							//	2
	BS_DEFPUSHBUTTON,	TEXT("R"),		48,	1,	20,	22,							//	3
	BS_DEFPUSHBUTTON,	TEXT("L"),		69,	1,	20,	22,							//	4
};

#define ButtonNum (sizeof ButtonList/sizeof ButtonList[0])
static HWND ButtonHwnd[ButtonNum];

//----------------------------------------------------------------------------
bool WindowCondition::CreatWindow(HWND hWnd,LPARAM lParam)
{	
	int i;
	WC.Button_Number=ButtonNum;
	ButtonHwnd[0]=CreateWindow(TEXT("button"),
							ButtonList[0].ButtonText,
							WS_CHILD|WS_VISIBLE|ButtonList[0].ButtonStyle,
							ButtonList[0].x,ButtonList[0].y,ButtonList[0].w,ButtonList[0].h,
							hWnd,NULL,((LPCREATESTRUCT)lParam)->hInstance,NULL);
	EnableWindow(ButtonHwnd[0],FALSE);
	WC.Button_Select=0;
	for(i=1;i<ButtonNum;i++)
		ButtonHwnd[i]=CreateWindow(TEXT("button"),
								ButtonList[i].ButtonText,
								WS_CHILD|WS_VISIBLE|ButtonList[i].ButtonStyle,
								ButtonList[i].x,ButtonList[i].y,ButtonList[i].w,ButtonList[i].h,
								/*ButtonHwnd[0]*/hWnd,(HMENU)i,((LPCREATESTRUCT)lParam)->hInstance,NULL);
	return 1;
}

bool WindowCondition::DrawItem(LPARAM lParam)
{
	LPDRAWITEMSTRUCT pdi;
	pdi=(LPDRAWITEMSTRUCT)lParam;
	FillRect(pdi->hDC,&pdi->rcItem,(HBRUSH)GetStockObject(GRAY_BRUSH));
	FrameRect(pdi->hDC,&pdi->rcItem,(HBRUSH)GetStockObject(BLACK_BRUSH));
	return 1;
}

bool WindowCondition::WC_LButtonDown(LPARAM lParam)
{
	WC.StartPoint.x=LOWORD(lParam);
	WC.StartPoint.y=HIWORD(lParam);
	WC.LBUTTONDOWN=TRUE;
	return 1;
}

bool WindowCondition::WC_MouseMove(LPARAM lParam)
{
	WC.PrePoint.x=WC.CurPoint.x;
	WC.PrePoint.y=WC.CurPoint.y;
	WC.CurPoint.x=LOWORD(lParam);
	WC.CurPoint.y=HIWORD(lParam);
	return 1;
}

bool WindowCondition::WC_LButtonUp(LPARAM lParam)
{
	WC.CurPoint.x=LOWORD(lParam);
	WC.CurPoint.y=HIWORD(lParam);
	WC.LBUTTONDOWN=FALSE;
	return 1;
}
