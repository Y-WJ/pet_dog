#include "stdafx.h"
#include "Select_Pan.h"
#include "WindowCondition.h"

//---------------------------------------------------------------------
static void USE_POINT_RECT(HWND hWnd)
{
	HDC hdc;
	hdc=GetDC(hWnd);
	SelectObject(hdc,GetStockObject(WHITE_PEN));
	MoveToEx(hdc,WC.StartPoint.x,WC.StartPoint.y,NULL);
	LineTo(hdc,WC.StartPoint.x,WC.PrePoint.y);
	LineTo(hdc,WC.PrePoint.x,WC.PrePoint.y);
	LineTo(hdc,WC.PrePoint.x,WC.StartPoint.y);
	LineTo(hdc,WC.StartPoint.x,WC.StartPoint.y);
	SelectObject(hdc,GetStockObject(BLACK_PEN));
	LineTo(hdc,WC.StartPoint.x,WC.CurPoint.y);
	LineTo(hdc,WC.CurPoint.x,WC.CurPoint.y);
	LineTo(hdc,WC.CurPoint.x,WC.StartPoint.y);
	LineTo(hdc,WC.StartPoint.x,WC.StartPoint.y);
	ReleaseDC(hWnd,hdc);
	InvalidateRect(hWnd,NULL,0);
}

//PAN-------------------------------------------------------------------
bool Select_Pan::LButtonDown()
{
	if(WC.Button_Select==2)
	{
		pPoint=&(pLine->StartPoint);
		pPoint->coordinate=WC.CurPoint;
		pPoint->next=NULL;
		pLine->next=NULL;
	}
	return 1;
}
bool Select_Pan::MouseMove(HWND hWnd)
{
	if(WC.LBUTTONDOWN&&WC.Button_Select==2)
	{
		pPoint->next=(LINE*)malloc(sizeof(LINE));
		pPoint=pPoint->next;
		pPoint->coordinate=WC.CurPoint;
		pPoint->next=NULL;
		InvalidateRect(hWnd,NULL,0);
	}
	return 1;
}

bool Select_Pan::LButtonUp()
{
	if(WC.Button_Select==2)
	{
		pLine->next=(LINELIST*)malloc(sizeof(LINELIST));
		pLine=pLine->next;
		pLine->next=NULL;
		pLine->StartPoint.next=NULL;
	}
	return 1;
}
/*
bool Select_Pan::Paint(HDC hdc)
{
	LINELIST *pPaint;
	pPaint=&Line;	
	while(pPaint!=NULL)
	{
		pPoint=&(pPaint->StartPoint);
		MoveToEx(hdc,pPoint->next->coordinate.x,pPoint->next->coordinate.y,NULL);
		while(pPoint->next!=NULL)
		{
			pPoint=pPoint->next;
			LineTo(hdc,pPoint->coordinate.x,pPoint->coordinate.y);
			MoveToEx(hdc,pPoint->coordinate.x,pPoint->coordinate.y,NULL);
		}
		pPaint=pPaint->next;
	}
	return 1;
}
*/
bool Select_Pan::Paint(HDC hdc)
{
	LINELIST *pPaint;
	pPaint=&Line;	
	while(pPaint!=NULL)
	{
		pPoint=&(pPaint->StartPoint);
		MoveToEx(hdc,pPoint->coordinate.x,pPoint->coordinate.y,NULL);
		while(pPoint->next!=NULL)
		{
			pPoint=pPoint->next;
			LineTo(hdc,pPoint->coordinate.x,pPoint->coordinate.y);
			MoveToEx(hdc,pPoint->coordinate.x,pPoint->coordinate.y,NULL);
		}
		pPaint=pPaint->next;
	}
	return 1;
}
//
bool Select_Pan::CommondErase()
{
//	LINELIST *preLine;
	LINELIST *curLine;
	LINE *prePoint;
	LINE *curPoint;
	curLine=&Line;
	curPoint=&(curLine->StartPoint);
	while(curLine!=NULL)
	{
		curPoint=&(curLine->StartPoint);
		while(curPoint!=NULL)
		{
			prePoint=curPoint;
			curPoint=curPoint->next;
			free(prePoint);
		}
//		preLine=curLine;
		curLine=curLine->next;
//		free(preLine);
	}
//	curLine=Line.next;
	Line.next=NULL;
	Line.StartPoint.next=NULL;
	pLine=&Line;
	return 1;
}
//
//RECT---------------------------------------------------------------------
bool Select_Rect::LButtonDown()
{
	if(WC.Button_Select==3)
	{
		pRect->next=(Select_Rect*)malloc(sizeof Select_Rect);
		pRect=pRect->next;
		pRect->xPoint=WC.StartPoint;
	}
	return 1;
}

bool Select_Rect::MouseMove(HWND hWnd)
{
	if(WC.Button_Select==3&&WC.LBUTTONDOWN)
	{
		pRect->yPoint=WC.CurPoint;
		USE_POINT_RECT(hWnd);
	}
	return 1;
}

bool Select_Rect::LButtonUp()
{
	if(WC.Button_Select==3)
	{
		pRect->yPoint=WC.CurPoint;
	}
	return 1;
}

bool Select_Rect::Paint(HDC hdc)
{
	Select_Rect *pPaint;
	pPaint=Rect.next;
	SelectObject(hdc,GetStockObject(BLACK_PEN));
	while(pPaint!=NULL)
	{
		MoveToEx(hdc,pPaint->xPoint.x,pPaint->xPoint.y,NULL);
		LineTo(hdc,pPaint->xPoint.x,pPaint->yPoint.y);
		LineTo(hdc,pPaint->yPoint.x,pPaint->yPoint.y);
		LineTo(hdc,pPaint->yPoint.x,pPaint->xPoint.y);
		LineTo(hdc,pPaint->xPoint.x,pPaint->xPoint.y);
		pPaint=pPaint->next;
	}
	return 1;
}

bool Select_Rect::CommondErase()
{
	Select_Rect *pPaint;
	Select_Rect *prePaint;
	pPaint=Rect.next;
	while(pPaint!=NULL)
	{
		prePaint=pPaint;
		pPaint=pPaint->next;
		free(prePaint);
	}
//	Rect.next=NULL;
	pRect=&Rect;
	return 1;
}

