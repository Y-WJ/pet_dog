#pragma   once  
#define LINELIST Select_Pan

struct LINE
{
	POINT coordinate;
	LINE *next;
};


class Select_Pan
{
private:
	LINE StartPoint;
	LINELIST *next;
public:
	bool MouseMove(HWND);
	bool LButtonUp();
	bool LButtonDown();
	bool Paint(HDC);
	bool CommondErase();
};

class Select_Rect
{
private:
	POINT xPoint;
	POINT yPoint;
	Select_Rect *next;
public:
	bool MouseMove(HWND);
	bool LButtonUp();
	bool LButtonDown();
	bool Paint(HDC);
	bool CommondErase();
};

static LINELIST Line,*pLine=&Line;
static LINE *pPoint;
static Select_Rect Rect,*pRect=&Rect;


