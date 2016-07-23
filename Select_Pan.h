#pragma   once  
//#define LINELIST Select_Pan
//DATA LIST------------------------------------------------------------------------
struct LINE
{
	POINT coordinate;
	LINE *next;
};

struct LINELIST
{
	LINE StartPoint;
	LINELIST *next;
};

struct RECTLIST
{
	POINT xPoint;
	POINT yPoint;
	RECTLIST *next;
};

//CLASS PAN---------------------------------------------------------------------
class Select_Pan
{
private:
	LINELIST Line;
	LINELIST *pLine;
	LINE *pPoint;
public:
	bool MouseMove(HWND);
	bool LButtonUp();
	bool LButtonDown();
	bool Paint(HDC);
	bool CommondErase();
	Select_Pan();
};

//CLASS RECT------------------------------------------------------------------------
class Select_Rect
{
private:
	RECTLIST Rect;
	RECTLIST *pRect;
public:
	bool MouseMove(HWND);
	bool LButtonUp();
	bool LButtonDown();
	bool Paint(HDC);
	bool CommondErase();
	Select_Rect();
};

//CLASS LINE-----------------------------------------------------------------------
class Select_Line
{
private:
	RECTLIST Line;
	RECTLIST *pLine;
public:
	bool MouseMove(HWND);
	bool LButtonUp();
	bool LButtonDown();
	bool Paint(HDC);
	bool CommondErase();
	Select_Line();
};
