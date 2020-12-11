#pragma once
#include <Windows.h>
#include <wingdi.h>
class Graphics
{
private:
	HDC hDC_;
public:
	
	Graphics();
	Graphics(HDC& hDC_);
//	void getThick(int thick);
	void setColor(HPEN& color);
	void setFill(HBRUSH& color);
	void drawRectangle(int x, int y, int width, int height);
	void drawCircle(int x, int y, int width, int height);
	void drawLine(int x, int y, int width, int height);
	void drawGroup(int x, int y, int width, int height);
	static HPEN PEN_RED, PEN_GREEN, PEN_BLUE, PEN_YELLOW, PEN_BLACK, PEN_WHITE, PEN_GRAY;
	static HBRUSH BRUSH_RED, BRUSH_GREEN, BRUSH_BLUE, BRUSH_YELLOW, BRUSH_BLACK, BRUSH_WHITE, BRUSH_INVISIBLE;
};

