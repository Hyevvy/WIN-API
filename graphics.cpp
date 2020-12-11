#include "graphics.h"

Graphics::Graphics() {

}

Graphics::Graphics(HDC& hDC_) : hDC_(hDC_) {

}

void Graphics::setColor(HPEN& color){
	SelectObject(hDC_, color);
}

void Graphics::setFill(HBRUSH& color) {
	SelectObject(hDC_, color);
}
void Graphics::drawRectangle(int x, int y, int width, int height){
	Rectangle(hDC_, x, y, x + width, y + height);
}

void Graphics::drawGroup(int x, int y, int width, int height) {
	Rectangle(hDC_, x, y, x + width, y + height);
}

void Graphics::drawCircle(int x, int y, int width, int height) {
	Ellipse(hDC_, x, y, x + width, y + height);
}
void Graphics::drawLine(int x, int y, int width, int height) {
	MoveToEx(hDC_, x, y,NULL);
	LineTo(hDC_,x+width, y+height);
	
}
HPEN Graphics::PEN_RED = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
HPEN Graphics::PEN_GREEN = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
HPEN Graphics::PEN_BLUE = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
HPEN Graphics::PEN_YELLOW = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
HPEN Graphics::PEN_BLACK = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
HPEN Graphics::PEN_WHITE = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
HPEN Graphics::PEN_GRAY = CreatePen(PS_SOLID, 1, RGB(140, 140, 140));

HBRUSH Graphics::BRUSH_RED = CreateSolidBrush(RGB(255, 0, 0));
HBRUSH Graphics::BRUSH_GREEN = CreateSolidBrush(RGB(0, 255, 0));
HBRUSH Graphics::BRUSH_BLUE = CreateSolidBrush(RGB(0, 0, 255));
HBRUSH Graphics::BRUSH_YELLOW = CreateSolidBrush(RGB(255, 255, 0));
HBRUSH Graphics::BRUSH_BLACK = CreateSolidBrush(RGB(0, 0, 0));
HBRUSH Graphics::BRUSH_WHITE = CreateSolidBrush(RGB(255, 255, 255));
HBRUSH Graphics::BRUSH_INVISIBLE = (HBRUSH)GetStockObject(NULL_BRUSH);