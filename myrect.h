#pragma once
#include "figure.h"
#include <Windows.h>
class PainterFrame;
class MyRect:public Figure
{
public:
	MyRect();
	MyRect(int x1, int y1, int x2, int y2,int thick);
	//MyRect(Frame* parent_,int x1, int y1, int x2, int y2);
	void draw() override;
	bool isIncluded(int x, int y) override;
};

