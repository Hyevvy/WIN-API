#pragma once
#include <Windows.h>
class MyPoint;
class PainterFrame;
class Frame;
class Figure
{
public:
	Figure();
	Figure(int x1, int y1, int x2, int y2,int thick);
	//Figure(Frame* parent_, int x1, int y1, int x2, int y2);
	void setParent(PainterFrame*);
	virtual void draw();
	void changePosition(int oldx, int oldy, int newx, int newy);
	virtual bool isIncluded(int x, int y)=0;
	int getX1();
	int getY1();
	int getX2();
	int getY2();
	void setX1(int x1);
	void setY1(int y1);
	void setX2(int x2);
	void setY2(int y2);
	void setRgbPushed(bool);
	void setMyGroup(Figure* myGroup);
	MyPoint getBasePosition();
protected:
	int x1, y1, x2, y2;
	int thick;// 도형의 thick을 가지고 있다.
	Figure* myGroup;
	HDC hDC_;
	PainterFrame* parent_;
	
};

