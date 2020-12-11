#pragma once
#include "Windows.h"
class MyEvent {
private:
	UINT msg_;
	WPARAM wParam_;
	LPARAM lParam_;
public:
	MyEvent(UINT msg, WPARAM wParam, LPARAM lParam);
	bool isLButtonDown();
	bool isLButtonUp();
	int getX();
	int getY();
	bool isShiftPressed();
	bool isCtrlPressed();
	// bool isCtrlDown()
	// bool isRButtonUp()
	// bool isRButtonDown()
};

struct MyPoint{
	MyPoint();
	MyPoint(int x, int y);
	int x, y;
};

