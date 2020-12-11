#pragma once
#include "frame.h"
class Button;
class FigGroup;
class MyRect;
class MyCircle;
class Rbutton;
class PainterFrame: public Frame
{
public:
	PainterFrame();
	PainterFrame(std::wstring title, int width, int height);
	void initialize() override;
	bool eventHandler(MyEvent e) override;
	Figure* findIncludedFigure(int x, int y);
	void repaint() override;
	void addFigure(Figure* added);
	bool isInside(Figure* item, int sx, int sy, int ex, int ey);
	void grouping() override;

private:
	list<Figure*> mylist;
	Figure* selectedFigure;
	Button* btnRect;
	Button* btnCircle;
	Button* btnLine;
	Button* btnGroup;
	Rbutton* radio;
};

