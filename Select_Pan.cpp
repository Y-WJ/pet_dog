#include "stdafx.h"
#include "Select_Pan.h"
#include "WindowCondition.h"

//NO PAINTING ---------------------------------------------------------------------
static void USE_MOUSE_RECT(HWND hWnd)
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

static void USE_MOUSE_LINE(HWND hWnd)
{
	HDC hdc;
	hdc=GetDC(hWnd);
	SelectObject(hdc,GetStockObject(WHITE_PEN));
	MoveToEx(hdc,WC.StartPoint.x,WC.StartPoint.y,NULL);
	LineTo(hdc,WC.PrePoint.x,WC.PrePoint.y);
	SelectObject(hdc,GetStockObject(BLACK_PEN));
	MoveToEx(hdc,WC.StartPoint.x,WC.StartPoint.y,NULL);
	LineTo(hdc,WC.CurPoint.x,WC.CurPoint.y);
	ReleaseDC(hWnd,hdc);
	InvalidateRect(hWnd,NULL,0);
}

//PAN-------------------------------------------------------------------
Select_Pan::Select_Pan()
{
	pLine=&Line;
	Line.next=NULL;
	Line.StartPoint.next=NULL;
}

bool Select_Pan::LButtonDown()
{
	if(WC.Button_Select==2)
	{
		pLine->next=(LINELIST*)malloc(sizeof(LINELIST));
		pLine=pLine->next;
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
//		pLine->next=(LINELIST*)malloc(sizeof(LINELIST));
//		pLine=pLine->next;
		pLine->next=NULL;
		pPoint->next=NULL;
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
	pPaint=Line.next;	
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
	LINELIST *preLine;
	LINELIST *curLine;
	LINE *prePoint;
	LINE *curPoint;
	curLine=Line.next;
	curPoint=&(curLine->StartPoint);
	while(curLine!=NULL)
	{
		curPoint=curLine->StartPoint.next;
		while(curPoint!=NULL)
		{
			prePoint=curPoint;
			curPoint=curPoint->next;
			free(prePoint);
		}
		preLine=curLine;
		curLine=curLine->next;
		free(preLine);
	}
	curLine=Line.next;
	Line.next=NULL;
	Line.StartPoint.next=NULL;
	pLine=&Line;
	return 1;
}
//
//RECT---------------------------------------------------------------------
Select_Rect::Select_Rect()
{
	pRect=&Rect;
	pRect->next=NULL;
}

bool Select_Rect::LButtonDown()
{
	if(WC.Button_Select==3)
	{
		pRect->next=(RECTLIST*)malloc(sizeof(RECTLIST));
		pRect=pRect->next;
		pRect->xPoint=WC.StartPoint;
		pRect->next=NULL;
	}
	return 1;
}

bool Select_Rect::MouseMove(HWND hWnd)
{
	if(WC.Button_Select==3&&WC.LBUTTONDOWN)
	{
		pRect->yPoint=WC.CurPoint;
		USE_MOUSE_RECT(hWnd);
	}
	return 1;
}

bool Select_Rect::LButtonUp()
{
	if(WC.Button_Select==3)
	{
		pRect->yPoint=WC.CurPoint;
		pRect->next=NULL;
	}
	return 1;
}

bool Select_Rect::Paint(HDC hdc)
{
	RECTLIST *pPaint;
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
	RECTLIST *pPaint;
	RECTLIST *prePaint;
	pPaint=Rect.next;
	while(pPaint!=NULL)
	{
		prePaint=pPaint;
		pPaint=pPaint->next;
		free(prePaint);
	}
	Rect.next=NULL;
	pRect=&Rect;
	return 1;
}

//LINE---------------------------------------------------------------------------------
Select_Line::Select_Line()
{
	pLine=&Line;
	pLine->next=NULL;
}

bool Select_Line::LButtonDown()
{
	if(WC.Button_Select==4)
	{
		pLine->next=(RECTLIST*)malloc(sizeof(RECTLIST));
		pLine=pLine->next;
		pLine->xPoint=WC.StartPoint;
		pLine->next=NULL;
	}
	return 1;
}

bool Select_Line::MouseMove(HWND hWnd)
{
	if(WC.Button_Select==4&&WC.LBUTTONDOWN)
	{
		pLine->yPoint=WC.CurPoint;
		USE_MOUSE_LINE(hWnd);
	}
	return 1;
}

bool Select_Line::LButtonUp()
{
	if(WC.Button_Select==4)
	{
		pLine->yPoint=WC.CurPoint;
		pLine->next=NULL;
	}
	return 1;
}

bool Select_Line::Paint(HDC hdc)
{
	RECTLIST *pPaint;
	pPaint=Line.next;
	SelectObject(hdc,GetStockObject(BLACK_PEN));
	while(pPaint!=NULL)
	{
		MoveToEx(hdc,pPaint->xPoint.x,pPaint->xPoint.y,NULL);
		LineTo(hdc,pPaint->yPoint.x,pPaint->yPoint.y);
		pPaint=pPaint->next;
	}
	return 1;
}

bool Select_Line::CommondErase()
{
	RECTLIST *pPaint;
	RECTLIST *prePaint;
	pPaint=Line.next;
	while(pPaint!=NULL)
	{
		prePaint=pPaint;
		pPaint=pPaint->next;
		free(prePaint);
	}
	Line.next=NULL;
	pLine=&Line;
	return 1;
}
