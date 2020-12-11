#pragma once
#include "figure.h"
#include <Windows.h>
class PainterFrame;
class MyLine:public Figure
{
public:
	MyLine();
	MyLine( int x1, int y1, int x2, int y2, int thick);
	//MyLine(Frame* parent_, int x1, int y1, int x2, int y2);
	void draw() override;
	bool isIncluded(int x, int y) override;
};

