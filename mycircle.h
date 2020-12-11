#pragma once
#include "figure.h"
class PainterFrame;
class MyCircle:public Figure
{
public:
	MyCircle();
	MyCircle(int x1, int y1, int x2, int y2,int thick);
	//MyCircle(Frame* parent_, int x1, int y1, int x2, int y2);
	void draw() override;
	bool isIncluded(int x, int y) override;
};

