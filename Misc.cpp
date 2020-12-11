#include "Misc.h"

MyEvent::MyEvent(UINT msg, WPARAM wParam, LPARAM lParam) :
	msg_(msg), wParam_(wParam), lParam_(lParam) 
{
	//  Nothing to do here.
}

bool MyEvent::isLButtonDown() {
	if (msg_ == WM_LBUTTONDOWN) return true;
	else return false;
}

bool MyEvent::isLButtonUp() {
	if (msg_ == WM_LBUTTONUP) return true;
	else return false;
}

int MyEvent::getX() {
	return LOWORD(lParam_);
}
int MyEvent::getY() {
	return HIWORD(lParam_);
}
bool MyEvent::isShiftPressed() {
	if ((wParam_ & MK_SHIFT) != 0)  return true;
	else return false;
}

bool MyEvent::isCtrlPressed() {
	if ((wParam_ & MK_CONTROL) != 0) return true;
	else return false;
}

MyPoint::MyPoint() {
//비어있습니다.
}
MyPoint::MyPoint(int x, int y) :x(x), y(y) {

}
