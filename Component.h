#pragma once
#include <Windows.h>
#include <string>
class Frame;
class Component
{
public:
	Component();
	Component(int x, int y, int width, int height);
	virtual bool isIncluded(int x, int y)=0;
	virtual void draw() = 0;
	void setHDC(HDC& hDC);
	void setParent(Frame*);
	void setBounds(int x, int y, int width, int height);
	Frame* getParent();
	std::string getTypestr();
	void IsRgbdown(bool);
	bool getIsRgbdown();
//	void setisRgbDown(bool);
protected:
	Frame* parent_;
	HDC hDC_;
	bool isRgbDown;
	int x_, y_, width_, height_;
	std::string typestr;
};

